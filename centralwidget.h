#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include "sorter.hpp"
#include <QtWidgets>

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    CentralWidget(QWidget * paren = nullptr);
    virtual ~CentralWidget();
private slots:
    void inputButtonClicked();
    void outputButtonClicked();
    void startButtonClicked();
    void enableStartButton();
    void togglerClicked();

private:
    QLayout * createLayout(QLayout* layout, QWidget * w1, QWidget * w2);

    QLabel * inputLabel;
    QLabel * outputLabel;

    QLineEdit * inputPathLine;
    QLineEdit * outputPathLine;

    QPushButton * findInputButton;
    QPushButton * findOutputButton;
    QPushButton * startButton;

    QRadioButton * toggleOrderButton;
};

#endif // CENTRALWIDGET_H
