#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    VecA.clear();
    VecF.clear();
    HideSubj(true);
    HideStud(true);
    ui->addButton->setHidden(true);
    ToAdd = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ExitButton_clicked()                ///КНОПКА ВЫХОДА
{
    Dialog *DialogWindow = new Dialog();
    DialogWindow->exec();

    ui->errBrowser->setText("");
    if(DialogWindow->GetClose())
    {
        this->close();
    }
}

bool MainWindow::Connect(QString subject, QString student)
{
    int indStudent;
    int res = 0;
    for(int i = 0; i < VecA.size(); i++)
    {
        indStudent = i;
        res++;
    }

    int indSubject;
    for(int i = 0; i < VecF.size(); i++)
    {
        if(VecF.at(i).getName() == student)
        {
            indSubject = i;
            res++;
        }
    }

    if(res != 2)
    {
        return false;
    }
}

bool MainWindow::CheckClones(bool VecNumber, QString _name)
{
    if(VecNumber)
    {
        foreach (Subjects Name, VecA) {
           if(Name.getName() == _name)
           {
               return false;
           }
        }
    }
    else
    {
        foreach (Students student, VecF) {
           if(student.getName() == _name)
           {
               return false;
           }
        }
    }
    return true;
}

void MainWindow::showRelationsSubject(QModelIndex Qindex)               ///ВЫВЕСТИ НА ЭКРАН ПРЕДМЕТЫ
{
    ui->firstList->setRowCount(0);
    int row = Qindex.row();
    QSet <QString> tmp;
    ui->firstList->setColumnCount(4);
    QStringList list;
    list << "Предмет" << "Кол-во часов" << "Номер семстра" << "Имя преподавателя";
    ui->firstList->setHorizontalHeaderLabels(list);
    ui->firstList->setColumnWidth(0, (ui->firstList->width()) - qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent) / 2);
    Subjects Obj = VecA.at(row);
    tmp = Obj.getConnections();
    for(QSet<QString>::Iterator it = tmp.begin(); it != tmp.end(); it++)
    {
        ui->firstList->insertRow(ui->firstList->rowCount());
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 0, new QTableWidgetItem(*it));
        int IndSubject = 0;
        for(int i = 0; i < VecA.size(); i++)
        {
            if(VecA.at(i).getName() == *it)
            {
                IndSubject = i;
            }
        }
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 1, new QTableWidgetItem(VecA.at(IndSubject).getTime()));
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 2, new QTableWidgetItem(VecA.at(IndSubject).getSemester()));
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 3, new QTableWidgetItem(VecA.at(IndSubject).getTeacher()));
    }
    ui->firstList->horizontalHeader()->setStretchLastSection(1);
}

void MainWindow::showRelationsStudent(QModelIndex Qindex)                   ///ВЫВЕСТИ НА ЭКРАН СТУДЕНТОВ
{
    ui->errBrowser->setText("");
    ui->firstList->setRowCount(0);
    int row = Qindex.row();
    QSet <QString> tmp;
    ui->firstList->setColumnCount(4);
    QStringList list;
    list << " ФИО" << "Пол" << "Дата зачетки" << "№ Зачетки";
    ui->firstList->setHorizontalHeaderLabels(list);
    ui->firstList->setColumnWidth(0, (ui->firstList->width()) - qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent) / 2);
    Students Obj = VecF.at(row);
    tmp = Obj.getConnections();
    for(QSet<QString>::Iterator it = tmp.begin(); it != tmp.end(); it++)
    {
        ui->firstList->insertRow(ui->firstList->rowCount());
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 0, new QTableWidgetItem(*it));
        int IndStudent = 0;
        for(int i = 0; i < VecF.size(); i++)
        {
            if(VecF.at(i).getName() == *it)
            {
                IndStudent = i;
            }
        }
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 1, new QTableWidgetItem(VecF.at(IndStudent).getPol()));
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 2, new QTableWidgetItem(VecF.at(IndStudent).getBorn()));
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 3, new QTableWidgetItem(VecF.at(IndStudent).getNumber()));
    }
    ui->firstList->horizontalHeader()->setStretchLastSection(1);
}

void MainWindow::HideSubj(bool value)               ///СПРАТЯТЬ МЕНЮ ПРЕДМЕТОВ
{
    ui->SubjectsHourEdit->setHidden(value);
    ui->SubjectsNameEdit->setHidden(value);
    ui->SubjectsSemesterEdit->setHidden(value);
    ui->SubjectsTeacherNameEdit->setHidden(value);
    ui->SubjectsHoursLabel->setHidden(value);
    ui->SubjectsNameLabel->setHidden(value);
    ui->SubjectsSemesterLabel->setHidden(value);
    ui->SubjectsTeacherName->setHidden(value);
}

