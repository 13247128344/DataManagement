
#include <mutex>
#include <list>
#include <map>
#include <string>
#include <atomic>
#include <chrono> 
#include <string.h>
//#include <windows.h>




using std::map;
using std::list;
//using std::vector;
using std::mutex;
using std::unique_lock;
using std::lock_guard;
using std::condition_variable;
using std::shared_ptr;
using std::make_shared;
using std::string;
using std::atomic;


template<typename T>
class Fifo {
public:
	explicit Fifo(bool block) :block_(block) { }
	explicit Fifo(unsigned maxDataCount) :maxDataCount_(maxDataCount) { }
	explicit Fifo() { }
	Fifo(bool block, unsigned maxDataCount) :block_(block), maxDataCount_(maxDataCount) { }
	~Fifo() {
		unique_lock<mutex> lock(cvlock_);
		quitSignal_ = true;
		lock.unlock();
		cvEmpty_.notify_all();
		cvFull_.notify_all();
	}
	bool pushFront(const T &data) {
		return add(data);
	}
	bool pushFront(T &&data) {
		return add(std::forward<T>(data));
	}
	bool popBack(T &data) {
		unique_lock<mutex> lock(cvlock_);
		cvEmpty_.wait(lock, [&] {
			return !dataList_.empty() || quitSignal_;
		});
		/*cvEmpty_.wait_for(lock, std::chrono::seconds(1), [&] {
			return !dataList_.empty() || quitSignal_;
		});*/


		if (dataList_.empty() || quitSignal_)
		{
			lock.unlock();

			return false;
		}
		data = dataList_.back();
		dataList_.pop_back();
		lock.unlock();
		cvFull_.notify_one();
		return true;
	}
private:
	template<typename Ty>
	bool add(Ty &&data) {
		unique_lock<mutex> lock(cvlock_);
		if (dataList_.size() >= maxDataCount_) {
			if (!block_)
				return false;/*非阻塞情况下,丢弃这一帧,预览时需要用到*/
			cvFull_.wait(lock, [&] {
				return dataList_.size() < maxDataCount_ || quitSignal_;
			});
			if (quitSignal_)
				return false;
		}
		dataList_.push_front(data);
		lock.unlock();
		cvEmpty_.notify_one();
		return true;
	}
private:
	list<T> dataList_;
	bool block_ = false;
	bool quitSignal_ = false;
	unsigned maxDataCount_ = 3;/*默认最大缓存3*/
	mutex cvlock_;
	condition_variable cvEmpty_;
	condition_variable cvFull_;
};