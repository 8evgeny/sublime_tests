#include <QDateTime>

#include "client.h"
int sending = -1;
int errors = 0;
QDateTime time_start;
bool partSend = false;

std::vector<std::string> errorParts;
// using boost::asio::ip::tcp;
typedef boost::asio::streambuf streambufer;
using namespace boost;

// Function pointer type that points to the callback function which is called
// when a request is complete.
typedef void (*Callback)(unsigned int request_id, const std::string& response,
                         const system::error_code& ec);

// Structure represents a context of a single request.
struct Session {
  Session(asio::io_service& ios, const std::string& raw_ip_address,
          unsigned short port_num, const std::string& request, unsigned int id,
          Callback callback)
      : m_sock(ios),
        m_ep(asio::ip::address::from_string(raw_ip_address), port_num),
        m_request(request),
        m_id(id),
        m_callback(callback),
        m_was_cancelled(false) {}

  asio::ip::tcp::socket m_sock;  // Socket used for communication
  asio::ip::tcp::endpoint m_ep;  // Remote endpoint.
  std::string m_request;         // Request string.

  // streambuf where the response will be stored.
  asio::streambuf m_response_buf;
  std::string m_response;  // Response represented as a string.

  // Contains the description of an error if one occurs during the request
  // lifecycle.
  system::error_code m_ec;

  unsigned int m_id;  // Unique ID assigned to the request.

  // Pointer to the function to be called when the request completes.
  Callback m_callback;
  bool m_was_cancelled;
  std::mutex m_cancel_guard;
};

class AsyncTCPClient : public boost::noncopyable {
 public:
  AsyncTCPClient() {
    m_work.reset(new boost::asio::io_service::work(m_ios));
    m_thread.reset(new std::thread([this]() { m_ios.run(); }));
  }

  void sendFile_to_server(std::string& to_server,
                          const std::string& raw_ip_address,
                          unsigned short port_num, Callback callback,
                          unsigned int request_id) {
    std::string request = to_server;
    std::shared_ptr<Session> session = std::shared_ptr<Session>(new Session(
        m_ios, raw_ip_address, port_num, request, request_id, callback));
    session->m_sock.open(session->m_ep.protocol());

    /* Add new session to the list of active sessions so that we can access it
       if the user decides to cancel the corresponding request before it
       completes. Because active sessions list can be accessed from multiple
       threads, we guard it with a mutex to avoid data corruption.*/
    std::unique_lock<std::mutex> lock(m_active_sessions_guard);
    m_active_sessions[request_id] = session;
    lock.unlock();

    session->m_sock.async_connect(
        session->m_ep, [this, session](const system::error_code& ec) {
          if (ec.value() != 0) {
            session->m_ec = ec;
            onRequestComplete(session);
            return;
          }
          std::unique_lock<std::mutex> cancel_lock(session->m_cancel_guard);
          if (session->m_was_cancelled) {
            onRequestComplete(session);
            return;
          }
          QDateTime time_(QDateTime::currentDateTime());
          time_start = time_;

          asio::async_write(
              session->m_sock,
              asio::buffer(session->m_request),  // Sending request
              [this, session](const boost::system::error_code& ec,
                              std::size_t bytes_transferred) {
                partSend = true;



                session->m_sock.shutdown(
                    boost::asio::socket_base::shutdown_send);

                std::cout << "send: " << bytes_transferred
                          << " ";

                //  if (ec.value() != 0) {
                //   session->m_ec = ec;
                //   onRequestComplete(session);
                //   return;
                //  }

                std::unique_lock<std::mutex> cancel_lock(
                    session->m_cancel_guard);
                if (session->m_was_cancelled) {
                  onRequestComplete(session);
                  return;
                }
                //Читаем ответ сервера
                asio::async_read_until(
                    session->m_sock, session->m_response_buf, '\n',
                    [this, session](const boost::system::error_code& ec,
                                    std::size_t bytes_transferred) {
           QDateTime time_end(QDateTime::currentDateTime());
           int msec = time_end.toMSecsSinceEpoch() - time_start.toMSecsSinceEpoch();
           std::cout << "long sending: " << msec << std::endl;




                      if (ec.value() != 0) {
                        session->m_ec = ec;
                      } else {
                        std::istream strm(&session->m_response_buf);
                        std::getline(strm, session->m_response);
                      }
                      onRequestComplete(session);
                    });  // обработчик чтения с сервера
              });        // обработчик записи на сервер
        });              // обработчик коннекта
  };

