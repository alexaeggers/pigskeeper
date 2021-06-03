#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include <QFile>
#include "qdom.h"


namespace Ui {
class logindialog;
}

class logindialog : public QDialog
{
    Q_OBJECT

public:
    explicit logindialog(QWidget *parent = 0);
    ~logindialog();

private slots:
    void on_login_clicked();
    void showPigwindow();


private:
    Ui::logindialog *ui;
    MainWindow *pigWindow;
    QDomDocument mydoc;

};

#endif // LOGINDIALOG_H
