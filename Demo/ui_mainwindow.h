/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *ipLabel;
    QLineEdit *ipEdit;
    QLabel *portLabel;
    QLineEdit *portEdit;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *pwdLabel;
    QLineEdit *pwdEdit;
    QPushButton *LoginBtn;
    QPushButton *LogoutBtn;
    QLabel *label;
    QPushButton *leftBtn;
    QPushButton *stopBtn;
    QPushButton *upBtn;
    QPushButton *downBtn;
    QPushButton *rightBtn;
    QPushButton *playBtn;
    QPushButton *captureBtn;
    QPushButton *reBootBtn;
    QPushButton *alarmBtn;
    QPushButton *closeAlarmBtn;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QComboBox *comboBox;
    QLabel *label_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_4;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QWidget *widget_1;
    QWidget *widget_2;
    QWidget *widget_3;
    QWidget *widget_4;
    QWidget *widget_5;
    QWidget *widget_6;
    QWidget *widget_7;
    QWidget *widget_8;
    QWidget *widget_9;
    QWidget *widget_10;
    QWidget *widget_11;
    QWidget *widget_12;
    QWidget *widget_13;
    QWidget *widget_14;
    QWidget *widget_15;
    QWidget *widget_16;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1075, 780);
        MainWindow->setLayoutDirection(Qt::RightToLeft);
        MainWindow->setStyleSheet(QLatin1String("#MainWindow{background-image: url(:/resouse/bj.png);}\n"
""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ipLabel = new QLabel(centralWidget);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));
        ipLabel->setGeometry(QRect(180, 0, 61, 31));
        ipLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);"));
        ipEdit = new QLineEdit(centralWidget);
        ipEdit->setObjectName(QStringLiteral("ipEdit"));
        ipEdit->setGeometry(QRect(260, 0, 170, 31));
        ipEdit->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\347\251\272\347\231\275.png);"));
        portLabel = new QLabel(centralWidget);
        portLabel->setObjectName(QStringLiteral("portLabel"));
        portLabel->setGeometry(QRect(180, 50, 61, 31));
        portLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
""));
        portEdit = new QLineEdit(centralWidget);
        portEdit->setObjectName(QStringLiteral("portEdit"));
        portEdit->setGeometry(QRect(260, 50, 171, 31));
        portEdit->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\347\251\272\347\231\275.png);"));
        nameLabel = new QLabel(centralWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setGeometry(QRect(460, 0, 61, 31));
        nameLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
""));
        nameEdit = new QLineEdit(centralWidget);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));
        nameEdit->setGeometry(QRect(540, 0, 171, 31));
        nameEdit->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\347\251\272\347\231\275.png);"));
        pwdLabel = new QLabel(centralWidget);
        pwdLabel->setObjectName(QStringLiteral("pwdLabel"));
        pwdLabel->setGeometry(QRect(460, 50, 61, 31));
        pwdLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
""));
        pwdEdit = new QLineEdit(centralWidget);
        pwdEdit->setObjectName(QStringLiteral("pwdEdit"));
        pwdEdit->setGeometry(QRect(540, 50, 171, 31));
        pwdEdit->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\347\251\272\347\231\275.png);"));
        LoginBtn = new QPushButton(centralWidget);
        LoginBtn->setObjectName(QStringLiteral("LoginBtn"));
        LoginBtn->setGeometry(QRect(740, 10, 111, 51));
        LoginBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
""));
        LogoutBtn = new QPushButton(centralWidget);
        LogoutBtn->setObjectName(QStringLiteral("LogoutBtn"));
        LogoutBtn->setGeometry(QRect(890, 10, 121, 51));
        LogoutBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
