#ifndef MAKEINPUTWIDGET_H
#define MAKEINPUTWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <fstream>
#include <cmath>
#include "mymessagebox.h"
#include "layoutconstructor.h"


class MakeInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MakeInputWidget(std::function<void ()> callback, QWidget *parent = nullptr);

signals:

private slots:
    void browseButtonClicked();
    void enableGenerateButton();
    void generateButtonClicked();
    void backButtonClicked(std::function<void ()> callback);

private:
    double makeRandom();

    QLabel * pathLabel;
    QLabel * countLabel;

    QLineEdit * pathLine;
    QLineEdit* countLine;

    QPushButton * browseButton;
    QPushButton * generateButton;
    QPushButton * backButton;

    QProgressBar* progressBar;
};

#endif // MAKEINPUTWIDGET_H
