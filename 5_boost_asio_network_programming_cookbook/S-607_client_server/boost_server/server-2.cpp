#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

 struct Session_read {
    // Keeps objects we need in a callback to
    // identify whether all data has been read
    // from the socket and to initiate next async
    // reading operation if needed.
        std::shared_ptr<asio::ip::tcp::socket> sock;
        std::unique_ptr<char[]> buf;
        std::size_t total_bytes_read;
        unsigned int buf_size;
 };

 struct Session_write {
     // Keeps objects we need in a callback to
     // identify whether all data has been written
     // to the socket and to initiate next async
     // writing operatino if needed.
         std::shared_ptr<asio::ip::tcp::socket> sock;
         std::string buf;
         std::size_t total_bytes_written;
 };


 void callback_read(const boost::system::error_code& ec,
           std::size_t bytes_transferred,std::shared_ptr<Session_read> s){
    // Function used as a callback for asynchronous reading operation.
    // Checks if all data has been read from the socket and initiates
    // new readnig operation if needed.
        if (ec.value() != 0) {
                std::cout << "Error occured! Error code = "
                        << ec.value()
                        << ". Message: " << ec.message();
                return;
        }

        s->total_bytes_read += bytes_transferred;

        if (s->total_bytes_read == s->buf_size) {
                return;
        }

        s->sock->async_read_some(
                asio::buffer(
                s->buf.get() +
                s->total_bytes_read,
                s->buf_size -
                s->total_bytes_read),
                std::bind(callback_read, std::placeholders::_1,
                std::placeholders::_2, s));
        }

 void readFromSocket(std::shared_ptr<asio::ip::tcp::socket> sock) {
        std::shared_ptr<Session_read> s(new Session_read);

        const unsigned int MESSAGE_SIZE = 7;

        // Step 4. Allocating the buffer.
        s->buf.reset(new char[MESSAGE_SIZE]);

        s->total_bytes_read = 0;
        s->sock = sock;
        s->buf_size = MESSAGE_SIZE;

        // Step 5. Initiating asynchronous reading opration.
        s->sock->async_read_some(
                asio::buffer(s->buf.get(), s->buf_size),
                std::bind(callback_read,
                        std::placeholders::_1,
                        std::placeholders::_2,
                        s));
 }

 void callback_write(const boost::system::error_code& ec,
           std::size_t bytes_transferred,std::shared_ptr<Session_write> s){
     // Function used as a callback for
     // asynchronous writing operation.
     // Checks if all data from the buffer has
     // been written to the socket and initiates
     // new writting operation if needed.
         if (ec.value() != 0) {
                 std::cout << "Error occured! Error code = "
                         << ec.value()
                         << ". Message: " << ec.message();

                 return;
         }

         s->total_bytes_written += bytes_transferred;

         if (s->total_bytes_written == s->buf.length()) {
                 return;
         }

         s->sock->async_write_some(
                 asio::buffer(
                 s->buf.c_str() +
                 s->total_bytes_written,
                 s->buf.length() -
                 s->total_bytes_written),
                 std::bind(callback_write, std::placeholders::_1,
                 std::placeholders::_2, s));
 }

 void writeToSocket(std::shared_ptr<asio::ip::tcp::socket> sock) {
         std::shared_ptr<Session_write> s(new Session_write);

         // Step 4. Allocating and filling the buffer.
         s->buf = std::string("Hello");
         s->total_bytes_written = 0;
         s->sock = sock;

         // Step 5. Initiating asynchronous write opration.
         s->sock->async_write_some(
                 asio::buffer(s->buf),
                 std::bind(callback_write,
                 std::placeholders::_1,
                 std::placeholders::_2,
                 s));
 }

 int readingFromTCPSockAsync(asio::ip::tcp::endpoint ep){
    try {
    asio::io_service ios;

    // Step 3. Allocating, opening and connecting a socket.
    std::shared_ptr<asio::ip::tcp::socket> sock(
    new asio::ip::tcp::socket(ios, ep.protocol()));

    sock->connect(ep);

    readFromSocket(sock);

    // Step 6.
    ios.run();
    }
    catch (system::system_error &e) {
            std::cout << "Error occured! Error code = " << e.code()
                    << ". Message: " << e.what();

            return e.code().value();
    }

    return 0;

}

 int writingToTCPSockAsync(asio::ip::tcp::endpoint ep){

     try {
             asio::io_service ios;

             // Step 3. Allocating, opening and connecting a socket.
             std::shared_ptr<asio::ip::tcp::socket> sock(
                     new asio::ip::tcp::socket(ios, ep.protocol()));

             sock->connect(ep);

             writeToSocket(sock);

             // Step 6.
             ios.run();
     }
     catch (system::system_error &e) {
             std::cout << "Error occured! Error code = " << e.code()
                     << ". Message: " << e.what();

             return e.code().value();
     }

     return 0;
 }

 int main(int argc, char* argv[]){
     if (argc != 2)
     {
       std::cerr << "Usage: server <port>\n";
       return 1;
     }
     // Step 1. Here we assume that the server application has
     //already obtained the protocol port number.
      unsigned short port_num = stoi(std::string(argv[1]));

     // Step 2. Create special object of asio::ip::address class
     // that specifies all IP-addresses available on the host. Note
     // that here we assume that server works over IPv6 protocol.
     asio::ip::address ip_address = asio::ip::address_v6::any();

     // Step 3.
     asio::ip::tcp::endpoint ep(ip_address, port_num);

     // Step 4. The endpoint is created and can be used to
     // specify the ip-addresses and a port number on which
     // the server application wants to listen to incoming
     // connections.

//     readingFromTCPSockAsync(ep);
//     writingToTCPSockAsync(ep);
    }

