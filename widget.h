#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#include<stdio.h>
#include<string>
#include<cstring>
#include<dirent.h>
#include<vector>
#include<unistd.h>
#include<ctime>
#include<cstdlib>
using namespace std;

struct Pair{
    string file1;
    string file2;
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void start();
    string removeblank(string);

public slots:
    void dealbutton();

private:
    Ui::Widget *ui;

    int equalind;
    string route;

    string tof1;
    string tof2;
};

#endif // WIDGET_H
