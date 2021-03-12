#include <stdlib.h>
#include <time.h> /* time_t, struct tm, difftime, time, mktime */

#include <algorithm>
#include <cstdlib>
#include <execution>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
using namespace std;

// Узел дерева
class Node {
 public:
  int num_in_node{0};   // число в узле
  char char_in_node{};  //символ в узле
  Node* left_branch;
  Node* right_branch;

  Node() {  // Конструктор для потомков
    left_branch = nullptr;
    right_branch = nullptr;
  }
  Node(Node* left, Node* right) {  // Конструктор для создания родителя
    left_branch = left;
    right_branch = right;
    num_in_node = left->num_in_node + left->num_in_node;
  }
};

// Структура для сортировки list
struct Compare_Node {
  bool operator()(const Node* l, const Node* r) const {
    return l->num_in_node < r->num_in_node;
  }
};

// Печать дерева
void PrintTree(Node* root, unsigned k = 0) {
  if (root != nullptr) {
    PrintTree(root->left_branch, k + 4);
    for (unsigned i = 0; i < k; i++) {
      cout << "  ";
    }
    if (root->char_in_node)
      cout << root->num_in_node << " (" << root->char_in_node << ") " << endl;
    else
      cout << root->num_in_node << endl;
    PrintTree(root->right_branch, k + 3);
  }
}

//Глобальные переменные code  и  tabl
vector<bool> code;
map<char, vector<bool> > tabl;

//Строим таблицу кодирования
void BuildTable(Node* root) {
  if (root->left_branch != nullptr) {
    code.push_back(0);
    BuildTable(root->left_branch);
  }  // Рекурсия
  if (root->right_branch != nullptr) {
    code.push_back(1);
    BuildTable(root->right_branch);
  }

  if (root->left_branch == nullptr && root->right_branch == nullptr)
    tabl[root->char_in_node] = code;  //лист

  code.pop_back();  // один символ из vector убираем - фактически встаем на
                    // предыдущий элемент
}

void PrintTable() {
  cout << endl
       << "--------------------    CODDING TABL   ------------------------- "
       << endl;
  int l = 1;
  for (auto i : tabl) {
    cout << l << "\t" << i.first << " - ";
    auto itboolvector = i.second.begin();
    for (itboolvector = i.second.begin(); itboolvector != i.second.end();
         ++itboolvector) {
      cout << *itboolvector;
    }
    cout << endl;
    ++l;
  }
}

// Вывод помощи о пользовании программой
void help() { cout << "encoding name_input_file\n"; }

