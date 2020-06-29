#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void inputButtonClicked();
    void outputButtonClicked();
    void startButtonClicked();


private:
    QLayout * createLayout(QLayout* layout, QWidget * w1, QWidget * w2);
    QLayout * createLayout(QLayout* layout, QLayout * l1, QLayout * l2);
    Ui::MainWindow *ui;

    QLabel * inputLabel;
    QLabel * outputLabel;

    QLineEdit * inputPathLine;
    QLineEdit * outputPathLine;

    QPushButton * findInputButton;
    QPushButton * findOutputButton;
    QPushButton * startButton;

};
#endif // MAINWINDOW_H
