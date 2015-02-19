#include "mainwindow.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>

//http://doc.qt.io/qt-5/videooverview.html

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //w.showMaximized();
    w.show();

    return a.exec();
}
