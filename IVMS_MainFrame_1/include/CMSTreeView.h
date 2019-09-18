#ifndef CMSTREEVIEW_H
#define CMSTREEVIEW_H

#include <QTreeView>
#include "GeneratedFiles/ui_CMSTreeView.h"
#include "CMSTreeItemModel.h"
#include "ivms_public_global.h"

class IVMS_PUBLIC_EXPORT CMSTreeView : public QTreeView
{
	Q_OBJECT

		signals :
	void checkStateChanged(QModelIndex index, bool isChecked);

public:
	enum PermissionType { PREVIEW, PLAYBACK };
	enum CheckType { NO, RADIO, MULTI };	//�豸����0���Ƿ��и�ѡ�����ö������
	enum ColumnType { ORIGIN, REC_STATUS, USER_Permission };
	enum ChOrAlarmIn { CH, AlarmIn, NoAlarmOut, All };
	enum FishType { ShowEye, HideEye };
	enum AiType { ShowAllType, ShowAiType };
	//ͨ��Ȩ��
	struct Auth
	{
		bool isPlayback;
		bool isRecord;
		bool isIntercom;
		int iPtzLevel;
		Auth() { isPlayback = false; isRecord = false; isIntercom = false; iPtzLevel = 0; }
	};
	//�豸Ȩ�޼���
	struct AuthCount
	{
		int iPreview;
		int iPlayback;
		int iRecord;
		int iIntercom;
		AuthCount() { iPreview = 1; iPlayback = 0; iRecord = 0; iIntercom = 0; }
	};

	CMSTreeView(QWidget *parent = 0, PermissionType permissionType = PREVIEW, CheckType checkType = NO, ColumnType columnType = ORIGIN, ChOrAlarmIn chOrAlarmIn = CH, FishType fishType = HideEye, AiType aiType = ShowAllType);
	~CMSTreeView();

	void update(const QModelIndex &index);
	void update();

	static CMSTreeItemModel *sta_m_pCMSTreeItemModel;
	QList<QModelIndex> m_listCheckedIndex;	//��ѡ��ͨ���ļ���
	QList<QModelIndex> m_listPreviewedIndex;	//���ŵ�ͨ���ļ���
	QList<QModelIndex> m_listCtrlSelectIndex;	//Ctrl��ѡ��ͨ������
	QModelIndex m_intercomIndex;			//�Խ�ͨ��
	QList<QModelIndex> m_listDisabled;		//�����õĽڵ㼯��
	QMap<CMS_CONNECT_PARSE_ChannelNode*, Auth> m_mapChannelAuth;	//ͨ��Ȩ�޵ļ���
	QMap<CMS_CONNECT_PARSE_DeviceNode*, AuthCount> m_mapDeviceAuthCount;	//�ֽڵ�Ȩ�޸����ļ���

	PermissionType m_permissionType;
	CheckType m_checkType;
	ColumnType m_columnType;
	ChOrAlarmIn m_chOrAlarmIn;
	FishType m_fishType;
	AiType m_aiType;
	int m_iColumnMaxWidth;

	static void initTreeModel(long lHandle);
	static CMS_CONNECT_PARSE_Node * getNodebyModelIndex(QModelIndex &index);
	static QModelIndex getModelIndexByDevSNandChNo(QString strDevSN, int iChNo);
	static QModelIndex getModelIndexByDevSNandAlarmInNo(QString strDevSN, int iAlarmInNo);
	static QModelIndex getModelIndexByDevSNandAlarmOutNo(QString strDevSN, int iAlarmOutNo);
	static QModelIndex getModelIndexAreaByAreaName(QString strAreaName);
	static void setAllDeviceOffLine(QModelIndex index = sta_m_pCMSTreeItemModel->index(0, 0));
	static void getAllDeviceList(CMS_CONNECT_PARSE_Node* pNode, QList<QString>&);
	static void reloadTreeView(CMS_CONNECT_PARSE_Node* pNode, QList<QString>&);
	static bool isAreaNameExits(QString strAreaName);

	static QList<CMSTreeView *> m_listCmsTreeView;


	void setTreeViewItemPlayedIcon(QModelIndex &index, bool isOpenPreview);
	void setTreeViewItemIntercomIcon(QModelIndex &index, bool isOpenIntercom);

	void setChannelAuth(QMap<CMS_CONNECT_PARSE_ChannelNode*, Auth> &mapChAuth);

	void sendCheckStateChanged(QModelIndex index, bool isChecked);

	void setItemDisabled(QModelIndex index, bool isDisabled);
private:
	Ui::CMSTreeView ui;

	void iteratorTreeViewForPara(QModelIndex &parent);
	void setViewPara();
	static QModelIndex iteratorTreeViewForFindCh(QModelIndex &parent, QString &strDevSN, int &iChNo);
	static QModelIndex iteratorTreeViewForFindAlarmIn(QModelIndex &parent, QString &strDevSN, int &iAlarmInNo);
	static QModelIndex iteratorTreeViewForFindAlarmOut(QModelIndex &parent, QString &strDevSN, int &iAlarmOutNo);
	static QModelIndex iteratorTreeForFindAreaIndex(QModelIndex &parent, QString &strAreaName);
	static bool iteratorTreeViewForCompareAraeName(QModelIndex &parent, QString &strDevSN);

	QString resetFishChannelName(int currentType, int chnanelNo);  //add by hq

	static void updateFishEyeChannel(CMS_CONNECT_PARSE_Node* pNode);
};

#endif // CMSTREEVIEW_H
