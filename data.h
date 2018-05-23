#ifndef DATA_H
#define DATA_H

#include <QSet>
#include <QVector>
#include <QString>
#include <QTime>


bool CheckTime(QString _time);


class Subjects
{
public:
    Subjects();
    ~Subjects();
    void operator=(const Subjects&);
    void connect(QString);
    void disconnect(QString);
    void setName(QString _name);
    void setTime(int _time);
    void setSemester(int _semester);
    void setTeacher(QString _teacherName);

    QSet <QString> getConnections() const;
    QString getName() const;
    int getTime() const;
    int getSemester() const;
    QString getTeacher() const;
private:
    QString Name;
    int Time;
    int semester;
    QString TeacherName;
    QSet <QString> connections;
};

class Students
{
public:
    Students();
    ~Students();
    void operator=(const Students&);
    void connect(QString _Subjects);
    void disconnect(QString);
    void setName(QString _name);
    void setPol(QString _pol);
    void setBorn(int _born);
    void setNumber(int _number);

    QSet <QString> getConnections() const;
    QString getName() const;
    QString getPol() const;
    int getBorn() const;
    int getNumber() const;
private:
    QString Name;
    QString Pol;
    int Born;
    int Number;
    QSet <QString> connections;
};

#endif // DATA_H
