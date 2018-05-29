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
        if(VecA.at(i).getName() == subject)
        {
            indStudent = i;
            res++;
        }
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
    QVector<Subjects>::iterator itA = VecA.begin() + indStudent;
    itA->connect(subject);
    QVector<Students>::iterator itF = VecF.begin() + indSubject;
    itF->connect(student);
    return true;
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
    list << "ФИО" << "Пол" << "Дата рождения" << "№ Зачетки";
    ui->firstList->setHorizontalHeaderLabels(list);
    ui->firstList->setColumnWidth(0, ((ui->firstList->width()) - qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent)) / 3);
    ui->firstList->setColumnWidth(1, ((ui->firstList->width()) - qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent)) / 6);
    ui->firstList->setColumnWidth(2, ((ui->firstList->width()) - qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent)) / 6);
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
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 2, new QTableWidgetItem(QString::number(VecF.at(IndStudent).getBorn())));
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 3, new QTableWidgetItem(QString::number(VecF.at(IndStudent).getNumber())));
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
    list << "Предмет" << "Кол-во часов" << "Номер семестра" << "Имя преподавателя";
    ui->firstList->setHorizontalHeaderLabels(list);
    ui->firstList->setColumnWidth(0, ((ui->firstList->width()) - qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent)) / 3);
    ui->firstList->setColumnWidth(1, ((ui->firstList->width()) - qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent)) / 6);
    ui->firstList->setColumnWidth(2, ((ui->firstList->width()) - qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent)) / 6);
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
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 1, new QTableWidgetItem(QString::number(VecA.at(IndSubject).getTime())));
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 2, new QTableWidgetItem(QString::number(VecA.at(IndSubject).getSemester())));
        ui->firstList->setItem(ui->firstList->rowCount() - 1, 3, new QTableWidgetItem(VecA.at(IndSubject).getTeacher()));
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
    ui->SubjectsWidget->clear();
    ui->StudentsWidget->clear();
    ui->firstList->setRowCount(0);
    ui->firstList->setColumnCount(0);

    if(VecA.empty() && VecF.empty() )
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
                return;
            }
            if(ui->SubjectsTeacherNameEdit->text().isEmpty())
            {
                ui->errBrowser->setText("Имя преподавателя указано некорректно");
                return;
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
            return;
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
            return;
        }
    }
    updateData();
}

void MainWindow::on_conButton_clicked()
{
    ui->errBrowser->setText("");
    if(!Connect(ui->ConPortEdit->text(), ui->ConFlightEdit->text()))
    {
        ui->errBrowser->setText("Не удалось\nнайти\nэлементы");
    }
    updateData();
}


void MainWindow::on_disconButton_clicked()
{
    ui->errBrowser->setText("");
    int IndSubj;
    QString SubjName = ui->ConPortEdit->text();
    QString StudName = ui->ConFlightEdit->text();
    int res = 0;
    for(int i = 0; i < VecA.size(); i++)
    {
        if(VecA.at(i).getName() == SubjName)
        {
            IndSubj = i;
            res++;
        }
    }
    int IndStud;
    for(int i = 0; i < VecF.size(); i++)
    {
        if(VecF.at(i).getName() == StudName)
        {
            IndStud = i;
            res++;
        }
    }
    if(res != 2)
    {
        ui->errBrowser->setText("Не удалось найти элементы");
        return;
    }
    QVector<Subjects>::iterator itA = VecA.begin() + IndSubj;
    itA->disconnect(SubjName);
    QVector<Students>::iterator itF = VecF.begin() + IndStud;
    itF->disconnect(StudName);
    updateData();
}

