#include "ClientQt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientQt w;
    w.show();
    return a.exec();
}
