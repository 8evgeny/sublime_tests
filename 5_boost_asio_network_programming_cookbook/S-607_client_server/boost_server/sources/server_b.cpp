#include <QDateTime>
#include <algorithm>
#include <atomic>
#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <sstream>
#include <thread>
#include <vector>

using namespace boost;
std::string nameFile;
int lenth_file;
int numberPart = 0;
QDateTime time_start;
std::list<std::string> file_to_write;
class Service {
 public:
  Service(std::shared_ptr<asio::ip::tcp::socket> sock) : m_sock(sock) {}

  void StartHandling() {

    //    auto end = "\n\n";
    //    asio::async_read_until(*m_sock.get(), m_request, end,
    QDateTime time_(QDateTime::currentDateTime());
    time_start = time_;

    asio::async_read(*m_sock.get(), m_request,
    [this](const boost::system::error_code& ec, std::size_t bytes_transferred) {
     QDateTime time_end(QDateTime::currentDateTime());
     int msec = time_end.toMSecsSinceEpoch() - time_start.toMSecsSinceEpoch();
     std::cout << "long receiving: " << msec <<"ms ";

//     std::cout << "m_request.size: " << m_request.size() << " ";
     onRequestReceived(ec, bytes_transferred);
                     });
  }

  void receiveServiceData(std::string& received) {
    file_to_write.clear();
    // received.pop_back(); received.pop_back(); //удаляем последние endl
    std::string name_and_len = received.substr(
        7);  //читаем строку, начиная с длины контрольных звeздочек
    std::string len = name_and_len.substr(name_and_len.find(" ") +
                                          1);  //читаем все что после пробела
    lenth_file = stoi(len) - 1;
    std::string name = name_and_len;
    for (unsigned int i = 0; i < len.size() + 1; ++i) {
      name.pop_back();
    }  //удаляем длину строки длины - остается имя
    nameFile = name + "_received";
    std::ofstream file;
    file.open(nameFile,
              std::ios::out | std::ios::binary);  //готовим файл к записи
    std::cout << "name file: " << nameFile ;
  }

  std::string receiveNumberData(std::string& received) {
    std::string numPart = received.substr(7, 5);
    numberPart = stoi(numPart);
    std::cout << "receive file. "  ;
    return received.substr(12);
  }

  void writeData() {
    std::ofstream file;
    file.open(nameFile, std::ios::app | std::ios::binary);
    int i = 0;
    for (auto ind = file_to_write.begin(); ind != file_to_write.end(); ++ind) {
      ++i;
      //  //у последнего контейнера удаляем 2 раза \n
      //        auto it = ind;
      //        ++it;
      //        if (it == file_to_write.end()){
      //          auto xx = *ind;
      //          xx.pop_back();
      //          xx.pop_back();
      //          file_to_write.pop_back();
      //          file_to_write.push_back(xx);
      //        }
      std::cout << i << " part_to_write size: " << (*ind).size() << std::endl;
      file << *ind;
    }
    file_to_write.clear();
  }

  void eraseData(std::string& received) {
    std::string erase_in_string = received.substr(
        7);  //читаем строку, начиная с длины контрольных звeздочек
    //парсим строку типа  5*12*22*
    std::vector<std::string> errCodes;
    while (erase_in_string.size() > 0) {
      auto len = erase_in_string.find("*", 0);  //длина кода ошибки
      std::string errcode = erase_in_string.substr(0, len);
      errCodes.push_back(errcode);
      erase_in_string = erase_in_string.substr(len + 1);
    }

    //удаляем
    for (unsigned int i = 0; i < errCodes.size(); ++i) {
      auto badData = errCodes[i];
      int del = stoi(badData);
      std::cout << "errcode: " << del << std::endl;
      auto it = file_to_write.begin();
      for (int i = 1; i < del; ++i) {  //шагаем на нужный блок данных
        ++it;
      }
      it->erase();
    }
  }

 private:
  void onRequestReceived(const boost::system::error_code& ec,
                         std::size_t bytes_transferred) {
    //  if ( ec.value() == 0){
    request_size = m_request.size();
    std::stringstream ss;
    ss << &m_request;
    std::string received = ss.str();  //тут полученное от клиента
    std::string partFile;  //часть файла для записи без служебной информации

    if (received.find("* * * *", 0, 7) == 0){//получаем имя и длину файла
    receiveServiceData(received);
    }
    if (received.find("*^*^*^*", 0, 7) == 0) {
      partFile =
          receiveNumberData(received);  //извлекаем номер части файла и
                                        //возвращает часть файла для записи
      file_to_write.push_back(partFile);
    }

    if (received.find("*^***^*", 0, 7) == 0) {

      // Файл пока не пишем на диск - работать будем с данными в list
      //      writeData();  // команда на запись файла и удаление последних 2
      //      переводов строки
    }
      if (received.find("*^^*^^*", 0, 7) == 0) {
        eraseData(received);  // команда на удаление ошибок
        writeData();          //пишем в файл
      }
    //  }
    //  if ( ec.value() != 0) {
    //    std::cout<<"error!!! transferred: "<<bytes_transferred<<std::endl;
    //    std::cout << "Error occured! Error code = "  << ec.value() << ".
    //    Message: " << ec.message(); onFinish(); return;
    //  }

    // Process the request.
    m_response = ProcessRequest(std::to_string(
        request_size - 12));  //отправляем меньше на длину префикса
    std::cout << " transferred " << bytes_transferred - 12<<" byte."<<std::endl;


    // Initiate asynchronous write operation.
    asio::async_write(*m_sock.get(), asio::buffer(m_response),
                      [this](const boost::system::error_code& ec,
                             std::size_t bytes_transferred) {
                        onResponseSent(ec, bytes_transferred);
                      });
  }

