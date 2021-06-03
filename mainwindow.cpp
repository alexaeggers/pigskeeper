#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //当前页begin
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->begin);
}

MainWindow::~MainWindow()
{
    file.setFileName("C:/Users/12565/Desktop/c++project/pigkeeper/pigfarmdata.txt");
    bool isok=file.open((QIODevice::WriteOnly));
    if(isok)
    {
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("utf-8"));
        stream<<Time<<' '<<Money<<' '<<'\n';
        for(int i=0;i<100;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(pigpen[i].pig[j]==NULL)
                {
                    stream<<'#'<<'\n';
                }
                else
                {
                    stream<<pigpen[i].pig[j]->Breednum<<' ';
                    stream<<pigpen[i].pig[j]->Weight<<' ';
                    stream<<pigpen[i].pig[j]->feedTime<<' ';
                    stream<<pigpen[i].pig[j]->isIll<<' ';
                    stream<<'\n';
                }
             }
         }
      }
      file.close();
      delete ui;
}

void MainWindow::on_save_clicked()//存档
{
    file.setFileName("C:/Users/12565/Desktop/c++project/pigkeeper/pigfarmdata.txt");
    bool isok=file.open((QIODevice::WriteOnly));
    if(isok)
    {
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("utf-8"));
        stream<<Time<<' '<<Money<<' '<<'\n';
        for(int i=0;i<100;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(pigpen[i].pig[j]==NULL)
                {
                    stream<<'#'<<'\n';
                }
                else
                {
                    stream<<pigpen[i].pig[j]->Breednum<<' ';
                    stream<<pigpen[i].pig[j]->Weight<<' ';
                    stream<<pigpen[i].pig[j]->feedTime<<' ';
                    stream<<pigpen[i].pig[j]->isIll<<' ';
                    stream<<'\n';
                }
             }
         }
      }
      file.close();
}

void MainWindow::on_startgame_clicked()//开始游戏
{

    file.setFileName("C:/Users/12565/Desktop/c++project/pigkeeper/pigfarmdata.txt");
    if(!file.exists())
    {
        QMessageBox::warning(this,"提示","请开始新游戏");
        return;
    }
    file.open(QIODevice::ReadOnly);
    QString str =file.readLine();
    int space=0;//记录str位置
    int lasttime;
    float lastmoney;
    int lastspace=-1;//上个空格
    for(int i=0;i<str.length();i++)//读取时间和钱
    {
        if(str[i]==' ')
        {
            QString str1=str.mid(lastspace+1,i-lastspace-1);
            lastspace=i;
            if(space==0)
            {
                lasttime=str1.toInt();
                space++;
                str1.clear();
            }
            else if(space==1)
            {
                lastmoney=str1.toDouble();
                space--;
                str1.clear();
            }
        }
    }
    Time=lasttime;
    Money=lastmoney;
    for(int i=0;i<100;i++)//读取小猪
    {
        for(int j=0;j<10;j++)
        {
            space=0;
            lastspace=-1;
            QString str=file.readLine();
            if(str[0]=='#')
            {
                continue;
            }
            else
            {
                addPig(i,0);
                pigallcount++;
                for(int k=0;k<str.length();k++)
                {
                    if(str[k]==' ')
                    {
                        QString str1=str.mid(lastspace+1,k-lastspace-1);
                        lastspace=k;
                        if(space==0)
                        {
                            int breed=str1.toInt();
                            pigpen[i].pig[j]->Breednum=breed;
                            if(breed==0)
                            {
                                pigpen[i].hasblack=true;
                            }
                            space++;
                            str1.clear();
                        }
                        else if(space==1)
                        {
                            double weight=str1.toDouble();
                            pigpen[i].pig[j]->Weight=weight;
                            space++;
                            str1.clear();
                        }
                        else if(space==2)
                        {
                            int feedtime=str1.toInt();
                            pigpen[i].pig[j]->feedTime=feedtime;
                            space++;
                            str1.clear();
                        }
                        else if(space==3)
                        {
                            bool ill=str1.toInt();
                            pigpen[i].pig[j]->isIll=ill;
                            space++;
                            str1.clear();
                        }
                    }
                }
            }
        }
    }
    ui->stackedWidget->setCurrentWidget(ui->mainwidge);
    ui->time->display(Time);
}

void MainWindow::on_newgame_clicked()//新的游戏
{
    file0.setFileName("C:/Users/12565/Desktop/c++project/pigkeeper/shopdata.txt");
    file0.open(QFile::WriteOnly|QFile::Truncate);
    file0.close();
    file.setFileName("C:/Users/12565/Desktop/c++project/pigkeeper/pigfarmdata.txt");
    file.open(QFile::WriteOnly|QFile::Truncate);
    file.close();
    Money=3000;
    Time=1;
    ui->stackedWidget->setCurrentWidget(ui->mainwidge);
}

