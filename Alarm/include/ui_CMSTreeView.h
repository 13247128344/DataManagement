/********************************************************************************
** Form generated from reading UI file 'CMSTreeView.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMSTREEVIEW_H
#define UI_CMSTREEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_CMSTreeView
{
public:

    void setupUi(QTreeView *CMSTreeView)
    {
        if (CMSTreeView->objectName().isEmpty())
            CMSTreeView->setObjectName(QStringLiteral("CMSTreeView"));
        CMSTreeView->resize(313, 392);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(34, 35, 40, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        CMSTreeView->setPalette(palette);
        CMSTreeView->setMouseTracking(true);
        CMSTreeView->setAutoFillBackground(true);
        CMSTreeView->setStyleSheet(QStringLiteral(""));
        if (CMSTreeView->header()->objectName().isEmpty())

        retranslateUi(CMSTreeView);

        QMetaObject::connectSlotsByName(CMSTreeView);
    } // setupUi

    void retranslateUi(QTreeView *CMSTreeView)
    {
        CMSTreeView->setWindowTitle(QApplication::translate("CMSTreeView", "CMSTreeView", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CMSTreeView: public Ui_CMSTreeView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMSTREEVIEW_H
