#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include "sorter.hpp"
#include <QtWidgets>

#include "mymessagebox.h"
#include "layoutconstructor.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget(QWidget * paren = nullptr);
    virtual ~MainWidget();
private slots:
    void inputButtonClicked();
    void outputButtonClicked();
    void startButtonClicked();

    void enableStartButton();
    void togglerClicked();

    void memoryLimitChanged(const QString & );

private:
    QLayout * createLayout(QLayout* layout, QWidget * w1, QWidget * w2);

    QLabel * inputLabel;
    QLabel * outputLabel;
    QLabel * memoryLimitLabel;

    QLineEdit * inputPathLine;
    QLineEdit * outputPathLine;
    QLineEdit * memoryLimitLine;

    QPushButton * findInputButton;
    QPushButton * findOutputButton;
    QPushButton * startButton;

    QRadioButton * toggleOrderButton;
};

#endif // CENTRALWIDGET_H
