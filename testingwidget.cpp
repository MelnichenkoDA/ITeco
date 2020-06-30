#include "testingwidget.h"

TestingWidget::TestingWidget(callback func, QWidget *parent) : QWidget(parent)
{
    pathLabel = new QLabel(tr("Path to the file"));

    pathLine = new QLineEdit();
    pathLabel->setBuddy(pathLine);

    browseButton = new QPushButton(tr("Browse..."));
    connect(browseButton, &QPushButton::clicked, this, &TestingWidget::browseButtonClicked);

    runButton = new QPushButton(tr("Run"));
    connect(runButton, &QPushButton::clicked, this, &TestingWidget::runButtonCLicked);

    returnButton = new QPushButton(tr("Back"));
    connect(returnButton, &QPushButton::clicked, this, std::bind(&TestingWidget::returnButtonClicked, this, func));

}

void TestingWidget::browseButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("Choose File"), "", tr("Text Files(*)", nullptr, QFileDialog::DontUseNativeDialog));
    pathLine->setText(filename);
}

void TestingWidget::runButtonCLicked()
{

}

void TestingWidget::returnButtonClicked(callback func)
{
    func();
}
