#include "resultmodel.h"

#include <QAbstractItemModel>

#include <iostream>

int main()
{
    ResultModel model;
    int emissions = 0;
    QModelIndex top;
    QModelIndex bottom;

    QObject::connect(&model, &QAbstractItemModel::dataChanged, &model,
                     [&](const QModelIndex &changedTop, const QModelIndex &changedBottom, const QList<int> &) {
                         ++emissions;
                         top = changedTop;
                         bottom = changedBottom;
                     });

    model.setScore(0, 100);

    const QModelIndex name = model.index(0, 0);
    const QModelIndex score = model.index(0, 1);
    const QModelIndex otherScore = model.index(1, 1);
    const bool range = emissions == 1 && top == score && bottom == score;
    const bool values = model.data(name).toString() == QStringLiteral("alpha")
                        && model.data(score).toInt() == 100
                        && model.data(otherScore).toInt() == 84;

    std::cout << "emissions=" << emissions
              << " top=" << top.row() << "," << top.column()
              << " bottom=" << bottom.row() << "," << bottom.column()
              << " name=" << model.data(name).toString().toStdString()
              << " score=" << model.data(score).toInt()
              << " other=" << model.data(otherScore).toInt()
              << "\n";

    return range && values ? 0 : 1;
}
