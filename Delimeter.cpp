#include "Delimeter.h"
#include <QPainter>

Delimeter::Delimeter(QWidget *parent) :
    QWidget(parent)
{
    setMinimumHeight(1);
    setMaximumHeight(1);
}

void Delimeter::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(164, 165, 161)));
    for (int x = 0; x < size().width(); x += 4)
    {
        painter.drawPoint(x, 0);
    }
}