  void onResponseSent(const boost::system::error_code& ec,
                      std::size_t bytes_transferred) {
    //  if (ec.value() != 0) {
    //  std::cout << "Error occured! Error code = " << ec.value() << ". Message:
    //  " << ec.message();
    //  }
    onFinish();
  }

  // Here we perform the cleanup.
  void onFinish() { delete this; }

  std::string ProcessRequest(std::string size) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // Prepare and return the response message.
    std::string response = size + "\n";
    return response;
  }

 private:
  std::shared_ptr<asio::ip::tcp::socket> m_sock;
  std::string m_response;
  asio::streambuf m_request;
  unsigned long request_size;
};

class Acceptor {
 public:
  Acceptor(asio::io_service& ios, unsigned short port_num)
      : m_ios(ios),
        m_acceptor(m_ios, asio::ip::tcp::endpoint(asio::ip::address_v4::any(),
                                                  port_num)),
        m_isStopped(false) {}

  // Start accepting incoming connection requests.
  void Start() {
    m_acceptor.listen();
    InitAccept();
  }
  // Stop accepting incoming connection requests.
  void Stop() { m_isStopped.store(true); }

 private:
  void InitAccept() {
    std::shared_ptr<asio::ip::tcp::socket> sock(
        new asio::ip::tcp::socket(m_ios));
    m_acceptor.async_accept(
        *sock.get(), [this, sock](const boost::system::error_code& error) {
          onAccept(error, sock);
        });
  }

  void onAccept(const boost::system::error_code& ec,
                std::shared_ptr<asio::ip::tcp::socket> sock) {
    if (ec.value() == 0) {
      (new Service(sock))->StartHandling();
    } else {
      std::cout << "Error occured! Error code = " << ec.value()
                << ". Message: " << ec.message();
    }

    // Init next async accept operation if acceptor has not been stopped yet.
    if (!m_isStopped.load()) {
      InitAccept();
    } else {
      // Stop accepting incoming connections and free allocated resources.
      m_acceptor.close();
    }
  }

 private:
  asio::io_service& m_ios;
  asio::ip::tcp::acceptor m_acceptor;
  std::atomic<bool> m_isStopped;
};

class Server {
 public:
  Server() { m_work.reset(new asio::io_service::work(m_ios)); }

  // Start the server.
  void Start(unsigned short port_num, unsigned int thread_pool_size) {
    std::cout << "START THE SERVER port: " << port_num << std::endl;
    assert(thread_pool_size > 0);
    // Create and start Acceptor.
    acc.reset(new Acceptor(m_ios, port_num));
    acc->Start();

    // Create specified number of threads and
    // add them to the pool.
    for (unsigned int i = 0; i < thread_pool_size; i++) {
      std::unique_ptr<std::thread> th(
          new std::thread([this]() { m_ios.run(); }));
      m_thread_pool.push_back(std::move(th));
    }
  }

  // Stop the server.
  void Stop() {
    std::cout << "Stop the server" << std::endl;
    acc->Stop();
    m_ios.stop();
    for (auto& th : m_thread_pool) {
      th->join();
    }
  }

 private:
  asio::io_service m_ios;
  std::unique_ptr<asio::io_service::work> m_work;
  std::unique_ptr<Acceptor> acc;
  std::vector<std::unique_ptr<std::thread>> m_thread_pool;
};

const unsigned int DEFAULT_THREAD_POOL_SIZE = 2;

int main(int argc, char** argv) {
  unsigned short port_num = 0;
  if (argc == 2) port_num = static_cast<short unsigned int>(atoi(argv[1]));
  if (argc != 2) std::cout << "invalid port number" << std::endl;
  //    unsigned short port_num = 3333;

  try {
    Server srv;
            unsigned int thread_pool_size =
            std::thread::hardware_concurrency() * 2;
//    unsigned int thread_pool_size = 1;
    std::cout << "hardware: " << std::thread::hardware_concurrency()
              << std::endl;
    if (thread_pool_size == 0) thread_pool_size = DEFAULT_THREAD_POOL_SIZE;

    srv.Start(port_num, thread_pool_size);

    std::this_thread::sleep_for(std::chrono::hours(1000000000));
    srv.Stop();
  } catch (system::system_error& e) {
    std::cout << "Error occured! Error code = " << e.code()
              << ". Message: " << e.what();
  }

  return 0;
}
