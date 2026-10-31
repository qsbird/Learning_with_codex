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

void ResultModel::setScore(int row, int score)
{
    if(row < 0 || row >= results_.size()) {
        return;
    }
    results_[row].score = score;
    emit dataChanged(index(row, 1), index(row, 1));
}

void ResultModel::setName(int row, const QString &name)
{
    // TODO: Ignore invalid rows. Update the name and notify only its cell.
    if(row < 0 || row >= results_.size()) {
        return;
    }
    results_[row].name = name;
    emit dataChanged(index(row, 0), index(row, 0));
}
