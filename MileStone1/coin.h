#ifndef COIN_H
#define COIN_H
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <cstdlib>
#include <time.h>
#include <QTimer>

class coin : public QObject, public QGraphicsPixmapItem
{
     Q_OBJECT
public:
    coin();
    static int count;
private:
    QPixmap * COIN1;
    QPixmap * COIN2;
    QPixmap * COIN3;
    QPixmap * COIN4;
    QPixmap * COIN5;
    QPixmap * COIN6;
    int controlimage=0;
    int todelete = 0;
    std::chrono::steady_clock::time_point before;
    std::chrono::steady_clock::time_point after;
public slots:
    void changeimage();
    void update();
};

#endif // COIN_H
