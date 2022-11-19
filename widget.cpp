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
    QFont fff;
    fff.setPointSize(10);
    ui->content1->setFont(fff);
    ui->content2->setGeometry(750,100,650,1000);
    ui->content2->setFont(fff);
    ui->name1->setGeometry(50,30,400,50);
    ui->name1->setFont(fff);
    ui->name2->setGeometry(750,30,400,50);
    ui->name2->setFont(fff);

    string buffer;
    buffer = getcwd(NULL,0);
    string::size_type posit0;
    posit0 = buffer.find_first_of('5');
    route = buffer.substr(0,posit0+1);
    //cout<<route<<endl;

    fstream fe,fine,func;
    string pp1=route+"//human//equal.csv",pp2=route+"//human//inequal.csv",pp3=route+"//human//uncertain.csv";
   // cout<<pp1<<" "<<pp2<<" "<<pp3<<endl;
    if(access((route+"\\human").c_str(),0)==-1)
         system(("md "+route+"\\human").c_str());

    fe.open(pp1,ios::out);
    if(!fe)
    {
        cout<<"error"<<endl;
        exit(4);
    }
    fe << "file1,file2\n";
    fe.close();
    fine.open(pp2,ios::out);
    if(!fine)
    {
        cout<<"error"<<endl;
        exit(4);
    }
    fine << "file1,file2\n";
    fine.close();
    func.open(pp3,ios::out);
    if(!func)
    {
        cout<<"error"<<endl;
        exit(4);
    }
    func << "file1,file2\n";
    func.close();

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

    string n = inequalpairs[inequalind].file1;
    string::size_type p1 = n.find_first_of("/");
    string::size_type p2 = n.find_last_of("/");
    dirname = n.substr(p1+1,p2);

    start();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::start()
{
    string fpath1,fpath2;
    string next = equalpairs[equalind].file1;
    string::size_type p1 = next.find_first_of("/");
    string::size_type p2 = next.find_last_of("/");
    newdir = next.substr(p1+1,p2);

    if(judge == 0 && newdir==dirname)
    {
        fpath1 = route + "//" + equalpairs[equalind].file1;
        fpath2 = route +"//" + equalpairs[equalind].file2;
        dirname = newdir;

        tof1 = equalpairs[equalind].file1;
        tof2 = equalpairs[equalind].file2;
        ui->name1->append(QString::fromStdString(tof1));
        ui->name2->append(QString::fromStdString(tof2));

        equalind++;
    }
    else
    {
        fpath1 = route + "//" + inequalpairs[inequalind].file1;
        fpath2 = route +"//" + inequalpairs[inequalind].file2;
        next = inequalpairs[inequalind].file1;
        string::size_type p1 = next.find_first_of("/");
        string::size_type p2 = next.find_last_of("/");
        newdir = next.substr(p1+1,p2);
        dirname = newdir;

        tof1 = inequalpairs[inequalind].file1;
        tof2 = inequalpairs[inequalind].file2;
        ui->name1->append(QString::fromStdString(tof1));
        ui->name2->append(QString::fromStdString(tof2));
        inequalind++;
    }

    fstream file1, file2;
    cout<<fpath1<<endl;
    cout<<fpath2<<endl;

    vector<string> fcontext1;
    vector<string> fcontext2;

    file1.open(fpath1,ios::in);
    if(!file1)
    {
        cout<<"file1 error!"<<endl;
        exit(2);
    }

    string fstr;
    while(getline(file1, fstr))
    {
        fcontext1.push_back(fstr);
    }
    file1.close();

    file2.open(fpath2,ios::in);
    if(!file2)
    {
        cout<<"file2 error!"<<endl;
        exit(2);
    }
    while(getline(file2, fstr))
    {
        fcontext2.push_back(fstr);
    }
    file2.close();

    for(int i=0;i<fcontext1.size();i++)
    {
        QString tmp = QString::fromStdString(fcontext1[i]);
        ui->content1->append(tmp);
    }
    for(int i=0;i<fcontext2.size();i++)
    {
        QString tmp = QString::fromStdString(fcontext2[i]);
        ui->content2->append(tmp);
    }

}

void Widget::dealbutton()
{
    QObject*mySender=this->sender();
    QPushButton*Button_Pointer=(QPushButton*)mySender;

    if(Button_Pointer!=nullptr)
    {
        QString Button_Text=Button_Pointer->text();

        if(Button_Text == "等价")
        {
            fstream fe;
            fe.open(route+"//human//equal.csv",ios::app);
            if(!fe)
            {
                cout<<"error"<<endl;
                exit(5);
            }
            fe << tof1<<","<<tof2<<"\n";
            fe.close();

        }
        else if(Button_Text == "不等价")
        {
            fstream fine;
            fine.open(route+"//human//inequal.csv",ios::app);
            if(!fine)
            {
                cout<<"error"<<endl;
                exit(5);
            }
            fine << tof1<<","<<tof2<<"\n";
            fine.close();
        }
        else
        {
            fstream func;
            func.open(route+"//human//uncertain.csv",ios::app);
            if(!func)
            {
                cout<<"error"<<endl;
                exit(5);
            }
            func << tof1<<","<<tof2<<"\n";
            func.close();

        }
   }

    ui->content1->clear();
    ui->content2->clear();
    ui->name1->clear();
    ui->name2->clear();

    start();

}


