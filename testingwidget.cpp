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

    QHBoxLayout * pathLayout = new QHBoxLayout();
    pathLayout->addWidget(pathLabel);
    pathLayout->addWidget(pathLine);
    pathLayout->addWidget(browseButton);

    QHBoxLayout * runLayout = new QHBoxLayout();
    runLayout->addWidget(toggleOrderButton);
    runLayout->addWidget(runButton);

    QVBoxLayout * main = new QVBoxLayout;
    main->addLayout(pathLayout);
    main->addLayout(runLayout);
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

        bool ok = true;
        double prev, current;
        file >> prev;

        while (file >> current){
            if (toggleOrderButton->isChecked()){
                if (prev < current){
                    ok = false;
                    break;
                }
            } else {
                if (prev > current){
                    ok = false;
                    break;
                }
            }
        }

        if (ok){
            QMessageBox msgBox(this);
            msgBox.setText("Numbers are sorted!");
            msgBox.exec();
        } else {
            QMessageBox msgBox;
            msgBox.setText("Numbers aren't sorted!");
            msgBox.exec();
        }
    } catch (const std::exception & ex) {
        QMessageBox msgBox;
        msgBox.setText(ex.what());
        msgBox.exec();
    }
}

void TestingWidget::returnButtonClicked(callback func)
{
    func();
}
