#include "layoutconstructor.h"


QLayout *LayoutConstructor::construct(QLayout * layout, QWidget *w1,
                                            QWidget *w2, QWidget *w3)
{
    layout->addWidget(w1);
    if (w2)
        layout->addWidget(w2);
    if (w3)
        layout->addWidget(w3);

    return layout;
}

QLayout *LayoutConstructor::construct(QLayout *layout, QLayout *l1, QLayout *l2, QLayout *l3)
{

}
