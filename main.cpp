#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logindialog logindlg;
    logindlg.show();
    return a.exec();
}
