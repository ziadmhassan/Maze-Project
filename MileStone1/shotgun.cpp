#include "shotgun.h"
#include "enemy.h"
#include <QtMultimedia>
#include <QMediaPlayer>
#include "winlosedialog.h"
#include "boss.h"


ShotGun::ShotGun(int TMPBoard [19][140], int newrow, int newcol,bool upp,bool downn, bool rightt,bool leftt, bool ISPlayer, Map & V): VIEW (&V)
{

    for(int i(0);i<19;i++)
     for(int j(0);j<140;j++)
         Board[i][j]=TMPBoard[i][j]; // Each projectile will have its own copy of the map board so that it can stop before hitting a wall

         rowS =newrow; colS=newcol; // Take the current coordinates of the player object and put them in each new projectile's object


        if(ISPlayer)
        { GBall= new QPixmap("gball.png");
          *GBall=GBall->scaledToWidth(15);
          *GBall=GBall->scaledToHeight(15);
           setPixmap(*GBall);}
        else
        {
             FireBall= new QPixmap("fireball.png");
            *FireBall=FireBall->scaledToWidth(15);
            *FireBall=FireBall->scaledToHeight(15);
             setPixmap(*FireBall);
        } // Set the photo of the projectile
        QTimer * timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(moveprojectile())); // Connect the signal from the space bar with the move function
        timer->start(35); // repeat the funtion to move the projectile each 35 milliseconds
        up=upp;down=downn;left=leftt;right=rightt;ISPLAYER=ISPlayer;

}
void ShotGun::moveprojectile()
{
         if(right)
         {
         if(colS==104){scene()->removeItem(this);delete this;}
         else
         {
         setPos(x()+40, y()); // move the projectile by 40 pixels each time
         colS++;
         }

         }
         else if(left)
         {
         if(colS==0){scene()->removeItem(this);delete this;}
         else
         {
         setPos(x()-40, y()); // move the projectile by 40 pixels each time
         colS--;
         }
         qDebug() << "MOVE PROJECTILE" << Qt::endl <<rowS << Qt::endl << colS;
         }else if(up)
         {
         if(rowS==0){scene()->removeItem(this);delete this;}
         else
         {
         setPos(x(), y()-40); // move the projectile by 40 pixels each time
         rowS--;
         }
         qDebug() << "MOVE PROJECTILE" << Qt::endl <<rowS << Qt::endl << colS;
         }
         else if(down)
         {
         if(rowS==18){scene()->removeItem(this);delete this;}
         else
         {
         setPos(x(), y()+40); // move the projectile by 40 pixels each time
         rowS++;
         }
         qDebug() << "MOVE PROJECTILE" << Qt::endl <<rowS << Qt::endl << colS;
         }

         QList<QGraphicsItem *> collidingitemslist= collidingItems();
         for(int i(0), size=collidingitemslist.size();i<size;i++)
         if(ISPLAYER && typeid(*(collidingitemslist[i]))==typeid(enemy))
         {

               if(enemy::counter>0){enemy::counter--;}
                     if(enemy::counter==0 && boss::bosshealth>0 && boss::count != 1)
                     {
                        boss * BOSS =new boss(Board,3,135, *VIEW); scene()->addItem(BOSS);
                     }
                     int l = rand()%4;
                     for(int j = 0; j <= l; ++j)
                     {coin* Coin =new coin; Coin->setPos(collidingitemslist[i]->x() + 5 * j,collidingitemslist[i]->y() +  5 * j); scene()->addItem(Coin);}

                     scene()->removeItem(collidingitemslist[i]);
                     scene()->removeItem(this);
                     delete collidingitemslist[i];
                     delete this;
         return;
         }
         else if(!ISPLAYER && typeid(*(collidingitemslist[i]))==typeid(player))
         {
                            QPixmap *deadHeart = new QPixmap ("deadheart.png");
                            *deadHeart=deadHeart->scaledToWidth(40);
                            *deadHeart=deadHeart->scaledToHeight(40);
                            for(int i = 0; i < 140; i+= 35)
                            {
                               QGraphicsPixmapItem * DEAD = new QGraphicsPixmapItem;
                               DEAD->setPixmap(*deadHeart);
                               scene()->addItem(DEAD);
                               DEAD->setPos(40 * i + 120 + 40 * player::health,40);
                            }
                         --player::health;
                         if(player::health <= 0)
                         {
                             VIEW->coinCount->setPos(500, 35);
                             qDebug()<<"wow";
                             delete collidingitemslist[i];
                             VIEW->displayendgamewindow(false);
                             QList<QGraphicsItem *> toFindBoss= scene()->items();
                             int size=toFindBoss.size();
                             for(int k = 0; k < size; ++k)
                             {
                                 if(typeid(*(toFindBoss[k])) == typeid(boss))
                                     delete toFindBoss[k];
                                 size=toFindBoss.size();
                             }
                             boss::bosshealth=4;

                         }
                         delete this;

         return;
         }
         else if(ISPLAYER && typeid(*(collidingitemslist[i]))==typeid(boss))
         {
             qDebug()<<"bossshot";
             boss::bosshealth -= player::weapon;
             if(boss::bosshealth<=0 && boss::count==1)
             {
                 boss::count=0;
                 qDebug()<<"JOL2";
                 VIEW->displayendgamewindow(true);
                 delete collidingitemslist[i];
             }
         delete this;
         }
         if(Board[rowS][colS]==0 || Board[rowS][colS]==3 || Board[rowS][colS]==4 || Board[rowS][colS]==7){delete this;}
}

