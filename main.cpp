#include "iamainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IaMainWindow w;
    w.show();
    return a.exec();
}
