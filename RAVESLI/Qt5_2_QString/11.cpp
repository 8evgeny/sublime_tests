#include <QTextStream>

int main() {

   QTextStream out(stdout);

   QString field1 = "Name: ";
   QString field2 = "Occupation: ";
   QString field3 = "Residence: ";
   QString field4 = "Marital status: ";

   // Вычисляем размер самой широкой строки
   int width = field4.size();

   out << field1.rightJustified(width, ' ') << "Robert\n";
   out << field2.rightJustified(width, ' ') << "programmer\n";
   out << field3.rightJustified(width, ' ') << "New York\n";
   out << field4.rightJustified(width, ' ') << "single\n";

   return 0;
}
