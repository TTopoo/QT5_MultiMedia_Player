#include "MP.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MP w;
    //QTextCodec* codec = QTextCodec::codecForName("utf-8");
    //QTextCodec::setCodecForLocale(codec);
    w.setWindowTitle("MultiPlayer");
    w.show();
    return a.exec();
}