int main_(int argc, char* argv[]) {
  if (argc != 2) {
    help();
    exit(2);
  }

  time_t timer;
  struct tm y2k = {0};
  double seconds;
  double seconds1;
  y2k.tm_hour = 0;
  y2k.tm_min = 0;
  y2k.tm_sec = 0;
  y2k.tm_year = 100;
  y2k.tm_mon = 0;
  y2k.tm_mday = 1;
  time(&timer); /* get current time; same as: timer = time(NULL)  */
  seconds = difftime(timer, mktime(&y2k));

  cout << "Encoding started" << endl;
  setlocale(LC_ALL, "Russian");

  ifstream in_sourse(argv[1], ios::in | ios::binary);

  map<char, int> m;
  cout << "First scan of the file" << endl;
  while (!in_sourse.eof()) {
    char c = in_sourse.get();
    //Записывааем символ в map и увеличиваем на 1 число вхождений
    m[c]++;
  }

  // Выводим таблицу частоты символов

  //        cout<<" ------------------  Character frequency table
  //        --------------- "<<endl; int k =1; for(auto i=m.begin();i !=m.end();
  //        ++i)
  //        {
  //        cout<< k<<"\t"<<i->first<<" - "<<i->second<<endl;
  //        ++k;
  //        }

  //Список указателей на узлы нашего дерева
  list<Node*> list_pNode;
  cout << "Creating a binary tree" << endl;
  //Проходим по map и для каждого символа создаем узел дерева node и помещаем
  //его в list
  map<char, int>::iterator itmap;
  for (itmap = m.begin(); itmap != m.end(); ++itmap) {
    Node* p = new Node;
    p->char_in_node = itmap->first;
    p->num_in_node = itmap->second;
    list_pNode.push_back(p);
  }

  //Работаем с деревом
  while (list_pNode.size() != 1) {  // пока не останется 1
    //  list_pNode.sort(execution::par, Compare_Node());
    list_pNode.sort(Compare_Node());
    Node* left_son = list_pNode.front();
    list_pNode.pop_front();
    Node* right_son = list_pNode.front();
    list_pNode.pop_front();
    Node* parrent = new Node(left_son, right_son);
    list_pNode.push_back(parrent);
  }
  // на выходе цикла остался 1 элемент - он-же корень
  Node* root = list_pNode.front();
  long lenth_in = root->num_in_node;
  cout << "sourse file - " << lenth_in << " bytes" << endl;
  //Печать дерева

  //    cout<<endl<<"--------------------    BINARE TREE
  //    ------------------------- "<<endl; PrintTree(root);

  // Ассоциируем символы с кодами - создаем структуру map  tabl
  BuildTable(root);

  // Печатаем tabl

  //   PrintTable();

  // Перемещаем указатель в начало файла
  cout << "Second scan of the file - start encodding" << endl;
  in_sourse.clear();
  in_sourse.seekg(0);
  //        ofstream out_code("CODDING_DATA", ios::out | ios::binary);
  int count = 0;
  char buf = 0;  //Буфер вывода
  int lenth_out = 0;

  vector<char> V_OUT;

  while (!in_sourse.eof()) {
    //Получаем символ из файла
    char c = in_sourse.get();
    //Код, соответствующий полученному символу берем из таблицы кодирования
    vector<bool> kod_simvola = tabl[c];
    //Формируем выходной поток битов (по 8)
    for (int n = 0; n < kod_simvola.size(); ++n) {
      buf = buf | kod_simvola[n] << (7 - count);
      count++;
      if (count == 8) {
        count = 0;
        V_OUT.push_back(buf);
        buf = 0;
        ++lenth_out;
      }
    }
  }
  in_sourse.close();

  // Для декодирования нам нужно будет построить дерево - для этого нужно
  // передать все символы и частоту вхождения каждого символа Выдаем колл.
  // символов таблицы, колл символов сжатого файла и три массива
  FILE* out;
  char* NAME = argv[1];

  //    char *SUFFIX = {".Huffman"};
  //    string NAME_STRING = NAME;
  //    string SUFFIX_STRING = SUFFIX;
  //    string FULLNAME = NAME_STRING+SUFFIX_STRING;
  //    const char *NAME_CHAR = FULLNAME.c_str();

  out = fopen("CODDING_DATA.HUFFMAN", "wb");

  int NUMBER;
  NUMBER = m.size();
  int DIG[m.size()];
  char SYM[m.size()];

  int k = 0;
  for (auto i = m.begin(); i != m.end(); ++i) {
    DIG[k] = i->second;
    SYM[k] = i->first;
    ++k;
  }

  fwrite(&NUMBER, sizeof NUMBER, 1, out);
  fwrite(&lenth_out, sizeof lenth_out, 1, out);
  fwrite(SYM, sizeof SYM, 1, out);
  fwrite(DIG, sizeof DIG, 1, out);
  char cc;
  for (int z = 0; z < lenth_out; ++z) {
    cc = V_OUT[z];
    fwrite(&cc, sizeof cc, 1, out);
  }

  //    int size_name = sizeof argv[1];
  //    ++size_name;
  //    fwrite (&size_name, sizeof size_name, 1, out);
  //    fwrite (argv[1], (sizeof argv[1]+1), 1, out);
  fclose(out);

  cout << "Creating file "
       << "CODDING_DATA.HUFFMAN"
       << " - " << lenth_out << " bytes" << endl;
  cout << "ratio  " << 100 - (100 * lenth_out / lenth_in) << "%" << endl;
  cout << "Encoding finishing" << endl;

  time(&timer); /* get current time; same as: timer = time(NULL)  */

  seconds1 = difftime(timer, mktime(&y2k));

  cout << "Time encoding - " << seconds1 - seconds << " seconds" << endl;

  return 0;
}
