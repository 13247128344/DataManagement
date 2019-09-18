
#include <QtCore/QCoreApplication>
#include "pb.grpc.pb.h"
//#include "I8H_SDK.h"

#include "QDebug"
#include <fifo.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "DeviceHttp.h"
#include "HandleHttp.h"
#include "public.h"


using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using namespace pb;


const int MAX_WORKER_COUNT = 8;

//阻塞
Fifo<shared_ptr<pb::StreamMessage>> readMsgfifo_(true,10);
Fifo<shared_ptr<pb::StreamMessage>> writeMsgfifo_(true,10);
Fifo<shared_ptr<pb::MessageCb>> pushMsgfifo_(true, 10);


void __stdcall message_Call_Back(char * strMessageType, char * messageData)
{
	shared_ptr<MessageCb> buffer;
	buffer->set_topic(strMessageType);
	buffer->set_data(messageData);
	pushMsgfifo_.pushFront(buffer);
}

class Client
{
public:
	Client(std::shared_ptr<Channel> channel, const std::string& db);
		
	~Client();


	void publishMessage() {
		ClientContext context;
		shared_ptr<MessageCb> buffer;
		buffer->set_topic("123");
		//buffer->set_data()
		while (pushMsgfifo_.popBack(buffer))
		{
			CommonResponse response;
			stub_->publishMsg(&context, *buffer.get(),&response);
		}
	}



	void readMessage() {
		ClientContext context;
		pb::RegisterMsg request;
//		strcpy(request.mutable_clientname()->c_str(), "IVMS/test");
		
		request.set_clientname("IVMS/DeviceProtocl/I8H");

		std::unique_ptr<ClientReader<pb::StreamMessage>> reader(stub_->registerResponseCb(&context,request));

		
		//std::thread([&]() {
			pb::StreamMessage message;

			while (reader->Read(&message))
			{
				//message.cmd();

				shared_ptr<StreamMessage> buffer = make_shared<StreamMessage>(message);
				

				readMsgfifo_.pushFront(buffer);

				/*std::string srcTopic = buffer->srctopic();
				std::string dstTopic = buffer->dsttopic();
				buffer->set_dsttopic(srcTopic);
				buffer->set_srctopic(dstTopic);
				buffer->set_state(1);

				writeMsgfifo_.pushFront(buffer);*/

				printf("%s-%s\n", message.cmd().c_str(), message.srctopic().c_str());
			}


			reader->Finish();
		//});


		


	}


	void writeMessage() {
		ClientContext context;
		pb::CommonResponse response;
		pb::StreamMessage message;
		std::unique_ptr<ClientWriter<pb::StreamMessage>> writer(stub_->registerRequestUpload(&context,&response));

		//std::thread([&]() {
					
		//	pb::StreamMessage message;

			shared_ptr<StreamMessage> buffer;
			while (writeMsgfifo_.popBack(buffer))
			{
				writer->Write(*buffer.get());
				//message.cmd();
				//shared_ptr<StreamMessage> buffer = make_shared<StreamMessage>(message);

				//writeMsgfifo_.pushFront(buffer);

				printf("%s-%s\n", buffer->cmd().c_str(), buffer->srctopic().c_str());
			}


			writer->Finish();
		//});

	}


private:
	const float kCoordFactor_ = 10000000.0;
	std::unique_ptr<Pb::Stub> stub_;
	//std::vector<Feature> feature_list_;
};

Client::Client(std::shared_ptr<Channel> channel, const std::string& db)
	: stub_(Pb::NewStub(channel))
{
	//channel->GetState(true);
}

Client::~Client()
{

}


//std::string getCommonResponse(int resultCode,QString msg)
//{
//	QJsonObject obj;
//	obj["resultCode"] = resultCode;
//	obj["errorMessage"] = msg;
//
//	QJsonDocument json_doc;
//	json_doc.setObject(obj);
//	return json_doc.toJson(QJsonDocument::Compact).constData();
//
//}




int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//启动I8H服务
	if (!DeviceHttp::startService())
	{
		printf("I8H 初始化失败\n");
		return 0;
	}
	DeviceHttp::setCAllback(message_Call_Back);

	//I8H_SDK_Init(true);
	//std::string db = routeguide::GetDbFileContent(argc, argv);

	Client client(grpc::CreateChannel("10.0.0.16:10000", grpc::InsecureChannelCredentials()),"xxxx");

	std::thread([&]() {
		client.readMessage();
	}).detach();

	std::thread([&]() {
		client.writeMessage();
	}).detach();
	
	std::thread([&]() {
		client.publishMessage();
	}).detach();

	
	//初始化支持的函数列表
	initHandleFunc();


	std::vector<std::thread> workers;
	for (int i = 0; i < MAX_WORKER_COUNT; ++i) {
		workers.push_back(std::thread([]() {
			shared_ptr<StreamMessage> buffer;
			while (readMsgfifo_.popBack(buffer))
			{

				std::string srcTopic = buffer->srctopic();
				std::string dstTopic = buffer->dsttopic();
				buffer->set_dsttopic(srcTopic);
				buffer->set_srctopic(dstTopic);
				buffer->set_state(1);

				std::string cmd = buffer->cmd();
			
			
				if (constructors.value(cmd) != NULL)
				{
					buffer->set_data(constructors.value(cmd)(QString(buffer->data().c_str())));
				}
				else {
					buffer->set_data(getCommonResponse(16, "this cmd is not exist"));
				}
					
				writeMsgfifo_.pushFront(buffer);

			}
		}));
	}


	for (int i = 0; i < MAX_WORKER_COUNT; ++i) {
		workers[i].join();
	}

	//关闭服务
	DeviceHttp::stopService();
	//和中心连接断了，重启算了 简单粗暴
	return 0;
}
