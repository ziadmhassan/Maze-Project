#ifndef PLAYER_H
#define PLAYER_H
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMediaPlayer>
#include<QTime>
#include <QtMultimedia>
#include <QMediaPlayer>
#include<QGraphicsView>
#include "map.h"
#include "coin.h"
#include "button.h"

class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:

    int Board[19][140];
    int bc = 3, br = 0;
    QMediaPlayer * s2 = new QMediaPlayer();
    Map * VIEW;
    bool up,down,right=true,left;
    QPixmap * PlayerRight;
    QPixmap * PlayerLeft;
    class shop : public QObject, public QGraphicsPixmapItem
    {
    public:
       shop()
       {
        QPixmap * tmp= new QPixmap("shop.png");
        *tmp=tmp->scaledToWidth(1000);
        *tmp=tmp->scaledToHeight(150);
        setPixmap(*tmp);
       }
    };
    shop * SHOP;
    QGraphicsRectItem * Window;
    bool storeOpen = 0;
    bool isMoving = 1;
    Button * restore;
    Button * upgrade;
    QGraphicsTextItem * restoretext;
    QGraphicsTextItem * upgradetext;


public:
    static int row;
    static int column;
    static int health;
    static int weapon;
    player(int [19][140], Map & V, QString);
    virtual ~player(){};
    QString name;


public slots:
    void keyPressEvent (QKeyEvent* event);
    void restoreHealth();
    void improveWeapon();
};
#endif // PLAYER_H
