#ifndef ALARM_H
#define ALARM_H

#include <QWidget>

namespace Ui {
class Alarm;
}

class Alarm : public QWidget
{
    Q_OBJECT

public:
    ~Alarm();
    static Alarm* getAlarmInfo(QWidget *parent);
    Alarm(QWidget *parent = 0);
	void initStyle();
private:
    static Alarm* stra_AlarmInfo;
	bool m_move;
	int m_iRowCount;
	QPoint m_startPoint;
	QPoint m_windowPoint;

    int m_iRowSum;//每页显示条数
    int m_iPageCount;//总页数
    int m_iPage;//当前页
    int m_iAlarmLogSum;//
    bool m_bCondition;//查询条件
    bool m_bAlarmLog;//是否为告警日志模式

	void getAlarmInfo();//查询数据
	void getAccessInfo();//查询门禁告警数据
	void enabledBtn();//禁用按钮

protected slots:
	void getAlarmInfoByCondition();//条件查询
	void getFirst();//首页
	void getLast();//尾页
	void getNext();//下一页
	void getPrev();//上一页
	void onBtnAlarmLog();//告警日志
	void onBtnAccessLog();//门禁日志

protected:
	void resizeEvent(QResizeEvent *e);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Alarm *ui;
};

#endif // ALARM_H
