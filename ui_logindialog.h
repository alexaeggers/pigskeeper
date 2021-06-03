/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_logindialog
{
public:
    QLineEdit *lineuser;
    QLineEdit *linepass;
    QLabel *title;
    QPushButton *login;
    QLabel *password;
    QLabel *username;

    void setupUi(QDialog *logindialog)
    {
        if (logindialog->objectName().isEmpty())
            logindialog->setObjectName(QStringLiteral("logindialog"));
        logindialog->resize(904, 527);
        lineuser = new QLineEdit(logindialog);
        lineuser->setObjectName(QStringLiteral("lineuser"));
        lineuser->setGeometry(QRect(340, 210, 271, 31));
        linepass = new QLineEdit(logindialog);
        linepass->setObjectName(QStringLiteral("linepass"));
        linepass->setGeometry(QRect(340, 300, 271, 31));
        title = new QLabel(logindialog);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(360, 80, 181, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\347\220\245\347\217\200"));
        font.setPointSize(20);
        font.setBold(false);
        font.setWeight(50);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);
        login = new QPushButton(logindialog);
        login->setObjectName(QStringLiteral("login"));
        login->setGeometry(QRect(410, 370, 101, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setWeight(50);
        login->setFont(font1);
        login->setFlat(true);
        password = new QLabel(logindialog);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(220, 300, 91, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        font2.setKerning(false);
        password->setFont(font2);
        username = new QLabel(logindialog);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(220, 210, 91, 31));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setWeight(75);
        username->setFont(font3);

        retranslateUi(logindialog);

        QMetaObject::connectSlotsByName(logindialog);
    } // setupUi

    void retranslateUi(QDialog *logindialog)
    {
        logindialog->setWindowTitle(QApplication::translate("logindialog", "Dialog", Q_NULLPTR));
        linepass->setText(QString());
        title->setText(QApplication::translate("logindialog", "\345\205\273\347\214\252\346\250\241\346\213\237\345\231\250", Q_NULLPTR));
        login->setText(QApplication::translate("logindialog", "\347\231\273  \345\275\225", Q_NULLPTR));
        password->setText(QApplication::translate("logindialog", "\345\257\206  \347\240\201\357\274\232", Q_NULLPTR));
        username->setText(QApplication::translate("logindialog", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class logindialog: public Ui_logindialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
