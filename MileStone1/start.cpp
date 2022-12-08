#include "start.h"
#include "ui_start.h"
#include "map.h"
#include "player.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "coin.h"


Start::Start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start)
{
    this->setFixedSize(282,423);
    ui->setupUi(this);
    QPixmap background("logo.jpeg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
    SoundTrack= new QMediaPlayer;
    audioOutput= new QAudioOutput;
    SoundTrack->setAudioOutput(audioOutput);
    SoundTrack->setSource(QUrl::fromLocalFile("soundtrack.mp3"));
    SoundTrack->setLoops(QSoundEffect::Infinite);
    audioOutput->setVolume(1); // Setting volume of the sound effect
    SoundTrack->play();
}

Start::~Start()
{
    delete ui;
}

void Start::on_pushButton_clicked()
{
    pName = ui->lineEdit->text();
    bool found = 0;

    QFile file("login.txt");
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return;

       QTextStream in(&file);
           while (!in.atEnd())
           {
               QString line = in.readLine();
               if(line == pName)
               {
                   found = true;
                   QString coins = in.readLine();
                   coin::count = coins.toInt();
                   break;
               }
           }
       file.close();
       if(found)
       {
           Map * x = new Map("BoardNew.txt", pName);
           this->close();
       }
       else
       {
           QMessageBox reg;
           reg.setText("Username does not exist, would you like to register?");
           reg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
           reg.setDefaultButton(QMessageBox::Yes);
           int answer = reg.exec();
           switch (answer) {
             case QMessageBox::Yes:
               newPlayer(pName);
             case QMessageBox::Cancel:
                 break;
           }
       }
}





void Start::on_pushButton_2_clicked()
{
    audioOutput->setMuted(0);

}

void Start::on_pushButton_3_clicked()
{
    audioOutput->setMuted(1);
}


void Start::on_pushButton_4_clicked()
{
    exit(0);
}

void Start::newPlayer(QString name)
{
    QFile file("login.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << Qt::endl << pName << Qt::endl << "0";
    QMessageBox registered;
    registered.setText("Registered Successfully!");
    registered.exec();
    return;
}
