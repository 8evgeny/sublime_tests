#include <QCoreApplication>

/*

  What
  Composite Pattern - Objects in objects

  Description
  Compose objects into tree structures to represent whole-part hierarchies

  Why
  Building an object tree

  Example
  Qt's parent child relations
  We have done this many many times
  https://sourcemaking.com/design_patterns/composite

  School
  Teacher
  Student

 */

#include "school.h"
#include "teacher.h"
#include "student.h"
#include <QDebug>

void populateSchool(School *school)
{
    for(int t = 0; t < 5; t++)
    {
        Teacher* teacher = new Teacher(school);
        teacher->setObjectName("Teacher " + QString::number(t));

        for(int s = 0; s < 20; s++)
        {
            Student* student = new Student(teacher);
            student->setObjectName("Student " + QString::number(t));
        }
    }

    //school->children().append() ????
}

void showTeachers(School *school)
{
    qInfo() << "Teachers:";
    foreach(QObject* object, school->children())
    {
        Teacher *teacher = qobject_cast<Teacher*>(object);
        if(teacher) qInfo() << teacher;
    }
}

void showStudents(School *school)
{
    qInfo() << "Students:";
    foreach(QObject* object, school->children())
    {
        Teacher *teacher = qobject_cast<Teacher*>(object);
        if(teacher)
        {
            foreach(QObject* object, teacher->children())
            {
                Student *student = qobject_cast<Student*>(object);
                if(student) qInfo() << student;
            }
        }
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    School school;
    populateSchool(&school);
    showTeachers(&school);
    showStudents(&school);

    return a.exec();
}
