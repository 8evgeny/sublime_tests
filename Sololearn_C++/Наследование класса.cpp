// InheritanceExample - пример наследования, при котором
// конструктор наследника передает
// информацию конструктору базового
// класса 
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <strings.h>
using namespace std;
// Advisor - пустой класс
class Advisor {};
const int MAXNAMESIZE = 40;
class Student
{
public:
Student(char *pName = "no name")
: average(0.0), semesterHours(0)
{
strncpy(name, pName, MAXNAMESIZE);
name[MAXNAMESIZE - 1] = '\0';
cout << "Конструктор Student "
<< name
<< endl;
}
void addCourse(int hours, float grade)
{
cout << "Добавляем оценку для " << name << endl;
average = (semesterHours * average + grade);
semesterHours += hours;
average = average / semesterHours;
}
int hours( ) { return semesterHours;}
float gpa( ) { return average;}
protected:
char name[MAXNAMESIZE];
int semesterHours;
float average;
};
class GraduateStudent : public Student
{
public:
GraduateStudent(char *pName, Advisork adv, float qG = 0.0)
: Student(pName), advisor(adv), qualifierGrade(qG)
{
cout << "Конструктор GraduateStudent "
<< pName
<< endl;
float qualifier( ) { return qualifierGrade; }
protected:
float qualifierGrade;
};

int main(int nNumberofArgs, char* pszArgs[])
{
Advisor advisor;
// Создание двух типов студентов
Student llu( "Cy N Sense");
GraduateStudent gs("Matt Madox" , advisor, 1.5);
// Добавляем им оценки
llu.addCourse(3, 2.5);
gs.addCourse(3, 3.0);
// Выводим их
cout << "Оценка Matt = "
<< gs.qualifier()
<< endl;
// Пауза для того, чтобы посмотреть
// на результат работы программы
system( "PAUSE");
return 0;
}
// В этой программе продемонстрировано создание и использование двух объектов—
// Student и GraduateStudent.Вывод программы выглядитследующим образом.
// Конструктор Student Су N Sense
// Конструктор Student Matt Madox
// Конструктор GraduateStudent Matt Madox
// Добавляем оценку для Су N Sense
// Добавляем оценку для Matt Madox
// Оценка Matt = 1.5

