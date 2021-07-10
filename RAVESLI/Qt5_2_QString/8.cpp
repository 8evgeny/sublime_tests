#include <QTextStream>

int main() {

  QTextStream out(stdout);

  // Наши строки
  QString s1 = "12";
  QString s2 = "15";
  QString s3, s4;

  // С помощью метода toInt() конвертируем строки в целочисленный тип данных, а затем складываем получившиеся числа
  out << s1.toInt() + s2.toInt() << Qt::endl;

  int n1 = 30;
  int n2 = 40;

  // С помощью метода setNum() выполняем конвертацию из целочисленного типа данных в QString, а затем соединяем уже строки
  out << s3.setNum(n1) + s4.setNum(n2) << Qt::endl;

  return 0;
}
