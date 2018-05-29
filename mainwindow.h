#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QtGui>
#include <QDialog>
#include <dialog.h>
#include <QFile>
#include <qfiledialog>
#include <QTableWidgetItem>
#include <string.h>
#include <data.h>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateData();
    void readFile(QString dir = "input.dat");
    bool CheckClones(bool VecNumber, QString _name);
    bool Connect(QString SubjName, QString StudName);

private slots:
    void on_ExitButton_clicked();
    void HideSubj(bool value);
    void HideStud(bool value);
    void showRelationsSubject(QModelIndex Qindex);
    void showRelationsStudent(QModelIndex Qindex);
    void updateGeometry();
    void on_comboBox_activated(const QString &arg1);

    void on_addButton_clicked();

    void on_conButton_clicked();


    void on_disconButton_clicked();

private:
    short ToAdd;
    Ui::MainWindow *ui;
    QVector <Subjects> VecA;
    QVector <Students> VecF;
};

#endif // MAINWINDOW_H
