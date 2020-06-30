#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Sorter");

    stackedWidgets = new QStackedWidget();

    createToolbar();
    addToolBar(Qt::TopToolBarArea, toolbar);

    mainWidget = new CentralWidget();
    stackedWidgets->addWidget(mainWidget);


    std::function<void ()> callback = std::bind(&MainWindow::setMainWidget, this);
    makeWidget = new MakeInputWidget(callback);
    stackedWidgets->addWidget(makeWidget);

    setCentralWidget(stackedWidgets);
    stackedWidgets->setCurrentWidget(mainWidget);

}

void MainWindow::setMainWidget(){
    stackedWidgets->setCurrentWidget(mainWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeButtonClicked()
{
    stackedWidgets->setCurrentWidget(makeWidget);
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



