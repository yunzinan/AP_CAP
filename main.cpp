#include "loginscene.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginScene w;
    w.show();
    return a.exec();
}
