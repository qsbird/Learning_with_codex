#include <QApplication>
#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle(QStringLiteral("P4 String List"));
    window.resize(360, 280);

    auto *view = new QListView;
    auto *addButton = new QPushButton(QStringLiteral("add"));

    auto *model = new QStringListModel(
        QStringList{QStringLiteral("alpha"), QStringLiteral("beta")},
        &window);

    // Baseline: model already has data. Your first task is to attach it to the view.
    // TODO(P4.1): view->setModel(model);
    view->setModel(model);

    QObject::connect(addButton, &QPushButton::clicked, [model]() {
        model->insertRow(model->rowCount());
        model->setData(model->index(model->rowCount() - 1), QStringLiteral("gamma"));
    });

    auto *row = new QHBoxLayout;
    row->addWidget(addButton);
    row->addStretch();

    auto *layout = new QVBoxLayout(&window);
    layout->addWidget(view);
    layout->addLayout(row);

    // TODO(P4.1): when add is clicked, append a new string THROUGH the model
    // (insertRow + setData, or setStringList with an updated list).
    // Do not only edit a detached QStringList copy and expect the view to refresh.
    Q_UNUSED(model);
    Q_UNUSED(addButton);

    window.show();
    return app.exec();
}
