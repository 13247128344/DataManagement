/********************************************************************************
** Form generated from reading UI file 'enabledcontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENABLEDCONTROL_H
#define UI_ENABLEDCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnabledControl
{
public:
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox;

    void setupUi(QWidget *EnabledControl)
    {
        if (EnabledControl->objectName().isEmpty())
            EnabledControl->setObjectName(QStringLiteral("EnabledControl"));
        EnabledControl->resize(101, 44);
        horizontalLayout = new QHBoxLayout(EnabledControl);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBox = new QCheckBox(EnabledControl);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setMinimumSize(QSize(16, 16));
        checkBox->setMaximumSize(QSize(16, 16));

        horizontalLayout_2->addWidget(checkBox);


        horizontalLayout->addLayout(horizontalLayout_2);


        retranslateUi(EnabledControl);

        QMetaObject::connectSlotsByName(EnabledControl);
    } // setupUi

    void retranslateUi(QWidget *EnabledControl)
    {
        EnabledControl->setWindowTitle(QApplication::translate("EnabledControl", "Form", Q_NULLPTR));
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EnabledControl: public Ui_EnabledControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENABLEDCONTROL_H
