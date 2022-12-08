#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include "start.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     Start S; // Create a new object of the start screen of the game
     S.show(); // Show the start screen object we created on the monitor

     return a.exec();
}
