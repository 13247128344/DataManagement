/********************************************************************************
** Form generated from reading UI file 'log.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOG_H
#define UI_LOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Log
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *labelType;
    QComboBox *comboBoxType;
    QLabel *labelStartTime;
    QDateTimeEdit *dateTimeEditFrom;
    QLabel *labelEndTime;
    QDateTimeEdit *dateTimeEditTo;
    QPushButton *btnRetrieve;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnExport;
    QVBoxLayout *verticalLayout_2;
    QWidget *widgetOut2;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widgetOut1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widgetIn1;
    QTableWidget *tableWidgetLog;
    QWidget *widgetIn3;
    QWidget *widgetIn4;
    QWidget *widgetOut3;
    QWidget *widgetOut4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelLogCount;
    QLabel *labelRecs;
    QLabel *labelPageCount;
    QLabel *labelPage;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnFirst;
    QWidget *widget;
    QPushButton *btnPrevious;
    QWidget *widget_2;
    QPushButton *btnNext;
    QWidget *widget_3;
    QPushButton *btnLast;

    void setupUi(QWidget *Log)
    {
        if (Log->objectName().isEmpty())
            Log->setObjectName(QStringLiteral("Log"));
        Log->resize(1386, 748);
        gridLayout = new QGridLayout(Log);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(12);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(12);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelType = new QLabel(Log);
        labelType->setObjectName(QStringLiteral("labelType"));
        labelType->setMinimumSize(QSize(55, 0));
        labelType->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette;
        QBrush brush(QColor(180, 180, 180, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 0));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush2(QColor(127, 127, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        labelType->setPalette(palette);
        labelType->setAutoFillBackground(false);
        labelType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(labelType);

        comboBoxType = new QComboBox(Log);
        comboBoxType->setObjectName(QStringLiteral("comboBoxType"));
        comboBoxType->setMinimumSize(QSize(100, 23));
        comboBoxType->setAutoFillBackground(false);
        comboBoxType->setFrame(false);

        horizontalLayout->addWidget(comboBoxType);

        labelStartTime = new QLabel(Log);
        labelStartTime->setObjectName(QStringLiteral("labelStartTime"));
        labelStartTime->setMinimumSize(QSize(35, 0));
        labelStartTime->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        labelStartTime->setPalette(palette1);
        labelStartTime->setAutoFillBackground(false);

        horizontalLayout->addWidget(labelStartTime);

        dateTimeEditFrom = new QDateTimeEdit(Log);
        dateTimeEditFrom->setObjectName(QStringLiteral("dateTimeEditFrom"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dateTimeEditFrom->sizePolicy().hasHeightForWidth());
        dateTimeEditFrom->setSizePolicy(sizePolicy);
        dateTimeEditFrom->setMinimumSize(QSize(160, 23));
        dateTimeEditFrom->setFrame(false);

        horizontalLayout->addWidget(dateTimeEditFrom);

        labelEndTime = new QLabel(Log);
        labelEndTime->setObjectName(QStringLiteral("labelEndTime"));
        labelEndTime->setMinimumSize(QSize(20, 0));
        labelEndTime->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        labelEndTime->setPalette(palette2);
        labelEndTime->setAutoFillBackground(false);
        labelEndTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(labelEndTime);

        dateTimeEditTo = new QDateTimeEdit(Log);
        dateTimeEditTo->setObjectName(QStringLiteral("dateTimeEditTo"));
        sizePolicy.setHeightForWidth(dateTimeEditTo->sizePolicy().hasHeightForWidth());
        dateTimeEditTo->setSizePolicy(sizePolicy);
        dateTimeEditTo->setMinimumSize(QSize(160, 23));
        dateTimeEditTo->setFrame(false);

        horizontalLayout->addWidget(dateTimeEditTo);

        btnRetrieve = new QPushButton(Log);
        btnRetrieve->setObjectName(QStringLiteral("btnRetrieve"));
        btnRetrieve->setMinimumSize(QSize(87, 23));
        btnRetrieve->setMaximumSize(QSize(87, 23));
        btnRetrieve->setStyleSheet(QStringLiteral(""));
        btnRetrieve->setFlat(true);

        horizontalLayout->addWidget(btnRetrieve);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnExport = new QPushButton(Log);
        btnExport->setObjectName(QStringLiteral("btnExport"));
        btnExport->setMinimumSize(QSize(87, 23));
        btnExport->setMaximumSize(QSize(87, 23));
        btnExport->setFlat(true);

        horizontalLayout->addWidget(btnExport);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widgetOut2 = new QWidget(Log);
        widgetOut2->setObjectName(QStringLiteral("widgetOut2"));
        widgetOut2->setMinimumSize(QSize(100, 1));
        widgetOut2->setMaximumSize(QSize(16777215, 1));
        QPalette palette3;
        QBrush brush3(QColor(255, 255, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        QBrush brush4(QColor(79, 80, 86, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush4);
        QBrush brush5(QColor(118, 120, 129, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Light, brush5);
        QBrush brush6(QColor(98, 100, 107, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Midlight, brush6);
        QBrush brush7(QColor(39, 40, 43, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Dark, brush7);
        QBrush brush8(QColor(52, 53, 57, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Mid, brush8);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette3.setBrush(QPalette::Active, QPalette::BrightText, brush3);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        QBrush brush9(QColor(0, 0, 0, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette3.setBrush(QPalette::Active, QPalette::Shadow, brush9);
        palette3.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush10(QColor(255, 255, 220, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipBase, brush10);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipText, brush9);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush5);
        palette3.setBrush(QPalette::Inactive, QPalette::Midlight, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Dark, brush7);
        palette3.setBrush(QPalette::Inactive, QPalette::Mid, brush8);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::BrightText, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::Shadow, brush9);
        palette3.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush10);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush5);
        palette3.setBrush(QPalette::Disabled, QPalette::Midlight, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Dark, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::Mid, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::BrightText, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Shadow, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush10);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush9);
        widgetOut2->setPalette(palette3);
        widgetOut2->setAutoFillBackground(true);

        verticalLayout_2->addWidget(widgetOut2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        widgetOut1 = new QWidget(Log);
        widgetOut1->setObjectName(QStringLiteral("widgetOut1"));
        widgetOut1->setMinimumSize(QSize(1, 100));
        widgetOut1->setMaximumSize(QSize(1, 16777215));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette4.setBrush(QPalette::Active, QPalette::Light, brush5);
        palette4.setBrush(QPalette::Active, QPalette::Midlight, brush6);
        palette4.setBrush(QPalette::Active, QPalette::Dark, brush7);
        palette4.setBrush(QPalette::Active, QPalette::Mid, brush8);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette4.setBrush(QPalette::Active, QPalette::BrightText, brush3);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette4.setBrush(QPalette::Active, QPalette::Shadow, brush9);
        palette4.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipBase, brush10);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipText, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette4.setBrush(QPalette::Inactive, QPalette::Light, brush5);
        palette4.setBrush(QPalette::Inactive, QPalette::Midlight, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::Dark, brush7);
        palette4.setBrush(QPalette::Inactive, QPalette::Mid, brush8);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::BrightText, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette4.setBrush(QPalette::Inactive, QPalette::Shadow, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush10);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::Light, brush5);
        palette4.setBrush(QPalette::Disabled, QPalette::Midlight, brush6);
        palette4.setBrush(QPalette::Disabled, QPalette::Dark, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::Mid, brush8);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::BrightText, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::Shadow, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush10);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush9);
        widgetOut1->setPalette(palette4);
        widgetOut1->setAutoFillBackground(true);

        horizontalLayout_4->addWidget(widgetOut1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        widgetIn1 = new QWidget(Log);
        widgetIn1->setObjectName(QStringLiteral("widgetIn1"));
        widgetIn1->setMinimumSize(QSize(3, 100));
        widgetIn1->setMaximumSize(QSize(3, 16777215));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        QBrush brush11(QColor(29, 30, 33, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush11);
        QBrush brush12(QColor(43, 45, 49, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Light, brush12);
        QBrush brush13(QColor(36, 37, 41, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Midlight, brush13);
        QBrush brush14(QColor(14, 15, 16, 255));
        brush14.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Dark, brush14);
        QBrush brush15(QColor(19, 20, 22, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Mid, brush15);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette5.setBrush(QPalette::Active, QPalette::BrightText, brush3);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush11);
        palette5.setBrush(QPalette::Active, QPalette::Shadow, brush9);
        palette5.setBrush(QPalette::Active, QPalette::AlternateBase, brush14);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipBase, brush10);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipText, brush9);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush11);
        palette5.setBrush(QPalette::Inactive, QPalette::Light, brush12);
        palette5.setBrush(QPalette::Inactive, QPalette::Midlight, brush13);
        palette5.setBrush(QPalette::Inactive, QPalette::Dark, brush14);
        palette5.setBrush(QPalette::Inactive, QPalette::Mid, brush15);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::BrightText, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush11);
        palette5.setBrush(QPalette::Inactive, QPalette::Shadow, brush9);
        palette5.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush14);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush10);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush9);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush14);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::Light, brush12);
        palette5.setBrush(QPalette::Disabled, QPalette::Midlight, brush13);
        palette5.setBrush(QPalette::Disabled, QPalette::Dark, brush14);
        palette5.setBrush(QPalette::Disabled, QPalette::Mid, brush15);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush14);
        palette5.setBrush(QPalette::Disabled, QPalette::BrightText, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush14);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::Shadow, brush9);
        palette5.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush10);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush9);
        widgetIn1->setPalette(palette5);
        widgetIn1->setAutoFillBackground(true);

        horizontalLayout_3->addWidget(widgetIn1);

        tableWidgetLog = new QTableWidget(Log);
        tableWidgetLog->setObjectName(QStringLiteral("tableWidgetLog"));
        tableWidgetLog->setStyleSheet(QStringLiteral(""));
        tableWidgetLog->setFrameShape(QFrame::NoFrame);
        tableWidgetLog->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidgetLog->setAlternatingRowColors(true);
        tableWidgetLog->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidgetLog->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetLog->horizontalHeader()->setDefaultSectionSize(100);
        tableWidgetLog->horizontalHeader()->setMinimumSectionSize(25);
        tableWidgetLog->verticalHeader()->setVisible(false);

        horizontalLayout_3->addWidget(tableWidgetLog);

        widgetIn3 = new QWidget(Log);
        widgetIn3->setObjectName(QStringLiteral("widgetIn3"));
        widgetIn3->setMinimumSize(QSize(3, 100));
        widgetIn3->setMaximumSize(QSize(3, 16777215));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette6.setBrush(QPalette::Active, QPalette::Button, brush11);
        palette6.setBrush(QPalette::Active, QPalette::Light, brush12);
        palette6.setBrush(QPalette::Active, QPalette::Midlight, brush13);
        palette6.setBrush(QPalette::Active, QPalette::Dark, brush14);
        palette6.setBrush(QPalette::Active, QPalette::Mid, brush15);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette6.setBrush(QPalette::Active, QPalette::BrightText, brush3);
        palette6.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush11);
        palette6.setBrush(QPalette::Active, QPalette::Shadow, brush9);
        palette6.setBrush(QPalette::Active, QPalette::AlternateBase, brush14);
        palette6.setBrush(QPalette::Active, QPalette::ToolTipBase, brush10);
        palette6.setBrush(QPalette::Active, QPalette::ToolTipText, brush9);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush11);
        palette6.setBrush(QPalette::Inactive, QPalette::Light, brush12);
        palette6.setBrush(QPalette::Inactive, QPalette::Midlight, brush13);
        palette6.setBrush(QPalette::Inactive, QPalette::Dark, brush14);
        palette6.setBrush(QPalette::Inactive, QPalette::Mid, brush15);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette6.setBrush(QPalette::Inactive, QPalette::BrightText, brush3);
        palette6.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush11);
        palette6.setBrush(QPalette::Inactive, QPalette::Shadow, brush9);
        palette6.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush14);
        palette6.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush10);
        palette6.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush9);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush14);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush11);
        palette6.setBrush(QPalette::Disabled, QPalette::Light, brush12);
        palette6.setBrush(QPalette::Disabled, QPalette::Midlight, brush13);
        palette6.setBrush(QPalette::Disabled, QPalette::Dark, brush14);
        palette6.setBrush(QPalette::Disabled, QPalette::Mid, brush15);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush14);
        palette6.setBrush(QPalette::Disabled, QPalette::BrightText, brush3);
        palette6.setBrush(QPalette::Disabled, QPalette::ButtonText, brush14);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush11);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush11);
        palette6.setBrush(QPalette::Disabled, QPalette::Shadow, brush9);
        palette6.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush11);
        palette6.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush10);
        palette6.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush9);
        widgetIn3->setPalette(palette6);
        widgetIn3->setAutoFillBackground(true);

        horizontalLayout_3->addWidget(widgetIn3);


        verticalLayout->addLayout(horizontalLayout_3);

        widgetIn4 = new QWidget(Log);
        widgetIn4->setObjectName(QStringLiteral("widgetIn4"));
        widgetIn4->setMinimumSize(QSize(100, 5));
        widgetIn4->setMaximumSize(QSize(16777215, 5));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette7.setBrush(QPalette::Active, QPalette::Button, brush11);
        palette7.setBrush(QPalette::Active, QPalette::Light, brush12);
        palette7.setBrush(QPalette::Active, QPalette::Midlight, brush13);
        palette7.setBrush(QPalette::Active, QPalette::Dark, brush14);
        palette7.setBrush(QPalette::Active, QPalette::Mid, brush15);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette7.setBrush(QPalette::Active, QPalette::BrightText, brush3);
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette7.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush11);
        palette7.setBrush(QPalette::Active, QPalette::Shadow, brush9);
        palette7.setBrush(QPalette::Active, QPalette::AlternateBase, brush14);
        palette7.setBrush(QPalette::Active, QPalette::ToolTipBase, brush10);
        palette7.setBrush(QPalette::Active, QPalette::ToolTipText, brush9);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette7.setBrush(QPalette::Inactive, QPalette::Button, brush11);
        palette7.setBrush(QPalette::Inactive, QPalette::Light, brush12);
        palette7.setBrush(QPalette::Inactive, QPalette::Midlight, brush13);
        palette7.setBrush(QPalette::Inactive, QPalette::Dark, brush14);
        palette7.setBrush(QPalette::Inactive, QPalette::Mid, brush15);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette7.setBrush(QPalette::Inactive, QPalette::BrightText, brush3);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush11);
        palette7.setBrush(QPalette::Inactive, QPalette::Shadow, brush9);
        palette7.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush14);
        palette7.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush10);
        palette7.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush9);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush14);
        palette7.setBrush(QPalette::Disabled, QPalette::Button, brush11);
        palette7.setBrush(QPalette::Disabled, QPalette::Light, brush12);
        palette7.setBrush(QPalette::Disabled, QPalette::Midlight, brush13);
        palette7.setBrush(QPalette::Disabled, QPalette::Dark, brush14);
        palette7.setBrush(QPalette::Disabled, QPalette::Mid, brush15);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush14);
        palette7.setBrush(QPalette::Disabled, QPalette::BrightText, brush3);
        palette7.setBrush(QPalette::Disabled, QPalette::ButtonText, brush14);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush11);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush11);
        palette7.setBrush(QPalette::Disabled, QPalette::Shadow, brush9);
        palette7.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush11);
        palette7.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush10);
        palette7.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush9);
        widgetIn4->setPalette(palette7);
        widgetIn4->setAutoFillBackground(true);

        verticalLayout->addWidget(widgetIn4);


        horizontalLayout_4->addLayout(verticalLayout);

        widgetOut3 = new QWidget(Log);
        widgetOut3->setObjectName(QStringLiteral("widgetOut3"));
        widgetOut3->setMinimumSize(QSize(1, 100));
        widgetOut3->setMaximumSize(QSize(1, 16777215));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette8.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette8.setBrush(QPalette::Active, QPalette::Light, brush5);
        palette8.setBrush(QPalette::Active, QPalette::Midlight, brush6);
        palette8.setBrush(QPalette::Active, QPalette::Dark, brush7);
        palette8.setBrush(QPalette::Active, QPalette::Mid, brush8);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette8.setBrush(QPalette::Active, QPalette::BrightText, brush3);
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette8.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette8.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette8.setBrush(QPalette::Active, QPalette::Shadow, brush9);
        palette8.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        palette8.setBrush(QPalette::Active, QPalette::ToolTipBase, brush10);
        palette8.setBrush(QPalette::Active, QPalette::ToolTipText, brush9);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette8.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette8.setBrush(QPalette::Inactive, QPalette::Light, brush5);
        palette8.setBrush(QPalette::Inactive, QPalette::Midlight, brush6);
        palette8.setBrush(QPalette::Inactive, QPalette::Dark, brush7);
        palette8.setBrush(QPalette::Inactive, QPalette::Mid, brush8);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette8.setBrush(QPalette::Inactive, QPalette::BrightText, brush3);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette8.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette8.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette8.setBrush(QPalette::Inactive, QPalette::Shadow, brush9);
        palette8.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette8.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush10);
        palette8.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush9);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
        palette8.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::Light, brush5);
        palette8.setBrush(QPalette::Disabled, QPalette::Midlight, brush6);
        palette8.setBrush(QPalette::Disabled, QPalette::Dark, brush7);
        palette8.setBrush(QPalette::Disabled, QPalette::Mid, brush8);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        palette8.setBrush(QPalette::Disabled, QPalette::BrightText, brush3);
        palette8.setBrush(QPalette::Disabled, QPalette::ButtonText, brush7);
        palette8.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::Shadow, brush9);
        palette8.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush10);
        palette8.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush9);
        widgetOut3->setPalette(palette8);
        widgetOut3->setAutoFillBackground(true);

        horizontalLayout_4->addWidget(widgetOut3);


        verticalLayout_2->addLayout(horizontalLayout_4);

        widgetOut4 = new QWidget(Log);
        widgetOut4->setObjectName(QStringLiteral("widgetOut4"));
        widgetOut4->setMinimumSize(QSize(100, 1));
        widgetOut4->setMaximumSize(QSize(16777215, 1));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette9.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette9.setBrush(QPalette::Active, QPalette::Light, brush5);
        palette9.setBrush(QPalette::Active, QPalette::Midlight, brush6);
        palette9.setBrush(QPalette::Active, QPalette::Dark, brush7);
        palette9.setBrush(QPalette::Active, QPalette::Mid, brush8);
        palette9.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette9.setBrush(QPalette::Active, QPalette::BrightText, brush3);
        palette9.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette9.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette9.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette9.setBrush(QPalette::Active, QPalette::Shadow, brush9);
        palette9.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        palette9.setBrush(QPalette::Active, QPalette::ToolTipBase, brush10);
        palette9.setBrush(QPalette::Active, QPalette::ToolTipText, brush9);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette9.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette9.setBrush(QPalette::Inactive, QPalette::Light, brush5);
        palette9.setBrush(QPalette::Inactive, QPalette::Midlight, brush6);
        palette9.setBrush(QPalette::Inactive, QPalette::Dark, brush7);
        palette9.setBrush(QPalette::Inactive, QPalette::Mid, brush8);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette9.setBrush(QPalette::Inactive, QPalette::BrightText, brush3);
        palette9.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette9.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette9.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette9.setBrush(QPalette::Inactive, QPalette::Shadow, brush9);
        palette9.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette9.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush10);
        palette9.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush9);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
        palette9.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette9.setBrush(QPalette::Disabled, QPalette::Light, brush5);
        palette9.setBrush(QPalette::Disabled, QPalette::Midlight, brush6);
        palette9.setBrush(QPalette::Disabled, QPalette::Dark, brush7);
        palette9.setBrush(QPalette::Disabled, QPalette::Mid, brush8);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        palette9.setBrush(QPalette::Disabled, QPalette::BrightText, brush3);
        palette9.setBrush(QPalette::Disabled, QPalette::ButtonText, brush7);
        palette9.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette9.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        palette9.setBrush(QPalette::Disabled, QPalette::Shadow, brush9);
        palette9.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush4);
        palette9.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush10);
        palette9.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush9);
        widgetOut4->setPalette(palette9);
        widgetOut4->setAutoFillBackground(true);

        verticalLayout_2->addWidget(widgetOut4);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelLogCount = new QLabel(Log);
        labelLogCount->setObjectName(QStringLiteral("labelLogCount"));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelLogCount->setPalette(palette10);

        horizontalLayout_2->addWidget(labelLogCount);

        labelRecs = new QLabel(Log);
        labelRecs->setObjectName(QStringLiteral("labelRecs"));
        labelRecs->setMinimumSize(QSize(0, 23));
        labelRecs->setMaximumSize(QSize(16777215, 23));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelRecs->setPalette(palette11);
        labelRecs->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(labelRecs);

        labelPageCount = new QLabel(Log);
        labelPageCount->setObjectName(QStringLiteral("labelPageCount"));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelPageCount->setPalette(palette12);

        horizontalLayout_2->addWidget(labelPageCount);

        labelPage = new QLabel(Log);
        labelPage->setObjectName(QStringLiteral("labelPage"));
        labelPage->setMinimumSize(QSize(0, 23));
        labelPage->setMaximumSize(QSize(16777215, 23));
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelPage->setPalette(palette13);
        labelPage->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(labelPage);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnFirst = new QPushButton(Log);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnFirst->sizePolicy().hasHeightForWidth());
        btnFirst->setSizePolicy(sizePolicy1);
        btnFirst->setMinimumSize(QSize(75, 23));
        btnFirst->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btnFirst);

        widget = new QWidget(Log);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(1, 10));
        widget->setMaximumSize(QSize(1, 10));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(128, 128, 128);"));

        horizontalLayout_2->addWidget(widget);

        btnPrevious = new QPushButton(Log);
        btnPrevious->setObjectName(QStringLiteral("btnPrevious"));
        sizePolicy1.setHeightForWidth(btnPrevious->sizePolicy().hasHeightForWidth());
        btnPrevious->setSizePolicy(sizePolicy1);
        btnPrevious->setMinimumSize(QSize(75, 23));
        btnPrevious->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btnPrevious);

        widget_2 = new QWidget(Log);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(1, 10));
        widget_2->setMaximumSize(QSize(1, 10));
        widget_2->setStyleSheet(QStringLiteral("background-color: rgb(128, 128, 128);"));

        horizontalLayout_2->addWidget(widget_2);

        btnNext = new QPushButton(Log);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        sizePolicy1.setHeightForWidth(btnNext->sizePolicy().hasHeightForWidth());
        btnNext->setSizePolicy(sizePolicy1);
        btnNext->setMinimumSize(QSize(75, 23));
        btnNext->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btnNext);

        widget_3 = new QWidget(Log);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(1, 10));
        widget_3->setMaximumSize(QSize(1, 10));
        widget_3->setStyleSheet(QStringLiteral("background-color: rgb(128, 128, 128);"));

        horizontalLayout_2->addWidget(widget_3);

        btnLast = new QPushButton(Log);
        btnLast->setObjectName(QStringLiteral("btnLast"));
        sizePolicy1.setHeightForWidth(btnLast->sizePolicy().hasHeightForWidth());
        btnLast->setSizePolicy(sizePolicy1);
        btnLast->setMinimumSize(QSize(75, 23));
        btnLast->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btnLast);


        verticalLayout_3->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(Log);

        QMetaObject::connectSlotsByName(Log);
    } // setupUi

    void retranslateUi(QWidget *Log)
    {
        Log->setWindowTitle(QApplication::translate("Log", "Log", Q_NULLPTR));
        labelType->setText(QApplication::translate("Log", "Log type:", Q_NULLPTR));
        labelStartTime->setText(QApplication::translate("Log", "Start time:", Q_NULLPTR));
        dateTimeEditFrom->setDisplayFormat(QApplication::translate("Log", "yyyy/MM/dd HH:mm:ss", Q_NULLPTR));
        labelEndTime->setText(QApplication::translate("Log", "End time:", Q_NULLPTR));
        dateTimeEditTo->setDisplayFormat(QApplication::translate("Log", "yyyy/MM/dd HH:mm:ss", Q_NULLPTR));
        btnRetrieve->setText(QApplication::translate("Log", "Retrieve", Q_NULLPTR));
        btnExport->setText(QApplication::translate("Log", "Export", Q_NULLPTR));
        labelLogCount->setText(QApplication::translate("Log", "TextLabel", Q_NULLPTR));
        labelRecs->setText(QApplication::translate("Log", "records, ", Q_NULLPTR));
        labelPageCount->setText(QApplication::translate("Log", "TextLabel", Q_NULLPTR));
        labelPage->setText(QApplication::translate("Log", "page", Q_NULLPTR));
        btnFirst->setText(QApplication::translate("Log", "First", Q_NULLPTR));
        btnPrevious->setText(QApplication::translate("Log", "Previous", Q_NULLPTR));
        btnNext->setText(QApplication::translate("Log", "Next", Q_NULLPTR));
        btnLast->setText(QApplication::translate("Log", "Last", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Log: public Ui_Log {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_H
