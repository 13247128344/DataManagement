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
	void startLoading();//加载
	void setText(QString text);
public slots:
	void setHidden();//关闭
private:

	QMovie *movie;
	int m_iFrameCount;
signals:
	void closeSignal();
	private slots:
	void FrmClose();//关闭
protected:
	//窗口改变事件,鼠标事件
	void resizeEvent(QResizeEvent *e);
	void closeEvent(QCloseEvent *e);
private:
    Ui::Loading *ui;
};

#endif // LOADING_H
