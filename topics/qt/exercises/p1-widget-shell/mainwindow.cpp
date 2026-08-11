#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::P1WidgetShell)
{
    ui->setupUi(this);

    auto *iconLabel = new QLabel(this);
    iconLabel->setPixmap(QIcon(":/icons/icons/icon.png").pixmap(64, 64));
    iconLabel->setAlignment(Qt::AlignCenter);
    setCentralWidget(iconLabel);

    auto *aboutAction = new QAction(tr("About"), this);
    aboutAction->setStatusTip(tr("Show a short about message"));

    // `this` is the context object: if MainWindow is destroyed, the connection is removed.
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, tr("About"), tr("P1 Widget Shell"));
        statusBar()->showMessage(tr("About shown"), 2000);
    });

    auto *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(aboutAction);

    auto *toolBar = addToolBar(tr("Main"));
    toolBar->addAction(aboutAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}
