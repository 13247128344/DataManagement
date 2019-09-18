/********************************************************************************
** Form generated from reading UI file 'prevscreennumctrl.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVSCREENNUMCTRL_H
#define UI_PREVSCREENNUMCTRL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_prevscreennumctrl
{
public:
    QPushButton *btn_screenSplit1;
    QPushButton *btn_screenSplit4;
    QPushButton *btn_screenSplit16;
    QPushButton *btn_screenSplit9;
    QPushButton *btn_screenSplit25;
    QPushButton *btn_screenSplit36;

    void setupUi(QWidget *prevscreennumctrl)
    {
        if (prevscreennumctrl->objectName().isEmpty())
            prevscreennumctrl->setObjectName(QStringLiteral("prevscreennumctrl"));
        prevscreennumctrl->resize(383, 87);
        btn_screenSplit1 = new QPushButton(prevscreennumctrl);
        btn_screenSplit1->setObjectName(QStringLiteral("btn_screenSplit1"));
        btn_screenSplit1->setGeometry(QRect(20, 20, 41, 41));
        btn_screenSplit4 = new QPushButton(prevscreennumctrl);
        btn_screenSplit4->setObjectName(QStringLiteral("btn_screenSplit4"));
        btn_screenSplit4->setGeometry(QRect(80, 20, 41, 41));
        btn_screenSplit16 = new QPushButton(prevscreennumctrl);
        btn_screenSplit16->setObjectName(QStringLiteral("btn_screenSplit16"));
        btn_screenSplit16->setGeometry(QRect(200, 20, 41, 41));
        btn_screenSplit9 = new QPushButton(prevscreennumctrl);
        btn_screenSplit9->setObjectName(QStringLiteral("btn_screenSplit9"));
        btn_screenSplit9->setGeometry(QRect(140, 20, 41, 41));
        btn_screenSplit25 = new QPushButton(prevscreennumctrl);
        btn_screenSplit25->setObjectName(QStringLiteral("btn_screenSplit25"));
        btn_screenSplit25->setGeometry(QRect(260, 20, 41, 41));
        btn_screenSplit36 = new QPushButton(prevscreennumctrl);
        btn_screenSplit36->setObjectName(QStringLiteral("btn_screenSplit36"));
        btn_screenSplit36->setGeometry(QRect(320, 20, 41, 41));

        retranslateUi(prevscreennumctrl);

        QMetaObject::connectSlotsByName(prevscreennumctrl);
    } // setupUi

    void retranslateUi(QWidget *prevscreennumctrl)
    {
        prevscreennumctrl->setWindowTitle(QApplication::translate("prevscreennumctrl", "Form", Q_NULLPTR));
        btn_screenSplit1->setText(QApplication::translate("prevscreennumctrl", "1", Q_NULLPTR));
        btn_screenSplit4->setText(QApplication::translate("prevscreennumctrl", "4", Q_NULLPTR));
        btn_screenSplit16->setText(QApplication::translate("prevscreennumctrl", "16", Q_NULLPTR));
        btn_screenSplit9->setText(QApplication::translate("prevscreennumctrl", "9", Q_NULLPTR));
        btn_screenSplit25->setText(QApplication::translate("prevscreennumctrl", "25", Q_NULLPTR));
        btn_screenSplit36->setText(QApplication::translate("prevscreennumctrl", "36", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class prevscreennumctrl: public Ui_prevscreennumctrl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVSCREENNUMCTRL_H
