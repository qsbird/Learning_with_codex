#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
// TODO(P3.1): add QVBoxLayout / QHBoxLayout includes when you switch from setGeometry.

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle(QStringLiteral("P3 Layout Form"));
    window.resize(320, 160);

    auto *label = new QLabel(QStringLiteral("ready"), &window);
    auto *clickButton = new QPushButton(QStringLiteral("click"), &window);
    auto *clearButton = new QPushButton(QStringLiteral("clear"), &window);

    // Baseline uses absolute geometry (P2 style). Your task: replace this block with layouts.
    auto *layout = new QVBoxLayout(&window);
    auto *layout2 = new QHBoxLayout();
    layout2->addWidget(clickButton);
    layout2->addWidget(clearButton);
    layout->addLayout(layout2);
    layout->addWidget(label);

    QObject::connect(clickButton, &QPushButton::clicked, label, [label]() {
        label->setText(QStringLiteral("clicked"));
    });
    QObject::connect(clearButton, &QPushButton::clicked, label, [label]() {
        label->setText(QStringLiteral("ready"));
    });

    window.show();
    return app.exec();
}
