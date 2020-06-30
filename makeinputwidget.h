#ifndef MAKEINPUTWIDGET_H
#define MAKEINPUTWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <fstream>

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
};

#endif // MAKEINPUTWIDGET_H
