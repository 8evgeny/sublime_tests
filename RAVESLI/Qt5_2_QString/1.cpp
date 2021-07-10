#include <QTextStream> // подключаем необходимый заголовочный файл

int main() {

   QTextStream out(stdout);

   // Создаем строку типа QString
   QString a = "love";

   // Добавляем текст в конец строки
   a.append(" chess");

   // Добавляем текст в начало строки
   a.prepend("I ");

   // Выводим строку
   out << a << Qt::endl;

   // Выводим количество символов строки
   out << "The a string has " << a.count() << " characters" << Qt::endl;

   // Выводим всю строку в верхнем регистре
   out << a.toUpper() << Qt::endl;

   // Выводим всю строку в нижнем регистре
   out << a.toLower() << Qt::endl;

   return 0;
}
