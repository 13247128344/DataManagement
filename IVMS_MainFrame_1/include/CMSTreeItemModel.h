#ifndef CMSTREEITEMMODEL_H
#define CMSTREEITEMMODEL_H

#include <QAbstractItemModel>
#include "ivms_public.h"
#include "ivms_public_global.h"

enum TreeChangeType {CT_DevOnOffLine,CT_RecordStateChanged,CT_AddArea,CT_ModifyArea,CT_AddDevice,CT_ModifyDevice,CT_AddCms,CT_ModifyCms,CT_AlarmStart,CT_AlarmStop};
enum TreeDeleteType {DT_DelArea,DT_DelDevice,DT_DelCms};

class IVMS_PUBLIC_EXPORT CMSTreeItemModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	CMSTreeItemModel(QObject *parent);
	~CMSTreeItemModel();

	static CMS_CONNECT_PARSE_Node *sta_m_pRootNode;

	QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;

	int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

	Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

	static CMS_CONNECT_PARSE_Node * findDevNodeBySN(char *cSerialNum);
	QModelIndex getModelIndexByDevSN(char *cSerialNum);

	void sendTreeChangedSignal(CMS_CONNECT_PARSE_NoticeType eNoticeType, unsigned char *cMessage);
	

private:
	static CMS_CONNECT_PARSE_Node * iteratorTreeDataForFindDevNode(CMS_CONNECT_PARSE_Node *parent,char *&cSerialNum);
	QModelIndex iteratorTreeForFindDev(QModelIndex &parent,char *&cSerialNum);
	void updateFishEysNode(QModelIndex, CMS_CONNECT_PARSE_Node*);
signals:
	void CMSTreeChanged(TreeChangeType changeType,CMS_CONNECT_PARSE_Node *pNode);	//pNode为新增的数据结点或改变后的数据结点的指针
	void CMSTreeDeleted(TreeDeleteType deleteType,QString strSN);	//对于区域，strSN是区域名

	void CMSTreeChanged_SelfUse(CMS_CONNECT_PARSE_NoticeType eNoticeType, unsigned char *cMessage);

private slots:
	void onCMSTreeChanged_SelfUse(CMS_CONNECT_PARSE_NoticeType eNoticeType, unsigned char *cMessage);
};

#endif // CMSTREEITEMMODEL_H
