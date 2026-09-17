#include "resultmodel.h"

ResultModel::ResultModel(QObject *parent)
    : QAbstractTableModel(parent)
    , results_{
          {QStringLiteral("alpha"), 91},
          {QStringLiteral("beta"), 84},
          {QStringLiteral("gamma"), 96},
      }
{
}

int ResultModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : results_.size();
}

int ResultModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 2;
}

QVariant ResultModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    return index.column() == 0 ? QVariant::fromValue(results_.at(index.row()).name) : QVariant::fromValue(results_.at(index.row()).score);
}