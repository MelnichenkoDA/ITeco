#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createToolbar();
    addToolBar(Qt::TopToolBarArea, toolbar);

    centralWidget = new CentralWidget();
    setCentralWidget(centralWidget);

    makeWidget = new MakeInputWidget();

    setWindowTitle("Sorter");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeButtonClicked()
{
    setCentralWidget(makeWidget);
}

void MainWindow::settingsButtonClicked()
{

}

void MainWindow::testButtonClicked()
{

}

void MainWindow::createToolbar()
{
    toolbar = new QToolBar("TEST");
    toolbar->addAction("Make file", this, SLOT(makeButtonClicked()));
    toolbar->addAction("Settings");
    toolbar->addAction("Test");
}



