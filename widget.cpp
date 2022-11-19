#include "widget.h"
#include "ui_widget.h"
#include <windows.h>

vector<Pair>equalpairs;
vector<Pair>inequalpairs;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("等价确认工具");

    setFixedSize(1500,1200);
    ui->btn1->setGeometry(450,1120,100,50);
    ui->btn2->setGeometry(650,1120,100,50);
    ui->btn3->setGeometry(850,1120,100,50);
    ui->content1->setGeometry(50,100,650,1000);
    ui->content2->setGeometry(750,100,650,1000);
    ui->name1->setGeometry(50,30,300,50);
    ui->name2->setGeometry(750,30,300,50);

    string buffer;
    buffer = getcwd(NULL,0);
    string::size_type posit0;
    posit0 = buffer.find_first_of('5');
    route = buffer.substr(0,posit0+1);
    //cout<<route<<endl;

    fstream f1,f2;
    string path1 = route+"\\output\\equal.csv";
    //cout<<path1<<endl;
    string path2 = route+"\\output\\inequal.csv";
    //cout<<path2<<endl;
    f1.open(path1,ios::in);
    if(!f1)
    {
        cout<<"f1 error"<<endl;
        exit(1);
    }
    int flag = 0;
    while(!f1.eof())
    {
        string str;
        f1 >> str;

        if(flag == 0)
        {
            flag = 1;
            continue;
        }
        else
        {
            string::size_type posit;
            posit = str.find_first_of(",");

            Pair newpair;
            newpair.file1 = str.substr(0,posit);
            newpair.file2 = str.substr(posit+1, str.length());

            equalpairs.push_back(newpair);
        }
    }
    f1.close();

    f2.open(path2,ios::in);
    if(!f2)
    {
        cout<<"f2 error"<<endl;
        exit(1);
    }
    flag = 0;
    while(!f2.eof())
    {
        string str;
        f2 >> str;

        if(flag == 0)
        {
            flag = 1;
            continue;
        }
        else
        {
            string::size_type posit;
            posit = str.find_first_of(",");

            Pair newpair;
            newpair.file1 = str.substr(0,posit);
            newpair.file2 = str.substr(posit+1, str.length());

            inequalpairs.push_back(newpair);
        }
    }
    f2.close();

    judge = 1;
    equalind = 0;
    inequalind = 0;

    connect(ui->btn1,&QPushButton::pressed,this,&Widget::dealbutton);
    connect(ui->btn2,&QPushButton::pressed,this,&Widget::dealbutton);
    connect(ui->btn3,&QPushButton::pressed,this,&Widget::dealbutton);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::start()
{/*
    string fpath1,fpath2;
    if(judge == 0)
    {
        fpath1 = route + "//" + equalpairs[equalind].file1 ;
        fpath2 = route +"//" + equalpairs[equalind].file2;
        equalind++;
    }
    else
    {
        fpath1 = route + "//" + inequalpairs[inequalind].file1 ;
        fpath2 = route +"//" + inequalpairs[inequalind].file2;
        inequalind++;
    }

    fstream file1, file2;
    file1.open(fpath1,ios::in);
    if(!file1)
    {
        cout<<"file1 error!"<<endl;
        exit(2);
    }
    while(!file1.eof())
    {

        file1 >>
    }

    file1.close();

    file2.open(fpath2,ios::in);




    for(int i=0;i<equalpairs.size();i++)
    {
        QString tmp = QString::fromStdString(equalpairs[i].file1 + equalpairs[i].file2 + "\n");
        ui->content1->append(tmp);
    }

    for(int i=0;i<inequalpairs.size();i++)
    {
        QString tmp = QString::fromStdString(inequalpairs[i].file1 + inequalpairs[i].file2 + "\n");
        ui->content2->append(tmp);
    }*/

}

void Widget::dealbutton()
{
    QObject*mySender=this->sender();
    QPushButton*Button_Pointer=(QPushButton*)mySender;

    if(Button_Pointer!=nullptr)
    {
        QString Button_Text=Button_Pointer->text();

        if(Button_Text != "OK")
        {

        }
        else
        {

        }
   }


        ui->content1->clear();
        ui->content2->clear();

        start();
}


