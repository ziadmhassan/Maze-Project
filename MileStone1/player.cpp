#include "player.h"
#include "map.h"
#include "shotgun.h"
#include "enemy.h"
#include "boss.h"
#include "winlosedialog.h"



int player::health = 3;
int player::row=0;
int player::column=0;
int player::weapon = 1;

QFont myfont("Helvatica", 16, QFont::Bold);

player::player(int TMPBoard [19][140], Map & V, QString pName)
:VIEW (&V)
{
       player::health=3;
       isMoving = 1;
       row=0;
       column=0;
       name = pName;
       PlayerRight= new QPixmap("steveright.png");
       PlayerLeft=new QPixmap("steveleft.png");
       *PlayerRight=PlayerRight->scaledToWidth(40);
       *PlayerRight=PlayerRight->scaledToHeight(40);
       *PlayerLeft=PlayerLeft->scaledToWidth(40);
       *PlayerLeft=PlayerLeft->scaledToHeight(40);
       setPixmap(*PlayerRight);
       setPos(40,40);

       for(int i(0);i<19;i++)
         for(int j(0);j<140;j++)
             Board[i][j]=TMPBoard[i][j];
}

void player::keyPressEvent (QKeyEvent* event)
{
    if(isMoving && event->key()==Qt::Key_Up && (Board[row-1][column]==1 || Board[row-1][column]==5 || Board[row-1][column]==2 || Board[row-1][column]==8 ) && row>-1 && row<19 && column >-1 && column<140)
    {
        up=true;down=false;right=false;left=false;
        if(row!=0){br = row--;}
    }
    else if(isMoving && event->key()==Qt::Key_Down && (Board[row+1][column]==1 || Board[row+1][column]==5 || Board[row+1][column]==2 || Board[row+1][column]==8 ) && row>-1 && row<19 && column >-1 && column<140)
    {

        up=false;down=true;right=false;left=false;
        if(row!=18)br = row++;
    }
    else if(isMoving && event->key()==Qt::Key_Left && (Board[row][column-1]==1 || Board[row][column-1]==5 || Board[row][column-1]==2 || Board[row][column-1]==8 ) && row>-1 && row<19 && column >-1 && column<140)
    {

        up=false;down=false;right=false;left=true;
        if(column!=0){bc = column--;setPixmap(*PlayerLeft);}
    }
    else if(isMoving && event->key()==Qt::Key_Right && (Board[row][column+1]==1 || Board[row][column+1]==5 || Board[row][column+1]==2 || Board[row][column+1]==8 ) && row>-1 && row<19 && column >-1 && column<140)
    {

        up=false;down=false;right=true;left=false;
        if(column!=104){bc = column++;setPixmap(*PlayerRight);}
    }
    else if(event->key()==Qt::Key_Shift)
    {
        boss::changeMove();
        enemy::changeMove();
        if(!storeOpen)
        {
        isMoving = 0;
        storeOpen=1;
        int k = 0;
        if(column <= 35)
            k = 0;
        else if(column <= 70)
            k = 1;
        else if(column <= 105)
            k = 2;
        else
            k = 3;
        QBrush BlackBrush(Qt::black);
        QPen BlackPen(Qt::black);
        Window = new QGraphicsRectItem(QRect(440 + 1400 * k,125 ,600,600));
        Window->setBrush(BlackBrush);
        Window->setOpacity(0.5);
        scene()->addItem(Window);
        restore = new Button (QString("BUY FOR 20 COINS"));
        restore->setPos(740 + 1400 * k,325);
        scene()->addItem(restore);
        upgrade = new Button (QString("BUY FOR 20 COINS"));
        upgrade->setPos(740 + 1400 * k,525);
        scene()->addItem(upgrade);
        SHOP = new shop;
        scene()->addItem(SHOP);
        SHOP->setPos(650 + 1400 * k,125);

        restoretext=scene()->addText("Restore all of\n your health");
        restoretext->setDefaultTextColor(Qt::white);
        restoretext->setPos(500 +1400*k,335);
        restoretext->setFont(myfont);


        upgradetext=scene()->addText("Increase the strength\n of your weapon");
        upgradetext->setDefaultTextColor(Qt::white);
        upgradetext->setPos(500 +1400*k,535);
        upgradetext->setFont(myfont);

        connect(restore,SIGNAL(clicked()),this,SLOT(restoreHealth()));
        connect(upgrade,SIGNAL(clicked()),this,SLOT(improveWeapon()));
        }
        else
        {
            isMoving = 1;
            storeOpen=0;
            scene()->removeItem(Window);
            scene()->removeItem(restore);
            scene()->removeItem(upgrade);
            scene()->removeItem(upgradetext);
            scene()->removeItem(restoretext);
            scene()->removeItem(SHOP);
            delete SHOP;
            delete Window;
            delete restore;
            delete upgrade;
            delete upgradetext;
            delete restoretext;
        }
    }
    else if(event->key()==Qt::Key_Space)
    {

        QMediaPlayer * ShotSound  = new QMediaPlayer;
        QAudioOutput * audioOutput = new QAudioOutput;
        ShotSound->setAudioOutput(audioOutput);
        ShotSound->setSource(QUrl::fromLocalFile("LaserGun.mp3"));
        audioOutput->setVolume(1); // Setting volume of the sound effect
        ShotSound->play();


        ShotGun * Shot = new ShotGun(Board,row,column,up,down,right,left,true,*VIEW); // Create a new projectile every time the player hits the space bar
        Shot->setPos(this->x(),this->y()); // Set the starting position of the new projectile to the current position of the player
        scene()->addItem(Shot); // Each QObject has a reference to the scene within it , so we add the projectile we created to the same scene of the playe

    }
    setPos(40+40*column,40+40*row);


    QList<QGraphicsItem *> collidingitemslist= collidingItems();

    for(int i(0), size=collidingitemslist.size();i<size;i++)
    {

        if(typeid(*(collidingitemslist[i]))==typeid(enemy))
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
                QList<QGraphicsItem *> toFindBoss= scene()->items();
                int size=toFindBoss.size();
                for(int k = 0; k < size; ++k)
                {
                    if(typeid(*(toFindBoss[k])) == typeid(boss))
                        delete toFindBoss[k];
                    size=toFindBoss.size();
                }
                VIEW->displayendgamewindow(false);
                delete this;
            }

         }
        else if(typeid(*(collidingitemslist[i]))==typeid(coin))
        {
            coin::count++;
            VIEW->coinCount->setPlainText(("Coin count: " + QString::number(coin::count)));
            scene()->removeItem(collidingitemslist[i]);
            delete collidingitemslist[i];
        }else if(typeid(*(collidingitemslist[i]))==typeid(boss))
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
                QList<QGraphicsItem *> toFindBoss= scene()->items();
                int size=toFindBoss.size();
                for(int k = 0; k < size; ++k)
                {
                    if(typeid(*(toFindBoss[k])) == typeid(boss))
                        delete toFindBoss[k];
                    size=toFindBoss.size();
                }

                VIEW->displayendgamewindow(false);
                 delete this;
             }
        }
    }
    if     (column == 104 && row == 18 && enemy::counter==0) {VIEW->centerOn(4940,this->y());VIEW->coinCount->setPos(4700, 35); column =107; setPos(40+40*column,40+40*row);}
    else if(column == 69 && row == 18 && enemy::counter <= 6){VIEW->centerOn(3540,this->y());VIEW->coinCount->setPos(3300, 35); column = 72; setPos(40+40*column,40+40*row);} //change to 4 when we add enemies to last room 3740
    else if(column == 34 && row == 18 && enemy::counter <= 9){VIEW->centerOn(2140,this->y());VIEW->coinCount->setPos(1900, 35); column = 37; setPos(40+40*column,40+40*row);} //change to 6
    else if(column == 36 && row == 18 ){VIEW->centerOn(0,0);VIEW->coinCount->setPos(500, 35); column = 33; setPos(40+40*column,40+40*row);} // change first 0 to 740 : icrement all x s by 1400
    else if(column == 71 && row == 18 ){VIEW->centerOn(2140,this->y());VIEW->coinCount->setPos(1900, 35); column = 68; setPos(40+40*column,40+40*row);} //
    else if(column == 106 && row == 18){VIEW->centerOn(3540,this->y());VIEW->coinCount->setPos(3300, 35);column=103;setPos(40+40*column,40+40*row);}

}

void player::improveWeapon()
{
    if(coin::count >= 20)
    {
    coin::count -= 20;
    VIEW->coinCount->setPlainText(("Coin count: " + QString::number(coin::count)));
    ++weapon;
    }
    this->setFocus();
}

void player::restoreHealth()
{
    if(health < 3 && coin::count >= 20)
    {
    coin::count -= 20;
    VIEW->coinCount->setPlainText(("Coin count: " + QString::number(coin::count)));
    health = 3;
    QPixmap * healthpng= new QPixmap("heart.png");
           *healthpng=healthpng->scaledToWidth(40);
           *healthpng=healthpng->scaledToHeight(40);
    for(int i = 0; i < 140; i+= 35)
               for(int j = 1; j < 4; ++j)
               {
                                  QGraphicsPixmapItem * HEALTH = new QGraphicsPixmapItem;
                                  HEALTH->setPixmap(*healthpng);
                                  scene()->addItem(HEALTH);
                                  HEALTH->setPos(40 * (i+j) + 120,40);
               }
    }
    this->setFocus();
}
