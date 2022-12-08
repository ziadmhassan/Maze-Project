#ifndef START_H
#define START_H
#include <QDialog>
#include <QtMultimedia>


namespace Ui {
class Start;
}

class Start : public QDialog
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();
    QString pName;
    QMediaPlayer * SoundTrack ;
    QAudioOutput * audioOutput ;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void newPlayer(QString);

private:
    Ui::Start *ui;
};

#endif // START_H
