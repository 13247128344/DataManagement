/********************************************************************************
** Form generated from reading UI file 'alarm.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALARM_H
#define UI_ALARM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Alarm
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QDateTimeEdit *dateTimeEditFrom;
    QLabel *label;
    QDateTimeEdit *dateTimeEditTo;
    QLabel *labelType;
    QComboBox *comboBoxType;
    QPushButton *btnSearch;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QWidget *widget_log;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_alarmlog;
    QPushButton *btn_accesslog;
    QSpacerItem *horizontalSpacer_3;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblPage;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnFirst;
    QPushButton *btnPrev;
    QPushButton *btnNext;
    QPushButton *btnLast;

    void setupUi(QWidget *Alarm)
    {
        if (Alarm->objectName().isEmpty())
            Alarm->setObjectName(QStringLiteral("Alarm"));
        Alarm->resize(1404, 762);
        layoutWidget = new QWidget(Alarm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 20, 1391, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 6, 9, 4);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        horizontalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QPalette palette;
        QBrush brush(QColor(180, 180, 180, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush3(QColor(255, 255, 220, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush3);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush1);
        label_2->setPalette(palette);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_2);

        dateTimeEditFrom = new QDateTimeEdit(layoutWidget);
        dateTimeEditFrom->setObjectName(QStringLiteral("dateTimeEditFrom"));
        dateTimeEditFrom->setFrame(false);
        dateTimeEditFrom->setReadOnly(false);

        horizontalLayout->addWidget(dateTimeEditFrom);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(30, 0));
        label->setMaximumSize(QSize(30, 16777215));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush4(QColor(120, 120, 120, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        label->setPalette(palette1);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        dateTimeEditTo = new QDateTimeEdit(layoutWidget);
        dateTimeEditTo->setObjectName(QStringLiteral("dateTimeEditTo"));
        dateTimeEditTo->setFrame(false);
        dateTimeEditTo->setReadOnly(false);

        horizontalLayout->addWidget(dateTimeEditTo);

        labelType = new QLabel(layoutWidget);
        labelType->setObjectName(QStringLiteral("labelType"));
        labelType->setMinimumSize(QSize(0, 0));
        labelType->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        labelType->setPalette(palette2);
        labelType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(labelType);

        comboBoxType = new QComboBox(layoutWidget);
        comboBoxType->setObjectName(QStringLiteral("comboBoxType"));
        comboBoxType->setDuplicatesEnabled(false);
        comboBoxType->setFrame(false);

        horizontalLayout->addWidget(comboBoxType);

        btnSearch = new QPushButton(layoutWidget);
        btnSearch->setObjectName(QStringLiteral("btnSearch"));
        btnSearch->setMinimumSize(QSize(75, 23));
        btnSearch->setMaximumSize(QSize(75, 23));
        QPalette palette3;
        QBrush brush5(QColor(210, 210, 210, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette3.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Shadow, brush1);
        palette3.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipBase, brush3);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette3.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Shadow, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Shadow, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush1);
        btnSearch->setPalette(palette3);
        btnSearch->setCursor(QCursor(Qt::PointingHandCursor));
        btnSearch->setFlat(true);

        horizontalLayout->addWidget(btnSearch);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(504, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        layoutWidget_2 = new QWidget(Alarm);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 60, 1391, 661));
        verticalLayout = new QVBoxLayout(layoutWidget_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(9, 0, 9, 0);
        tableWidget = new QTableWidget(layoutWidget_2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(72, 75, 82, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Shadow, brush1);
        QBrush brush7(QColor(51, 153, 255, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Highlight, brush7);
        palette4.setBrush(QPalette::Active, QPalette::HighlightedText, brush);
        QBrush brush8(QColor(54, 56, 62, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::AlternateBase, brush8);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipBase, brush3);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Shadow, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Highlight, brush7);
        palette4.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush8);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Shadow, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Highlight, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush8);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush1);
        tableWidget->setPalette(palette4);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSortingEnabled(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(30);

        verticalLayout->addWidget(tableWidget);

        widget_log = new QWidget(Alarm);
        widget_log->setObjectName(QStringLiteral("widget_log"));
        widget_log->setGeometry(QRect(0, 0, 1391, 16));
        horizontalLayout_2 = new QHBoxLayout(widget_log);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 1, -1, 0);
        btn_alarmlog = new QPushButton(widget_log);
        btn_alarmlog->setObjectName(QStringLiteral("btn_alarmlog"));
        btn_alarmlog->setMinimumSize(QSize(98, 33));
        btn_alarmlog->setMaximumSize(QSize(98, 33));
        btn_alarmlog->setSizeIncrement(QSize(0, 0));
        btn_alarmlog->setBaseSize(QSize(0, 0));

        horizontalLayout_2->addWidget(btn_alarmlog);

        btn_accesslog = new QPushButton(widget_log);
        btn_accesslog->setObjectName(QStringLiteral("btn_accesslog"));
        btn_accesslog->setMinimumSize(QSize(98, 33));
        btn_accesslog->setMaximumSize(QSize(98, 33));
        btn_accesslog->setSizeIncrement(QSize(0, 0));

        horizontalLayout_2->addWidget(btn_accesslog);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        layoutWidget_3 = new QWidget(Alarm);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(0, 720, 1391, 41));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(9, 4, 9, 4);
        lblPage = new QLabel(layoutWidget_3);
        lblPage->setObjectName(QStringLiteral("lblPage"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        lblPage->setPalette(palette5);

        horizontalLayout_5->addWidget(lblPage);

        horizontalSpacer = new QSpacerItem(722, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        btnFirst = new QPushButton(layoutWidget_3);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        btnFirst->setMinimumSize(QSize(75, 23));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        QBrush brush9(QColor(240, 240, 240, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette6.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette6.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette6.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette6.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        btnFirst->setPalette(palette6);
        btnFirst->setCursor(QCursor(Qt::PointingHandCursor));
        btnFirst->setFlat(true);

        horizontalLayout_5->addWidget(btnFirst);

        btnPrev = new QPushButton(layoutWidget_3);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));
        btnPrev->setMinimumSize(QSize(75, 23));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette7.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette7.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette7.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette7.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        btnPrev->setPalette(palette7);
        btnPrev->setCursor(QCursor(Qt::PointingHandCursor));
        btnPrev->setFlat(true);

        horizontalLayout_5->addWidget(btnPrev);

        btnNext = new QPushButton(layoutWidget_3);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        btnNext->setMinimumSize(QSize(75, 23));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette8.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette8.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        btnNext->setPalette(palette8);
        btnNext->setCursor(QCursor(Qt::PointingHandCursor));
        btnNext->setFlat(true);

        horizontalLayout_5->addWidget(btnNext);

        btnLast = new QPushButton(layoutWidget_3);
        btnLast->setObjectName(QStringLiteral("btnLast"));
        btnLast->setMinimumSize(QSize(75, 23));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette9.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette9.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette9.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette9.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette9.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette9.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette9.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        btnLast->setPalette(palette9);
        btnLast->setCursor(QCursor(Qt::PointingHandCursor));
        btnLast->setFlat(true);

        horizontalLayout_5->addWidget(btnLast);


        retranslateUi(Alarm);

        QMetaObject::connectSlotsByName(Alarm);
    } // setupUi

    void retranslateUi(QWidget *Alarm)
    {
        Alarm->setWindowTitle(QApplication::translate("Alarm", "Form", Q_NULLPTR));
        label_2->setText(QApplication::translate("Alarm", "BeginTime", Q_NULLPTR));
        dateTimeEditFrom->setDisplayFormat(QApplication::translate("Alarm", "yyyy/MM/dd HH:mm:ss", Q_NULLPTR));
        label->setText(QApplication::translate("Alarm", "to", Q_NULLPTR));
        dateTimeEditTo->setDisplayFormat(QApplication::translate("Alarm", "yyyy/MM/dd HH:mm:ss", Q_NULLPTR));
        labelType->setText(QApplication::translate("Alarm", "Type", Q_NULLPTR));
        btnSearch->setText(QApplication::translate("Alarm", "Search", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Alarm", "\345\221\212\350\255\246\347\256\241\347\220\206", Q_NULLPTR));
        btn_alarmlog->setText(QApplication::translate("Alarm", "Alarm Log", Q_NULLPTR));
        btn_accesslog->setText(QApplication::translate("Alarm", "Access Log", Q_NULLPTR));
        lblPage->setText(QApplication::translate("Alarm", "TextLabel", Q_NULLPTR));
        btnFirst->setText(QApplication::translate("Alarm", "First", Q_NULLPTR));
        btnPrev->setText(QApplication::translate("Alarm", "Prev", Q_NULLPTR));
        btnNext->setText(QApplication::translate("Alarm", "Next", Q_NULLPTR));
        btnLast->setText(QApplication::translate("Alarm", "Last", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Alarm: public Ui_Alarm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALARM_H
