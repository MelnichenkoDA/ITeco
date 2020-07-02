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
    void updateProgressBar(int value);

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

    QProgressBar * progressBar;
};

#endif // CENTRALWIDGET_H
