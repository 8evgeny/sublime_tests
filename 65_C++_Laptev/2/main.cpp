#include <iostream>

using namespace std;

int main()
{
    unsigned int counter = 0;
    double summa =0.0, number;
    while (cout << "Введите число: ", cin >> number)      // правильнее
                                                          // условие
                summa += number, ++counter;               // один оператор
    cout << "Среднее=" << summa / counter << endl;

/*  В программе написан совершенно необычный оператор цикла. В условии прописаны сразу и вывод приглашения,
    и ввод числа через запятую. Дело в том, что и вывод приглашения, и ввод значений на самом деле являются
    выражениями. В операторы они превращаются только тогда, когда мы ставим в конце точку с запятой.
    И запятая в языке C++ тоже является операцией, причем с двумя аргументами! Результатом этой операции
    является результат второго (правого) выражения. */

    return 0;

}