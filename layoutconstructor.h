#ifndef LAYOUTCONSTRUCTOR_H
#define LAYOUTCONSTRUCTOR_H

#include <QtWidgets>

class LayoutConstructor
{
public:
    LayoutConstructor() = delete;

    static QLayout* construct(QLayout * layout, QWidget * w1,
                                    QWidget * w2 = nullptr, QWidget * w3 = nullptr);

    static QLayout* construct(QLayout * layout, QLayout * l1,
                              QLayout * l2 = nullptr, QLayout * l3 = nullptr);
};

#endif // LAYOUTCONSTRUCTOR_H
