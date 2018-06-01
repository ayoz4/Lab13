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
    itA->connect(student);
    QVector<Students>::iterator itF = VecF.begin() + indSubject;
    itF->connect(subject);
    return true;
}

bool MainWindow::CheckClones(bool VecNumber, QString _name)                     ///ПРОВЕРКА НА ОДИНАКОВЫЕ ЭЛЕМЕНТЫ
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

void MainWindow::showRelationsStudent(QModelIndex Qindex)                   ///ВЫВЕСТИ НА ЭКРАН СТУДЕНТОВ
{
    ui->firstList->setRowCount(0);
    int row = Qindex.row();
    QSet <QString> tmp;
    ui->firstList->setColumnCount(4);
    QStringList list;
    list << "Предмет" << "Кол-во часов" << "Номер семстра" << "Имя преподавателя";
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

void MainWindow::showRelationsSubject(QModelIndex Qindex)               ///ВЫВЕСТИ НА ЭКРАН ПРЕДМЕТЫ
{
    ui->errBrowser->setText("");
    ui->firstList->setRowCount(0);
    int row = Qindex.row();
    QSet <QString> tmp;
    ui->firstList->setColumnCount(4);
    QStringList list;
    list << " ФИО" << "Пол" << "Дата зачетки" << "№ Зачетки";
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

void MainWindow::on_addButton_clicked()                                     ///ДОБАВИТЬ ЭЛЕМЕНТ
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


void MainWindow::on_disconButton_clicked()                                      ///УДАЛИТЬ СВЯЗЬ
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

void MainWindow::readFile(QString dir)
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
        bool ReadSubject = false;
        bool ReadStudent = false;
        bool ReadConnect = false;
        bool ReadContinue = false;

        short StepSubject = 0;
        short StepStudent = 0;
        short StepConnects = 0;

        QString SubjectName = "";
        int SubjectHours = 0;
        int SubjectSemester = 0;
        QString SubjectTeacher = "";

        QString StudentName = "";
        QString StudentGender = "";
        int StudentYear = 0;
        int StudentBook = 0;

        QString ConnectionSubject = "";

        while(!inputStream.atEnd())
        {
            res = inputStream.readLine();
            if(ReadContinue)
            {
                if(ReadSubject)
                {
                    if(StepSubject == 0)
                    {
                        SubjectName = res;
                        StepSubject++;
                    }
                    else if(StepSubject == 1)
                    {
                        SubjectHours = res.toInt();
                        StepSubject++;
                    }
                    else if(StepSubject == 2)
                    {
                        SubjectSemester = res.toInt();
                        StepSubject++;
                    }
                    else if(StepSubject == 3)
                    {
                        SubjectTeacher = res;
                        if(CheckClones(0, res))
                        {
                            Subjects *Subj = new Subjects();
                            Subj->setName(SubjectName);
                            Subj->setTime(SubjectHours);
                            Subj->setSemester(SubjectSemester);
                            Subj->setTeacher(SubjectTeacher);
                            VecA.push_back(*Subj);
                        }
                        ReadContinue = false;
                        StepSubject = 0;
                    }
                }
                else if(ReadStudent)
                {
                    if(StepStudent == 0)
                    {
                        StudentName = res;
                        StepStudent++;
                    }
                    else if(StepStudent == 1)
                    {
                        StudentGender = res;
                        StepStudent++;
                    }
                    else if(StepStudent == 2)
                    {
                        StudentYear = res.toInt();
                        StepStudent++;
                    }
                    else if(StepStudent == 3)
                    {
                        StudentBook = res.toInt();
                        StepStudent++;
                        if(CheckClones(0, res))
                        {
                            Students *Student = new Students();
                            Student->setName(StudentName);
                            Student->setPol(StudentGender);
                            Student->setBorn(StudentYear);
                            Student->setNumber(StudentBook);
                            VecF.push_back(*Student);
                        }
                        ReadContinue = false;
                        StepStudent = 0;
                    }
                }
                else if(ReadConnect)
                {
                    if(StepConnects == 0)
                    {
                        ConnectionSubject = res;
                        StepConnects++;
                    }
                    else
                    {
                        if(res == ">subject")
                        {
                            ReadSubject = true;
                            ReadStudent = false;
                            ReadConnect = false;
                            ReadContinue = true;
                            StepSubject = 0;
                        }
                        else if(res == ">student")
                        {
                            ReadSubject = false;
                            ReadStudent = true;
                            ReadConnect = false;
                            ReadContinue = true;
                            StepStudent = 0;
                        }
                        else if(res == ">connections")
                        {
                            ReadSubject = false;
                            ReadStudent = false;
                            ReadConnect = true;
                            ReadContinue = true;
                            StepConnects = 0;
                        }
                        else if(res == "")
                        {
                            ConnectionSubject = "";
                            StepConnects = 0;
                        }
                        else
                        {
                            if(!Connect(ConnectionSubject, res))
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
                if(res == ">subject")
                {
                    ReadSubject = true;
                    ReadStudent = false;
                    ReadConnect = false;
                    ReadContinue = true;
                    StepSubject = 0;
                }
                else if(res == ">student")
                {
                    ReadSubject = false;
                    ReadStudent = true;
                    ReadConnect = false;
                    ReadContinue = true;
                    StepStudent = 0;
                }
                else if(res == ">connections")
                {
                    ReadSubject = false;
                    ReadStudent = false;
                    ReadConnect = true;
                    ReadContinue = true;
                    StepConnects = 0;
                }
                else if(res == "")
                {
                    if(!ReadStudent && !ReadSubject && !ReadConnect)
                    {
                        continue;
                    }
                    ReadContinue = true;
                    StepSubject = 0;
                    StepStudent = 0;
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

void MainWindow::on_OpenAction_triggered()
{
    QString dir = QFileDialog::getOpenFileName();
    readFile(dir);
}

void MainWindow::on_save_triggered()                                        ///СОХРАНИТЬ В ФАЙЛ
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
}
