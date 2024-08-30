#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "touchchartview.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建简单的线条序列
    QLineSeries *series = new QLineSeries();
    series->append(0, 0);
    series->append(1, 3);
    series->append(2, 2);
    series->append(3, 5);
    series->append(4, 4);

    // 创建图表对象并添加序列
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple Line Chart Example");
    chart->createDefaultAxes();

    // 自定义X轴和Y轴的范围
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 4);
    axisX->setLabelFormat("%d");
    axisX->setTitleText("X Axis");

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 6);
    axisY->setTitleText("Y Axis");

    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);

    // 使用自定义的触摸图表视图
    TouchChartView *chartView = new TouchChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
