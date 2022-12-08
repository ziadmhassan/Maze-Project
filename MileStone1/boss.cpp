#include "boss.h"
#include "map.h"
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#define ROW 19
#define COL 140

using namespace std;


int boss::bosshealth=4;
bool boss::isMoving = 1;
int  boss::count = 0;

typedef pair<int,int> Pair;
typedef tuple<double, int, int> Tuple;


// A Function to check whether given cell (row, col) is a valid cell or not.

boss::boss(int TMPBoard [19][140], int tmprow, int tmpcol, Map & V) : VIEW (&V)
{
    boss::count = 1;
    boss::bosshealth=4;
    isMoving = 1;
    row=tmprow;
    column=tmpcol;
    PiglinRight= new QPixmap("piglinright.png");
    *PiglinRight=PiglinRight->scaledToWidth(40);
    *PiglinRight=PiglinRight->scaledToHeight(40);
    PiglinLeft= new QPixmap("piglinleft.png");
    *PiglinLeft=PiglinLeft->scaledToWidth(40);
    *PiglinLeft=PiglinLeft->scaledToHeight(40);
    setPixmap(*PiglinLeft);
    setPos(40+40*column,40+40*row);
    for(int i(0);i<19;i++)
      for(int j(0);j<140;j++)
          Board[i][j]=TMPBoard[i][j];
    QTimer * enemytimer = new QTimer();
    connect(enemytimer,SIGNAL(timeout()),this,SLOT(moveboss()));
    enemytimer->start(500);
    QTimer * enemytimer1 = new QTimer();
    connect(enemytimer1,SIGNAL(timeout()),this,SLOT(findshortest()));
    enemytimer1->start(1000);
}

void boss::moveboss()
{

    if(!Path.empty() && isMoving)
    {
    if(!(++heal % 20))
        ++bosshealth;
    Pair p=Path.top();
    Path.pop();
    Pair Shoot = Path.top();
    row=p.first;
    column=p.second;
    int up = Shoot.first - row;
    int right = Shoot.second - column;
    ShotGun * BShot;
    if(up>0)
    {
         BShot = new ShotGun(Board,row,column,false,true,false,false,false,*VIEW);
    }
    else if(up < 0)
    {
        BShot = new ShotGun(Board,row,column,true,false,false,false,false,*VIEW);
    }
    else if(right > 0)
    {
        BShot = new ShotGun(Board,row,column,false,false,true,false,false,*VIEW);
    }
    else if(right < 0)
    {
        BShot = new ShotGun(Board,row,column,false,false,false,true,false,*VIEW);
    }
    BShot->setPos(this->x(),this->y());
    scene()->addItem(BShot);
    setPos(40+40*column,40+40*row);
    ++spawn;
    if(spawn % 12 == 0 && type)
    {
        qDebug()<<"lol";
        enemy * E1 = new enemy(Board, Shoot.first, Shoot.second, 5, *VIEW);
        scene()->addItem(E1);
        type = 0;
    }
    else if(spawn % 12 == 0 && !type)
    {
        enemy * E2 = new enemy(Board, Shoot.first, Shoot.second, 6, *VIEW);
        scene()->addItem(E2);
        type = 1;
    }
    COLLISION();
    }

}

void boss::COLLISION()
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
                VIEW->displayendgamewindow(false);
                QList<QGraphicsItem *> toFindBoss= scene()->items();
                int size=toFindBoss.size();
                for(int k = 0; k < size; ++k)
                {
                    if(typeid(*(toFindBoss[k])) == typeid(boss))
                        delete toFindBoss[k];
                    size=toFindBoss.size();
                }
            }
         }
    }

}

void boss::findshortest()
{
while(!Path.empty())
    {
        Path.pop();
    }

Pair source(row,column);
Pair destination(player::row,player::column);
aStarSearch(Board, source, destination);
}

bool boss::isValid(const Pair& point)
{
    // Returns true if row number and column number is in range
         return (point.first >= 0) && (point.first < ROW) && (point.second >= 0) && (point.second < COL);
}

// A Function to check whether the given cell is blocked or not
bool boss::isUnBlocked(const int grid [ROW][COL],const Pair& point)
{
    // Returns true if the cell is not blocked else false
    qDebug() << "POINTSSS" <<  point.first <<point.second << grid[point.first][point.second];
    if(grid[point.first][point.second] == 5 || grid[point.first][point.second] == 2 || grid[point.first][point.second] == 8 || grid[point.first][point.second] == 1)
    {
    return true;
    } else {return false;}
}

// A Function to check whether destination cell has been reached or not
bool boss::isDestination(const Pair& position, const Pair& dest)
{
    return position == dest;
}

