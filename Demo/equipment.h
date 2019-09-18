#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QWidget>
#include <QtGui>

namespace Ui {
class treeview;
}

class treeview : public QWidget
{
    Q_OBJECT

public:
    explicit treeview(QWidget *parent = 0);
    ~treeview();
// 	void setUi();
// 	void iterateOverItems();
// 	QList<QStandardItem*> returnTheItems();
// 	void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::treeview *ui;
	QStandardItemModel *model;
	treeview *w;
};

#endif // TREEVIEW_H