void MainWindow::on_save_2_clicked()//退出
{
    QApplication* app;
    app->quit();
}

void MainWindow::on_timecontinue_clicked()//下一天
{
    Time++;
    ui->time->display(Time);


    //体重增长
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(pigpen[i].pig[j]==NULL)continue;
            else
            {
                pigpen[i].pig[j]->feedTime++;
                pigpen[i].pig[j]->Weight+=growRand(0.0,1.2);
            }
        }
    }
    //判断是否全部感染
    int illsum=0;
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(pigpen[i].pig[j]==NULL)continue;
            else if(pigpen[i].pig[j]->isIll==1)
            {
                illsum++;
            }
        }
    }
    if(illsum==pigallcount&&illsum!=0)
    {
        QMessageBox::warning(this,"提示","所有的猪已感染");
    }

    //3个月卖猪
    if(Time%90==0)
    {
        float blackmoney=0;//卖出黑猪的钱
        float smallwhitemoney=0;
        float bigwhitemoney=0;
        int blacksellnum=0;//卖出黑猪的数量
        int smallwhitesellnum=0;
        int bigwhitesellnum=0;
        for(int i=0;i<100;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(pigpen[i].pig[j]==NULL)continue;
                else if((pigpen[i].pig[j]->feedTime>360||pigpen[i].pig[j]->Weight>75.0)&&pigpen[i].pig[j]->isIll==0)//天数大于1年或体重大于75kg
                {
                    if(pigpen[i].pig[j]==pigpen[i].start)//0号猪
                    {
                        pigpen[i].start=pigpen[i].pig[j]->next;
                        Pig *p1=pigpen[i].pig[j];
                        for(int k=j;k<pigpen[i].pigCount-1;k++)
                        {
                            pigpen[i].pig[k]=pigpen[i].pig[k+1];
                        }
                        pigpen[i].pig[pigpen[i].pigCount-1]=NULL;
                        pigpen[i].pigCount--;
                        pigallcount--;
                        if(pigpen[i].pigCount==0)
                        {
                            pigpen[i].hasblack=0;
                        }
                        p1->next=NULL;
                        if(p1->Breednum==0&&p1->isIll==0)
                        {
                            blackmoney+=p1->Weight*30.0;
                            Money+=p1->Weight*30.0;
                            blacksellnum++;
                        }
                        else if(p1->Breednum==1&&p1->isIll==0)
                        {
                            smallwhitemoney+=p1->Weight*14.0;
                            Money+=p1->Weight*14.0;
                            smallwhitesellnum++;
                        }
                        else if(p1->Breednum==2&&p1->isIll==0)
                        {
                            bigwhitemoney+=p1->Weight*12.0;
                            Money+=p1->Weight*12.0;
                            bigwhitesellnum++;
                        }
                        delete p1;//回收卖出的猪
                        j--;
                    }
                    else if(pigpen[i].pig[j]==pigpen[i].end)//最后一只猪
                    {
                        pigpen[i].end=pigpen[i].pig[j-1];
                        pigpen[i].end->next=NULL;
                        Pig *p1=pigpen[i].pig[j];
                        pigpen[i].pig[j]=NULL;
                        pigpen[i].pigCount--;
                        pigallcount--;
                        if(p1->Breednum==0&&p1->isIll==0)
                        {
                            blackmoney+=p1->Weight*30.0;
                            Money+=p1->Weight*30.0;
                            blacksellnum++;
                        }
                        else if(p1->Breednum==1&&p1->isIll==0)
                        {
                            smallwhitemoney+=p1->Weight*14.0;
                            Money+=p1->Weight*14.0;
                            smallwhitesellnum++;
                        }
                        else if(p1->Breednum==2&&p1->isIll==0)
                        {
                            bigwhitemoney+=p1->Weight*12.0;
                            Money+=p1->Weight*12.0;
                            bigwhitesellnum++;
                        }
                        delete p1;
                    }
                    else
                    {
                        pigpen[i].pig[j-1]->next=pigpen[i].pig[j]->next;
                        Pig *p1=pigpen[i].pig[j];
                        for(int k=j;k<pigpen[i].pigCount-1;k++)
                        {
                            pigpen[i].pig[k]=pigpen[i].pig[k+1];
                        }
                        pigpen[i].pig[pigpen[i].pigCount-1]=NULL;
                        pigpen[i].pigCount--;
                        pigallcount--;
                        if(p1->Breednum==0&&p1->isIll==0)
                        {
                            blackmoney+=p1->Weight*30.0;
                            Money+=p1->Weight*30.0;
                            blacksellnum++;
                        }
                        else if(p1->Breednum==1&&p1->isIll==0)
                        {
                            smallwhitemoney+=p1->Weight*14.0;
                            Money+=p1->Weight*14.0;
                            smallwhitesellnum++;
                        }
                        else if(p1->Breednum==2&&p1->isIll==0)
                        {
                            bigwhitemoney+=p1->Weight*12.0;
                            Money+=p1->Weight*12.0;
                            bigwhitesellnum++;
                        }
                        delete p1;
                        j--;
                    }
                }
            }
        }
        float sellmoney=blackmoney+smallwhitemoney+bigwhitemoney;

        QMessageBox::warning(this,"提示","猪已卖出");

