#include <QtCore/QCoreApplication>
#include "Server.h"
int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    Server serv(&a);
    return a.exec();
}
