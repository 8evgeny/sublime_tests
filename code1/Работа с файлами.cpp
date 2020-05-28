#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main() {
  //ofstream MyFile;
  //for(int i=1,i<500,i++) { 
  //int i=1;
  //string name = i;
int i =1;

// stringstream ss;
// ss << i;
// string name = ss.str();

char p[17];
for(i=1;i<=10;i++){
itoa (i, p, 10);  //Преобразование типа
//printf(p);  // Можно так выводить
cout<<p<<"\n";
}

string filename ="H:\\1\\Python\\files_fo_primery\\";
filename += p;
filename += ".txt";

cout<<"\n"<< filename <<"\n";


// fstream читает массив char-ов, вы пытаетесь ему подсунуть string, 
//нужно вашу строку filename, взять и использовать метод
// filename.c_str();
// тоже самое относится к расширению данных 	

// char Path_sym = patch.c_str();
// cout<<"\n"<< Path_sym <<"\n";
// auto MyFile = filename; //+ format;
ofstream MyFile;

// string fname;
// fname = "H:\\1\\Python\\files_fo_primery\\1.txt";


const char * fnane_in_char = filename.c_str(); // ГЕНИАЛЬНО  !!!!!!!

cout<<fnane_in_char<<"\n";
MyFile.open(fnane_in_char);
//MyFile.open("H:\\1\\Python\\files_fo_primery\\1.txt"); 
  //for(int j=1,j<=10,j++) {
for(int i=1;i<100;i++){
MyFile << "OMM NAMAHA SHIVAYA \n"; 
} 
//}
cout << "creating file   " << MyFile << '\n';
MyFile.close();
//}

getch(); 
return 0;
}