//        //写入交易记录
//        file0.setFileName("C:/Users/12565/Desktop/c++project/pigkeeper/shopdata.txt");
//        file0.open(QIODevice::WriteOnly|QIODevice::Append);
//        bool isok=file.open(QIODevice::WriteOnly|QIODevice::Append);
//        if(isok)
//        {
//            QTextStream stream(&file0);
//            stream.setCodec(QTextCodec::codecForName("utf-8"));
//            QString str=QString("第 %1 天：\n"
//                             "卖出黑猪 %2 只，获得 %3 元。"
//                             "卖出小花猪 %4 只，获得 %5 元。"
//                             "卖出大花白猪 %6 只，获得 %7 元。"
//                             "共获得 %8 元 \n")
//                    .arg(Time).arg(blacksellnum).arg(blackmoney).arg(smallwhitesellnum)
//                    .arg(smallwhitemoney).arg(bigwhitesellnum).arg(bigwhitemoney).arg(sellmoney);
//            stream<<str.toUtf8();
//         }
//        file0.close();
    }

    //猪瘟传播
    if(Time>=30)
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        int illness=qrand()%100;
        if(illness==1)
        {
            int illpigpennum;
            int illpignum;
            do
            {
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                illpigpennum=qrand()%100;
            }
            while(pigpen[illpigpennum].pigCount==0);
            do
            {
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                illpignum=qrand()%10;
            }
            while(pigpen[illpigpennum].pig[illpignum]==NULL);
            pigpen[illpigpennum].pig[illpignum]->isIll=true;
            pigpen[illpigpennum].hasIll=true;
            QMessageBox::warning(this,"提示","有猪感染了猪瘟");
        }
        for(int i=0;i<100;i++)//同猪圈传染
        {
            if(pigpen[i].hasIll==0)continue;
            for(int j=0;j<10;j++)
            {
                if(pigpen[i].pig[j]==NULL)continue;
                else
                {
                    qsrand(QTime(0,0,j).secsTo(QTime::currentTime()));
                    if(qrand()%2)
                    {
                        pigpen[i].pig[j]->isIll=true;
                    }
                }
            }
            //相邻猪圈
            if(i-1>=0)
            {
                for(int j=0;j<10;j++)
                {
                    if(pigpen[i].pig[j]==NULL)continue;
                    else
                    {
                        qsrand(QTime(0,0,j).secsTo(QTime::currentTime()));
                        if(qrand()%20<3)
                        {
                            pigpen[i-1].pig[j]->isIll=true;
                        }
                    }

                }
            }
            if(i+1<=99)
            {
                for(int j=0;j<10;j++)
                {
                    if(pigpen[i].pig[j]==NULL)continue;
                    else
                    {
                        qsrand(QTime(0,0,j).secsTo(QTime::currentTime()));
                        if(qrand()%20<3)
                        {
                            pigpen[i-1].pig[j]->isIll=true;
                        }
                    }

                }
            }
        }
    }
}

void MainWindow::on_gopigfarm_clicked()//前往养猪场
{
    ui->stackedWidget->setCurrentWidget(ui->pigfarm);
}

void MainWindow::on_gomarket_clicked()//前往市场
{
    ui->stackedWidget->setCurrentWidget(ui->market);
    ui->money->display(Money);
}



//养猪场界面函数

void MainWindow::on_checkblack_clicked()//查询黑猪
{
    checkBreed(0);
}

void MainWindow::on_checksmallwhite_clicked()//查询小花猪
{
    checkBreed(1);
}

void MainWindow::on_checkbigwhite_clicked()//查询大花白猪
{
    checkBreed(2);
}

void MainWindow::on_checkill_clicked()//查询瘟疫情况
{
    int illsum=0;
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<10;j++)
        {
           if(pigpen[i].pig[j]==NULL)continue;
           else if(pigpen[i].pig[j]->isIll==1)
           {
               illsum++;
           }
        }
    }
    ui->checkresult->insertPlainText(QString("患猪瘟的猪数量：%1\n").arg(illsum));
}

void MainWindow::on_moveill_clicked()//隔离病猪
{
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(pigpen[i].pig[j]==NULL)continue;
            else if(pigpen[i].pig[j]->isIll==1)
            {
                moveIll(i,j);
            }
        }
    }
    ui->checkresult->append(QString("病猪已隔离\n"));
}

