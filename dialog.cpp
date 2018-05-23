#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    close = false;
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::GetClose()
{
    return close;
}

void Dialog::on_buttonBox_accepted()
{
    close = true;
}
