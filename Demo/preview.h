#ifndef PREVIEW_H
#define PREVIEW_H

/*****************************/
/*  author: xiafei           */
/*  time:   2019-06-28       */
/*****************************/

#include <QWidget>
#include "ui_preview.h"

class VPrevMulitWindow;

class Preview : public QWidget
{
	Q_OBJECT

public:
	Preview(QWidget *parent = Q_NULLPTR);
	~Preview();
	void closeAllStream();

	public slots:
	void slot_hide();
	void slot_split1();
	void slot_split4();
	void slot_split9();
	void slot_split16();
	//˫������Ԥ���Ĵ��ڷŴ����С��bShowMax�Ƿ�Ŵ󣬷�����С��iFirstWin����Ҫ�ŵ�������С�Ĵ���
	void slot_double_clicked(bool bShowMax, int iFirstWin);
	//����������ڵĹرհ�ť���ر�ʵʱ��
	void slot_pre_close(int);
	//���㴰�ڴ򿪴�ͨ���ŵ���
	void slot_open_realstream(int);
	//�رմ�ͨ���ŵ���
	void slot_close_by_channel(int iChannel);

private:
	void layoutWinsByChans(int iChans);
	void resizeEvent(QResizeEvent *e);

public:
	static QMap<int, int> sta_listStream;

private:
	Ui::Preview ui;
	VPrevMulitWindow *m_pMulitWindow;
};

#endif // PREVIEW_H