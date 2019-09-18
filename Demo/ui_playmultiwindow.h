/********************************************************************************
** Form generated from reading UI file 'playmultiwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYMULTIWINDOW_H
#define UI_PLAYMULTIWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_playmultiwindow
{
public:
    QWidget *widget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;

    void setupUi(QWidget *playmultiwindow)
    {
        if (playmultiwindow->objectName().isEmpty())
            playmultiwindow->setObjectName(QStringLiteral("playmultiwindow"));
        playmultiwindow->resize(330, 326);
        widget = new QWidget(playmultiwindow);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 331, 321));
        gridLayoutWidget = new QWidget(widget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(-1, -1, 331, 321));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(playmultiwindow);

        QMetaObject::connectSlotsByName(playmultiwindow);
    } // setupUi

    void retranslateUi(QWidget *playmultiwindow)
    {
        playmultiwindow->setWindowTitle(QApplication::translate("playmultiwindow", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class playmultiwindow: public Ui_playmultiwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYMULTIWINDOW_H
