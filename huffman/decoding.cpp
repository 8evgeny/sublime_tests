// decoding.cpp :
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Для декодирования файла нам нужно восстановить дерево.
//для этого нам нужна таблица частоты вхождения каждого символа

// Узел дерева
    class node
    {
    public:
        node(){left=right=nullptr;}              // Конструктор для потомков
        node(node *l,node *r) // Конструктор для создания родителя
        {
        left=l;
        right=r;
        a=l->a+r->a;
        }
        int a;      // число в узле
        char c;     //символ в узле
        node *left;
        node *right;
    };

// Структура для сортировки list
    struct MyCompare
    {
    bool operator()(const node* l, const node* r) const { return l->a < r->a; }
    };

// Печать дерева
    void PrintTree(node *root, unsigned k=0)
        {
             if (root !=nullptr)
            {
             PrintTree(root->left,k+4) ;
              for(unsigned i=0; i<k; i++)
              {
               cout<<"  ";
              }
              if(root->c) cout<<root->a<<" ("<<root->c<<") "<<endl;
              else cout<<root->a<<endl;
              PrintTree(root->right,k+3);
            }
        }

    int main()
{
cout<<"Start decoding file CODDING_DATA.HUFFMAN"<<endl;
    setlocale(LC_ALL,"Russian");

    int NUMBER;  //Общее число символов в таблице
    int lenth_in; //Длина сжатых данных
    FILE *in;
    in=fopen("CODDING_DATA.HUFFMAN", "rb");
//Получаем длину таблицы и длину сжатого файла
    fread (&NUMBER, sizeof NUMBER, 1, in);
    fread (&lenth_in, sizeof lenth_in, 1, in);
//В зависимости от полученных значений создаем 3 массива
    int DIG[NUMBER];
    char SYM[NUMBER];
    vector<char> V_IN;
    char cc;
//    char DATA_IN[lenth_in];
//Читаем в массивы данные
    fread (SYM, sizeof SYM, 1, in);
    fread (DIG, sizeof DIG, 1, in);

    for (int z=0;z<lenth_in;++z)
    {
        fread (&cc,sizeof cc,1,in);
        V_IN.push_back(cc);
    }
//    int  name_size;
//    fread (&name_size, sizeof name_size, 1, in);
//    char NAME[name_size+1];
//    fread (NAME, sizeof NAME, 1, in);

    fclose (in);

// Восстанавливаем кодовую таблицу - создаем map
    pair <char, int> p;
    map<char,int> m;
    int i=0;
    for (i=0; i<NUMBER; ++i)
     {
        p.first=SYM[i];
        p.second=DIG[i];
        m.insert(p);
     }

//Список указателей на узлы нашего дерева
        list <node*> t;

//Проходим по map и для каждого символа создаем узел дерева node и помещаем его в list
        map<char,int>::iterator itmap;
        for(itmap=m.begin();itmap !=m.end(); ++itmap)
        {
         node *p = new node;
         p->c=itmap->first;
         p->a=itmap->second;
         t.push_back(p);
        }

//Строим дерево
             while (t.size()!=1) // Цикл пока в контейнере не останется корень
             {
                t.sort(MyCompare());
                node *SONL = t.front();
                t.pop_front();
                node *SONR =t.front();
                t.pop_front();
                node *parrent = new node(SONL,SONR);
                t.push_back(parrent);
             }
// на выходе цикла остался 1 элемент - он-же корень
            node *root = t.front();

//Печать дерева
//               cout<<endl<<"--------------------    BINARE TREE   ------------------------- "<<endl;
//               PrintTree(root);

// Данные будем писать в файл ORIGINAL_DATA

    ofstream DATA_OUT("SOURSE_DATA", ios::out | ios::binary);


    node *pp = root;
    int count=0;
    char byte;
//Процедура декодирования
   byte = V_IN[0];
   for(int i=1;i<(lenth_in);)
     {
        bool b = byte & (1 << (7-count) ) ;
        if (b) pp=pp->right;
        else pp=pp->left;
            if (pp->left==nullptr && pp->right==nullptr)
            {
                DATA_OUT<<pp->c;
                pp=root;
            }
        count++;
        if (count==8)
        {
            count=0;
            byte = V_IN[i];
            ++i;
        }
    }
    DATA_OUT.close();
    cout<<"Creating file "<<"SOURSE_DATA"<<endl;
    system("pause");
return 0;
}
















