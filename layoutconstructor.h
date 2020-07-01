#ifndef LAYOUTCONSTRUCTOR_H
#define LAYOUTCONSTRUCTOR_H

#include <QtWidgets>

class LayoutConstructor
{
public:
    LayoutConstructor() = delete;

    static QLayout* construct(QLayout * layout, QWidget * w1,
                                    QWidget * w2 = nullptr, QWidget * w3 = nullptr);

    static QVBoxLayout* construct(QVBoxLayout * layout, QHBoxLayout * l1,
                              QHBoxLayout * l2 = nullptr, QHBoxLayout * l3 = nullptr);
};

#endif // LAYOUTCONSTRUCTOR_H
