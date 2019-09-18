/********************************************************************************
** Form generated from reading UI file 'vprevmulitwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VPREVMULITWINDOW_H
#define UI_VPREVMULITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vPrevMulitWindow
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;

    void setupUi(QWidget *vPrevMulitWindow)
    {
        if (vPrevMulitWindow->objectName().isEmpty())
            vPrevMulitWindow->setObjectName(QStringLiteral("vPrevMulitWindow"));
        vPrevMulitWindow->resize(544, 429);
        gridLayoutWidget = new QWidget(vPrevMulitWindow);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 10, 451, 381));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(vPrevMulitWindow);

        QMetaObject::connectSlotsByName(vPrevMulitWindow);
    } // setupUi

    void retranslateUi(QWidget *vPrevMulitWindow)
    {
        vPrevMulitWindow->setWindowTitle(QApplication::translate("vPrevMulitWindow", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class vPrevMulitWindow: public Ui_vPrevMulitWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VPREVMULITWINDOW_H
