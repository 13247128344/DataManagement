/********************************************************************************
** Form generated from reading UI file 'treeview.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREEVIEW_H
#define UI_TREEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_treeview
{
public:
    QTreeWidget *treeWidget;

    void setupUi(QWidget *treeview)
    {
        if (treeview->objectName().isEmpty())
            treeview->setObjectName(QStringLiteral("treeview"));
        treeview->resize(277, 431);
        treeview->setStyleSheet(QStringLiteral(""));
        treeWidget = new QTreeWidget(treeview);
        QFont font;
        font.setPointSize(11);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setFont(1, font);
        __qtreewidgetitem->setFont(0, font);
        __qtreewidgetitem->setBackground(0, QColor(255, 255, 255));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::NoBrush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::NoBrush);
        QBrush brush2(QColor(0, 255, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem1->setBackground(1, brush2);
        __qtreewidgetitem1->setBackground(0, brush1);
        __qtreewidgetitem1->setForeground(0, brush);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(30, 0, 211, 431));
        treeWidget->setStyleSheet(QStringLiteral("background-image: url(:/shebei.png);"));

        retranslateUi(treeview);

        QMetaObject::connectSlotsByName(treeview);
    } // setupUi

    void retranslateUi(QWidget *treeview)
    {
        treeview->setWindowTitle(QApplication::translate("treeview", "Form", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("treeview", "\345\210\206\347\273\204", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("treeview", "\350\256\276\345\244\207", Q_NULLPTR));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("treeview", "\347\256\241\347\220\206\344\270\255\345\277\203", Q_NULLPTR));
        treeWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class treeview: public Ui_treeview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREEVIEW_H
