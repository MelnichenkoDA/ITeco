#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widget = new CentralWidget();
    setCentralWidget(widget);

    setWindowTitle("Sorter");
}

MainWindow::~MainWindow()
{
    delete ui;
}



