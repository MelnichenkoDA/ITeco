#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwidget.h"
#include "makeinputwidget.h"


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
    void makeButtonClicked();
    void settingsButtonClicked();
    void testButtonClicked();

private:
    void createToolbar();
    void setMainWidget();

    QStackedWidget * stackedWidgets;
    MainWidget* mainWidget;
    MakeInputWidget * makeWidget;

    QToolBar * toolbar;
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H