""));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 141, 81));
        label->setStyleSheet(QStringLiteral("border-image: url(:/resouse/enz.png);"));
        leftBtn = new QPushButton(centralWidget);
        leftBtn->setObjectName(QStringLiteral("leftBtn"));
        leftBtn->setGeometry(QRect(750, 300, 75, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        leftBtn->setFont(font);
        leftBtn->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";border-image: url(:/resouse/\345\234\206\350\247\222.png);border:2px groove gray;border-radius:10px;padding:2px 4px"));
        stopBtn = new QPushButton(centralWidget);
        stopBtn->setObjectName(QStringLiteral("stopBtn"));
        stopBtn->setGeometry(QRect(850, 300, 75, 41));
        stopBtn->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";border-image: url(:/resouse/\345\234\206\350\247\222.png);border:2px groove gray;border-radius:10px;padding:2px 4px"));
        upBtn = new QPushButton(centralWidget);
        upBtn->setObjectName(QStringLiteral("upBtn"));
        upBtn->setGeometry(QRect(850, 220, 75, 41));
        upBtn->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";border-image: url(:/resouse/\345\234\206\350\247\222.png);border:2px groove gray;border-radius:10px;padding:2px 4px"));
        downBtn = new QPushButton(centralWidget);
        downBtn->setObjectName(QStringLiteral("downBtn"));
        downBtn->setGeometry(QRect(850, 380, 75, 41));
        downBtn->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";border-image: url(:/resouse/\345\234\206\350\247\222.png);border:2px groove gray;border-radius:10px;padding:2px 4px"));
        rightBtn = new QPushButton(centralWidget);
        rightBtn->setObjectName(QStringLiteral("rightBtn"));
        rightBtn->setGeometry(QRect(950, 300, 75, 41));
        rightBtn->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";border-image: url(:/resouse/\345\234\206\350\247\222.png);border:2px groove gray;border-radius:10px;padding:2px 4px"));
        playBtn = new QPushButton(centralWidget);
        playBtn->setObjectName(QStringLiteral("playBtn"));
        playBtn->setGeometry(QRect(840, 470, 101, 61));
        playBtn->setStyleSheet(QString::fromUtf8("color : black;\n"
"font: 75 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"border:2px groove ;border-radius:10px;padding:2px 4px\n"
"\n"
""));
        captureBtn = new QPushButton(centralWidget);
        captureBtn->setObjectName(QStringLiteral("captureBtn"));
        captureBtn->setGeometry(QRect(840, 570, 101, 61));
        captureBtn->setStyleSheet(QString::fromUtf8("color : black;\n"
"font: 75 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px"));
        reBootBtn = new QPushButton(centralWidget);
        reBootBtn->setObjectName(QStringLiteral("reBootBtn"));
        reBootBtn->setGeometry(QRect(960, 700, 111, 41));
        reBootBtn->setStyleSheet(QString::fromUtf8("color : black;\n"
"font: 75 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"border:2px groove ;border-radius:10px;padding:2px 4px"));
        alarmBtn = new QPushButton(centralWidget);
        alarmBtn->setObjectName(QStringLiteral("alarmBtn"));
        alarmBtn->setGeometry(QRect(60, 640, 91, 41));
        alarmBtn->setStyleSheet(QString::fromUtf8("color : black;\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"border:2px groove ;border-radius:10px;padding:2px 4px"));
        closeAlarmBtn = new QPushButton(centralWidget);
        closeAlarmBtn->setObjectName(QStringLiteral("closeAlarmBtn"));
        closeAlarmBtn->setGeometry(QRect(180, 640, 91, 41));
        closeAlarmBtn->setStyleSheet(QString::fromUtf8("color : black;\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"border:2px groove ;border-radius:10px;padding:2px 4px"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(400, 640, 91, 41));
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px"));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(520, 640, 91, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px"));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(110, 100, 81, 31));
        comboBox->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 100, 71, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(60, 150, 41, 31));
        pushButton_3->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px"));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(110, 150, 41, 31));
        pushButton_5->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px"));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(160, 150, 41, 31));
        pushButton_6->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px"));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(210, 150, 41, 31));
        pushButton_7->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px"));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(270, 150, 75, 31));
        pushButton_4->setStyleSheet(QString::fromUtf8("border-image: url(:/resouse/\345\234\206\350\247\222.png);\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 200, 651, 431));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(10);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 5);
        widget_1 = new QWidget(layoutWidget);
        widget_1->setObjectName(QStringLiteral("widget_1"));
        widget_1->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_1, 0, 0, 1, 1);

        widget_2 = new QWidget(layoutWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_2, 0, 1, 1, 1);

        widget_3 = new QWidget(layoutWidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_3, 0, 2, 1, 1);

        widget_4 = new QWidget(layoutWidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_4, 0, 3, 1, 1);

        widget_5 = new QWidget(layoutWidget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_5, 1, 0, 1, 1);

        widget_6 = new QWidget(layoutWidget);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_6, 1, 1, 1, 1);

        widget_7 = new QWidget(layoutWidget);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_7, 1, 2, 1, 1);

        widget_8 = new QWidget(layoutWidget);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        widget_8->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_8, 1, 3, 1, 1);

        widget_9 = new QWidget(layoutWidget);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_9, 2, 0, 1, 1);

        widget_10 = new QWidget(layoutWidget);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        widget_10->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_10, 2, 1, 1, 1);

        widget_11 = new QWidget(layoutWidget);
        widget_11->setObjectName(QStringLiteral("widget_11"));
        widget_11->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_11, 2, 2, 1, 1);

        widget_12 = new QWidget(layoutWidget);
        widget_12->setObjectName(QStringLiteral("widget_12"));
        widget_12->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_12, 2, 3, 1, 1);

        widget_13 = new QWidget(layoutWidget);
        widget_13->setObjectName(QStringLiteral("widget_13"));
        widget_13->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_13, 3, 0, 1, 1);

        widget_14 = new QWidget(layoutWidget);
        widget_14->setObjectName(QStringLiteral("widget_14"));
        widget_14->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_14, 3, 1, 1, 1);

        widget_15 = new QWidget(layoutWidget);
        widget_15->setObjectName(QStringLiteral("widget_15"));
        widget_15->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_15, 3, 2, 1, 1);

        widget_16 = new QWidget(layoutWidget);
        widget_16->setObjectName(QStringLiteral("widget_16"));
        widget_16->setStyleSheet(QStringLiteral("border-image: url(:/resouse/TTT.png);"));

        gridLayout->addWidget(widget_16, 3, 3, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1075, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        ipLabel->setText(QApplication::translate("MainWindow", "    IP:", Q_NULLPTR));
        portLabel->setText(QApplication::translate("MainWindow", "  Port:", Q_NULLPTR));
        nameLabel->setText(QApplication::translate("MainWindow", "UserName:", Q_NULLPTR));
        pwdLabel->setText(QApplication::translate("MainWindow", "Password:", Q_NULLPTR));
        LoginBtn->setText(QApplication::translate("MainWindow", "\347\231\273\351\231\206", Q_NULLPTR));
        LogoutBtn->setText(QApplication::translate("MainWindow", "\346\263\250\351\224\200", Q_NULLPTR));
        label->setText(QString());
        leftBtn->setText(QApplication::translate("MainWindow", "\345\267\246\350\275\254", Q_NULLPTR));
        stopBtn->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242", Q_NULLPTR));
        upBtn->setText(QApplication::translate("MainWindow", "\344\270\212\345\215\207", Q_NULLPTR));
        downBtn->setText(QApplication::translate("MainWindow", "\344\270\213\351\231\215", Q_NULLPTR));
        rightBtn->setText(QApplication::translate("MainWindow", "\345\217\263\350\275\254", Q_NULLPTR));
        playBtn->setText(QApplication::translate("MainWindow", "\345\274\200\346\234\272", Q_NULLPTR));
        captureBtn->setText(QApplication::translate("MainWindow", "\346\212\223\345\233\276", Q_NULLPTR));
        reBootBtn->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\351\207\215\345\220\257", Q_NULLPTR));
        alarmBtn->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\346\212\245\350\255\246", Q_NULLPTR));
        closeAlarmBtn->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\346\212\245\350\255\246", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\345\275\225\345\203\217", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\345\275\225\345\203\217", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "chinese", Q_NULLPTR)
         << QApplication::translate("MainWindow", "English", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("MainWindow", "\350\257\255\350\250\200\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "8", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "12", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "16", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "push", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