  // Cancels the request.
  void cancelRequest(unsigned int request_id) {
    std::cout << "cancelRequest" << std::endl;
    std::unique_lock<std::mutex> lock(m_active_sessions_guard);
    auto it = m_active_sessions.find(request_id);
    if (it != m_active_sessions.end()) {
      std::unique_lock<std::mutex> cancel_lock(it->second->m_cancel_guard);

      it->second->m_was_cancelled = true;
      it->second->m_sock.cancel();
    }
  }

  void close() {
    // std::cout<<"close"<<std::endl;
    // Destroy work object. This allows the I/O thread to
    // exits the event loop when there are no more pending
    // asynchronous operations.
    m_work.reset(NULL);

    // Wait for the I/O thread to exit.
    m_thread->join();
  }

 private:
  void onRequestComplete(std::shared_ptr<Session> session) {
    // std::cout<<"onRequestComplete"<<std::endl;

    // Shutting down the connection. This method may fail in case socket is not
    // connected. We don't care about the error code if this function fails.
    boost::system::error_code ignored_ec;

    session->m_sock.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);

    // Remove session form the map of active sessions.
    std::unique_lock<std::mutex> lock(m_active_sessions_guard);

    auto it = m_active_sessions.find(session->m_id);
    if (it != m_active_sessions.end()) m_active_sessions.erase(it);

    lock.unlock();

    boost::system::error_code ec;

    if (session->m_ec.value() == 0 && session->m_was_cancelled)
      ec = asio::error::operation_aborted;
    else
      ec = session->m_ec;

    // Call the callback provided by the user.
    session->m_callback(session->m_id, session->m_response, ec);
  };

 private:
  asio::io_service m_ios;
  std::map<int, std::shared_ptr<Session>> m_active_sessions;
  std::mutex m_active_sessions_guard;
  std::unique_ptr<boost::asio::io_service::work> m_work;
  std::unique_ptr<std::thread> m_thread;
};

void handler(unsigned int request_id, const std::string& response,
             const system::error_code& ec) {
  // std::cout<<"handler"<<std::endl;
  //    if (ec.value() == 0) {

  if (request_id != 0) {
//    std::cout << "Request " << request_id
//              << " has completed. Response: " << response;
    sending = stoi(response);
  }
//  if (request_id == 0) std::cout << "service Ok " << std::endl;

  //    }

  //    else if (ec == asio::error::operation_aborted) {
  //    std::cout <<std::endl<< "Request #" << request_id
  //        << " has been cancelled by the user." << std::endl;
  //    }
  //    else {
  //     ++errors ;
  //     std::cout<<"error_response: "<<response;
  //     sending = 0;
  //     errorParts.push_back(std::to_string(request_id)); //номер ошибки в
  //     векторе
  //        std::cout <<std::endl<< "Request #" << request_id
  //        << " failed! Error code = " << ec.value()
  //        << ". Error message = " << ec.message() << std::endl;
  //    }
  //    return;
}

void readFileAttributes(FILE_& file) {
  //  //Определяем параметры файла
  //  std::ifstream f(file.nameFile, std::ios::in | std::ios::binary);
  //  std::stringstream lenthFile;
  //         lenthFile <<f.rdbuf()<<std::endl;
  //  lenthFile <<f.rdbuf();
  //  f.close();
  //  std::string part(lenthFile.str());
  //  file.lenthFile = part.size();
  file.lenthFile = 65536;  //это фиктивное значение
  //       file.numberPart =file.lenthFile/file.sizePartToSend + 1;
}

std::string readFile(FILE_& file) {
  std::ifstream ff(file.nameFile, std::ios::in | std::ios::binary);
  std::stringstream stream_file;
  //  stream_file <<ff.rdbuf()<<std::endl<<std::endl;
  stream_file << ff.rdbuf();
  std::string fileToServer(stream_file.str());  //тут наш исходный файл
  return fileToServer;
}

