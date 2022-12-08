#ifndef BOSS_H
#define BOSS_H
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <cstdlib>
#include <time.h>
#include <QTimer>
#include <stack>
#include "shotgun.h"
#include "map.h"
#include "enemy.h"
#define ROW 19
#define COL 140

using namespace std;

typedef pair<int,int> Pair;

class boss : public QObject, public QGraphicsPixmapItem
{
 Q_OBJECT
public:
    boss(int [19][140],int , int , Map & V);
    static int bosshealth;
     static int count;

public slots:

    void moveboss();
    void findshortest();
    static void changeMove();

private:
    struct cell {
        // Row and Column index of its parent
        Pair parent;
        // f = g + h
        double f, g, h;
        cell()
            : parent(-1, -1)
            , f(-1)
            , g(-1)
            , h(-1)
        {
        }
    };
    int row;
    int column;
    int Board[19][140];
    void COLLISION();
    bool type = 1;
    Map * VIEW;
    QPixmap * PiglinRight;
    QPixmap * PiglinLeft;
    stack<Pair> Path;
    bool isValid(const Pair& point);
    bool isUnBlocked(const int grid [ROW][COL],const Pair& point);
    bool isDestination(const Pair& position, const Pair& dest);
    double calculateHValue(const Pair& src, const Pair& dest);
    void tracePath(const array<array<cell, COL>, ROW>& cellDetails,const Pair& dest);
    void aStarSearch(const int grid[ROW][COL],const Pair& src, const Pair& dest);
    static bool isMoving;
    int heal=0;
    int spawn = 0;

};

#endif // BOSS_H
