#include "mymessagebox.h"


MyMessageBox::MyMessageBox(QString text, QWidget * parent)
{
    messageBox = new QMessageBox(parent);
    messageBox->setText(text);
    messageBox->exec();
}

MyMessageBox::~MyMessageBox()
{
    delete messageBox;
}
