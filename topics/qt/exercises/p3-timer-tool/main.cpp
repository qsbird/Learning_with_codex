#include <QAction>
#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle(QStringLiteral("P3 Timer Tool"));
    window.resize(360, 200);

    auto *label = new QLabel(QStringLiteral("ticks: 0"));
    label->setAlignment(Qt::AlignCenter);
    auto *central = new QWidget;
    auto *layout = new QVBoxLayout(central);
    layout->addWidget(label);
    window.setCentralWidget(central);

    auto *timer = new QTimer(&window);
    int ticks = 0;

    auto *startAction = new QAction(QStringLiteral("Start"), &window);
    auto *stopAction = new QAction(QStringLiteral("Stop"), &window);

    // One-time init only — not enough once the tool can run/stop repeatedly.
    startAction->setEnabled(true);
    stopAction->setEnabled(false);

    auto *timerMenu = window.menuBar()->addMenu(QStringLiteral("&Timer"));
    timerMenu->addAction(startAction);
    timerMenu->addAction(stopAction);

    auto *toolBar = window.addToolBar(QStringLiteral("Timer"));
    toolBar->addAction(startAction);
    toolBar->addAction(stopAction);

    window.statusBar()->showMessage(QStringLiteral("stopped"));

    // TODO(P3.2): wire Start / Stop / timeout so UI state stays consistent:
    // - Start: timer->start(500); disable Start; enable Stop; status "running"
    // - Stop:  timer->stop(); enable Start; disable Stop; status "stopped"
    // - timeout: ++ticks; label shows "ticks: N"
    // Prefer one small helper (e.g. syncUi(bool running)) called after every transition
    // instead of only setting enabled/disabled once above.
    auto syncUi = [startAction, stopAction](bool isRunning) {
        startAction->setEnabled(!isRunning);
        stopAction->setEnabled(isRunning);
    };
    QObject::connect(startAction, &QAction::triggered, [timer, syncUi]() {
        timer->start(500);
        syncUi(true);
    });
    QObject::connect(stopAction, &QAction::triggered, [timer, syncUi]() {
        timer->stop();
        syncUi(false);
    });
    QObject::connect(timer, &QTimer::timeout, [label, &ticks]() {
        ++ticks;
        label->setText(QStringLiteral("ticks: %1").arg(ticks));
    });
    Q_UNUSED(timer);
    Q_UNUSED(ticks);

    window.show();
    return app.exec();
}
