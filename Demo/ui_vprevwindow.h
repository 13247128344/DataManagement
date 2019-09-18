/********************************************************************************
** Form generated from reading UI file 'vprevwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VPREVWINDOW_H
#define UI_VPREVWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vPrevWindow
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widgetPrevUp;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widgetPrevLeft;
    QVBoxLayout *verticalLayout;
    QWidget *widgetTitle;
    QLabel *label;
    QPushButton *btnWinClose;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_video_3;
    QWidget *widgetVideoArea;
    QWidget *widget_video_4;
    QWidget *widget_2;
    QWidget *widgetPrevRight;
    QWidget *widgetPrevDown;

    void setupUi(QWidget *vPrevWindow)
    {
        if (vPrevWindow->objectName().isEmpty())
            vPrevWindow->setObjectName(QStringLiteral("vPrevWindow"));
        vPrevWindow->resize(423, 396);
        layoutWidget = new QWidget(vPrevWindow);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(-1, 3, 421, 391));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widgetPrevUp = new QWidget(layoutWidget);
        widgetPrevUp->setObjectName(QStringLiteral("widgetPrevUp"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetPrevUp->sizePolicy().hasHeightForWidth());
        widgetPrevUp->setSizePolicy(sizePolicy);
        widgetPrevUp->setMinimumSize(QSize(0, 1));
        widgetPrevUp->setMaximumSize(QSize(16777215, 1));

        verticalLayout_2->addWidget(widgetPrevUp);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetNoConstraint);
        widgetPrevLeft = new QWidget(layoutWidget);
        widgetPrevLeft->setObjectName(QStringLiteral("widgetPrevLeft"));
        sizePolicy.setHeightForWidth(widgetPrevLeft->sizePolicy().hasHeightForWidth());
        widgetPrevLeft->setSizePolicy(sizePolicy);
        widgetPrevLeft->setMinimumSize(QSize(1, 0));
        widgetPrevLeft->setMaximumSize(QSize(1, 16777215));

        horizontalLayout_3->addWidget(widgetPrevLeft);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetTitle = new QWidget(layoutWidget);
        widgetTitle->setObjectName(QStringLiteral("widgetTitle"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetTitle->sizePolicy().hasHeightForWidth());
        widgetTitle->setSizePolicy(sizePolicy1);
        widgetTitle->setMinimumSize(QSize(0, 16));
        widgetTitle->setMaximumSize(QSize(16777215, 16));
        widgetTitle->setAutoFillBackground(false);
        label = new QLabel(widgetTitle);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 0, 54, 16));
        QPalette palette;
        QBrush brush(QColor(181, 181, 181, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(41, 42, 46, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label->setPalette(palette);
        QFont font;
        font.setPointSize(9);
        label->setFont(font);
        label->setScaledContents(true);
        btnWinClose = new QPushButton(widgetTitle);
        btnWinClose->setObjectName(QStringLiteral("btnWinClose"));
        btnWinClose->setGeometry(QRect(411, 3, 10, 9));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnWinClose->sizePolicy().hasHeightForWidth());
        btnWinClose->setSizePolicy(sizePolicy2);
        btnWinClose->setMinimumSize(QSize(10, 9));
        btnWinClose->setMaximumSize(QSize(10, 9));
        btnWinClose->setLayoutDirection(Qt::RightToLeft);
        btnWinClose->setIconSize(QSize(10, 9));

        verticalLayout->addWidget(widgetTitle);

        widget_5 = new QWidget(layoutWidget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(widget_5);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 16777215));
        widget->setAutoFillBackground(false);

        verticalLayout_3->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget_video_3 = new QWidget(widget_5);
        widget_video_3->setObjectName(QStringLiteral("widget_video_3"));
        widget_video_3->setAutoFillBackground(false);

        horizontalLayout->addWidget(widget_video_3);

        widgetVideoArea = new QWidget(widget_5);
        widgetVideoArea->setObjectName(QStringLiteral("widgetVideoArea"));
        sizePolicy1.setHeightForWidth(widgetVideoArea->sizePolicy().hasHeightForWidth());
        widgetVideoArea->setSizePolicy(sizePolicy1);
        widgetVideoArea->setAutoFillBackground(false);

        horizontalLayout->addWidget(widgetVideoArea);

        widget_video_4 = new QWidget(widget_5);
        widget_video_4->setObjectName(QStringLiteral("widget_video_4"));
        widget_video_4->setAutoFillBackground(false);

        horizontalLayout->addWidget(widget_video_4);


        verticalLayout_3->addLayout(horizontalLayout);

        widget_2 = new QWidget(widget_5);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setAutoFillBackground(false);

        verticalLayout_3->addWidget(widget_2);

        widget_2->raise();
        widget->raise();

        verticalLayout->addWidget(widget_5);


        horizontalLayout_3->addLayout(verticalLayout);

        widgetPrevRight = new QWidget(layoutWidget);
        widgetPrevRight->setObjectName(QStringLiteral("widgetPrevRight"));
        sizePolicy.setHeightForWidth(widgetPrevRight->sizePolicy().hasHeightForWidth());
        widgetPrevRight->setSizePolicy(sizePolicy);
        widgetPrevRight->setMinimumSize(QSize(1, 0));
        widgetPrevRight->setMaximumSize(QSize(1, 16777215));

        horizontalLayout_3->addWidget(widgetPrevRight);


        verticalLayout_2->addLayout(horizontalLayout_3);

        widgetPrevDown = new QWidget(layoutWidget);
        widgetPrevDown->setObjectName(QStringLiteral("widgetPrevDown"));
        sizePolicy.setHeightForWidth(widgetPrevDown->sizePolicy().hasHeightForWidth());
        widgetPrevDown->setSizePolicy(sizePolicy);
        widgetPrevDown->setMinimumSize(QSize(0, 1));
        widgetPrevDown->setMaximumSize(QSize(16777215, 1));

        verticalLayout_2->addWidget(widgetPrevDown);


        retranslateUi(vPrevWindow);

        QMetaObject::connectSlotsByName(vPrevWindow);
    } // setupUi

    void retranslateUi(QWidget *vPrevWindow)
    {
        vPrevWindow->setWindowTitle(QApplication::translate("vPrevWindow", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("vPrevWindow", "TextLabel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btnWinClose->setToolTip(QApplication::translate("vPrevWindow", "Close", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnWinClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class vPrevWindow: public Ui_vPrevWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VPREVWINDOW_H
