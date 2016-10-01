

#include <JNMS/JApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    JApplication a(argc, argv);
    MainWindow w;


    return a.exec();
}
