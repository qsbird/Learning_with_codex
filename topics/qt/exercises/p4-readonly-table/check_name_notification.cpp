#include "resultmodel.h"

#include <iostream>

int main()
{
    ResultModel model;
    int emissions = 0;
    QModelIndex top;
    QModelIndex bottom;

    QObject::connect(&model, &QAbstractItemModel::dataChanged, &model,
                     [&](const QModelIndex &first, const QModelIndex &last, const QList<int> &) {
                         ++emissions;
                         top = first;
                         bottom = last;
                     });

    model.setName(2, QStringLiteral("delta"));
    const bool oneCell = emissions == 1
                         && top == model.index(2, 0)
                         && bottom == model.index(2, 0);
    const bool changedName = model.data(model.index(2, 0)).toString() == QStringLiteral("delta");
    const bool unchangedValues = model.data(model.index(2, 1)).toInt() == 96
                                 && model.data(model.index(0, 0)).toString() == QStringLiteral("alpha")
                                 && model.data(model.index(0, 1)).toInt() == 91;

    const int emissionsBeforeInvalid = emissions;
    model.setName(-1, QStringLiteral("invalid"));
    model.setName(model.rowCount(), QStringLiteral("invalid"));
    const bool ignoredInvalid = emissions == emissionsBeforeInvalid
                                && model.rowCount() == 3
                                && model.data(model.index(2, 0)).toString() == QStringLiteral("delta");

    std::cout << "oneCell=" << oneCell
              << " changedName=" << changedName
              << " unchangedValues=" << unchangedValues
              << " ignoredInvalid=" << ignoredInvalid << '\n';

    return oneCell && changedName && unchangedValues && ignoredInvalid ? 0 : 1;
}
