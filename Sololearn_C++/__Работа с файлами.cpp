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
//int i =1;
char p[17];
for(int i=1;i<=108;i++){
itoa (i, p, 10);  //Преобразование типа - в 10тичный формат
//printf(p);  // Можно так выводить
//cout<<p<<"\n";

string filename1 ="H:\\1\\Python\\files_fo_primery\\";
string filename2 = p;
filename2 += ".txt"; 
string filename = filename1+filename2; // Тут уже полное имя c i
//cout<<"\n"<< filename <<"\n";

// fstream читает массив char-ов, вы пытаетесь ему подсунуть string, 
//нужно вашу строку filename, взять и использовать метод
// filename.c_str();
// тоже самое относится к расширению данных 	
ofstream MyFile;
const char * fnane_in_char = filename.c_str(); // ГЕНИАЛЬНО  !!!!!!!
//cout<<fnane_in_char<<"\n";
MyFile.open(fnane_in_char);

for(int j=1;j<=108;j++){
MyFile <<j<< "  OMM NAMAHA SHIVAYA \n"; 
} 
//}
cout <<" "<< i <<'\t'<<" creating file - "<<'\t'<< filename2 << '\n';
MyFile.close();
//}
}
getch(); 
return 0;
}


