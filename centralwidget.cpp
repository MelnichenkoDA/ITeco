#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget * parent) :
    QWidget(parent)
{
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

    toggleOrderButton = new QRadioButton(tr("Desc"));
    toggleOrderButton->setChecked(true);

    connect(toggleOrderButton, SIGNAL(toggled(bool)), this, SLOT(togglerClicked()));
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

CentralWidget::~CentralWidget()
{

}

void CentralWidget::inputButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("Choose File"), "", tr("Text Files(*)", nullptr, QFileDialog::DontUseNativeDialog));
    inputPathLine->setText(filename);
}

void CentralWidget::outputButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("Choose File"), "", tr("Text Files(*)", nullptr, QFileDialog::DontUseNativeDialog));
    outputPathLine->setText(filename);
}

void CentralWidget::startButtonClicked()
{
    try {
        if (toggleOrderButton->isChecked()){
            sort<std::less<double>>(100000, inputPathLine->text().toStdString().c_str(), outputPathLine->text().toStdString().c_str());
        } else {
            sort<std::greater<double>>(100000, inputPathLine->text().toStdString().c_str(), outputPathLine->text().toStdString().c_str());
        }

        QMessageBox msgBox;
        msgBox.setText("Finished!");
        msgBox.exec();
    } catch (const std::exception & ex) {
        qInfo() << "CATCH EX" << ex.what();
    }
}

void CentralWidget::enableStartButton()
{
    startButton->setEnabled(inputPathLine->text().length() && outputPathLine->text().length());
}

void CentralWidget::togglerClicked()
{
    if (toggleOrderButton->isChecked()){
        toggleOrderButton->setText("Desc");
    } else {
        toggleOrderButton->setText("Asc");
    }
}

QLayout *CentralWidget::createLayout(QLayout *layout, QWidget *w1, QWidget *w2)
{
    layout->addWidget(w1);
    layout->addWidget(w2);
    return layout;
}
