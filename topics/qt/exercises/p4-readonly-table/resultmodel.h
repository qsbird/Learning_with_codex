#pragma once

#include <QAbstractTableModel>
#include <QString>
#include <QVector>

class ResultModel : public QAbstractTableModel
{
public:
    explicit ResultModel(QObject *parent = nullptr);

    // QAbstractTableModel already implements index() and parent() for a flat table.
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    struct Result
    {
        QString name;
        int score;
    };

    QVector<Result> results_;
};