void sendServicePart(FILE_& file, std::string host, int port) {
  AsyncTCPClient client;
  std::stringstream stream_service;
  //  stream_service<<"* * * *"<<file.nameFile<<"
  //  "<<file.lenthFile<<std::endl<<std::endl;
  stream_service << "* * * *" << file.nameFile << " " << file.lenthFile;
  std::string service(stream_service.str());
  client.sendFile_to_server(service, host, port, handler, 0);
  client.close();
  file.servisePart = false;
}

void eraseErrodData(std::string host, int port) {
//  AsyncTCPClient client;
//  std::stringstream erase;
//  std::string erase_in_string;
//  //   ошибки переводим из вектора в строку
//  for (auto iter = errorParts.begin(); iter != errorParts.end(); ++iter) {
//    erase_in_string.append(*iter);
//    erase_in_string.append("*");
//  }
//  std::cout << "erase_in_string: " << erase_in_string << std::endl;
//  //  erase<<"*^^*^^*"<<erase_in_string<<std::endl<<std::endl;
//  erase << "*^^*^^*" << erase_in_string;
//  std::string eras(erase.str());
//  client.sendFile_to_server(eras, host, port, handler, 0);
//  client.close();
//  errors = 0;
}

void writeConteinersToFile(std::string host, int port) {
//  AsyncTCPClient client;
//  std::stringstream write;
//  //  write<<"*^***^*"<<std::endl<<std::endl;
//  write << "*^***^*";
//  std::string wr(write.str());
//  client.sendFile_to_server(wr, host, port, handler, 0);
//  client.close();
}

void sendToServer(FILE_& file, std::string host, int port,
                  std::string& fileToServer, int need_send) {
  auto store = need_send;
  std::string fileToServerPrefix;
  int i = 0;  //номер запроса

//  while (need_send > 0) {
    AsyncTCPClient client;
    ++i;
    std::string ii(std::to_string(i));
    std::string prefix{"00000"};
    prefix.replace(5 - ii.length(), ii.length(), ii);
    prefix = "*^*^*^*" + prefix;  //тут префикс 12 символов
//    std::cout << " prefix: " << prefix << " ";
    fileToServerPrefix = prefix + fileToServer;
    // partSend = false;
    client.sendFile_to_server(fileToServerPrefix, host, port, handler, i);
    // while(  partSend == false){}
    client.close();
//    std::cout << "  need_send: " << need_send;
//    std::cout << "  sending: " << sending
//              << " file.need_send: " << file.need_send << std::endl;
    if (need_send != sending) fileToServer.erase(0, sending);
    need_send = need_send - sending;
//  }  //весь файл отправлен

  file.fileSending = true;
  if (errors != 0) file.errorfix = false;

  //даем команду на удаление контейнеров с ошибками
  if (!file.errorfix) eraseErrodData(host, port);

  //даем команду на запись файла
  if (file.fileSending && file.errorfix) {
    writeConteinersToFile(host, port);
    file.fileSending = false;
  }
  file.need_send = file.need_send - store;
}

int main(int argc, char** argv) {
  //  QDateTime time_start(QDateTime::currentDateTime());

  std::string host;
  int port;
  try {
    FILE_ file;
    if (argc == 4) {
      host = argv[1];
      port = atoi(argv[2]);
      file.nameFile = argv[3];
    }
    if (argc != 4) {
      std::cout << "Bad arguments ";
      return -1;
    }

    readFileAttributes(file);

    if (file.servisePart)
      sendServicePart(file, host, port);  //отправляем сервисные данные
    auto fileToServer = readFile(file);  //читаем файл



    file.need_send = fileToServer.size();
//    std::cout << "file.need_send: " << file.need_send << std::endl;
    sendToServer(file, host, port, fileToServer, file.need_send);
  }

  catch (system::system_error& e) {
    std::cout << "Error occured! Error code = " << e.code()
              << ". Message: " << e.what();

    return e.code().value();
  }
  if (errors != 0)
    std::cout << std::endl << "!!! " << errors << " errors" << std::endl;
//  if (errors == 0) std::cout << std::endl << "no errors" << std::endl;



  return 0;
};
