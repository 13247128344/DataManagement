#include "AccessInfo.h"
#include "common.h"

QList<CMS_CONNECT_PASER_AccessControlInfo*> AccessInfo::m_listInfo;

AccessInfo* AccessInfo::sta_instance = NULL;

AccessInfo::AccessInfo(QObject *parent)
	: QObject(parent)
{
	qRegisterMetaType<CMS_CONNECT_PASER_AccessControlInfo*>("CMS_CONNECT_PASER_AccessControlInfo*");

	connect(_pMainDlg, SIGNAL(SendAccessState(CMS_CONNECT_PARSE_NoticeType, unsigned char*)), this, SLOT(onAccessChange(CMS_CONNECT_PARSE_NoticeType, unsigned char*)));
}

AccessInfo::~AccessInfo()
{
}

CMS_CONNECT_PASER_AccessControlInfo* AccessInfo::GetControlInfoBySerialNum(QString strSerialNum)
{
	for each (auto var in m_listInfo)
	{
		if (var != NULL)
		{
			if (strcmp(var->cSerialNum, strSerialNum.toUtf8().data()) == 0)
			{
				return var;
			}
		}
	}
	return NULL;
}

void AccessInfo::InitControlInfo()
{
	//创建Instance
	AccessInfo::GetInstance();

	m_listInfo.clear();
	//获取门禁节点信息
	CMS_CONNECT_PASER_AccessControl* pReply = new CMS_CONNECT_PASER_AccessControl;

	memset(pReply, 0, sizeof(CMS_CONNECT_PASER_AccessControl));

	int ret = CMS_Conncet_Client_GetControlList(_lLoginHandle, pReply);

	//将获取到的数据转换成QList
	for (int i = 0; i < pReply->iControlCount; i++)
	{
		CMS_CONNECT_PASER_AccessControlInfo *pInfo = new CMS_CONNECT_PASER_AccessControlInfo;

		memcpy(pInfo, &pReply->controlInfo[i], sizeof(CMS_CONNECT_PASER_AccessControlInfo));

		m_listInfo.append(pInfo);
	}
}

AccessInfo* AccessInfo::GetInstance()
{
	if (sta_instance == NULL)
	{
		sta_instance = new AccessInfo();
	}

	return sta_instance;
}

void AccessInfo::onAccessChange(CMS_CONNECT_PARSE_NoticeType eNotice, unsigned char*lpMessage)
{
	if (lpMessage == NULL)
	{
		return;
	}

	CMS_CONNECT_PASER_AccessControlInfo* pInfo = (CMS_CONNECT_PASER_AccessControlInfo*)lpMessage;

	if (pInfo == NULL)
	{
		return;
	}

	if (eNotice == NoticeType_AddAccess)
	{

		m_listInfo.append(pInfo);

		sigAccessStateChange(eNotice, QString(pInfo->cSerialNum));
	}
	else if (eNotice == NoticeType_DelAccess)
	{
		CMS_CONNECT_PASER_AccessControlInfo* deletInfo = NULL;
		for each (CMS_CONNECT_PASER_AccessControlInfo* var in m_listInfo)
		{
			if (strcmp(var->cSerialNum, pInfo->cSerialNum) == 0)
			{
				deletInfo = var;

				break;
			}
		}

		if (deletInfo != NULL)
		{
			m_listInfo.removeOne(deletInfo);

			delete deletInfo;
		}

		sigAccessStateChange(eNotice, QString(pInfo->cSerialNum));

		delete pInfo;
	}
	else if (eNotice == NoticeType_ModifyAccess)
	{
		for each (CMS_CONNECT_PASER_AccessControlInfo* var in m_listInfo)
		{
			if (strcmp(var->cSerialNum, pInfo->cSerialNum) == 0)
			{
				memcpy(var, pInfo, sizeof(CMS_CONNECT_PASER_AccessControlInfo));

				if (var != NULL)
				{
					if (var->isOnline == true)
					{
						insertEvent(tr("Access State %1 %2").arg(var->cAccessName).arg(tr("online")));
					}
					else
					{
						insertEvent(tr("Access State %1 %2").arg(var->cAccessName).arg(tr("offline")));
					}
				}

				break;
			}
		}

		sigAccessStateChange(eNotice, QString(pInfo->cSerialNum));

		delete pInfo;
	}
}

QList<CMS_CONNECT_PASER_AccessControlInfo*> AccessInfo::GetListInstance()
{
	return m_listInfo;
}