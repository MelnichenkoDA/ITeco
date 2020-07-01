#include "layoutconstructor.h"


QLayout *LayoutConstructor::construct(QLayout * layout, QWidget *w1,
                                            QWidget *w2, QWidget *w3)
{
    layout->addWidget(w1);
    if (w2){
        layout->addWidget(w2);
        if (w3)
            layout->addWidget(w3);
    }
    return layout;
}

QVBoxLayout *LayoutConstructor::construct(QVBoxLayout *layout, QHBoxLayout *l1,
                                          QHBoxLayout *l2, QHBoxLayout *l3)
{
    layout->addLayout(l1);
    if (l2){
        layout->addLayout(l2);
        if (l3)
            layout->addLayout(l3);
    }
    return layout;
}