void MainWindow::on_returnmain_clicked()//返回主页
{
    ui->stackedWidget->setCurrentWidget(ui->mainwidge);
}

void MainWindow::on_gomarket2_clicked()//前往市场
{
    ui->stackedWidget->setCurrentWidget(ui->market);
}

void MainWindow::on_pigpen0_clicked()//查询0号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=0;
}

void MainWindow::on_pigpen1_clicked()//查询1号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=1;
}

void MainWindow::on_pigpen2_clicked()//查询2号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=2;
}

void MainWindow::on_pigpen3_clicked()//查询3号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=3;
}

void MainWindow::on_pigpen4_clicked()//查询4号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=4;
}

void MainWindow::on_pigpen5_clicked()//查询5号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=5;
}

void MainWindow::on_pigpen6_clicked()//查询6号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=6;
}

void MainWindow::on_pigpen7_clicked()//查询7号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=7;
}

void MainWindow::on_pigpen8_clicked()//查询8号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=8;
}

void MainWindow::on_pigpen9_clicked()//查询9号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=9;
}

void MainWindow::on_pigpen10_clicked()//查询10号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=10;
}

void MainWindow::on_pigpen11_clicked()//查询11号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=11;
}

void MainWindow::on_pigpen12_clicked()//查询12号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=12;
}

void MainWindow::on_pigpen13_clicked()//查询13号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=13;
}

void MainWindow::on_pigpen14_clicked()//查询14号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=14;
}

void MainWindow::on_pigpen15_clicked()//查询15号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=15;
}

void MainWindow::on_pigpen16_clicked()//查询16号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=16;
}

void MainWindow::on_pigpen17_clicked()//查询17号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=17;
}

void MainWindow::on_pigpen18_clicked()//查询18号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=18;
}

void MainWindow::on_pigpen19_clicked()//查询19号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=19;
}

void MainWindow::on_pigpen20_clicked()//查询20号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=20;
}

void MainWindow::on_pigpen21_clicked()//查询21号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=21;
}

void MainWindow::on_pigpen22_clicked()//查询22号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=22;
}

void MainWindow::on_pigpen23_clicked()//查询23号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=23;
}

void MainWindow::on_pigpen24_clicked()//查询24号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=24;
}

void MainWindow::on_pigpen25_clicked()//查询25号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=25;
}

void MainWindow::on_pigpen26_clicked()//查询26号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=26;
}

void MainWindow::on_pigpen27_clicked()//查询27号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=27;
}

void MainWindow::on_pigpen28_clicked()//查询28号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=28;
}

void MainWindow::on_pigpen29_clicked()//查询29号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=29;
}

void MainWindow::on_pigpen30_clicked()//查询30号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=30;
}

void MainWindow::on_pigpen31_clicked()//查询31号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=31;
}

void MainWindow::on_pigpen32_clicked()//查询32号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=32;
}

void MainWindow::on_pigpen33_clicked()//查询33号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=33;
}

void MainWindow::on_pigpen34_clicked()//查询34号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=34;
}

void MainWindow::on_pigpen35_clicked()//查询35号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=35;
}

void MainWindow::on_pigpen36_clicked()//查询36号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=36;
}

void MainWindow::on_pigpen37_clicked()//查询37号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=37;
}

void MainWindow::on_pigpen38_clicked()//查询38号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=38;
}

void MainWindow::on_pigpen39_clicked()//查询39号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=39;
}

void MainWindow::on_pigpen40_clicked()//查询40号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=40;
}

void MainWindow::on_pigpen41_clicked()//查询41号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=41;
}

void MainWindow::on_pigpen42_clicked()//查询42号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=42;
}

void MainWindow::on_pigpen43_clicked()//查询43号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=43;
}

void MainWindow::on_pigpen44_clicked()//查询44号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=44;
}

void MainWindow::on_pigpen45_clicked()//查询45号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=45;
}

void MainWindow::on_pigpen46_clicked()//查询46号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=46;
}

void MainWindow::on_pigpen47_clicked()//查询47号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=47;
}

void MainWindow::on_pigpen48_clicked()//查询48号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=48;
}

void MainWindow::on_pigpen49_clicked()//查询49号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=49;
}

void MainWindow::on_pigpen50_clicked()//查询50号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=50;
}

void MainWindow::on_pigpen51_clicked()//查询51号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=51;
}

void MainWindow::on_pigpen52_clicked()//查询52号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=52;
}

void MainWindow::on_pigpen53_clicked()//查询53号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=53;
}

void MainWindow::on_pigpen54_clicked()//查询54号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=54;
}

void MainWindow::on_pigpen55_clicked()//查询55号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=55;
}

