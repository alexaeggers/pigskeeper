#include "logindialog.h"
#include "ui_logindialog.h"

logindialog::logindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindialog)
{
    ui->setupUi(this);
    ui->linepass->setFocus();//输入焦点初始置于密码框
}

void logindialog::on_login_clicked()
{
    showPigwindow();//调用验证显示窗口
}

void logindialog::showPigwindow()
{
    QFile file("userlog.xml");//创建xml对象
    mydoc.setContent(&file);//将xml对象赋给QdomDocument类型的qt文档句柄
    QDomElement root = mydoc.documentElement();//获取XML文档的DOM根元素
    if (root.hasChildNodes())
    {
        QDomNodeList userlist =root.childNodes();//获取根元素的全部子节点
        bool exist = false;
        for(int i = 0;i<userlist.count();i++)
        {
            QDomNode user =userlist.at(i);
            QDomNodeList record=user.childNodes();
            QString uname =record.at(0).toElement().text();
            QString pword =record.at(1).toElement().text();
            if(uname==ui->lineuser->text())
            {
                exist=true;
                if(!(pword==ui->linepass->text()))
                {
                    QMessageBox::warning(0,QObject::tr("提示"),"用户名或密码错误，请重新输入");
                    ui->linepass->clear();
                    ui->linepass->setFocus();
                    return;
                }
            }
        }
        if(!exist)
        {
            QMessageBox::warning(0,QObject::tr("提示"),"用户不存在");
            ui->lineuser->clear();
            ui->linepass->clear();
            ui->lineuser->setFocus();
            return;
        }
        pigWindow=new MainWindow();
        pigWindow ->setWindowTitle(ui->lineuser->text());
        pigWindow->show();
        this->close();
    }
}

logindialog::~logindialog()
{
    delete ui;
}
