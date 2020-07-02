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

    toggleOrderButton = new QRadioButton(tr("Desc"));
    toggleOrderButton->setChecked(true);
    connect(toggleOrderButton, &QPushButton::clicked, this, &TestingWidget::toggleButtonClicked);

    progressBar = new QProgressBar;
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->setValue(0);

    QHBoxLayout * pathLayout = static_cast<QHBoxLayout*>(
                LayoutConstructor::construct(new QHBoxLayout, pathLabel, pathLine, browseButton));

    QHBoxLayout * runLayout = static_cast<QHBoxLayout*>(
                LayoutConstructor::construct(new QHBoxLayout, toggleOrderButton, runButton));

    QVBoxLayout * main = LayoutConstructor::construct(new QVBoxLayout, pathLayout, runLayout);
    main->addWidget(progressBar);
    main->addWidget(returnButton);

    setLayout(main);
}

void TestingWidget::browseButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("Choose File"), "", tr("Text Files(*)", nullptr, QFileDialog::DontUseNativeDialog));
    pathLine->setText(filename);
}

void TestingWidget::runButtonCLicked()
{
    try {
        std::ifstream file(pathLine->text().toStdString());

        if (!file.is_open()){
            std::string error("Couldn't open file: ");
            throw  std::runtime_error(error + pathLine->text().toStdString());
        }

        std::function<bool (double, double)> comparator;
        if (toggleOrderButton->isChecked()){
            comparator = std::less_equal<double>();
        } else {
            comparator = std::greater_equal<double>();
        }

        double current, count = 0;
        while(file >> current){
            ++count;
        }

        file.clear();
        file.seekg(0, std::ios::beg);

        double prev;
        file >> prev;

        for (double temp = 0; file >> current; ++temp){
            progressBar->setValue(int((temp / count) * 100));
            if (comparator(prev, current)){
                MyMessageBox box("Numbers arent sorted!", this);
                return;
            }
        }

        progressBar->setValue(100);
        MyMessageBox box("Numbers are sorted", this);
    } catch (const std::exception & ex) {
        MyMessageBox box(ex.what(), this);
    }
}

void TestingWidget::returnButtonClicked(callback func)
{
    pathLine->setText("");
    toggleOrderButton->setChecked(true);
    progressBar->setValue(0);
    func();
}

void TestingWidget::toggleButtonClicked()
{
    if(toggleOrderButton->isChecked()){
        toggleOrderButton->setText("Desc");
    } else {
        toggleOrderButton->setText("Asc");
    }
}
