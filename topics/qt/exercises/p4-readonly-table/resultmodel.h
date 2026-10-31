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

    // Change the score of an existing row and notify views about that one cell.
    void setScore(int row, int score);

    // Change an existing name and notify views about the affected cell only.
    void setName(int row, const QString &name);

private:
    struct Result
    {
        QString name;
        int score;
    };

    QVector<Result> results_;
};
