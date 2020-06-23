#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QtCharts/QtCharts>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startButtonClicked);
    connect(ui->quitButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(&sort, &SortThread::iterationComplete, this, &MainWindow::updateChart);

    QChart *chart = new QChart();
    chart->setTitle("Bubble sort");
    chart->setAnimationOptions(QChart::NoAnimation);
    ui->chartView->setChart(chart);

    sort.randomize();
    updateChart(sort.array, 0);
}

void MainWindow::startButtonClicked()
{
    /**
     * @brief Обработчик нажатия кнопки запуска сортировки
     */
    sort.start();
    ui->startButton->setEnabled(false);
}

void MainWindow::updateChart(int *array, int iteration)
{
    /**
     * @brief Обработчик нажатия кнопки выхода
     */
    QBarSet *set = new QBarSet("Iteration " + QString::number(iteration) + " of 500000");
    for(int i = 0; i < 100; i++)
    {
        unsigned long long int average=0;
        for(int j = 0; j < 5000; j++)
            average += array[j + 5000*i];
        average /= 5000;
        *set << average;

        QBarSeries *series = new QBarSeries();
        series->append(set);


        ui->chartView->chart()->removeAllSeries();
        ui->chartView->chart()->addSeries(series);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

