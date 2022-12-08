#include "enemy.h"
#include "map.h"
#include "winlosedialog.h"
#include "boss.h"


int enemy::counter=0;
bool enemy::isMoving = 1;

enemy::enemy(int TMPBoard [19][140], int tmprow, int tmpcol, int Movetype, Map & V) : VIEW (&V)
{
    isMoving = 1;
    row=tmprow;
    column=tmpcol;
    movetype=Movetype;
    if(movetype==5||movetype==6){enemy::counter--;}
    if(movetype==1 || movetype==6 || movetype==5)
    {
         SpiderRight= new QPixmap("spiderright.png");
         *SpiderRight=SpiderRight->scaledToWidth(40);
         *SpiderRight=SpiderRight->scaledToHeight(40);
         SpiderLeft= new QPixmap("spiderleft.png");
         *SpiderLeft=SpiderLeft->scaledToWidth(40);
         *SpiderLeft=SpiderLeft->scaledToHeight(40);
         setPixmap(*SpiderRight);
    } else if(movetype==2)
    {
         Blaze= new QPixmap("blaze.png");
         *Blaze=Blaze->scaledToWidth(30);
         *Blaze=Blaze->scaledToHeight(40);
         setPixmap(*Blaze);
    }else if(movetype==3||movetype==4)
    {
        ZombieRight= new QPixmap("zombieright.png");
        *ZombieRight=ZombieRight->scaledToWidth(40);
        *ZombieRight=ZombieRight->scaledToHeight(40);
        ZombieLeft= new QPixmap("zombieleft.png");
        *ZombieLeft=ZombieLeft->scaledToWidth(40);
        *ZombieLeft=ZombieLeft->scaledToHeight(40);
        setPixmap(*ZombieRight);
    }


    setPos(40+40*column,40+40*row);
    for(int i(0);i<19;i++)
      for(int j(0);j<140;j++)
          Board[i][j]=TMPBoard[i][j];
    counter++;
    if(movetype==1)
    {
    QTimer * enemytimer = new QTimer();
    connect(enemytimer,SIGNAL(timeout()),this,SLOT(move()));
    enemytimer->start(500);
    }
    else if(movetype==2)
    {
    QTimer * enemytimer = new QTimer();
    connect(enemytimer,SIGNAL(timeout()),this,SLOT(movetype2()));
    enemytimer->start(500);
    }else if(movetype==3)
    {
    QTimer * enemytimer = new QTimer();
    connect(enemytimer,SIGNAL(timeout()),this,SLOT(movetype3()));
    enemytimer->start(500);
    }else if(movetype==4)
    {
    QTimer * enemytimer = new QTimer();
    connect(enemytimer,SIGNAL(timeout()),this,SLOT(movetype4()));
    enemytimer->start(500);
    }else if(movetype==5)
    {
    QTimer * enemytimer = new QTimer();
    connect(enemytimer,SIGNAL(timeout()),this,SLOT(movetype5()));
    enemytimer->start(500);
    }else if(movetype==6)
    {
    QTimer * enemytimer = new QTimer();
    connect(enemytimer,SIGNAL(timeout()),this,SLOT(movetype6s()));
    enemytimer->start(500);
    }


}
void enemy::move()
{
    if(isMoving)
    {
    int random = rand()%4;
    //&& Board[row-1][column]!=0
    if(random==0  && (Board[row-1][column]==1 || Board[row-1][column]==5 || Board[row-1][column]==2 || Board[row-1][column]==8) && row>-1 && row<19 && column >-1 && column<34)
    {

        if(row!=0)
        {
           row--;
           ShotGun * EShot = new ShotGun(Board,row,column,true,false,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
           EShot->setPos(this->x(),this->y());
           scene()->addItem(EShot);
        } //UP
    }
    else if(random==1  && (Board[row+1][column]==1 || Board[row+1][column]==5 || Board[row+1][column]==2 || Board[row+1][column]==8 ) && row<19 && column >-1 && column<34)
    {
        if(row!=18)
        {
            row++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,true,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            qDebug()<<this->x()<<Qt::endl;
           scene()->addItem(EShot);
        } //DOWN
    }
    else if(random==2 &&  (Board[row][column-1]==1 || Board[row][column-1]==5 || Board[row][column-1]==2 || Board[row][column-1]==8 ) && row>-1 && row<19 && column >-1 && column<34)
    {
        if(column!=0)
        {
        setPixmap(*SpiderLeft);
        column--;
        ShotGun * EShot = new ShotGun(Board,row,column,false,false,false,true,false,*VIEW); // Create a new projectile every time the player hits the space bar
        EShot->setPos(this->x(),this->y());
        scene()->addItem(EShot);
        } //LEFT
    }
    else if(random==3  && (Board[row][column+1]==1 || Board[row][column+1]==5 || Board[row][column+1]==2 || Board[row][column+1]==8 )  && row>-1 && row<19 && column >-1 && column<34)
    {
        if(column!=33)
        {
            setPixmap(*SpiderRight);
            column++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,false,true,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            scene()->addItem(EShot);
        } //RIGHT
    }
    setPos(40+40*column,40+40*row);
    COLLISION();
    }
}
void enemy::movetype2()
{
    if(isMoving)
    {
    int random = rand()%4;
    //&& Board[row-1][column]!=0
    if(random==0  && row>-1 && row<19 && column >34 && column<69)
    {
        if(row!=1)
        {
           row--;
           ShotGun * EShot = new ShotGun(Board,row,column,true,false,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
           EShot->setPos(this->x(),this->y());
           scene()->addItem(EShot);
        } //UP

    }
    else if(random==1  && row>-1 && row<19 && column >34 && column<69)
    {
        if(row!=17)
        {
            row++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,true,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            qDebug()<<this->x()<<Qt::endl;
           scene()->addItem(EShot);
        } //DOWN
    }
    else if(random==2 && row>-1 && row<19 && column >34 && column<69)
    {
        if(column!=35)
        {
        column--;
        ShotGun * EShot = new ShotGun(Board,row,column,false,false,false,true,false,*VIEW); // Create a new projectile every time the player hits the space bar
        EShot->setPos(this->x(),this->y());
        scene()->addItem(EShot);
        } //LEFT

    }
    else if(random==3 && row>-1 && row<19 && column >34 && column<69)
    {
        if(column!=68)
        {
            column++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,false,true,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            scene()->addItem(EShot);
        } //RIGHT
    }
    setPos(40+40*column,40+40*row);
    COLLISION();
    }
}
void enemy::movetype3()
{
    if(isMoving)
    {
    int random = rand()%4;
    //&& Board[row-1][column]!=0
    if(random==0  && row>-1 && row<19 && column >70 && column<104)
    {
        if(row!=1)
        {
           row--;
           ShotGun * EShot = new ShotGun(Board,row,column,true,false,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
           EShot->setPos(this->x(),this->y());
           scene()->addItem(EShot);
        } //UP

    }
    else if(random==1  && row>-1 && row<19 && column >70 && column<104)
    {
        if(row!=17)
        {
            row++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,true,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            qDebug()<<this->x()<<Qt::endl;
           scene()->addItem(EShot);
        } //DOWN
    }
    else if(random==2 && row>-1 && row<19 && column >70 && column<104)
    {
        if(column!=71)
        {
        setPixmap(*ZombieLeft);
        column--;
        ShotGun * EShot = new ShotGun(Board,row,column,false,false,false,true,false,*VIEW); // Create a new projectile every time the player hits the space bar
        EShot->setPos(this->x(),this->y());
        scene()->addItem(EShot);
        } //LEFT

    }
    else if(random==3 && row>-1 && row<19 && column >70 && column<104)
    {
        if(column!=103)
        {
            setPixmap(*ZombieRight);
            column++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,false,true,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            scene()->addItem(EShot);
        } //RIGHT
    }
    setPos(40+40*column,40+40*row);
    COLLISION();
    }
}
void enemy::movetype4()
{
    if(isMoving)
    {
    int random = rand()%4;
    //&& Board[row-1][column]!=0
    if(random==0 && (Board[row-1][column]==1 || Board[row-1][column]==5 || Board[row-1][column]==2 || Board[row-1][column]==8) && row>-1 && row<19 && column >70 && column<104)
    {
        if(row!=1)
        {
           row--;
           ShotGun * EShot = new ShotGun(Board,row,column,true,false,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
           EShot->setPos(this->x(),this->y());
           scene()->addItem(EShot);
        } //UP

    }
    else if(random==1  && (Board[row+1][column]==1 || Board[row+1][column]==5 || Board[row+1][column]==2 || Board[row+1][column]==8 ) && row>-1 && row<19 && column >70 && column<104)
    {
        if(row!=17)
        {
            row++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,true,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            qDebug()<<this->x()<<Qt::endl;
           scene()->addItem(EShot);
        } //DOWN
    }
    else if(random==2  && (Board[row][column-1]==1 || Board[row][column-1]==5 || Board[row][column-1]==2 || Board[row][column-1]==8 )&& row>-1 && row<19 && column >70 && column<104)
    {
        if(column!=71)
        {
        setPixmap(*ZombieLeft);
        column--;
        ShotGun * EShot = new ShotGun(Board,row,column,false,false,false,true,false,*VIEW); // Create a new projectile every time the player hits the space bar
        EShot->setPos(this->x(),this->y());
        scene()->addItem(EShot);
        } //LEFT

    }
    else if(random==3  && (Board[row][column+1]==1 || Board[row][column+1]==5 || Board[row][column+1]==2 || Board[row][column+1]==8 ) && row>-1 && row<19 && column >70 && column<104)
    {
        if(column!=103)
        {
            setPixmap(*ZombieRight);
            column++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,false,true,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            scene()->addItem(EShot);
        } //RIGHT
    }
    setPos(40+40*column,40+40*row);
    COLLISION();
    }
}
void enemy::movetype5()
{
//SPAWNED BY BOSS DOESN'T MOVE THROUGH WALLS
    if(isMoving)
    {
    int random = rand()%4;
    if(random==0  && (Board[row-1][column]==1 || Board[row-1][column]==5 || Board[row-1][column]==2 || Board[row-1][column]==8) && row>-1 && row<19 && column >-1 && column<140)
    {

        if(row!=0)
        {
           row--;
           ShotGun * EShot = new ShotGun(Board,row,column,true,false,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
           EShot->setPos(this->x(),this->y());
           scene()->addItem(EShot);
        } //UP
    }
    else if(random==1  && (Board[row+1][column]==1 || Board[row+1][column]==5 || Board[row+1][column]==2 || Board[row+1][column]==8 ) && row<19 && column >-1 && column<140)
    {
        if(row!=18)
        {
            row++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,true,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            qDebug()<<this->x()<<Qt::endl;
           scene()->addItem(EShot);
        } //DOWN
    }
    else if(random==2 &&  (Board[row][column-1]==1 || Board[row][column-1]==5 || Board[row][column-1]==2 || Board[row][column-1]==8 ) && row>-1 && row<19 && column >-1 && column<140)
    {
        if(column!=0)
        {
        setPixmap(*SpiderLeft);
        column--;
        ShotGun * EShot = new ShotGun(Board,row,column,false,false,false,true,false,*VIEW); // Create a new projectile every time the player hits the space bar
        EShot->setPos(this->x(),this->y());
        scene()->addItem(EShot);
        } //LEFT
    }
    else if(random==3  && (Board[row][column+1]==1 || Board[row][column+1]==5 || Board[row][column+1]==2 || Board[row][column+1]==8 )  && row>-1 && row<19 && column >-1 && column<140)
    {
        if(column!=139)
        {
            setPixmap(*SpiderRight);
            column++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,false,true,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            scene()->addItem(EShot);
        } //RIGHT
    }
    setPos(40+40*column,40+40*row);
    COLLISION();
    }
}
void enemy::movetype6()
{
//SPAWNED BY BOSS MOVE THROUGH WALLS
    if(isMoving)
    {
    int random = rand()%4;
    if(random==0 && row>-1 && row<19 && column >-1 && column<140)
    {

        if(row!=0)
        {
           row--;
           ShotGun * EShot = new ShotGun(Board,row,column,true,false,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
           EShot->setPos(this->x(),this->y());
           scene()->addItem(EShot);
        } //UP
    }
    else if(random==1 && row<19 && column >-1 && column<140)
    {
        if(row!=18)
        {
            row++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,true,false,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            qDebug()<<this->x()<<Qt::endl;
           scene()->addItem(EShot);
        } //DOWN
    }
    else if(random==2 && row>-1 && row<19 && column >-1 && column<140)
    {
        if(column!=0)
        {
        setPixmap(*SpiderLeft);
        column--;
        ShotGun * EShot = new ShotGun(Board,row,column,false,false,false,true,false,*VIEW); // Create a new projectile every time the player hits the space bar
        EShot->setPos(this->x(),this->y());
        scene()->addItem(EShot);
        } //LEFT
    }
    else if(random==3 && row>-1 && row<19 && column >-1 && column<140)
    {
        if(column!=139)
        {
            setPixmap(*SpiderRight);
            column++;
            ShotGun * EShot = new ShotGun(Board,row,column,false,false,true,false,false,*VIEW); // Create a new projectile every time the player hits the space bar
            EShot->setPos(this->x(),this->y());
            scene()->addItem(EShot);
        } //RIGHT
    }
    setPos(40+40*column,40+40*row);
    COLLISION();
}
}


void enemy::COLLISION()
{

    QList<QGraphicsItem *> collidingitemslist= collidingItems();
    for(int i(0), size=collidingitemslist.size();i<size;i++)
    {

        if(typeid(*(collidingitemslist[i]))==typeid(player))
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
                delete collidingitemslist[i];
                QList<QGraphicsItem *> toFindBoss= scene()->items();
                int size=toFindBoss.size();
                for(int k = 0; k < size; ++k)
                {
                    if(typeid(*(toFindBoss[k])) == typeid(boss))
                        delete toFindBoss[k];
                    size=toFindBoss.size();
                }
                VIEW->displayendgamewindow(false);
            }
         }
    }

}

void enemy::changeMove()
{
    if(isMoving)
        isMoving = 0;
    else
        isMoving = 1;
}
