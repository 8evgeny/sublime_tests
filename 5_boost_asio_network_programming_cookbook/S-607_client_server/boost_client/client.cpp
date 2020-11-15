#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <list>
#include <string>
#include <vector>
#include <map>
//using namespace std;


#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
typedef boost::asio::streambuf streambufer;
enum { max_length = 16000 };

//std::string readFile_str1(const std::string& fileName) {
//    return std::string((std::istreambuf_iterator<char>(std::ifstream(fileName))),
//        std::istreambuf_iterator<char>());
//}
std::string readFile_str2(const std::string& fileName) {
    //file to string
    std::ifstream f(fileName);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

char* readFile(const std::string& fileName) {
    std::ifstream fin(fileName);
  // get pointer to associated buffer object
  std::filebuf* pbuf = fin.rdbuf();
  // get file size using buffer's members
  std::size_t size = pbuf->pubseekoff (0,fin.end,fin.in);
  pbuf->pubseekpos (0,fin.in);
  // allocate memory to contain file data
  char* buffer=new char[size];
  // get file data
  pbuf->sgetn (buffer,size);
  fin.close();
  return buffer;
}

std::string readFile_str3(const std::string& fileName) {
    std::ifstream f(fileName);
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    std::string s(size, ' ');
    f.seekg(0);
    f.read(&s[0], size); // по стандарту можно в C++11, по факту работает и на старых компиляторах
    return s;
}

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 4)
    {
      std::cerr << "Usage: client <host> <port> <img>\n";
      return 1;
    }

    boost::asio::io_service io_service;
    tcp::socket s(io_service);

    tcp::resolver resolver(io_service);
    boost::asio::connect(s, resolver.resolve({argv[1], argv[2]}));
   //    std::string message ="test_message";
   //читаем файл в строку
    auto file =  readFile_str3 (std::string(argv[3]));
//    auto file_char = readFile(std::string(argv[3]));
    auto file_str =  readFile(std::string(argv[3]));

//    std::cout<<file<<std::endl<<std::endl<<file_str;



//    size_t request_length = std::strlen(file.c_str());

//    char request[5555];
//    for (unsigned int i=0;i<5555;++i){
//        request[i]=file[i];
//        std::cout<<request[i];
//    }

    auto buff = boost::asio::buffer(file.c_str(), file.size());
//    boost::asio::write(s, buff);

    streambufer sbuff;
    std::ostream out(&sbuff);
//    out << "file_lenth: "<<file.size()<<std::endl<<file.c_str();
      out << file_str;
    //отправляем файл в сокет
    write(s, sbuff);
//    write(s, buff);

//    s.write_some(buff);
//    s.send(sbuff);



    std::cout<<"send_message : "<<file.size()<<" "<<file<<std::endl;

    //тестовая запись файла
        FILE *test;
        test=fopen( "test_test", "wb");
        fwrite (file.c_str(), file.size(), 1, test);

    //получаем ответ сервера
    char reply[max_length];
    size_t reply_length = boost::asio::read(s,boost::asio::buffer(reply, file.size()));
    std::cout <<"reply from server is: "<<reply<<std::endl;



    //std::this_thread::sleep_for(std::chrono::milliseconds(15));
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
