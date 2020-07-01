#include "makeinputwidget.h"

MakeInputWidget::MakeInputWidget(std::function<void ()> callback,
                                 QWidget *parent) : QWidget(parent)
{
    pathLabel = new QLabel(tr("Path to the file"));

    pathLine = new QLineEdit();
    connect(pathLine, &QLineEdit::textChanged, this, &MakeInputWidget::enableGenerateButton);

    browseButton = new QPushButton(tr("Browse..."));
    connect(browseButton, &QPushButton::clicked, this, &MakeInputWidget::browseButtonClicked);

    QHBoxLayout* pathLayout = static_cast<QHBoxLayout*>(
                LayoutConstructor::construct(new QHBoxLayout, pathLabel, pathLine, browseButton));

    countLabel = new QLabel(tr("Count of numbers"));

    countLine = new QLineEdit();
    connect(countLine, &QLineEdit::textChanged, this, &MakeInputWidget::enableGenerateButton);

    generateButton = new QPushButton(tr("Generate"));
    generateButton->setEnabled(false);
    connect(generateButton, &QPushButton::clicked, this, &MakeInputWidget::generateButtonClicked);

    QHBoxLayout* generateLayout = static_cast<QHBoxLayout*>(
                LayoutConstructor::construct(new QHBoxLayout, countLabel, countLine, generateButton));

    backButton = new QPushButton(tr("Back"));
    connect(backButton, &QPushButton::clicked, this, std::bind(&MakeInputWidget::backButtonClicked, this, callback));

    QVBoxLayout * main = static_cast<QVBoxLayout*>(
                LayoutConstructor::construct(new QVBoxLayout(this), pathLayout, generateLayout));
    main->addWidget(backButton);

    setLayout(main);
}

void MakeInputWidget::browseButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("Choose File"), "", tr("Text Files(*)", nullptr, QFileDialog::DontUseNativeDialog));
    pathLine->setText(filename);
}

void MakeInputWidget::enableGenerateButton()
{
    generateButton->setEnabled(pathLine->text().length() && countLine->text().length());
}

void MakeInputWidget::generateButtonClicked()
{

    try {
        bool ok = true;
        double count = countLine->text().toDouble(&ok);
        if (!ok){
            throw std::runtime_error("Wrong numbers count format");
        }

        std::ofstream output(pathLine->text().toStdString());

        if (!output.is_open()){
            std::string message("Couldn't open file ");
            throw std::runtime_error(message + pathLine->text().toStdString());
        }

        for (; count > 0; --count){
            output << makeRandom() << " ";
        }

        MyMessageBox("The file have finished!", this);
    } catch (const std::exception & ex) {
        MyMessageBox(ex.what(), this);
    }

}

void MakeInputWidget::backButtonClicked(std::function<void ()> callback)
{
    pathLine->setText("");
    countLine->setText("");
    callback();
}

double MakeInputWidget::makeRandom()
{
    return double(rand()) / double(rand()) * 10 - 100;
}