/*void MainWindow::readFile(QString dir)
{
    QString res = "";
    QString name = "";
    VecA.clear();
    VecF.clear();
    QSet <QString> Settmp;
    QFile file(dir);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream inputStream(&file);

        ui->errBrowser->setText("");
        bool ReadSubj = false;
        bool ReadStud = false;
        bool ReadConnect = false;
        bool ReadContinue = false;

        short StepSubj = 0;
        short StepStud = 0;
        short StepConnects = 0;

        QString SubjName = "";
        int SubjTime = 0;
        int Semester = 0;
        QString Teacher = "";

        QString StudName = "";
        QString Pol = "";
        int Born = 0;
        int Number = 0;

        QString ConnectionPort = "";

        while(!inputStream.atEnd())
        {
            res = inputStream.readLine();
            if(ReadContinue)
            {
                if(ReadSubj)
                {
                    if(StepSubj == 0)
                    {
                        StudName = res;
                        StepSubj++;
                    }
                    else if(StepSubj == 1)
                    {
                        SubjTime = res;
                        StepSubj++;
                        if(CheckClones(0, res))
                        {
                            Subjects *Subj = new Subjects();
                            Subj->setName(StudName);
                            Subj->setSemester(Semester);
                            Subj->setTeacher(Teacher);
                            Subj->setTime(SubjTime);
                            VecA.push_back(*Subj);
                        }
                        ReadContinue = false;
                        StepSubj = 0;
                    }
                }
                else if(ReadStud)
                {
                    if(StepStud == 0)
                    {
                        StudName = res;
                        StepStud++;
                    }
                    else if(StepStud == 1)
                    {
                        if(CheckTime(res))
                        {
                            Born = res;
                        }
                        else
                        {
                            ui->errBrowser->setText("Ошибка\nполучения\nвремени");
                            return;
                        }
                        StepStud++;
                    }
                    else if(StepStud == 2)
                    {
                        if(CheckTime(res))
                        {
                            Pol = res.toStdString();
                        }
                        else
                        {
                            ui->errBrowser->setText("Ошибка\nполучения\nвремени");
                            return;
                        }
                        StepStud++;
                    }
                    else if(StepStud == 3)
                    {
                        Number = res;
                        StepStud++;
                        if(CheckClones(0, res))
                        {
                            Students *Student = new Students();
                            Student->setName(StudName);
                            Student->setBorn(Born);
                            Student->setPol(Pol);
                            Student->setNumber(Number);
                            VecF.push_back(*Student);
                        }
                        ReadContinue = false;
                        StepStud = 0;
                    }
                }
                else if(ReadConnect)
                {
                    if(StepConnects == 0)
                    {
                        ConnectionPort = res;
                        StepConnects++;
                    }
                    else
                    {
                        if(res == ">airports")
                        {
                            ReadSubj = true;
                            ReadStud = false;
                            ReadConnect = false;
                            ReadContinue = true;
                            StepSubj = 0;
                        }
                        else if(res == ">flights")
                        {
                            ReadSubj = false;
                            ReadStud = true;
                            ReadConnect = false;
                            ReadContinue = true;
                            StepStud = 0;
                        }
                        else if(res == ">connections")
                        {
                            ReadSubj = false;
                            ReadStud = false;
                            ReadConnect = true;
                            ReadContinue = true;
                            StepConnects = 0;
                        }
                        else if(res == "")
                        {
                            ConnectionPort = "";
                            StepConnects = 0;
                        }
                        else
                        {
                            if(!Connect(ConnectionPort, res))
                            {
                                ui->errBrowser->setText("Ошибка\nполучения\nсвязей");
                                return;
                            }
                        }
                    }
                }
            }
            else
            {
                if(res == ">airports")
                {
                    ReadSubj = true;
                    ReadStud = false;
                    ReadConnect = false;
                    ReadContinue = true;
                    StepSubj = 0;
                }
                else if(res == ">flights")
                {
                    ReadSubj = false;
                    ReadStud = true;
                    ReadConnect = false;
                    ReadContinue = true;
                    StepStud = 0;
                }
                else if(res == ">connections")
                {
                    ReadSubj = false;
                    ReadStud = false;
                    ReadConnect = true;
                    ReadContinue = true;
                    StepConnects = 0;
                }
                else if(res == "")
                {
                    ReadContinue = true;
                    StepSubj = 0;
                    StepStud = 0;
                    StepConnects = 0;
                }
                else
                {
                    ui->errBrowser->setText("Ошибка\nчтения\nфайла");
                    return;
                }
            }
        }
        if(inputStream.status() != QTextStream::Ok)
        {
            ui->errBrowser->setText("Ошибка\nоткрытия\nфайла");
        }
        updateData();
    }
    else
    {
        ui->errBrowser->setText("Ошибка\nчтения\nфайла");
    }
}

void MainWindow::on_save_triggered()
{
    FILE *fout = fopen("output.txt", "w");
    if(fout)
    {
        fprintf(fout, ">subjects\n");
        for(int i = 0; i < VecA.size(); i++)
        {
            string Name = VecA.at(i).getName().toStdString();
            int Semester = VecA.at(i).getSemester();
            int Time = VecA.at(i).getTime();
            string Teacher = VecA.at(i).getTeacher().toStdString();
            fprintf(fout, "%s\n%s\n%s\n%s\n", Name.c_str(), Semester, Time, Teacher.c_str());
            if(i < VecA.size() - 1)
            {
                fprintf(fout, "\n");
            }
        }
        fprintf(fout, ">students\n");
        for(int i = 0; i < VecF.size(); i++)
        {
            fprintf(fout, "%s\n%s\n%s\n%s\n", VecF.at(i).getName().toStdString().c_str(),
                                      VecF.at(i).getBorn(),
                                      VecF.at(i).getNumber(),
                                      VecF.at(i).getPol().toStdString().c_str());
            if(i < VecF.size() - 1)
            {
                fprintf(fout, "\n");
            }
        }
        fprintf(fout, ">connections\n");
        for(int i = 0; i < VecA.size(); i++)
        {
            fprintf(fout, "%s\n", VecA.at(i).getName().toStdString().c_str());
            foreach (QString StudentName, VecA.at(i).getConnections())
            {

                fprintf(fout, "%s\n", (StudentName.toStdString().c_str()));
            }
            if(i < VecA.size() - 1)
            {
                fprintf(fout, "\n");
            }
        }
        fclose(fout);
    }
}*/
