#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    FenetrePrincipale w;
    w.show();



    return a.exec();
}
