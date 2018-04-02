#include "mainwindow.h"
#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    //окно приложения располгается в центре экрана
    w.setGeometry(screenGeometry.center().x() - w.minimumWidth() / 2,
                  screenGeometry.center().y() - w.minimumHeight() / 2,
                  w.minimumWidth(),
                  w.minimumHeight());
    w.show();

    return a.exec();
}