void MainWindow::on_pigpen56_clicked()//查询56号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=56;
}

void MainWindow::on_pigpen57_clicked()//查询57号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=57;
}

void MainWindow::on_pigpen58_clicked()//查询58号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=58;
}

void MainWindow::on_pigpen59_clicked()//查询59号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=59;
}

void MainWindow::on_pigpen60_clicked()//查询60号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=60;
}

void MainWindow::on_pigpen61_clicked()//查询61号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=61;
}

void MainWindow::on_pigpen62_clicked()//查询62号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=62;
}

void MainWindow::on_pigpen63_clicked()//查询63号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=63;
}

void MainWindow::on_pigpen64_clicked()//查询64号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=64;
}

void MainWindow::on_pigpen65_clicked()//查询65号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=65;
}

void MainWindow::on_pigpen66_clicked()//查询66号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=66;
}

void MainWindow::on_pigpen67_clicked()//查询67号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=67;
}

void MainWindow::on_pigpen68_clicked()//查询68号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=68;
}

void MainWindow::on_pigpen69_clicked()//查询69号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=69;
}

void MainWindow::on_pigpen70_clicked()//查询70号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=70;
}

void MainWindow::on_pigpen71_clicked()//查询71号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=71;
}

void MainWindow::on_pigpen72_clicked()//查询72号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=72;
}

void MainWindow::on_pigpen73_clicked()//查询73号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=73;
}

void MainWindow::on_pigpen74_clicked()//查询74号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=74;
}

void MainWindow::on_pigpen75_clicked()//查询75号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=75;
}

void MainWindow::on_pigpen76_clicked()//查询76号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=76;
}

void MainWindow::on_pigpen77_clicked()//查询77号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=77;
}

void MainWindow::on_pigpen78_clicked()//查询78号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=78;
}

void MainWindow::on_pigpen79_clicked()//查询79号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=79;
}

void MainWindow::on_pigpen80_clicked()//查询80号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=80;
}

void MainWindow::on_pigpen81_clicked()//查询81号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=81;
}

void MainWindow::on_pigpen82_clicked()//查询82号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=82;
}

void MainWindow::on_pigpen83_clicked()//查询83号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=83;
}

void MainWindow::on_pigpen84_clicked()//查询84号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=84;
}

void MainWindow::on_pigpen85_clicked()//查询85号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=85;
}

void MainWindow::on_pigpen86_clicked()//查询86号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=86;
}

void MainWindow::on_pigpen87_clicked()//查询87号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=87;
}

void MainWindow::on_pigpen88_clicked()//查询88号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=88;
}

void MainWindow::on_pigpen89_clicked()//查询89号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=89;
}

void MainWindow::on_pigpen90_clicked()//查询90号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=90;
}

void MainWindow::on_pigpen91_clicked()//查询91号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=91;
}

void MainWindow::on_pigpen92_clicked()//查询92号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=92;
}

void MainWindow::on_pigpen93_clicked()//查询93号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=93;
}

void MainWindow::on_pigpen94_clicked()//查询94号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=94;
}

void MainWindow::on_pigpen95_clicked()//查询95号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=95;
}

void MainWindow::on_pigpen96_clicked()//查询96号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=96;
}

void MainWindow::on_pigpen97_clicked()//查询97号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=97;
}

void MainWindow::on_pigpen98_clicked()//查询98号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=98;
}

void MainWindow::on_pigpen99_clicked()//查询99号猪圈
{
    ui->stackedWidget->setCurrentWidget(ui->pigpen);
    p=99;
}



//猪圈界面函数

void MainWindow::on_pig0_clicked()//查询0号猪
{
    if(pigpen[p].pig[0]!=NULL)
    {
        QMessageBox::information(this,"信息",QString("种类：%1 \n"
                                    "体重：%2 kg\n"
                                    "饲养时间：%3 天\n"
                                    "是否得病：%4")
                                 .arg(pigpen[p].pig[0]->Breed)
                                 .arg(pigpen[p].pig[0]->Weight)
                                 .arg(pigpen[p].pig[0]->feedTime)
                                 .arg(pigpen[p].pig[0]->isIll));
    }
    else
    {
        QMessageBox::warning(this,"提示","没有该编号的猪");
    }
}

void MainWindow::on_pig1_clicked()//查询1号猪
{
    if(pigpen[p].pig[1]!=NULL)
    {
        QMessageBox::information(this,"信息",QString("种类：%1 \n"
                                    "体重：%2 kg\n"
                                    "饲养时间：%3 天\n"
                                    "是否得病：%4")
                                 .arg(pigpen[p].pig[1]->Breed)
                                 .arg(pigpen[p].pig[1]->Weight)
                                 .arg(pigpen[p].pig[1]->feedTime)
                                 .arg(pigpen[p].pig[1]->isIll));
    }
    else
    {
        QMessageBox::warning(this,"提示","没有该编号的猪");
    }
}

