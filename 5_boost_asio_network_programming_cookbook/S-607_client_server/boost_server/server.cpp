#include <fstream>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
typedef boost::asio::streambuf streambufer;

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket)
    : socket_(std::move(socket))
  {
  }

  void start()
  {
    do_read();
  }

private:
  void do_read()
  {


    auto self(shared_from_this());
    auto buff = boost::asio::buffer(data_, max_length);
    streambufer sbuff;
    std::istream in(&sbuff);
//    auto buff = setbuffer(file);
//    read(socket_,sbuff);
//    read_until(socket_,sbuff,"\n");
//    socket_.read_some(buff);

    in>>data_;


      socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {

            std::cout<<"receeve file from client: "<<data_<<std::endl;

             writeFile ();
             do_write();

             }
        });

  }

  void writeFile (){
      //                FILE *file;
      //                file=fopen( "receeve_file", "wb");
      //                fwrite (&data_, sizeof data_, 1, file);

                   std::ofstream file("receeve_file", std::ios::out | std::ios::binary);
                   file <<data_;
                   file.close();
  }

    void do_write()
  {
//        streambufer sbuff;
//        std::ostream out(&sbuff);
//        out << "Ok...";
//        write(socket_, sbuff);


      auto ansver = "Ok...";
      std::string replay ="file receeve";
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(ansver, std::size_t(ansver)),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
              std::cout<<"send message to client: Ok..."<<std::endl;
            do_read();

          }
        });
  }

  tcp::socket socket_;
  enum { max_length = 32000 };
  char data_[max_length];
};

class server
{
public:
  server(boost::asio::io_service& io_service, short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      socket_(io_service)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket_))->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    server s(io_service, std::atoi(argv[1]));

    io_service.run();

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}


