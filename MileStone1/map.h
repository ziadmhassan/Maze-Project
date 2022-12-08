#ifndef MAP_H
#define MAP_H
#include "button.h"
#include <QGraphicsView>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <QTime>
#include <cstdlib>
#include <time.h>
#include <QMediaPlayer>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsRectItem>


class Map : public QGraphicsView
{
    Q_OBJECT
public:
    Map(QString, QString);
    void updateHealth();
    QGraphicsScene * scene;
    int boarddata[19][140];
    QGraphicsPixmapItem * * dataimage;
    QPixmap * grass ;
    QPixmap * dirt;
    QPixmap * door;
    QPixmap * halfd;
    QPixmap * lava;
    QPixmap * floor;
    QPixmap * gold;
    QPixmap * sbrick;
    QPixmap * sgrass;
    QPixmap * health;
    QPixmap * YOUWIN;
    QPixmap * GAMEOVER;
    QGraphicsTextItem * coinCount;
    QString Pname;
    Button * quit;
    Button * playAgain;
    class GameOver : public QObject, public QGraphicsPixmapItem
    {
    public:
       GameOver()
       {QPixmap * tmp= new QPixmap("GAMEOVER.png");
        *tmp=tmp->scaledToWidth(600);
        *tmp=tmp->scaledToHeight(235);
        setPixmap(*tmp);
       }
    };
    class YouWin : public QObject, public QGraphicsPixmapItem
    {
    public:
    YouWin()
    {QPixmap * tmp= new QPixmap("YOUWON.png");
    *tmp=tmp->scaledToWidth(600);
    *tmp=tmp->scaledToHeight(235);
    setPixmap(*tmp);
    }
   };
    GameOver * Lost;
    YouWin * Won;
    QGraphicsRectItem * Window;


    void displayendgamewindow(bool winorlose);
public slots:
    void start();
    void exitgame();
    void restartgamewon();
    void restartgamelost();


private:

};

#endif // Map_H
