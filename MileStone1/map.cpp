#include "map.h"
#include "mainwindow.h"
#include "player.h"
#include "enemy.h"
#include <QPushButton>
#include "boss.h"
#include "coin.h"

using namespace std;

QFont serifFont("Helvatica", 25, QFont::Bold);

Map::Map(QString BoardName, QString PNAME)

{
    this->setDragMode(QGraphicsView::NoDrag);
    srand(time(NULL));
    Pname=PNAME;
    scene = new QGraphicsScene;
    setFixedSize(1400,770);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Turn off the scroll bars
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Turn off the scroll bars
    setWindowTitle("Maze 1");
    QBrush * brush= new QBrush(Qt::black);
    setBackgroundBrush(*brush);
    QFile * file= new QFile(BoardName);
        file->open(QIODevice::ReadOnly);


        QTextStream stream(file);
        QString temp;

        for (int i=0;i<19;i++)
            for (int j=0;j<140;j++)
            {
             stream>>temp;
             boarddata[i][j]=temp.toInt();
            }
        dataimage = new QGraphicsPixmapItem * [19];

        for(int i(0);i<19;i++)
           dataimage[i]= new QGraphicsPixmapItem [140];

        grass = new QPixmap("grass.png");
        dirt  = new QPixmap("dirt.png");
        door  = new QPixmap("door.png");
        halfd = new QPixmap("halfd.png");
        lava  = new QPixmap("lava.jpeg");
        floor = new QPixmap("netherrack.png");
        gold  = new QPixmap("gold.png");
        sbrick = new QPixmap("sbrickdark.png");
        sgrass = new QPixmap("sgrass.png");

        *grass=grass->scaledToWidth(40);
        *grass=grass->scaledToHeight(40);
        *dirt=dirt->scaledToWidth(40);
        *dirt=dirt->scaledToHeight(40);
        *halfd=halfd->scaledToWidth(40);
        *halfd=halfd->scaledToHeight(40);
        *lava=lava->scaledToWidth(40);
        *lava=lava->scaledToHeight(40);
        *floor=floor->scaledToWidth(40);
        *floor=floor->scaledToHeight(40);
        *gold=gold->scaledToWidth(40);
        *gold=gold->scaledToHeight(40);
        *sbrick=sbrick->scaledToWidth(40);
        *sbrick=sbrick->scaledToHeight(40);
        *sgrass=sgrass->scaledToWidth(40);
        *sgrass=sgrass->scaledToHeight(40);
        *door=door->scaledToWidth(40);
        *door=door->scaledToHeight(40);

        for (int i=0;i<19;i++)
            for (int j=0;j<140;j++)
            {
                if(boarddata[i][j]==1)
                    (*(*(dataimage+i)+j)).setPixmap(*grass);
                else if(boarddata[i][j]==0)
                    (*(*(dataimage+i)+j)).setPixmap(*dirt);
                else if(boarddata[i][j]==2)
                    (*(*(dataimage+i)+j)).setPixmap(*door);
                else if(boarddata[i][j]==3)
                    (*(*(dataimage+i)+j)).setPixmap(*halfd);
                else if(boarddata[i][j]==4)
                    (*(*(dataimage+i)+j)).setPixmap(*lava);
                else if(boarddata[i][j]==5)
                    (*(*(dataimage+i)+j)).setPixmap(*floor);
                else if(boarddata[i][j]==6)
                    (*(*(dataimage+i)+j)).setPixmap(*gold);
                else if(boarddata[i][j]==7)
                    (*(*(dataimage+i)+j)).setPixmap(*sgrass);
                else if(boarddata[i][j]==8)
                    (*(*(dataimage+i)+j)).setPixmap(*sbrick);

                (*(*(dataimage+i)+j)).setPos(40+40*j,40+40*i);
               scene->addItem((*(dataimage+i)+j));
            }


        this->show(); // We show the maze we created on the screen
        this->centerOn(0, 0); //Show map #1

        qDebug() << Pname;
        coinCount= new QGraphicsTextItem;
        coinCount=scene->addText(("Coin count: " + QString::number(coin::count)));
        coinCount->setPos(500, 35);
        coinCount->setFont(serifFont);
        coinCount->setDefaultTextColor(Qt::white);

        setScene(scene);
        start();

}
void Map::start()
{
    //coin::coinCount = scene->addText("coin count: ");
    int n=scene->items().size();
    for(int i=0; i<n ;i++)
    {
        scene->items()[i]->setEnabled(true);
    }
    this->centerOn(0,0);
    player * PL = new player(boarddata, *this, Pname);
    // Create a new player object
    scene->addItem(PL); // Add the player object to the scene

    PL->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    PL->setFocus();



    if(enemy::counter<12){enemy * E1 = new enemy(boarddata,17,5,1, *this);scene->addItem(E1);}
    if(enemy::counter<12){enemy * E2 = new enemy(boarddata,3,32,1, *this);scene->addItem(E2);}
    if(enemy::counter<12){enemy * E3 = new enemy(boarddata,9,21,1, *this);scene->addItem(E3);}
    if(enemy::counter<12){enemy * E4 = new enemy(boarddata,1,40,2, *this);scene->addItem(E4);}
    if(enemy::counter<12){enemy * E5 = new enemy(boarddata,7,49,2, *this);scene->addItem(E5);}
    if(enemy::counter<12){enemy * E6 = new enemy(boarddata,10,60,2, *this);scene->addItem(E6);}
    if(enemy::counter<12){enemy * E7 = new enemy(boarddata,11,101,3, *this);scene->addItem(E7);}
    if(enemy::counter<12){enemy * E8 = new enemy(boarddata,8,89,3, *this);scene->addItem(E8);}
    if(enemy::counter<12){enemy * E9 = new enemy(boarddata,2,75,3, *this);scene->addItem(E9);}
    if(enemy::counter<12){enemy * E10 = new enemy(boarddata,11,95,4, *this);scene->addItem(E10);}
    if(enemy::counter<12){enemy * E11 = new enemy(boarddata,8,75,4, *this);scene->addItem(E11);}
    if(enemy::counter<12){enemy * E12 = new enemy(boarddata,2,80,4, *this);scene->addItem(E12);}




     health= new QPixmap("heart.png");
            *health=health->scaledToWidth(40);
            *health=health->scaledToHeight(40);

    for(int i = 0; i < 140; i+= 35)
           {
               QGraphicsTextItem *name = scene->addText(Pname);
               name->setPos(900 + 1440 * (i/35), 35);
               name->setFont(serifFont);
               name->setDefaultTextColor(Qt::white);
               for(int j = 1; j < 4; ++j)
               {
                                  QGraphicsPixmapItem * HEALTH = new QGraphicsPixmapItem;
                                  HEALTH->setPixmap(*health);
                                  scene->addItem(HEALTH);
                                  HEALTH->setPos(40 * (i+j) + 120,40);
               }
           }
    PL->setFocus();
}
void Map::displayendgamewindow(bool winorlose)
{
    int k = 0;
    if(player::column <= 35)
        k = 0;
    else if(player::column <= 70)
        k = 1;
    else if(player::column <= 105)
        k = 2;
    else
        k = 3;

    int n=scene->items().size();
    if(winorlose)
    {
        for(int i=0; i<n ;i++)
        {
            if(typeid(*(scene->items()[i]))==typeid(player))
            {delete scene->items()[i];}
            n=scene->items().size();
        }
        Won = new YouWin;
        scene->addItem(Won);
        Won->setPos(510 + 1400 * k,225);
    }
    else
    {
        Lost = new GameOver;
        scene->addItem(Lost);
        Lost->setPos(510 + 1400 * k, 225);
    }

    for(int i=0; i<n ;i++)
    {
        scene->items()[i]->setEnabled(false);
    }

    QBrush BlackBrush(Qt::black);
    QPen BlackPen(Qt::black);
    Window = new QGraphicsRectItem(QRect(440 + 1400 * k,125 ,600,600));
    Window->setBrush(BlackBrush);
    Window->setOpacity(0.5);
    scene->addItem(Window);
    playAgain = new Button (QString("Play Again"));
    playAgain->setPos(480 + 1400 * k,600);
    scene->addItem(playAgain);
    quit = new Button (QString("Exit"));
    quit->setPos(750 + 1400 * k,600);
    scene->addItem(quit);
    if(winorlose){connect(playAgain,SIGNAL(clicked()),this,SLOT(restartgamewon()));}else{connect(playAgain,SIGNAL(clicked()),this,SLOT(restartgamelost()));}
    connect(quit,SIGNAL(clicked()),this,SLOT(exitgame()));


}



