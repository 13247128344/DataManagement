/********************************************************************************
** Form generated from reading UI file 'tvwallctrl.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TVWALLCTRL_H
#define UI_TVWALLCTRL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TvwallCtrl
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnModify;
    QPushButton *btnDelete;
    QPushButton *btnEnable;
    QPushButton *btnGroup;

    void setupUi(QWidget *TvwallCtrl)
    {
        if (TvwallCtrl->objectName().isEmpty())
            TvwallCtrl->setObjectName(QStringLiteral("TvwallCtrl"));
        TvwallCtrl->resize(310, 47);
        horizontalLayout_2 = new QHBoxLayout(TvwallCtrl);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, -1, 5, -1);
        btnModify = new QPushButton(TvwallCtrl);
        btnModify->setObjectName(QStringLiteral("btnModify"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnModify->sizePolicy().hasHeightForWidth());
        btnModify->setSizePolicy(sizePolicy);
        btnModify->setMinimumSize(QSize(60, 23));
        btnModify->setMaximumSize(QSize(60, 23));
        btnModify->setFlat(true);

        horizontalLayout->addWidget(btnModify);

        btnDelete = new QPushButton(TvwallCtrl);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        sizePolicy.setHeightForWidth(btnDelete->sizePolicy().hasHeightForWidth());
        btnDelete->setSizePolicy(sizePolicy);
        btnDelete->setMinimumSize(QSize(60, 23));
        btnDelete->setMaximumSize(QSize(60, 23));
        btnDelete->setFlat(true);

        horizontalLayout->addWidget(btnDelete);

        btnEnable = new QPushButton(TvwallCtrl);
        btnEnable->setObjectName(QStringLiteral("btnEnable"));
        sizePolicy.setHeightForWidth(btnEnable->sizePolicy().hasHeightForWidth());
        btnEnable->setSizePolicy(sizePolicy);
        btnEnable->setMinimumSize(QSize(60, 23));
        btnEnable->setMaximumSize(QSize(60, 23));
        btnEnable->setFlat(true);

        horizontalLayout->addWidget(btnEnable);

        btnGroup = new QPushButton(TvwallCtrl);
        btnGroup->setObjectName(QStringLiteral("btnGroup"));
        sizePolicy.setHeightForWidth(btnGroup->sizePolicy().hasHeightForWidth());
        btnGroup->setSizePolicy(sizePolicy);
        btnGroup->setMinimumSize(QSize(60, 23));
        btnGroup->setMaximumSize(QSize(60, 23));
        btnGroup->setFlat(true);

        horizontalLayout->addWidget(btnGroup);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TvwallCtrl);

        QMetaObject::connectSlotsByName(TvwallCtrl);
    } // setupUi

    void retranslateUi(QWidget *TvwallCtrl)
    {
        TvwallCtrl->setWindowTitle(QApplication::translate("TvwallCtrl", "Form", Q_NULLPTR));
        btnModify->setText(QApplication::translate("TvwallCtrl", "Modify", Q_NULLPTR));
        btnDelete->setText(QApplication::translate("TvwallCtrl", "Delete", Q_NULLPTR));
        btnEnable->setText(QApplication::translate("TvwallCtrl", "Enable", Q_NULLPTR));
        btnGroup->setText(QApplication::translate("TvwallCtrl", "Group", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TvwallCtrl: public Ui_TvwallCtrl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TVWALLCTRL_H
