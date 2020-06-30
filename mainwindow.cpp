#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle("Sorter");


    inputLabel = new QLabel(tr("Input path"));
    outputLabel = new QLabel(tr("Output path"));

    inputPathLine = new QLineEdit;
    inputLabel->setBuddy(inputPathLine);

    outputPathLine = new QLineEdit;
    outputLabel->setBuddy(outputPathLine);    

    connect(inputPathLine, SIGNAL(textChanged(QString)), this, SLOT(enableStartButton()));
    connect(outputPathLine, SIGNAL(textChanged(QString)), this, SLOT(enableStartButton()));

    findInputButton = new QPushButton(tr("Choose..."));
    findInputButton->setDefault(true);
    connect(findInputButton, SIGNAL(clicked()), this, SLOT(inputButtonClicked()));

    findOutputButton = new QPushButton(tr("Choose..."));
    connect(findOutputButton, SIGNAL(clicked()), this, SLOT(outputButtonClicked()));

    startButton = new QPushButton(tr("Start"));
    startButton->setEnabled(false);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));

    toggleOrderButton = new QRadioButton(tr("Toggle order"));
    connect(toggleOrderButton, SIGNAL(toggled(bool)), this, SLOT(makeClicked()));
    QHBoxLayout * inputLayout = static_cast<QHBoxLayout*>(createLayout(new QHBoxLayout(), inputLabel, inputPathLine));
    inputLayout->addWidget(findInputButton);

    QHBoxLayout * outputLayout = static_cast<QHBoxLayout*>(createLayout(new QHBoxLayout(), outputLabel, outputPathLine));
    outputLayout->addWidget(findOutputButton);

    QHBoxLayout * startLayout = static_cast<QHBoxLayout*>(createLayout(new QHBoxLayout(), toggleOrderButton, startButton));

    QVBoxLayout * main = new QVBoxLayout;
    main->addLayout(inputLayout);
    main->addLayout(outputLayout);
    main->addLayout(startLayout);

    setLayout(main);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inputButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("Choose File"), "", tr("Text Files(*)", nullptr, QFileDialog::DontUseNativeDialog));
    inputPathLine->setText(filename);
}

void MainWindow::outputButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("Choose File"), "", tr("Text Files(*)", nullptr, QFileDialog::DontUseNativeDialog));
    outputPathLine->setText(filename);
}

void MainWindow::startButtonClicked()
{
    try {
        //if (toggleOrderButton->getContentsMargins())
        sort<std::greater<double>>(1000, inputPathLine->text().toStdString().c_str(), outputPathLine->text().toStdString().c_str());
        QMessageBox msgBox;
        msgBox.setText("Finished!");
        msgBox.exec();
    } catch (const std::exception & ex) {
        qInfo() << "CATCH EX" << ex.what();
    }
}

QLayout *MainWindow::createLayout(QLayout *layout, QWidget *w1, QWidget *w2){
    layout->addWidget(w1);
    layout->addWidget(w2);
    return layout;
}

void MainWindow::enableStartButton()
{
    startButton->setEnabled(inputPathLine->text().length() && outputPathLine->text().length());
}

void MainWindow::makeClicked()
{

}

