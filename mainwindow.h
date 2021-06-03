#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QPushButton>
#include <QLabel>
#include <QTime>
#include <QTextStream>
#include <QTextCodec>

const QString Breeds[3]={"黑猪","小花猪","大花白猪"};//猪的品种

namespace Ui {
class MainWindow;
}

//猪类
struct Pig
{

    int Breednum;//品种编号
    QString Breed=Breeds[Breednum];//品种名
    double Weight=0;//体重
    int feedTime=0;//饲养时间
    bool isIll=0;//疾病状态
    Pig *next;
};

//猪圈类
struct Pigpen
{
    int pigCount;//猪的数量
    bool hasblack;//有无黑猪
    bool hasIll;//有无病猪
    Pig *start=NULL;//猪圈头
    Pig *end=NULL;//猪圈尾
    Pig *pig[10]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};//指向猪
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Pigpen pigpen[100];
    //购买3种猪的数量
    int blacknum=0;
    int smallwhitenum=0;
    int bigwhitenum=0;

    int pigallcount=0;
    int randWeight=0;

    int Time=0;
    double Money;
    int p;//查询
    int blacki=0;//记录猪圈编号
    int whitei=0;
    QFile file0;
    QFile file;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addPig(int pigpennum,int breed);//添加猪
    void addwhitepig();//购买白猪
    void addblackpig();//购买黑猪
    void moveIll(int pigpennum,int num);//移除病猪
    void checkBreed(int breed);//查询某种类猪
    void setMarket();//更新市场
    void setShopdata();//购买记录
    double growRand(double min,double max);//体重增长

//    void setSelldata();//卖出记录
private slots:
    void on_startgame_clicked();

    void on_newgame_clicked();

    void on_timecontinue_clicked();

    void on_checkblack_clicked();

    void on_checksmallwhite_clicked();

    void on_checkbigwhite_clicked();

    void on_checkill_clicked();

    void on_moveill_clicked();

    void on_returnmain_clicked();

    void on_gomarket2_clicked();

    void on_gopigfarm_clicked();

    void on_pigpen0_clicked();
    void on_pigpen1_clicked();
    void on_pigpen2_clicked();
    void on_pigpen3_clicked();
    void on_pigpen4_clicked();
    void on_pigpen5_clicked();
    void on_pigpen6_clicked();
    void on_pigpen7_clicked();
    void on_pigpen8_clicked();
    void on_pigpen9_clicked();
    void on_pigpen10_clicked();
    void on_pigpen11_clicked();
    void on_pigpen12_clicked();
    void on_pigpen13_clicked();
    void on_pigpen14_clicked();
    void on_pigpen15_clicked();
    void on_pigpen16_clicked();
    void on_pigpen17_clicked();
    void on_pigpen18_clicked();
    void on_pigpen19_clicked();
    void on_pigpen20_clicked();
    void on_pigpen21_clicked();
    void on_pigpen22_clicked();
    void on_pigpen23_clicked();
    void on_pigpen24_clicked();
    void on_pigpen25_clicked();
    void on_pigpen26_clicked();
    void on_pigpen27_clicked();
    void on_pigpen28_clicked();
    void on_pigpen29_clicked();
    void on_pigpen30_clicked();
    void on_pigpen31_clicked();
    void on_pigpen32_clicked();
    void on_pigpen33_clicked();
    void on_pigpen34_clicked();
    void on_pigpen35_clicked();
    void on_pigpen36_clicked();
    void on_pigpen37_clicked();
    void on_pigpen38_clicked();
    void on_pigpen39_clicked();
    void on_pigpen40_clicked();
    void on_pigpen41_clicked();
    void on_pigpen42_clicked();
    void on_pigpen43_clicked();
    void on_pigpen44_clicked();
    void on_pigpen45_clicked();
    void on_pigpen46_clicked();
    void on_pigpen47_clicked();
    void on_pigpen48_clicked();
    void on_pigpen49_clicked();
    void on_pigpen50_clicked();
    void on_pigpen51_clicked();
    void on_pigpen52_clicked();
    void on_pigpen53_clicked();
    void on_pigpen54_clicked();
    void on_pigpen55_clicked();
    void on_pigpen56_clicked();
    void on_pigpen57_clicked();
    void on_pigpen58_clicked();
    void on_pigpen59_clicked();
    void on_pigpen60_clicked();
    void on_pigpen61_clicked();
    void on_pigpen62_clicked();
    void on_pigpen63_clicked();
    void on_pigpen64_clicked();
    void on_pigpen65_clicked();
    void on_pigpen66_clicked();
    void on_pigpen67_clicked();
    void on_pigpen68_clicked();
    void on_pigpen69_clicked();
    void on_pigpen70_clicked();
    void on_pigpen71_clicked();
    void on_pigpen72_clicked();
    void on_pigpen73_clicked();
    void on_pigpen74_clicked();
    void on_pigpen75_clicked();
    void on_pigpen76_clicked();
    void on_pigpen77_clicked();
    void on_pigpen78_clicked();
    void on_pigpen79_clicked();
    void on_pigpen80_clicked();
    void on_pigpen81_clicked();
    void on_pigpen82_clicked();
    void on_pigpen83_clicked();
    void on_pigpen84_clicked();
    void on_pigpen85_clicked();
    void on_pigpen86_clicked();
    void on_pigpen87_clicked();
    void on_pigpen88_clicked();
    void on_pigpen89_clicked();
    void on_pigpen90_clicked();
    void on_pigpen91_clicked();
    void on_pigpen92_clicked();
    void on_pigpen93_clicked();
    void on_pigpen94_clicked();
    void on_pigpen95_clicked();
    void on_pigpen96_clicked();
    void on_pigpen97_clicked();
    void on_pigpen98_clicked();
    void on_pigpen99_clicked();

    void on_pig0_clicked();
    void on_pig1_clicked();
    void on_pig2_clicked();
    void on_pig3_clicked();
    void on_pig4_clicked();
    void on_pig5_clicked();
    void on_pig6_clicked();
    void on_pig7_clicked();
    void on_pig8_clicked();
    void on_pig9_clicked();

    void on_returnpigfarm_clicked();



    void on_buy_clicked();

    void on_returnmain_2_clicked();

    void on_gomarket_clicked();

    void on_save_clicked();

    void on_save_2_clicked();

    void on_checkpigpen_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
