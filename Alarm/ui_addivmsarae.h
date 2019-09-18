/********************************************************************************
** Form generated from reading UI file 'addivmsarae.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDIVMSARAE_H
#define UI_ADDIVMSARAE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddIVMSArae
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_confirm;
    QPushButton *btn_cancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *AddIVMSArae)
    {
        if (AddIVMSArae->objectName().isEmpty())
            AddIVMSArae->setObjectName(QStringLiteral("AddIVMSArae"));
        AddIVMSArae->resize(371, 458);
        gridLayout = new QGridLayout(AddIVMSArae);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, -1, 5);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_confirm = new QPushButton(AddIVMSArae);
        btn_confirm->setObjectName(QStringLiteral("btn_confirm"));
        btn_confirm->setMinimumSize(QSize(70, 25));
        btn_confirm->setMaximumSize(QSize(70, 25));
        btn_confirm->setLayoutDirection(Qt::LeftToRight);
        btn_confirm->setFlat(true);

        horizontalLayout->addWidget(btn_confirm);

        btn_cancel = new QPushButton(AddIVMSArae);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));
        btn_cancel->setMinimumSize(QSize(70, 25));
        btn_cancel->setMaximumSize(QSize(70, 25));
        btn_cancel->setAutoFillBackground(false);
        btn_cancel->setFlat(true);

        horizontalLayout->addWidget(btn_cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(AddIVMSArae);

        QMetaObject::connectSlotsByName(AddIVMSArae);
    } // setupUi

    void retranslateUi(QWidget *AddIVMSArae)
    {
        AddIVMSArae->setWindowTitle(QApplication::translate("AddIVMSArae", "Form", Q_NULLPTR));
        btn_confirm->setText(QApplication::translate("AddIVMSArae", "OK", Q_NULLPTR));
        btn_cancel->setText(QApplication::translate("AddIVMSArae", "CANCEL", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddIVMSArae: public Ui_AddIVMSArae {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDIVMSARAE_H
