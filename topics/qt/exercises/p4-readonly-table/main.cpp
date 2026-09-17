#include "resultmodel.h"

#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTableView view;
    ResultModel model;
    view.setModel(&model);
    view.setWindowTitle(QStringLiteral("P4 Read-only Table"));
    view.resize(420, 240);
    view.show();

    return app.exec();
}
