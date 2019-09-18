#ifndef CMSITEMDELEGATE_H
#define CMSITEMDELEGATE_H

#include <QStyledItemDelegate>
#include "CMSTreeView.h"
#include "ivms_public_global.h"

class  IVMS_PUBLIC_EXPORT CMSItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	CMSItemDelegate(CMSTreeView *parent);
	~CMSItemDelegate();

	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const;

protected:
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
	bool editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index);

private:
	CMSTreeView *m_pCMSTreeView;
	QRect getCheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)const;
};

#endif // CMSITEMDELEGATE_H
