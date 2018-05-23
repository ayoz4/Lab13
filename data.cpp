#include "data.h"

bool CheckTime(QString _time)
{
    if(_time[0].isDigit() && _time[1].isDigit() && _time[2] == ':' && _time[3].isDigit() && _time[4].isDigit())
    {
        return true;
    }
    else
    {
        return false;
    }
}

///ОПИСАНИЕ КЛАССА SUBJECTS

Subjects::Subjects()
{
    Name = "";
    semester = 0;
    TeacherName = "";
    connections.clear();
}

Subjects::~Subjects()
{
    connections.clear();
}

void Subjects::operator =(const Subjects &Subjects)
{
    setName(Subjects.getName());
    setSemester(Subjects.getSemester());
    setTime(Subjects.getTime());
    setTeacher(Subjects.getTeacher());
}

void Subjects::connect(QString _student)
{
    connections.insert(_student);
}

void Subjects::disconnect(QString _student)
{
    connections.remove(_student);
}

void Subjects::setName(QString _name)
{
    Name = _name;
}

void Subjects::setSemester(int _semester)
{
    semester = _semester;
}

void Subjects::setTeacher(QString _teacherName)
{
    TeacherName = _teacherName;
}

void Subjects::setTime(int _time)
{
    Time = _time;
}

QSet <QString> Subjects::getConnections() const
{
    return connections;
}

QString Subjects::getName() const
{
    return Name;
}

int Subjects::getSemester() const
{
    return semester;
}

QString Subjects::getTeacher() const
{
    return TeacherName;
}

int Subjects::getTime() const
{
    return Time;
}


///ОПИСАНИЕ КЛАССА STUDENTS


Students::Students()
{
    Name = "";
    Born = 0;
    Pol = "";
    Number = 0;
}

Students::~Students()
{

}

void Students::operator =(const Students &Student)
{
    setName(Student.getName());
    setBorn(Student.getBorn());
    setNumber(Student.getNumber());
    setPol(Student.getPol());
}

void Students::connect(QString _Subjects)
{
    connections.insert(_Subjects);
}

void Students::disconnect(QString _Subjects)
{
    connections.remove(_Subjects);
}

void Students::setName(QString _name)
{
    Name = _name;
}

void Students::setBorn(int _born)
{
    Born = _born;
}

void Students::setNumber(int _number)
{
    Number = _number;
}

void Students::setPol(QString _pol)
{
    Pol = _pol;
}

QSet <QString> Students::getConnections() const
{
    return connections;
}

QString Students::getName() const
{
    return Name;
}

QString Students::getPol() const
{
    return Pol;
}

int Students::getBorn() const
{
    return Born;
}

int Students::getNumber() const
{
    return Number;
}
