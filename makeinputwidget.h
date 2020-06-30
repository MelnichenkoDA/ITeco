#ifndef MAKEINPUTWIDGET_H
#define MAKEINPUTWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <fstream>

class MakeInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MakeInputWidget(QWidget *parent = nullptr);

signals:

private slots:
    void browseButtonClicked();
    void enableGenerateButton();
    void generateButtonClicked();
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
