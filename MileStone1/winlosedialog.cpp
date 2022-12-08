#include "winlosedialog.h"
#include "ui_winlosedialog.h"
#include "start.h"
#include "map.h"

WinLoseDialog::WinLoseDialog(QWidget *parent, bool win) :
    QDialog(parent)
    ,ui(new Ui::WinLoseDialog)
{
    ui->setupUi(this);
    if(win)
    ui->label->setText("You Win!");
}

WinLoseDialog::~WinLoseDialog()
{
    delete ui;
}

void WinLoseDialog::on_exit_clicked()
{
   exit(0);
}


void WinLoseDialog::on_newGame_clicked()
{
    this->close();
}