void MainWindow::on_pig2_clicked()//查询2号猪
{
    if(pigpen[p].pig[2]!=NULL)
    {
        QMessageBox::information(this,"信息",QString("种类：%1 \n"
                                    "体重：%2 kg\n"
                                    "饲养时间：%3 天\n"
                                    "是否得病：%4")
                                 .arg(pigpen[p].pig[2]->Breed)
                                 .arg(pigpen[p].pig[2]->Weight)
                                 .arg(pigpen[p].pig[2]->feedTime)
                                 .arg(pigpen[p].pig[2]->isIll));
    }
    else
    {
        QMessageBox::warning(this,"提示","没有该编号的猪");
    }
}

void MainWindow::on_pig3_clicked()//查询3号猪
{
    if(pigpen[p].pig[3]!=NULL)
    {
        QMessageBox::information(this,"信息",QString("种类：%1 \n"
                                    "体重：%2 kg\n"
                                    "饲养时间：%3 天\n"
                                    "是否得病：%4")
                                 .arg(pigpen[p].pig[3]->Breed)
                                 .arg(pigpen[p].pig[3]->Weight)
                                 .arg(pigpen[p].pig[3]->feedTime)
                                 .arg(pigpen[p].pig[3]->isIll));
    }
    else
    {
        QMessageBox::warning(this,"提示","没有该编号的猪");
    }
}

void MainWindow::on_pig4_clicked()//查询4号猪
{
    if(pigpen[p].pig[4]!=NULL)
    {
        QMessageBox::information(this,"信息",QString("种类：%1 \n"
                                    "体重：%2 kg\n"
                                    "饲养时间：%3 天\n"
                                    "是否得病：%4")
                                 .arg(pigpen[p].pig[4]->Breed)
                                 .arg(pigpen[p].pig[4]->Weight)
                                 .arg(pigpen[p].pig[4]->feedTime)
                                 .arg(pigpen[p].pig[4]->isIll));
    }
    else
    {
        QMessageBox::warning(this,"提示","没有该编号的猪");
    }
}

void MainWindow::on_pig5_clicked()//查询5号猪
{
    if(pigpen[p].pig[5]!=NULL)
    {
        QMessageBox::information(this,"信息",QString("种类：%1 \n"
                                    "体重：%2 kg\n"
                                    "饲养时间：%3 天\n"
                                    "是否得病：%4")
                                 .arg(pigpen[p].pig[5]->Breed)
                                 .arg(pigpen[p].pig[5]->Weight)
                                 .arg(pigpen[p].pig[5]->feedTime)
                                 .arg(pigpen[p].pig[5]->isIll));
    }
    else
    {
        QMessageBox::warning(this,"提示","没有该编号的猪");
    }
}

void MainWindow::on_pig6_clicked()//查询6号猪
{
    if(pigpen[p].pig[6]!=NULL)
    {
        QMessageBox::information(this,"信息",QString("种类：%1 \n"
                                    "体重：%2 kg\n"
                                    "饲养时间：%3 天\n"
                                    "是否得病：%4")
                                 .arg(pigpen[p].pig[6]->Breed)
                                 .arg(pigpen[p].pig[6]->Weight)
                                 .arg(pigpen[p].pig[6]->feedTime)
                                 .arg(pigpen[p].pig[6]->isIll));
    }
    else
    {
        QMessageBox::warning(this,"提示","没有该编号的猪");
    }
}

void MainWindow::on_pig7_clicked()//查询7号猪
{
    if(pigpen[p].pig[7]!=NULL)
    {
        QMessageBox::information(this,"信息",QString("种类：%1 \n"
                                    "体重：%2 kg\n"
                                    "饲养时间：%3 天\n"
                                    "是否得病：%4")
                                 .arg(pigpen[p].pig[7]->Breed)
                                 .arg(pigpen[p].pig[7]->Weight)
                                 .arg(pigpen[p].pig[7]->feedTime)
                                 .arg(pigpen[p].pig[7]->isIll));
    }
    else
    {
        QMessageBox::warning(this,"提示","没有该编号的猪");
    }
}

void MainWindow::on_pig8_clicked()//查询8号猪
{
    if(pigpen[p].pig[8]!=NULL)
    {
        QMessageBox::information(this,"信息",QString("种类：%1 \n"
                                    "体重：%2 kg\n"
                                    "饲养时间：%3 天\n"
                                    "是否得病：%4")
                                 .arg(pigpen[p].pig[8]->Breed)
                                 .arg(pigpen[p].pig[8]->Weight)
                                 .arg(pigpen[p].pig[8]->feedTime)
                                 .arg(pigpen[p].pig[8]->isIll));
    }
    else
    {
        QMessageBox::warning(this,"提示","没有该编号的猪");
    }
}