void MainWindow::HideStud(bool value)               ///СПРЯТАТЬ МЕНЮ СТУДЕНТОВ
{
    ui->StudenstNameLabel->setHidden(value);
    ui->StudentsBornLabel->setHidden(value);
    ui->StudentsNumberLabel->setHidden(value);
    ui->StudentsPolLabel->setHidden(value);
    ui->StudentsBornEdit->setHidden(value);
    ui->StudentsNumberEdit->setHidden(value);
    ui->StudentsPolEdit->setHidden(value);
    ui->StudentsNameEdit->setHidden(value);
}

void MainWindow::updateGeometry()
{
    if(ToAdd == 1)
    {
        HideStud(true);
        HideSubj(false);
        ui->addButton->setHidden(false);
    }
    else if(ToAdd == 2)
    {
        HideStud(false);
        HideSubj(true);
        ui->addButton->setHidden(false);
    }
    else
    {
        HideStud(true);
        HideSubj(true);
        ui->addButton->setHidden(true);
    }
}

void MainWindow::updateData()
{
    ui->StudentsWidget->clear();
    ui->StudentsWidget->clear();
    ui->firstList->setRowCount(0);
    ui->firstList->setColumnCount(0);

    if(VecA.empty())
    {
        return;
    }

    for(QVector<Subjects>::iterator it = VecA.begin(); it != VecA.end(); it++)
    {
        QString Name = it->getName();
        ui->SubjectsWidget->addItem(Name);
        QObject::connect(ui->SubjectsWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showRelationsSubject(QModelIndex)));
    }
    for(QVector<Students>::iterator it = VecF.begin(); it != VecF.end(); it++)
    {
        QString Name = it->getName();
        ui->StudentsWidget->addItem(Name);
        QObject::connect(ui->StudentsWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showRelationsStudent(QModelIndex)));
    }
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    ui->errBrowser->setText("");
    if(arg1 == "Предмет")
    {
        ToAdd = 1;
    }
    else if(arg1 == "Студент")
    {
        ToAdd = 2;
    }
    else
    {
        ToAdd = 0;
    }
    updateGeometry();
}

void MainWindow::on_addButton_clicked()
{
    ui->errBrowser->setText("");
    if(ToAdd == 1)
    {
        QString name = ui->SubjectsNameEdit->text();
        if(CheckClones(1, name))
        {
            if(name.isEmpty())
            {
                ui->errBrowser->setText("Имя указано некорректно");
                return;
            }
            if(ui->SubjectsHourEdit->text().isEmpty())
            {
                ui->errBrowser->setText("Кол-во часов указано некорректно");
                return;
            }
            if(ui->SubjectsSemesterEdit->text().isEmpty())
            {
                ui->errBrowser->setText("Номер семестра указан некорректно");
            }
            if(ui->SubjectsTeacherNameEdit->text().isEmpty())
            {
                ui->errBrowser->setText("Имя преподавателя указано некорректно");
            }
            Subjects *subject = new Subjects;
            subject->setName(name);
            subject->setTime(ui->SubjectsHourEdit->text().toInt());
            subject->setSemester(ui->SubjectsSemesterEdit->text().toInt());
            subject->setTeacher(ui->SubjectsTeacherNameEdit->text());
            VecA.push_back(*subject);
        }
        else
        {
            ui->errBrowser->setText("Такой предмет уже добавлен");
        }
    }
    else if(ToAdd == 2)
    {
        QString name = ui->StudentsNameEdit->text();
        if(CheckClones(0, name))
        {
            if(name.isEmpty())
            {
                ui->errBrowser->setText("Имя студента задано некорректно");
                return;
            }
            if(ui->StudentsPolEdit->text().isEmpty())
            {
                ui->errBrowser->setText("Пол задан некорректно");
                return;
            }
            Students *student = new Students;
            student->setName(name);
            student->setPol(ui->StudentsPolEdit->text());
            student->setBorn(ui->StudentsBornEdit->text().toInt());
            student->setNumber(ui->StudentsNumberEdit->text().toInt());
            VecF.push_back(*student);
        }
        else
        {
            ui->errBrowser->setText("Такой студент уже добавлен");
        }
    }
    updateData();
}

void MainWindow::on_conButton_clicked()
{

}
