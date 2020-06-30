#ifndef TESTINGWIDGET_H
#define TESTINGWIDGET_H

#include <QWidget>
#include <QtWidgets>

#include <fstream>


using callback = std::function<void ()>;

class TestingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestingWidget(callback func,
                           QWidget *parent = nullptr);

private slots:
    void browseButtonClicked();
    void runButtonCLicked();
    void returnButtonClicked(callback func);

private:
    QLabel * pathLabel;

    QLineEdit * pathLine;

    QPushButton * browseButton;
    QPushButton * runButton;
    QPushButton * returnButton;

    QRadioButton * toggleOrderButton;

};

#endif // TESTINGWIDGET_H
