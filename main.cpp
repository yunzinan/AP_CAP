#include "loginscene.h"
#include <QDir>
#include <QApplication>

int main(int argc, char *argv[])
{
    QString filePath = QDir::currentPath();
    QDir dir(filePath);
    if(!dir.exists("res")) {
        dir.mkdir("res");
    }
    QApplication a(argc, argv);
    LoginScene w;
    w.show();
    return a.exec();
}
