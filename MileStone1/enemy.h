#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <cstdlib>
#include <time.h>
#include <QTimer>
#include "shotgun.h"
#include "map.h"



class enemy : public QObject, public QGraphicsPixmapItem
{
     Q_OBJECT
public:
    enemy(int [19][140],int , int , int, Map & V);
    static int counter;
    static void changeMove();
    int row;
    int column;
    int movetype;
public slots:
    void move();
    void movetype2();
    void movetype3();
    void movetype4();
    void movetype5();
    void movetype6();
private:

    int Board[19][140];

    void COLLISION();
    Map * VIEW;
    QPixmap * SpiderRight;
    QPixmap * SpiderLeft;
    QPixmap * ZombieRight;
    QPixmap * ZombieLeft;
    QPixmap * Blaze;
    void findshortest();
    static bool isMoving;

};

#endif // ENEMY_H