// A Function to calculate the 'h' heuristics.
double boss::calculateHValue(const Pair& src, const Pair& dest)
{
    // h is estimated with Manhatten Distance formula
    return abs(src.first - dest.first)+abs(src.second - dest.second);
}

// A Utility Function to trace the path from the source to
// destination
void boss::tracePath(const array<array<cell, COL>, ROW>& cellDetails,const Pair& dest)
{
    int row = dest.first;
    int col = dest.second;
    Pair next_node = cellDetails[row][col].parent;
     do{
        Path.push(next_node);
        next_node = cellDetails[row][col].parent;
        row = next_node.first;
        col = next_node.second;
        } while (cellDetails[row][col].parent != next_node);
      Path.emplace(row, col);

}
void boss::aStarSearch(const int grid[ROW][COL],const Pair& src, const Pair& dest)
{

 // If the source is out of range
    if (!isValid(src)) {
        qDebug() << "Source is invalid\n";
        return;
    }

    // If the destination is out of range
    if (!isValid(dest)) {
        qDebug() << "Destination is invalid\n";
        return;
    }

    // Either the source or the destination is blocked
    if (!isUnBlocked(grid, src) || !isUnBlocked(grid, dest))
    {
        qDebug() << "Source or the destination is blocked\n";
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src, dest)) {
        qDebug() << "We are already at the destination\n";
        return;
    }

    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    // Declare a 2D array of structure to hold the details
    // of that cell
    array<array<cell, COL>, ROW> cellDetails;

    int i, j;
    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent = { i, j };

    /*
    Create an open list having information as-
    <f, <i, j>>
    where f = g + h,
    and i, j are the row and column index of that cell
    Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    This open list is implemented as a set of tuple.*/
    std::priority_queue<Tuple, std::vector<Tuple>,
                        std::greater<Tuple> >
        openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.emplace(0.0, i, j);

    // We set this boolean value as false as initially
    // the destination is not reached.
    while (!openList.empty()) {
        const Tuple& p = openList.top();
        // Add this vertex to the closed list
        i = get<1>(p); // second element of tuple
        j = get<2>(p); // third element of tuple

        // Remove this vertex from the open list
        openList.pop();
        closedList[i][j] = true;
        /*
                Generating all the 4 successor of this cell
                Cell-->Popped Cell (i, j)
                N --> North     (i-1, j)
                S --> South     (i+1, j)
                E --> East     (i, j+1)
                W --> West         (i, j-1)

        */
        for (int add_x = -1; add_x <= 1; add_x++) {
            for (int add_y = -1; add_y <= 1; add_y++) {
             if((add_x==0 && add_y!=0)||(add_x!=0 && add_y==0))
                {
                Pair neighbour(i + add_x, j + add_y);
                // Only process this cell if this is a valid
                // one
                if (isValid(neighbour)) {
                    // If the destination cell is the same
                    // as the current successor
                    if (isDestination(
                            neighbour,
                            dest)) { // Set the Parent of
                                     // the destination cell
                        cellDetails[neighbour.first]
                                   [neighbour.second]
                                       .parent
                            = { i, j };
                        printf("The destination cell is "
                               "found\n");
                        tracePath(cellDetails, dest);
                        return;
                    }
                    // If the successor is already on the
                    // closed list or if it is blocked, then
                    // ignore it.  Else do the following
                    else if (!closedList[neighbour.first]
                                        [neighbour.second]
                             && isUnBlocked(grid,
                                            neighbour)) {
                        double gNew, hNew, fNew;
                        gNew = cellDetails[i][j].g + 1.0;
                        hNew = calculateHValue(neighbour,
                                               dest);
                        fNew = gNew + hNew;

                        if (cellDetails[neighbour.first]
                                       [neighbour.second]
                                           .f
                                == -1
                            || cellDetails[neighbour.first]
                                          [neighbour.second]
                                              .f
                                   > fNew) {
                            openList.emplace(
                                fNew, neighbour.first,
                                neighbour.second);

                            cellDetails[neighbour.first]
                                       [neighbour.second]
                                           .g
                                = gNew;
                            cellDetails[neighbour.first]
                                       [neighbour.second]
                                           .h
                                = hNew;
                            cellDetails[neighbour.first]
                                       [neighbour.second]
                                           .f
                                = fNew;
                            cellDetails[neighbour.first]
                                       [neighbour.second]
                                           .parent
                                = { i, j };

              }
            }
          }
        }
      }
    }
  }
}

void boss::changeMove()
{
    if(isMoving)
        isMoving = 0;
    else
        isMoving = 1;
}