void MainWindow::on_pig9_clicked()//查询9号猪
{
    if(pigpen[p].pig[9]!=NULL)
    {
        QMessageBox::information(this,"信息",QString("种类：%1 \n"
                                    "体重：%2 kg\n"
                                    "饲养时间：%3 天\n"
                                    "是否得病：%4")
                                 .arg(pigpen[p].pig[9]->Breed)
                                 .arg(pigpen[p].pig[9]->Weight)
                                 .arg(pigpen[p].pig[9]->feedTime)
                                 .arg(pigpen[p].pig[9]->isIll));
    }
    else
    {
        QMessageBox::warning(this,"提示","没有该编号的猪");
    }
}

void MainWindow::on_checkpigpen_clicked()//查询猪圈
{
    int b=0;
    int sw=0;
    int bw=0;
    for(int j=0;j<10;j++)
    {
        if(pigpen[p].pig[j]==NULL)continue;
        else if(pigpen[p].pig[j]->Breednum==0)
        {
            b++;
        }
        else if(pigpen[p].pig[j]->Breednum==1)
        {
            sw++;
        }
        else if(pigpen[p].pig[j]->Breednum==2)
        {
            bw++;
        }
    }
    ui->pigpeninform->insertPlainText(QString("黑猪数量：%1\n"
                                              "小花猪数量：%2\n"
                                              "大白花猪数量：%3\n"  )
                                                .arg(b).arg(sw).arg(bw));
}

void MainWindow::on_returnpigfarm_clicked()//返回养猪场界面
{
    ui->stackedWidget->setCurrentWidget(ui->pigfarm);
}


//市场界面功能
void MainWindow::on_returnmain_2_clicked()//返回主界面
{
    ui->stackedWidget->setCurrentWidget(ui->mainwidge);
}

void MainWindow::on_buy_clicked()//购买
{
    blacknum= ui->spnblack->value();
    smallwhitenum=ui->spnsmallwhite->value();
    bigwhitenum=ui->spnbigwhite->value();
    if(Money>=blacknum*1500+smallwhitenum*700+bigwhitenum*600)
    {
        setShopdata();
        addwhitepig();
        addblackpig();
        ui->money->display(Money);
        QMessageBox::warning(this,"提示","购买完成");
    }
    else
    {
        QMessageBox::warning(this,"提示","资金不足");
    }
}

void MainWindow::setShopdata()//购买记录
{
    file0.setFileName("C:/Users/12565/Desktop/c++project/pigkeeper/shopdata.txt");
    bool isok=file0.open(QIODevice::WriteOnly|QIODevice::Append);
    if(isok)
    {
        QTextStream stream(&file0);
        stream.setCodec(QTextCodec::codecForName("utf-8"));
        QString str=QString("第 %1 天：\n"
                            "购买黑猪 %2 只，"
                            "购买小花猪 %3 只，"
                            "购买大花白猪 %4 只。\n")
                .arg(Time).arg(blacknum).arg(smallwhitenum).arg(bigwhitenum);
        stream<<str.toUtf8();
    }
    file0.close();
//    blacknum=0;
//    smallwhitenum=0;
//    bigwhitenum=0;
}

void MainWindow::addwhitepig()//添加白猪
{
    whitei=0;
    while(smallwhitenum)
    {
        for(int i=0;i<100;i++)
        {
            if(pigpen[i].hasblack==0&&pigpen[i].pigCount<10)
            {
                whitei=i;
                break;
            }
        }
        for(int i=0;i<100;i++)//白猪分布均匀
        {
            if(pigpen[i].hasblack=0&&pigpen[i].pigCount<pigpen[whitei].pigCount)
            {
                whitei=i;
            }
        }
        addPig(whitei,1);
        Money-=randWeight*14;
        smallwhitenum--;
        whitei=0;
     }
     while(bigwhitenum)
     {
        for(int i=0;i<100;i++)
        {
            if(pigpen[i].hasblack==0&&pigpen[i].pigCount<10)
            {
                whitei=i;
                break;
            }
        }
        for(int i=0;i<100;i++)//白猪分布均匀
        {
            if(pigpen[i].hasblack=0&&pigpen[i].pigCount<pigpen[whitei].pigCount)
            {
                whitei=i;
            }
        }
        addPig(whitei,2);
        Money-=randWeight*12;
        bigwhitenum--;
        whitei=0;
     }
     return;
}

