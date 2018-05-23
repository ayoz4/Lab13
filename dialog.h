#ifndef DIALOG_H
#define DIALOG_H
#include <mainwindow.h>

namespace Ui
{
    class Dialog;
}


class Dialog: public QDialog
 {
     Q_OBJECT

public:
    explicit Dialog(QDialog *parent = 0);
    ~Dialog();

    bool GetClose();

private slots:

    void on_buttonBox_accepted();



private:
    bool close;
    Ui::Dialog *ui;
 };

#endif // DIALOG_H
