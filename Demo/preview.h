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
	//双击正在预览的窗口放大或缩小，bShowMax是否放大，否则缩小，iFirstWin是需要放到或者缩小的窗口
	void slot_double_clicked(bool bShowMax, int iFirstWin);
	//点击单个窗口的关闭按钮，关闭实时流
	void slot_pre_close(int);
	//焦点窗口打开此通道号的流
	void slot_open_realstream(int);
	//关闭此通道号的流
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