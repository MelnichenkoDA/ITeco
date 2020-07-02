#include "mainwidget.h"

MainWidget::MainWidget(QWidget * parent) :
    QWidget(parent)
{
    inputLabel = new QLabel(tr("Input path"));
    outputLabel = new QLabel(tr("Output path"));
    memoryLimitLabel = new QLabel(tr("Memory limit"));

    inputPathLine = new QLineEdit;
    inputLabel->setBuddy(inputPathLine);

    memoryLimitLine = new QLineEdit();
    memoryLimitLine->setText("10000");
    connect(memoryLimitLine, SIGNAL(textChanged(const QString &)), this, SLOT(memoryLimitChanged(const QString& )));
    memoryLimitLabel->setBuddy(memoryLimitLine);

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

    progressBar = new QProgressBar();
    progressBar->setValue(0);
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);

    QHBoxLayout * inputLayout = static_cast<QHBoxLayout*>(
                LayoutConstructor::construct(new QHBoxLayout, inputLabel, inputPathLine, findInputButton));

    QHBoxLayout * outputLayout = static_cast<QHBoxLayout*>(
                LayoutConstructor::construct(new QHBoxLayout(), outputLabel, outputPathLine, findOutputButton));

    QHBoxLayout * startLayout = static_cast<QHBoxLayout*>(
                LayoutConstructor::construct(new QHBoxLayout(), toggleOrderButton, startButton));

    QHBoxLayout * limitLayout = static_cast<QHBoxLayout*>(
                LayoutConstructor::construct(new QHBoxLayout(), memoryLimitLabel, memoryLimitLine));

    QVBoxLayout * main = LayoutConstructor::construct(new QVBoxLayout, inputLayout, outputLayout, limitLayout);
    main->addLayout(startLayout);
    main->addWidget(progressBar);

    setLayout(main);
}

MainWidget::~MainWidget()
{

}

void MainWidget::inputButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("Choose File"), "", tr("Text Files(*)", nullptr, QFileDialog::DontUseNativeDialog));
    inputPathLine->setText(filename);
}

void MainWidget::outputButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("Choose File"), "", tr("Text Files(*)", nullptr, QFileDialog::DontUseNativeDialog));
    outputPathLine->setText(filename);
}

void MainWidget::startButtonClicked()
{
    try {
        progressBar->setValue(0);
        bool ok = true;

        int limit = memoryLimitLine->text().toInt(&ok);
        if (!ok){
            throw std::runtime_error("Wrong memory limit format (Only digits allowed)!");
        }

        std::function<void (int)> callback = std::bind(&MainWidget::updateProgressBar, this, std::placeholders::_1);
        if (toggleOrderButton->isChecked()){
            sort<std::less<double>>(limit, inputPathLine->text().toStdString().c_str(),
                                    outputPathLine->text().toStdString().c_str(), callback);
        } else {
            sort<std::greater<double>>(limit, inputPathLine->text().toStdString().c_str(),
                                       outputPathLine->text().toStdString().c_str(), callback);
        }
        progressBar->setValue(100);

        MyMessageBox("Sorting have finished!", this);
    } catch (const std::exception & ex) {
        MyMessageBox(ex.what(), this);
    }
}

void MainWidget::enableStartButton()
{
    startButton->setEnabled(inputPathLine->text().length() && outputPathLine->text().length());
}

void MainWidget::togglerClicked()
{
    if (toggleOrderButton->isChecked()){
        toggleOrderButton->setText("Desc");
    } else {
        toggleOrderButton->setText("Asc");
    }
}

void MainWidget::memoryLimitChanged(const QString & text)
{
    bool ok = true;
    text.toInt(&ok);
    if (!ok){
        memoryLimitLine->setText("");
    }
}

void MainWidget::updateProgressBar(int value)
{
    progressBar->setValue(progressBar->value() + value);
}
