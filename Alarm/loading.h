#ifndef LOADING_H
#define LOADING_H

#include <QDialog>

namespace Ui {
class Loading;
}

class Loading : public QDialog
{
    Q_OBJECT

public:
    explicit Loading(QWidget *parent = 0);
    ~Loading();
	void startLoading();//����
	void setText(QString text);
public slots:
	void setHidden();//�ر�
private:

	QMovie *movie;
	int m_iFrameCount;
signals:
	void closeSignal();
	private slots:
	void FrmClose();//�ر�
protected:
	//���ڸı��¼�,����¼�
	void resizeEvent(QResizeEvent *e);
	void closeEvent(QCloseEvent *e);
private:
    Ui::Loading *ui;
};

#endif // LOADING_H
