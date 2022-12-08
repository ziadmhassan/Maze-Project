#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(QString buttonname)
{
    setRect(0,0,250,75);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBrush(brush);

    text = new QGraphicsTextItem(buttonname,this);
    text->setDefaultTextColor(Qt::white);
    int x = rect().width()/2 - text->boundingRect().width()/2;
    int y = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(x,y);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}


