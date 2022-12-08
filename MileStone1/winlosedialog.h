#ifndef WINLOSEDIALOG_H
#define WINLOSEDIALOG_H
#include <QDialog>
#include "map.h"


namespace Ui {
class WinLoseDialog;
}

class WinLoseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WinLoseDialog(QWidget *parent = nullptr, bool win = 1);
    ~WinLoseDialog();


private slots:
    void on_exit_clicked();

    void on_newGame_clicked();

private:

    Ui::WinLoseDialog *ui;

};

#endif // WINLOSEDIALOG_H
