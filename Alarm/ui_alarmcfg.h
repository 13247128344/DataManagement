/********************************************************************************
** Form generated from reading UI file 'alarmcfg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALARMCFG_H
#define UI_ALARMCFG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlarmCfg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAddLinkRule;
    QPushButton *btnAddAccessLinkRule;
    QPushButton *btnUpdLinkRule;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit;
    QTableWidget *tableWidget_Linkage;

    void setupUi(QWidget *AlarmCfg)
    {
        if (AlarmCfg->objectName().isEmpty())
            AlarmCfg->setObjectName(QStringLiteral("AlarmCfg"));
        AlarmCfg->resize(1415, 783);
        verticalLayout = new QVBoxLayout(AlarmCfg);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnAddLinkRule = new QPushButton(AlarmCfg);
        btnAddLinkRule->setObjectName(QStringLiteral("btnAddLinkRule"));
        btnAddLinkRule->setMinimumSize(QSize(75, 23));
        btnAddLinkRule->setMaximumSize(QSize(75, 23));
        btnAddLinkRule->setCursor(QCursor(Qt::PointingHandCursor));
        btnAddLinkRule->setFlat(true);

        horizontalLayout->addWidget(btnAddLinkRule);

        btnAddAccessLinkRule = new QPushButton(AlarmCfg);
        btnAddAccessLinkRule->setObjectName(QStringLiteral("btnAddAccessLinkRule"));
        btnAddAccessLinkRule->setMinimumSize(QSize(75, 23));
        btnAddAccessLinkRule->setMaximumSize(QSize(75, 23));
        btnAddAccessLinkRule->setFlat(true);

        horizontalLayout->addWidget(btnAddAccessLinkRule);

        btnUpdLinkRule = new QPushButton(AlarmCfg);
        btnUpdLinkRule->setObjectName(QStringLiteral("btnUpdLinkRule"));
        btnUpdLinkRule->setMinimumSize(QSize(75, 23));
        btnUpdLinkRule->setMaximumSize(QSize(75, 23));
        btnUpdLinkRule->setCursor(QCursor(Qt::PointingHandCursor));
        btnUpdLinkRule->setFlat(true);

        horizontalLayout->addWidget(btnUpdLinkRule);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(verticalSpacer);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        textEdit = new QTextEdit(AlarmCfg);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMinimumSize(QSize(260, 0));
        textEdit->setMaximumSize(QSize(260, 16777215));
        QPalette palette;
        QBrush brush(QColor(180, 180, 180, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(68, 68, 68, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(102, 102, 102, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(85, 85, 85, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(34, 34, 34, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(45, 45, 45, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush7(QColor(29, 30, 33, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush8(QColor(0, 0, 0, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush8);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush9(QColor(255, 255, 220, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush8);
        textEdit->setPalette(palette);
        textEdit->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(textEdit, 1, 1, 1, 1);

        tableWidget_Linkage = new QTableWidget(AlarmCfg);
        tableWidget_Linkage->setObjectName(QStringLiteral("tableWidget_Linkage"));
        QPalette palette1;
        QBrush brush10(QColor(210, 210, 210, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush10);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush10);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush10);
        QBrush brush11(QColor(72, 75, 82, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush11);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush8);
        QBrush brush12(QColor(51, 153, 255, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush12);
        palette1.setBrush(QPalette::Active, QPalette::HighlightedText, brush);
        QBrush brush13(QColor(54, 56, 62, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush9);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush8);
        tableWidget_Linkage->setPalette(palette1);
        tableWidget_Linkage->setStyleSheet(QStringLiteral(""));
        tableWidget_Linkage->setFrameShape(QFrame::NoFrame);
        tableWidget_Linkage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget_Linkage->setAlternatingRowColors(true);
        tableWidget_Linkage->horizontalHeader()->setMinimumSectionSize(25);
        tableWidget_Linkage->horizontalHeader()->setStretchLastSection(true);
        tableWidget_Linkage->verticalHeader()->setVisible(false);
        tableWidget_Linkage->verticalHeader()->setDefaultSectionSize(30);

        gridLayout_2->addWidget(tableWidget_Linkage, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);


        retranslateUi(AlarmCfg);

        QMetaObject::connectSlotsByName(AlarmCfg);
    } // setupUi

    void retranslateUi(QWidget *AlarmCfg)
    {
        AlarmCfg->setWindowTitle(QApplication::translate("AlarmCfg", "Form", Q_NULLPTR));
        btnAddLinkRule->setText(QApplication::translate("AlarmCfg", "ADD Decvice", Q_NULLPTR));
        btnAddAccessLinkRule->setText(QApplication::translate("AlarmCfg", "ADD ACCESS", Q_NULLPTR));
        btnUpdLinkRule->setText(QApplication::translate("AlarmCfg", "REFRESH", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AlarmCfg: public Ui_AlarmCfg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALARMCFG_H