void MainWindow::addblackpig()//添加黑猪
{
    blacki=0;
    while(blacknum)
    {
        bool empty=0;
        for(int i=0;i<100;i++)
        {
            if(pigpen[i].hasblack==1&&pigpen[i].pigCount<10||pigpen[i].pigCount==0)
            {
                empty=true;
                blacki=i;
                break;
            }
        }
        if(empty)//有空的黑猪猪圈
        {
            for(int i=0;i<100;i++)//黑猪分布均匀
            {
                if(pigpen[i].hasblack=1&&pigpen[i].pigCount<pigpen[blacki].pigCount)
                {
                    blacki=i;
                }
            }
            addPig(blacki,0);
            Money-=randWeight*30;
            blacknum--;
        }
        else
        {
            QMessageBox::warning(this,"提示","没有空余黑猪猪圈");
        }
        blacki=0;
    }
    return;
}

void MainWindow::addPig(int pigpennum, int breed)
{
    if(pigpen[pigpennum].start==NULL)
        {
            Pig *p1=new Pig;
            pigpen[pigpennum].start=p1;
            pigpen[pigpennum].end=p1;
            p1->next=NULL;
            p1->Breednum=breed;
            p1->Breed=Breeds[breed];
            randWeight=growRand(20.0,50.0);
            p1->Weight=randWeight;
            pigpen[pigpennum].pig[pigpen[pigpennum].pigCount]=p1;
            pigpen[pigpennum].pigCount++;
        }
        else
        {
            Pig *p1=new Pig;
            pigpen[pigpennum].end->next=p1;
            pigpen[pigpennum].end=p1;
            p1->next=NULL;
            p1->Breednum=breed;
            p1->Breed=Breeds[breed];
            randWeight=growRand(20.0,50.0);
            p1->Weight=randWeight;
            pigpen[pigpennum].pig[pigpen[pigpennum].pigCount]=p1;
            pigpen[pigpennum].pigCount++;
        }
        return;
}

void MainWindow::checkBreed(int breed)//查询种类
{
    int numsum=0;
    if(breed==0)
    {
        for(int i=0;i<100;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(pigpen[i].pig[j]==NULL)continue;
                else
                {
                    if(pigpen[i].pig[j]->Breednum==0)
                    {
                        numsum++;
                    }
                }
            }
        }
    }
    if(breed==1)
    {
        for(int i=0;i<100;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(pigpen[i].pig[j]==NULL)continue;
                else
                {
                    if(pigpen[i].pig[j]->Breednum==1)
                    {
                        numsum++;
                    }
                }
            }
        }
    }
    if(breed==2)
    {
        for(int i=0;i<100;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(pigpen[i].pig[j]==NULL)continue;
                else
                {
                    if(pigpen[i].pig[j]->Breednum==2)
                    {
                        numsum++;
                    }
                }
            }
        }
    }

    ui->checkresult->insertPlainText(QString("数量：%1 \n")
                                           .arg(numsum));
}

double MainWindow::growRand(double min, double max)//增长随机
{
    int growmin=int(min*1000);
    int growmax=int(max*1000);
    double randNum=(rand()%(growmax-growmin+1)+growmin)/1000.0;
    return randNum;
}

void MainWindow::moveIll(int pigpennum, int num)//移除病猪
{
    if(pigpen[pigpennum].pig[num]==pigpen[pigpennum].start)//0号猪
    {
        pigpen[pigpennum].start=pigpen[pigpennum].pig[num]->next;
        Pig *p1=pigpen[pigpennum].pig[num];
        for(int k=num;k<pigpen[pigpennum].pigCount-1;k++)
        {
            pigpen[pigpennum].pig[k]=pigpen[pigpennum].pig[k+1];
        }
        pigpen[pigpennum].pig[pigpen[pigpennum].pigCount-1]==NULL;
        pigpen[pigpennum].pigCount--;
        pigallcount--;
        if(pigpen[pigpennum].pigCount==0)
        {
            pigpen[pigpennum].hasblack=0;
        }
        p1->next=NULL;
        delete p1;//回收猪
    }
    else if(pigpen[pigpennum].pig[num]==pigpen[pigpennum].end)//最后一只猪
    {
        pigpen[pigpennum].end=pigpen[pigpennum].pig[num-1];
        pigpen[pigpennum].end->next=NULL;
        Pig *p1=pigpen[pigpennum].pig[num];
        pigpen[pigpennum].pig[num]=NULL;
        pigpen[pigpennum].pigCount--;
        pigallcount--;
        delete p1;
     }
     else
     {
        pigpen[pigpennum].pig[num-1]->next=pigpen[pigpennum].pig[num]->next;
        Pig *p1=pigpen[pigpennum].pig[num];
        for(int k=num;k<pigpen[pigpennum].pigCount-1;k++)
        {
            pigpen[pigpennum].pig[k]=pigpen[pigpennum].pig[k+1];
        }
        pigpen[pigpennum].pig[pigpen[pigpennum].pigCount-1]=NULL;
        pigpen[pigpennum].pigCount--;
        pigallcount--;
        delete p1;
     }
}





