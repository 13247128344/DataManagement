#ifndef ADDIVMSARAE_H
#define ADDIVMSARAE_H

#include <QWidget>
#include "./include/CMSTreeView.h"
#include "QListWidget"

class CMSTreeView;
class AddLinkageRule;
class AddAccessLinkageRule;

namespace Ui {
class AddIVMSArae;
}

class AddIVMSArae : public QWidget
{
    Q_OBJECT

public:
     AddIVMSArae(QWidget *parent = 0);
    ~AddIVMSArae();
	CMSTreeView *m_pCMSTreeView;
	QListWidget *m_pListWidget;
	AddLinkageRule *m_pAddLinkageRule;
	AddAccessLinkageRule *m_pAddAccessLinkageRule;
	int m_iType;
	Ui::AddIVMSArae *ui;

protected slots:
	void on_btn_confirm_clicked();
	void on_btn_cancel_clicked();
protected:
	void resizeEvent(QResizeEvent *);
private:
};

#endif // ADDIVMSARAE_H
