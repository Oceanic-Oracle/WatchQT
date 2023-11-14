#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), SLOT(update()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    int hour = currentTime.time().hour();
    int minute = currentTime.time().minute();
    int second = currentTime.time().second();

    QPainter Watch;

    Watch.begin(this);

    Watch.setRenderHint(QPainter::Antialiasing, true);

    Watch.translate(width() / 2, height() / 2);

    int Rad = 0.8 * qMin(width() / 2, height() / 2);

    for (int i = 0; i != 60; i++) {
        if (i % 5 == 0) {
            Watch.drawLine(0, Rad, 0, Rad - 10);
        }
        else {
            Watch.drawLine(0, Rad, 0, Rad - 5);
        }
        Watch.rotate(6.0);
    }

    Watch.setPen(Qt::NoPen);


    //HOUR
    Watch.save();

    QPolygon hour_stick;

    hour_stick << QPoint(-0.04 * Rad, 0) << QPoint(0.04 * Rad, 0) << QPoint(0, -0.4 * Rad);

    Watch.setBrush(QColor(0, 0, 0));

    Watch.rotate(30 * (hour + minute / 60 + second / 3600));

    Watch.drawPolygon(hour_stick);

    Watch.restore();


    //MINUTE
    Watch.save();

    QPolygon min_stick;

    min_stick << QPoint(-0.02 * Rad, 0) << QPoint(0.02 * Rad, 0) << QPoint(0, -0.7 * Rad);

    Watch.setBrush(QColor(0, 0, 0));

    Watch.rotate(6 * (minute + second / 60));

    Watch.drawPolygon(min_stick);

    Watch.restore();


    //SECOND
    QPolygon sec_stick;

    sec_stick << QPoint(-0.02 * Rad, 0) << QPoint(0.02 * Rad, 0) << QPoint(0, -0.7 * Rad);

    Watch.setBrush(QColor(102, 95, 95));

    Watch.rotate(6 * (second));

    Watch.drawPolygon(sec_stick);

    Watch.restore();

    Watch.end();
}