void Map::exitgame()
{
    exit(0);
}

void Map::restartgamelost()
{
QList<QGraphicsItem *> toFindBoss= scene->items();
int size=toFindBoss.size();
for(int k = 0; k < size; ++k)
    {
        if(typeid(*(toFindBoss[k])) == typeid(boss) || typeid(*(toFindBoss[k])) == typeid(enemy))
            delete toFindBoss[k];
        size=toFindBoss.size();
}
enemy::counter=0;
boss::bosshealth=4;
player::health = 3;
boss::count = 0;
scene->removeItem(Window);
scene->removeItem(playAgain);
scene->removeItem(quit);
scene->removeItem(Lost);
coinCount->setPos(500, 35);
delete Lost;
delete Window;
delete playAgain;
delete quit;
start();
}

void Map::restartgamewon()
{
    QList<QGraphicsItem *> toFindBoss= scene->items();
    int size=toFindBoss.size();
    for(int k = 0; k < size; ++k)
        {
            if(typeid(*(toFindBoss[k])) == typeid(boss) || typeid(*(toFindBoss[k])) == typeid(enemy))
                delete toFindBoss[k];
            size=toFindBoss.size();
        }
enemy::counter=0;
boss::bosshealth=4;
player::health = 3;
boss::count = 0;
scene->removeItem(Window);
scene->removeItem(playAgain);
scene->removeItem(quit);
scene->removeItem(Won);
coinCount->setPos(500, 35);
delete Won;
delete Window;
delete playAgain;
delete quit;
start();
}


