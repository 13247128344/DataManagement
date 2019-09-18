/********************************************************************************
** Form generated from reading UI file 'playframe.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYFRAME_H
#define UI_PLAYFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_playframe
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widgetVedioArea;
    QPushButton *btn_frameClose;

    void setupUi(QWidget *playframe)
    {
        if (playframe->objectName().isEmpty())
            playframe->setObjectName(QStringLiteral("playframe"));
        playframe->resize(435, 430);
        verticalLayoutWidget = new QWidget(playframe);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 421, 481));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetVedioArea = new QWidget(verticalLayoutWidget);
        widgetVedioArea->setObjectName(QStringLiteral("widgetVedioArea"));
        btn_frameClose = new QPushButton(widgetVedioArea);
        btn_frameClose->setObjectName(QStringLiteral("btn_frameClose"));
        btn_frameClose->setGeometry(QRect(400, 0, 21, 23));

        verticalLayout->addWidget(widgetVedioArea);


        retranslateUi(playframe);

        QMetaObject::connectSlotsByName(playframe);
    } // setupUi

    void retranslateUi(QWidget *playframe)
    {
        playframe->setWindowTitle(QApplication::translate("playframe", "Form", Q_NULLPTR));
        btn_frameClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class playframe: public Ui_playframe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYFRAME_H
