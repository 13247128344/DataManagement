/********************************************************************************
** Form generated from reading UI file 'alarminfowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALARMINFOWIDGET_H
#define UI_ALARMINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlarmInfoWidget
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QWidget *alarmTitle;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_alarm;
    QPushButton *btn_event;
    QPushButton *btn_alarm_info;
    QPushButton *btn_clear;
    QPushButton *btn_close_sound;
    QPushButton *btn_open_sound;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_stay;
    QPushButton *btn_maximum;
    QPushButton *btn_hide;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QTableWidget *table_alarm;
    QWidget *page_2;
    QGridLayout *gridLayout_2;
    QTableWidget *table_event;

    void setupUi(QWidget *AlarmInfoWidget)
    {
        if (AlarmInfoWidget->objectName().isEmpty())
            AlarmInfoWidget->setObjectName(QStringLiteral("AlarmInfoWidget"));
        AlarmInfoWidget->resize(821, 198);
        gridLayout_3 = new QGridLayout(AlarmInfoWidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        alarmTitle = new QWidget(AlarmInfoWidget);
        alarmTitle->setObjectName(QStringLiteral("alarmTitle"));
        horizontalLayout = new QHBoxLayout(alarmTitle);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(15, 2, 5, 3);
        btn_alarm = new QPushButton(alarmTitle);
        btn_alarm->setObjectName(QStringLiteral("btn_alarm"));
        btn_alarm->setMinimumSize(QSize(75, 24));
        QPalette palette;
        QBrush brush(QColor(180, 180, 180, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(12, 12, 12, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        btn_alarm->setPalette(palette);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(false);
        btn_alarm->setFont(font);
        btn_alarm->setAutoFillBackground(false);

        horizontalLayout->addWidget(btn_alarm);

        btn_event = new QPushButton(alarmTitle);
        btn_event->setObjectName(QStringLiteral("btn_event"));
        btn_event->setMinimumSize(QSize(75, 24));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        btn_event->setPalette(palette1);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        btn_event->setFont(font1);

        horizontalLayout->addWidget(btn_event);

        btn_alarm_info = new QPushButton(alarmTitle);
        btn_alarm_info->setObjectName(QStringLiteral("btn_alarm_info"));
        btn_alarm_info->setMinimumSize(QSize(16, 16));
        btn_alarm_info->setMaximumSize(QSize(16, 16));

        horizontalLayout->addWidget(btn_alarm_info);

        btn_clear = new QPushButton(alarmTitle);
        btn_clear->setObjectName(QStringLiteral("btn_clear"));
        btn_clear->setMinimumSize(QSize(16, 16));
        btn_clear->setMaximumSize(QSize(16, 16));

        horizontalLayout->addWidget(btn_clear);

        btn_close_sound = new QPushButton(alarmTitle);
        btn_close_sound->setObjectName(QStringLiteral("btn_close_sound"));
        btn_close_sound->setMinimumSize(QSize(16, 16));
        btn_close_sound->setMaximumSize(QSize(16, 16));

        horizontalLayout->addWidget(btn_close_sound);

        btn_open_sound = new QPushButton(alarmTitle);
        btn_open_sound->setObjectName(QStringLiteral("btn_open_sound"));
        btn_open_sound->setMinimumSize(QSize(16, 16));
        btn_open_sound->setMaximumSize(QSize(16, 16));

        horizontalLayout->addWidget(btn_open_sound);

        horizontalSpacer = new QSpacerItem(228, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_stay = new QPushButton(alarmTitle);
        btn_stay->setObjectName(QStringLiteral("btn_stay"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_stay->sizePolicy().hasHeightForWidth());
        btn_stay->setSizePolicy(sizePolicy);
        btn_stay->setMinimumSize(QSize(20, 20));
        btn_stay->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(btn_stay);

        btn_maximum = new QPushButton(alarmTitle);
        btn_maximum->setObjectName(QStringLiteral("btn_maximum"));
        sizePolicy.setHeightForWidth(btn_maximum->sizePolicy().hasHeightForWidth());
        btn_maximum->setSizePolicy(sizePolicy);
        btn_maximum->setMinimumSize(QSize(20, 20));
        btn_maximum->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(btn_maximum);

        btn_hide = new QPushButton(alarmTitle);
        btn_hide->setObjectName(QStringLiteral("btn_hide"));
        sizePolicy.setHeightForWidth(btn_hide->sizePolicy().hasHeightForWidth());
        btn_hide->setSizePolicy(sizePolicy);
        btn_hide->setMinimumSize(QSize(20, 20));
        btn_hide->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(btn_hide);


        verticalLayout->addWidget(alarmTitle);

        stackedWidget = new QStackedWidget(AlarmInfoWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setAutoFillBackground(false);
        gridLayout = new QGridLayout(page);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        table_alarm = new QTableWidget(page);
        if (table_alarm->rowCount() < 28)
            table_alarm->setRowCount(28);
        table_alarm->setObjectName(QStringLiteral("table_alarm"));
        table_alarm->setMaximumSize(QSize(16777215, 710));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush2(QColor(72, 75, 82, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush3(QColor(240, 240, 240, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush2);
        QBrush brush4(QColor(59, 62, 69, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush4);
        QBrush brush5(QColor(51, 153, 255, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Highlight, brush5);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::HighlightedText, brush6);
        QBrush brush7(QColor(54, 56, 62, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette2.setBrush(QPalette::Inactive, QPalette::Highlight, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        palette2.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush7);
        table_alarm->setPalette(palette2);
        QFont font2;
        font2.setPointSize(9);
        table_alarm->setFont(font2);
        table_alarm->setAutoFillBackground(false);
        table_alarm->setStyleSheet(QStringLiteral(""));
        table_alarm->setFrameShape(QFrame::NoFrame);
        table_alarm->setLineWidth(0);
        table_alarm->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        table_alarm->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_alarm->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        table_alarm->setAlternatingRowColors(true);
        table_alarm->setSelectionMode(QAbstractItemView::NoSelection);
        table_alarm->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_alarm->setShowGrid(true);
        table_alarm->setGridStyle(Qt::SolidLine);
        table_alarm->setSortingEnabled(false);
        table_alarm->setRowCount(28);
        table_alarm->horizontalHeader()->setDefaultSectionSize(500);
        table_alarm->horizontalHeader()->setHighlightSections(true);
        table_alarm->horizontalHeader()->setMinimumSectionSize(25);
        table_alarm->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        table_alarm->verticalHeader()->setVisible(false);
        table_alarm->verticalHeader()->setMinimumSectionSize(25);

        gridLayout->addWidget(table_alarm, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setAutoFillBackground(false);
        gridLayout_2 = new QGridLayout(page_2);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        table_event = new QTableWidget(page_2);
        if (table_event->rowCount() < 28)
            table_event->setRowCount(28);
        table_event->setObjectName(QStringLiteral("table_event"));
        table_event->setMaximumSize(QSize(16777215, 710));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette3.setBrush(QPalette::Active, QPalette::Highlight, brush5);
        palette3.setBrush(QPalette::Active, QPalette::HighlightedText, brush6);
        palette3.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::Highlight, brush5);
        palette3.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        palette3.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush7);
        table_event->setPalette(palette3);
        table_event->setAutoFillBackground(false);
        table_event->setStyleSheet(QStringLiteral(""));
        table_event->setFrameShape(QFrame::NoFrame);
        table_event->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        table_event->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_event->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        table_event->setAlternatingRowColors(true);
        table_event->setSelectionMode(QAbstractItemView::NoSelection);
        table_event->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_event->setRowCount(28);
        table_event->horizontalHeader()->setHighlightSections(true);
        table_event->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        table_event->verticalHeader()->setVisible(false);

        gridLayout_2->addWidget(table_event, 0, 0, 1, 1);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(AlarmInfoWidget);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AlarmInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *AlarmInfoWidget)
    {
        AlarmInfoWidget->setWindowTitle(QApplication::translate("AlarmInfoWidget", "Form", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btn_alarm->setToolTip(QApplication::translate("AlarmInfoWidget", "Alarm", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_alarm->setText(QApplication::translate("AlarmInfoWidget", "Alarm", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btn_event->setToolTip(QApplication::translate("AlarmInfoWidget", "Event", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_event->setText(QApplication::translate("AlarmInfoWidget", "Event", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btn_alarm_info->setToolTip(QApplication::translate("AlarmInfoWidget", "Alarm", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_alarm_info->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_clear->setToolTip(QApplication::translate("AlarmInfoWidget", "Clear", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_clear->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_close_sound->setToolTip(QApplication::translate("AlarmInfoWidget", "Close sound", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_close_sound->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_open_sound->setToolTip(QApplication::translate("AlarmInfoWidget", "Open sound", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_open_sound->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_stay->setToolTip(QApplication::translate("AlarmInfoWidget", "Stay", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_stay->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_maximum->setToolTip(QApplication::translate("AlarmInfoWidget", "Max", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_maximum->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_hide->setToolTip(QApplication::translate("AlarmInfoWidget", "Hide", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btn_hide->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AlarmInfoWidget: public Ui_AlarmInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALARMINFOWIDGET_H
