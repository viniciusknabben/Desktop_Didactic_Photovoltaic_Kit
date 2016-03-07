#include "kit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    kit w;
    w.show();
    w.setNetwork.show();

    return a.exec();
}
