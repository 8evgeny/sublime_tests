#include <QTextStream>

// Добавляем для лучшей читабельности кода
const int STR_EQUAL=0;

int main() {

   QTextStream out(stdout);

   // Будем сравнивать следующие 3 строки
   QString a = "Rain";
   QString b = "rain";
   QString c = "rain\n";

   // Первое сравнение - отличие сразу же в первом символе
   if (QString::compare(a, b) == STR_EQUAL) {
     out << "a, b are equal" << Qt::endl;
   } else {
     out << "a, b are not equal" << Qt::endl;
   }

   out << "In case insensitive comparison:" << Qt::endl;

   // С помощью флага Qt::CaseInsensitive отключаем чувствительность к регистру
   if (QString::compare(a, b, Qt::CaseInsensitive) == STR_EQUAL) {
     out << "a, b are equal" << Qt::endl; // и получаем равные строки
   } else {
     out << "a, b are not equal" << Qt::endl;
   }

   if (QString::compare(b, c) == STR_EQUAL) {
     out << "b, c are equal" << Qt::endl;
   } else {
     out << "b, c are not equal" << Qt::endl;
   }

   // Удаляем символ новой строки в строке c
   c.chop(1);

   out << "After removing the new line character" << Qt::endl;

   if (QString::compare(b, c) == STR_EQUAL) {
     out << "b, c are equal" << Qt::endl; // теперь наши строки равны
   } else {
     out << "b, c are not equal" << Qt::endl;
   }

   return 0;
}
