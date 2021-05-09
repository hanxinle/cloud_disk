/********************************************************************************
** Form generated from reading UI file 'xdiskgui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDISKGUI_H
#define UI_XDISKGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_xdiskguiClass
{
public:
    QPushButton *refreshButton;
    QPushButton *uploadButton;
    QPushButton *downloadButton;
    QTableWidget *filelistWidget;
    QSpinBox *portBox;
    QLineEdit *ipEdit;
    QLabel *label_ip;
    QLabel *label_port;
    QLabel *label_dir;
    QLineEdit *dirEdit;

    void setupUi(QWidget *xdiskguiClass)
    {
        if (xdiskguiClass->objectName().isEmpty())
            xdiskguiClass->setObjectName(QString::fromUtf8("xdiskguiClass"));
        xdiskguiClass->resize(600, 400);
        xdiskguiClass->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 254, 255);"));
        refreshButton = new QPushButton(xdiskguiClass);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(450, 230, 121, 31));
        QFont font;
        font.setPointSize(11);
        refreshButton->setFont(font);
        refreshButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 255);"));
        uploadButton = new QPushButton(xdiskguiClass);
        uploadButton->setObjectName(QString::fromUtf8("uploadButton"));
        uploadButton->setGeometry(QRect(450, 280, 121, 31));
        uploadButton->setFont(font);
        uploadButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 255);"));
        downloadButton = new QPushButton(xdiskguiClass);
        downloadButton->setObjectName(QString::fromUtf8("downloadButton"));
        downloadButton->setGeometry(QRect(450, 330, 121, 31));
        downloadButton->setFont(font);
        downloadButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 255);"));
        filelistWidget = new QTableWidget(xdiskguiClass);
        if (filelistWidget->columnCount() < 2)
            filelistWidget->setColumnCount(2);
        QFont font1;
        font1.setPointSize(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font1);
        filelistWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        filelistWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        filelistWidget->setObjectName(QString::fromUtf8("filelistWidget"));
        filelistWidget->setGeometry(QRect(20, 20, 401, 341));
        filelistWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 127);"));
        filelistWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        filelistWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        portBox = new QSpinBox(xdiskguiClass);
        portBox->setObjectName(QString::fromUtf8("portBox"));
        portBox->setGeometry(QRect(450, 180, 121, 21));
        portBox->setFont(font);
        portBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        portBox->setMinimum(1);
        portBox->setMaximum(10000);
        portBox->setValue(8888);
        ipEdit = new QLineEdit(xdiskguiClass);
        ipEdit->setObjectName(QString::fromUtf8("ipEdit"));
        ipEdit->setGeometry(QRect(450, 110, 121, 21));
        ipEdit->setFont(font);
        ipEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        label_ip = new QLabel(xdiskguiClass);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));
        label_ip->setGeometry(QRect(450, 80, 71, 16));
        label_ip->setFont(font);
        label_port = new QLabel(xdiskguiClass);
        label_port->setObjectName(QString::fromUtf8("label_port"));
        label_port->setGeometry(QRect(450, 146, 81, 20));
        label_port->setFont(font);
        label_dir = new QLabel(xdiskguiClass);
        label_dir->setObjectName(QString::fromUtf8("label_dir"));
        label_dir->setGeometry(QRect(450, 16, 71, 20));
        label_dir->setFont(font);
        dirEdit = new QLineEdit(xdiskguiClass);
        dirEdit->setObjectName(QString::fromUtf8("dirEdit"));
        dirEdit->setGeometry(QRect(450, 40, 121, 21));
        dirEdit->setFont(font1);
        dirEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));

        retranslateUi(xdiskguiClass);
        QObject::connect(refreshButton, SIGNAL(clicked()), xdiskguiClass, SLOT(Refresh()));
        QObject::connect(uploadButton, SIGNAL(clicked()), xdiskguiClass, SLOT(Upload()));
        QObject::connect(downloadButton, SIGNAL(clicked()), xdiskguiClass, SLOT(Download()));

        QMetaObject::connectSlotsByName(xdiskguiClass);
    } // setupUi

    void retranslateUi(QWidget *xdiskguiClass)
    {
        xdiskguiClass->setWindowTitle(QApplication::translate("xdiskguiClass", "xdiskgui", nullptr));
        refreshButton->setText(QApplication::translate("xdiskguiClass", "\345\210\267\346\226\260", nullptr));
        uploadButton->setText(QApplication::translate("xdiskguiClass", "\344\270\212\344\274\240", nullptr));
        downloadButton->setText(QApplication::translate("xdiskguiClass", "\344\270\213\350\275\275", nullptr));
        QTableWidgetItem *___qtablewidgetitem = filelistWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("xdiskguiClass", "\346\226\207\344\273\266\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = filelistWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("xdiskguiClass", "\345\244\247\345\260\217", nullptr));
        ipEdit->setText(QApplication::translate("xdiskguiClass", "127.0.0.1", nullptr));
        label_ip->setText(QApplication::translate("xdiskguiClass", "\346\234\215\345\212\241\345\231\250IP", nullptr));
        label_port->setText(QApplication::translate("xdiskguiClass", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243", nullptr));
        label_dir->setText(QApplication::translate("xdiskguiClass", "\350\257\273\345\217\226\350\267\257\345\276\204", nullptr));
        dirEdit->setText(QApplication::translate("xdiskguiClass", "./files", nullptr));
    } // retranslateUi

};

namespace Ui {
    class xdiskguiClass: public Ui_xdiskguiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDISKGUI_H
