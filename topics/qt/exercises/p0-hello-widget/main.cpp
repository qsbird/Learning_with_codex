//
// Created by Qs on 2026/7/30.
//
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.resize(640, 360);
    window.show();

    return app.exec();
}
