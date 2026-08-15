#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle(QStringLiteral("P2 Click Label"));
    window.resize(320, 160);

    auto *label = new QLabel(QStringLiteral("waiting"), &window);
    label->setGeometry(20, 20, 280, 32);

    auto *button = new QPushButton(QStringLiteral("click"), &window);
    button->setGeometry(20, 64, 120, 32);

    // 在这里接上：按钮 clicked -> 把 label 改成 "clicked"
    QObject::connect(button, &QPushButton::clicked, label, [label]() {
        label->setText(QStringLiteral("clicked"));
    });

    auto *button2 = new QPushButton(QStringLiteral("delete"), &window);
    button2->setGeometry(160, 64, 120, 32);

    // 在这里接上：按钮 clicked -> delete label
    QObject::connect(button2, &QPushButton::clicked, label, [label]() {
        label->deleteLater();
    });

    window.show();
    return app.exec();
}
