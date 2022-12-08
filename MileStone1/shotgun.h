#ifndef SHOTGUN_H
#define SHOTGUN_H
#include<QGraphicsPixmapItem>
#include<QGraphicsScene>
#include <QTimer>
#include "player.h"
#include "map.h"

class ShotGun : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ShotGun(int [19][140], int row, int col,bool,bool,bool,bool,bool,Map & V);
public slots:
    void moveprojectile();
private:
    int Board[19][140];
    int * DataIMage;
    int rowS;
    int colS;
    bool up,down,right,left,ISPLAYER;
    Map * VIEW;
    QPixmap * FireBall;
    QPixmap * GBall;
};

#endif // SHOTGUN_H
