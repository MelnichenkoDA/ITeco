#include "makeinputwidget.h"

MakeInputWidget::MakeInputWidget(std::function<void ()> callback,
                                 QWidget *parent) : QWidget(parent)
{
    QGridLayout * main = new QGridLayout(this);

    pathLabel = new QLabel(tr("Path to the file"));
    main->addWidget(pathLabel, 0, 0);

    pathLine = new QLineEdit();
    connect(pathLine, &QLineEdit::textChanged, this, &MakeInputWidget::enableGenerateButton);
    main->addWidget(pathLine, 0, 1);

    browseButton = new QPushButton(tr("Browse..."));
    connect(browseButton, &QPushButton::clicked, this, &MakeInputWidget::browseButtonClicked);
    main->addWidget(browseButton, 0, 2);

    countLabel = new QLabel(tr("Count of numbers"));
    main->addWidget(countLabel, 1, 0);

    countLine = new QLineEdit();
    connect(countLine, &QLineEdit::textChanged, this, &MakeInputWidget::enableGenerateButton);
    main->addWidget(countLine, 1, 1);

    generateButton = new QPushButton(tr("Generate"));
    generateButton->setEnabled(false);
    connect(generateButton, &QPushButton::clicked, this, &MakeInputWidget::generateButtonClicked);
    main->addWidget(generateButton);

    backButton = new QPushButton(tr("Ok"));
    connect(backButton, &QPushButton::clicked, this, std::bind(&MakeInputWidget::backButtonClicked, this, callback));
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
    double count = 0;
    std::ofstream output(pathLine->text().toStdString());
    try {
        count = countLine->text().toDouble();

        if (!output.is_open()){
            std::string message("Couldn't open file ");
            throw std::runtime_error(message + pathLine->text().toStdString());
        }

    } catch (const std::exception & ex) {
        QMessageBox msgBox;
        msgBox.setText(ex.what());
        msgBox.exec();
    }
    for (; count > 0; --count){
        output << makeRandom() << " ";
    }

    QMessageBox msgBox;
    msgBox.setText("Finished");
    msgBox.exec();
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


