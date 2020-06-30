#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QMessageBox>

class MyMessageBox
{

public:
    MyMessageBox(QString text, QWidget * parent = nullptr);
    ~MyMessageBox();

private:
    QMessageBox * messageBox;
};

#endif // MYMESSAGEBOX_H
