#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QRadioButton>
#include <QDebug>
#include <QMessageBox>

#include "Sorter.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void inputButtonClicked();
    void outputButtonClicked();
    void startButtonClicked();
    void enableStartButton();

private:
    QLayout * createLayout(QLayout* layout, QWidget * w1, QWidget * w2);

    Ui::MainWindow *ui;

    QLabel * inputLabel;
    QLabel * outputLabel;

    QLineEdit * inputPathLine;
    QLineEdit * outputPathLine;

    QPushButton * findInputButton;
    QPushButton * findOutputButton;
    QPushButton * startButton;

    QRadioButton * toggleOrderButton;

};
#endif // MAINWINDOW_H
