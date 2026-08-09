#include <QApplication>
#include <QMainWindow>

#include "ui_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    Ui::P1WidgetShell ui;
    ui.setupUi(&window);

    window.show();
    return app.exec();
}