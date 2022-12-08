#include "coin.h"
#include "qgraphicsscene.h"

int coin::count = 0;
QFont coolFont("Times", 22, QFont::Bold);

coin::coin()
{
    COIN1= new QPixmap("coin1.png");
    *COIN1=COIN1->scaledToWidth(40);
    *COIN1=COIN1->scaledToHeight(40);
    COIN2= new QPixmap("coin2.png");
    *COIN2=COIN2->scaledToWidth(40);
    *COIN2=COIN2->scaledToHeight(40);
    COIN3= new QPixmap("coin3.png");
    *COIN3=COIN3->scaledToWidth(40);
    *COIN3=COIN3->scaledToHeight(40);
    COIN4= new QPixmap("coin4.png");
    *COIN4=COIN4->scaledToWidth(40);
    *COIN4=COIN4->scaledToHeight(40);
    COIN5= new QPixmap("coin5.png");
    *COIN5=COIN5->scaledToWidth(40);
    *COIN5=COIN5->scaledToHeight(40);
    COIN6= new QPixmap("coin6.png");
    *COIN6=COIN6->scaledToWidth(40);
    *COIN6=COIN6->scaledToHeight(40);
    setPixmap(*COIN1);
    QTimer * cointimer = new QTimer();


/*    before = std::chrono::steady_clock::now();
    after = std::chrono::steady_clock::now();
    int TIME = std::chrono::duration_cast<std::chrono::nanoseconds>(after - before).count();
*/
    connect(cointimer,SIGNAL(timeout()),this,SLOT(changeimage()));
    cointimer->start(175);

    QTimer * updateCoin = new QTimer();
    connect(updateCoin,SIGNAL(timeout()),this,SLOT(update()));
    updateCoin->start(200);
}

void coin::changeimage()
{
    if(++todelete >= 100)
    {
        delete this;
        return;
    }
    controlimage=(controlimage+1)%6;
   if(controlimage==0)
   {
    setPixmap(*COIN1);
   } else if(controlimage==1)
   {
    setPixmap(*COIN2);
   } else if(controlimage==2)
   {
    setPixmap(*COIN3);
   } else if(controlimage==3)
   {
    setPixmap(*COIN4);
   } else if(controlimage==4)
   {
    setPixmap(*COIN5);
   } else if(controlimage==5)
   {
    setPixmap(*COIN6);
   }
}

void coin::update()
{

}
