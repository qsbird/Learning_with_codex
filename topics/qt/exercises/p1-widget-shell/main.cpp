#include <QApplication>
#include <QMainWindow>

#include "ui_mainwindow.h"
#include <QLabel>
#include <QIcon>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    Ui::P1WidgetShell ui;
    ui.setupUi(&window);

    auto *iconLabel = new QLabel(&window);
    iconLabel->setPixmap(QIcon(":/icons/icons/icon.png").pixmap(64, 64));
    iconLabel->setAlignment(Qt::AlignCenter);
    window.setCentralWidget(iconLabel);
    window.show();
    return app.exec();
}