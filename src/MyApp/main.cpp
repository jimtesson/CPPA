#include "mainwindow.h"
#include "iashape.h"
//#include "cppalgo.h"
#include "iostream"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    iaShape myShape;
    myShape.initializeMatrix(4, 8);

//    cppAlgo myCppAlgo;
    //int pStart;



    return a.exec();
}
