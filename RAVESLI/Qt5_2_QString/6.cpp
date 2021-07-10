#include <QTextStream>

int main() {

  QTextStream out(stdout);

  QString str = "There are many stars.";

  // Способ №1
  foreach (QChar qc, str) {
    out << qc << " ";
  }

  out << Qt::endl;

  // Способ №2
  for (QChar *it=str.begin(); it!=str.end(); ++it) {
    out << *it << " " ;
  }

  out << Qt::endl;

  // Способ №3
  for (int i = 0; i < str.size(); ++i) {
    out << str.at(i) << " ";
  }

  out << Qt::endl;

  return 0;
}
