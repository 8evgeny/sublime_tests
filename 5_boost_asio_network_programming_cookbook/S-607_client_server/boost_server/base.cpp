#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

int accepting_connection()
{
        // The size of the queue containing the pending connection requests.
        const int BACKLOG_SIZE = 30;

        // Step 1. Here we assume that the server application has
        // already obtained the protocol port number.
        unsigned short port_num = 3333;

        // Step 2. Creating a server endpoint.
        asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(),
                port_num);

        asio::io_service ios;

        try {
                // Step 3. Instantiating and opening an acceptor socket.
                asio::ip::tcp::acceptor acceptor(ios, ep.protocol());

                // Step 4. Binding the acceptor socket to the
                // server endpint.
                acceptor.bind(ep);

                // Step 5. Starting to listen to incoming connection
                // requests.
                acceptor.listen(BACKLOG_SIZE);

                // Step 6. Creating an active socket.
                asio::ip::tcp::socket sock(ios);

                // Step 7. Processing the next connection request and
                // connecting the active socket to the client.
                acceptor.accept(sock);

                // At this point 'sock' socket is connected to
                //the client application and can be used to send data to
                // or receive data from it.
        }
        catch (system::system_error &e) {
                std::cout << "Error occured! Error code = " << e.code()
                        << ". Message: " << e.what();

                return e.code().value();
        }

        return 0;
}
int binding_socket_TCP_passive(){
    // Step 1. Here we assume that the server application has already obtained the protocol port number.
    unsigned short port_num = 3333;

    // Step 2. Creating an endpoint.
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);

    // Used by 'acceptor' class constructor.
    asio::io_service ios;

    // Step 3. Creating and opening an acceptor socket.
    asio::ip::tcp::acceptor acceptor(ios, ep.protocol());

    boost::system::error_code ec;

    // Step 4. Binding the acceptor socket.
    acceptor.bind(ep, ec);

    // Handling errors if any.
    if (ec.value() != 0) {
            // Failed to bind the acceptor socket. Breaking execution.
            std::cout << "Failed to bind the acceptor socket."
                    << "Error code = " << ec.value() << ". Message: "
                    << ec.message();

            return ec.value();
    }

    return 0;

}
int binding_a_socket_UDP_active(){
    // Step 1. Here we assume that the server application has
    // already obtained the protocol port number.
    unsigned short port_num = 3333;

    // Step 2. Creating an endpoint.
    asio::ip::udp::endpoint ep(asio::ip::address_v4::any(), port_num);

    // Used by 'socket' class constructor.
    asio::io_service ios;

    // Step 3. Creating and opening a socket.
    asio::ip::udp::socket sock(ios, ep.protocol());

    boost::system::error_code ec;

    // Step 4. Binding the socket to an endpoint.
    sock.bind(ep, ec);

    // Handling errors if any.
    if (ec.value() != 0) {
            // Failed to bind the socket. Breaking execution.
            std::cout << "Failed to bind the socket."
                    << "Error code = " << ec.value() << ". Message: "
                    << ec.message();

            return ec.value();
    }

    return 0;
}
int connecting_a_socket(){
    // Step 1. Assume that the client application has already
    // obtained the IP address and protocol port number of the target server.
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try {
            // Step 2. Creating an endpoint designating a target server application.
            asio::ip::tcp::endpoint
                    ep(asio::ip::address::from_string(raw_ip_address), port_num);

            asio::io_service ios;

            // Step 3. Creating and opening a socket.
            asio::ip::tcp::socket sock(ios, ep.protocol());

            // Step 4. Connecting a socket.
            sock.connect(ep);
    }
    // Overloads of asio::ip::address::from_string() and
    // asio::ip::tcp::socket::connect() used here throw exceptions in case of error condition.
    catch (system::system_error &e) {
            std::cout << "Error occured! Error code = " << e.code()
                    << ". Message: " << e.what();

            return e.code().value();
    }

    return 0;
}
int connecting_a_socket_DNS_name(){
    // Step1. Assume that the client application has already
    // obtained the DNS name and protocol port number and
    // represented them as strings.
    std::string host = "samplehost.book";
    std::string port_num = "3333";

    // Used by a 'resolver' and a 'socket'.
    asio::io_service ios;

    // Creating a resolver's query.
    asio::ip::tcp::resolver::query resolver_query(host, port_num,
            asio::ip::tcp::resolver::query::numeric_service);

    // Creating a resolver.
    asio::ip::tcp::resolver resolver(ios);

    try {
            // Step 2. Resolving a DNS name.
            asio::ip::tcp::resolver::iterator it =
                    resolver.resolve(resolver_query);

            // Step 3. Creating a socket.
            asio::ip::tcp::socket sock(ios);

            // Step 4. asio::connect() method iterates over
            // each endpoint until successfully connects to one
            // of them. It will throw an exception if it fails
            // to connect to all the endpoints or if other
            // error occurs.
            asio::connect(sock, it);
    }
    // Overloads of asio::ip::tcp::resolver::resolve and
    // asio::connect() used here throw
    // exceptions in case of error condition.
    catch (system::system_error &e) {
            std::cout << "Error occured! Error code = " << e.code()
                    << ". Message: " << e.what();

            return e.code().value();
    }

    return 0;
}
int creating_a_passive_socket(){
    // Step 1. An instance of 'io_service' class is required by
    // socket constructor.
    asio::io_service ios;

    // Step 2. Creating an object of 'tcp' class representing
    // a TCP protocol with IPv6 as underlying protocol.
    asio::ip::tcp protocol = asio::ip::tcp::v6();

    // Step 3. Instantiating an acceptor socket object.
    asio::ip::tcp::acceptor acceptor(ios);

    // Used to store information about error that happens
    // while opening the acceptor socket.
    boost::system::error_code ec;

    // Step 4. Opening the acceptor socket.
    acceptor.open(protocol, ec);

    if (ec.value() != 0) {
            // Failed to open the socket.
            std::cout
                    << "Failed to open the acceptor socket!"
                    << "Error code = "
                    << ec.value() << ". Message: " << ec.message();
            return ec.value();
    }

    return 0;
}
int creating_an_active_socket_TCP_IPv4(){
    // Step 1. An instance of 'io_service' class is required by
    // socket constructor.
    asio::io_service ios;

    // Step 2. Creating an object of 'tcp' class representing
    // a TCP protocol with IPv4 as underlying protocol.
    asio::ip::tcp protocol = asio::ip::tcp::v4();

    // Step 3. Instantiating an active TCP socket object.
    asio::ip::tcp::socket sock(ios);

    // Used to store information about error that happens
    // while opening the socket.
    boost::system::error_code ec;

    // Step 4. Opening the socket.
    sock.open(protocol, ec);

    if (ec.value() != 0) {
            // Failed to open the socket.
            std::cout
                    << "Failed to open the socket! Error code = "
                    << ec.value() << ". Message: " << ec.message();
            return ec.value();
    }

    return 0;
}
int creating_an_active_socket_TCP_IPv4_open_in_constructor(){
    // Step 1. An instance of 'io_service' class is required by
    // socket constructor.
    asio::io_service ios;

    // Step 2. Creating an object of 'tcp' class representing
    // a TCP protocol with IPv4 as underlying protocol.
    asio::ip::tcp protocol = asio::ip::tcp::v4();

    try {
            // Step 3 + 4 in single call. May throw.
            asio::ip::tcp::socket sock(ios, protocol);
    }
    catch (boost::system::system_error & e) {
            std::cout << "Error occured! Error code = " << e.code()
                    << ". Message: " << e.what();
    }

    return 0;
}
int creating_endpoint_Client(){
    // Step1. Assume that the client application has already
    // obtained the IP-address and the protocol port number.
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    // Used to store information about error that happens
    // while parsing the raw IP-address.
    boost::system::error_code ec;

    // Step2. Using IP protocol version independent address
    // representation.
    asio::ip::address ip_address =
            asio::ip::address::from_string(raw_ip_address, ec);

    if (ec.value() != 0) {
            // Provided IP address is invalid. Breaking execution.
            std::cout
                    << "Failed to parse the IP address. Error code = "
                    << ec.value() << ". Message: " << ec.message();
            return ec.value();
    }

    // Step 3.
    asio::ip::tcp::endpoint ep(ip_address, port_num);

    // Step 4. The endpoint is ready and can be used to specify a
    // particular server in the network the client wants to
    // communicate with.

    return 0;
}
int creating_endpoint_Server(){
    // Step 1. Here we assume that the server application has
    //already obtained the protocol port number.
    unsigned short port_num = 3333;

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

    return 0;
}
int resolving_a_DNS_name_TCP(){
    // Step 1. Assume that the client application has already obtained
    // the DNS name and protocol port number and represented them as
    // strings.
    std::string host = "samplehost.com";
    std::string port_num = "3333";

    // Step 2.
    asio::io_service ios;

    // Step 3. Creating a query.
    asio::ip::tcp::resolver::query resolver_query(host,
            port_num, asio::ip::tcp::resolver::query::numeric_service);

    // Step 5. Creating a resolver.
    asio::ip::tcp::resolver resolver(ios);

    // Used to store information about error that happens
    // during the resolution process.
    boost::system::error_code ec;

    // Step 6.
    asio::ip::tcp::resolver::iterator it =
            resolver.resolve(resolver_query, ec);

    // Handling errors if any.
    if (ec.value() != 0) {
            // Failed to resolve the DNS name. Breaking execution.
            std::cout << "Failed to resolve a DNS name. Error code = "
                    << ec.value() << ". Message = " << ec.message();

            return ec.value();
    }

    asio::ip::tcp::resolver::iterator it_end;

    for (; it != it_end; ++it) {
            // Here we can access the endpoint like this.
            asio::ip::tcp::endpoint ep = it->endpoint();
    }

    return 0;
}
int resolving_a_DNS_name_UDP(){
    // Step 1. Assume that the client application has already
    // obtained the DNS name and protocol port number and
    // represented them as strings.
    std::string host = "samplehost.com";
    std::string port_num = "3333";

    // Step 2.
    asio::io_service ios;

    // Step 3. Creating a query.
    asio::ip::udp::resolver::query resolver_query(host,
            port_num, asio::ip::udp::resolver::query::numeric_service);

    // Step 4. Creating a resolver.
    asio::ip::udp::resolver resolver(ios);

    // Used to store information about error that happens
    // during the resolution process.
    boost::system::error_code ec;

    // Step 5.
    asio::ip::udp::resolver::iterator it =
            resolver.resolve(resolver_query, ec);

    // Handling errors if any.
    if (ec != 0) {
            // Failed to resolve the DNS name. Breaking execution.
            std::cout << "Failed to resolve a DNS name."
                    << "Error code = " << ec.value()
                    << ". Message = " << ec.message();

            return ec.value();
    }

    asio::ip::udp::resolver::iterator it_end;

    for (; it != it_end; ++it) {
            // Here we can access the endpoint like this.
            asio::ip::udp::endpoint ep = it->endpoint();
    }

    return 0;
}

int cancellingAsyncOperations(){
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try {
            asio::ip::tcp::endpoint
                    ep(asio::ip::address::from_string(raw_ip_address),
                    port_num);

            asio::io_service ios;

            std::shared_ptr<asio::ip::tcp::socket> sock(
                    new asio::ip::tcp::socket(ios, ep.protocol()));

            sock->async_connect(ep,
                    [sock](const boost::system::error_code& ec)
            {
                    // If asynchronous operation has been
                    // cancelled or an error occured during
                    // executon, ec contains corresponding
                    // error code.
                    if (ec != 0) {
                            if (ec == asio::error::operation_aborted) {
                                    std::cout << "Operation cancelled!";
                            }
                            else {
                                    std::cout << "Error occured!"
                                            << " Error code = "
                                            << ec.value()
                                            << ". Message: "
                                            << ec.message();
                            }

                            return;
                    }
                    // At this point the socket is connected and
                    // can be used for communication with
                    // remote application.
            });

            // Starting a thread, which will be used
            // to call the callback when asynchronous
            // operation completes.
            std::thread worker_thread([&ios](){
                    try {
                            ios.run();
                    }
                    catch (system::system_error &e) {
                            std::cout << "Error occured!"
                                    << " Error code = " << e.code()
                                    << ". Message: " << e.what();
                    }
            });

            // Emulating delay.
            std::this_thread::sleep_for(std::chrono::seconds(2));

            // Cancelling the initiated operation.
            sock->cancel();

            // Waiting for the worker thread to complete.
            worker_thread.join();
    }
    catch (system::system_error &e) {
            std::cout << "Error occured! Error code = " << e.code()
                    << ". Message: " << e.what();

            return e.code().value();
    }

    return 0;
}
int extensibleStreamOrientedBuffer(){
    asio::streambuf buf;

    std::ostream output(&buf);

    // Writing the message to the stream-based buffer.
    output << "Message1\nMessage2";

    // Now we want to read all data from a streambuf
    // until '\n' delimiter.
    // Instantiate an intput stream which uses our
    // stream buffer.
    std::istream input(&buf);

    // We'll read data into this string.
    std::string message1;

    std::getline(input, message1);

    // Now message1 string contains 'Message1'.

    return 0;
}
int fixedLengthBufferInput(){
    // We expect to receive a block of data no more than 20 bytes
    // long.
    const size_t BUF_SIZE_BYTES = 20;

    // Step 1. Allocating the buffer.
    std::unique_ptr<char[]> buf(new char[BUF_SIZE_BYTES]);

    // Step 2. Creating buffer representation that satisfies
    // MutableBufferSequence concept requirements.
    asio::mutable_buffers_1 input_buf =
            asio::buffer(static_cast<void*>(buf.get()),
            BUF_SIZE_BYTES);

    // Step 3. 'input_buf' is the representation of the buffer
    // 'buf' that can be used in Boost.Asio input operations.

    return 0;
}
int fixedLengthBufferOutput(){
    std::string buf; // 'buf' is the raw buffer.
    buf = "Hello";   // Step 1 and 2 in single line.

    // Step 3. Creating buffer representation that satisfies
    // ConstBufferSequence concept requirements.
    asio::const_buffers_1 output_buf = asio::buffer(buf);

    // Step 4. 'output_buf' is the representation of the
    // buffer 'buf' that can be used in Boost.Asio output
    // operations.

    return 0;
}

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
            void callback1(const boost::system::error_code& ec,std::size_t bytes_transferred,std::shared_ptr<Session_read> s){
                // Function used as a callback for
                // asynchronous reading operation.
                // Checks if all data has been read
                // from the socket and initiates
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
                            std::bind(callback1, std::placeholders::_1,
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
                            std::bind(callback1,
                                    std::placeholders::_1,
                                    std::placeholders::_2,
                                    s));
            }
int readingFromTCPSockAsync(){

    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try {
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),port_num);

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
int readingFromTCPSockAsyncEnhanced(){
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try {
            asio::ip::tcp::endpoint
                    ep(asio::ip::address::from_string(raw_ip_address),
                    port_num);

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
int readingFromTCPSockSync(){}

        void communicate(asio::ip::tcp::socket& sock) {
                // Allocating and filling the buffer with
                // binary data.
                const char request_buf[] = { 0x48, 0x65, 0x0, 0x6c, 0x6c, 0x6f };

                // Sending the request data.
                asio::write(sock, asio::buffer(request_buf));

                // Shutting down the socket to let the
                // server know that we've sent the whole
                // request.
                sock.shutdown(asio::socket_base::shutdown_send);

                // We use extensible buffer for response
                // because we don't know the size of the
                // response message.
                asio::streambuf response_buf;

                system::error_code ec;
                asio::read(sock, response_buf, ec);

                if (ec == asio::error::eof) {
                        // Whole response message has been received.
                        // Here we can handle it.
                }
                else {
                        throw system::system_error(ec);
                }
        }
int sockShutdownClient (){
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try {
            asio::ip::tcp::endpoint
                    ep(asio::ip::address::from_string(raw_ip_address),
                    port_num);

            asio::io_service ios;

            asio::ip::tcp::socket sock(ios, ep.protocol());

            sock.connect(ep);

            communicate(sock);
    }
    catch (system::system_error &e) {
            std::cout << "Error occured! Error code = " << e.code()
                    << ". Message: " << e.what();

            return e.code().value();
    }

    return 0;
}

        void processRequest(asio::ip::tcp::socket& sock) {
                // We use extensibel buffer because we don't
                // know the size of the request message.
                asio::streambuf request_buf;

                system::error_code ec;

                // Receiving the request.
                asio::read(sock, request_buf, ec);

                if (ec != asio::error::eof)
                        throw system::system_error(ec);

                // Request received. Sending response.
                // Allocating and filling the buffer with
                // binary data.
                const char response_buf[] = { 0x48, 0x69, 0x21 };

                // Sending the request data.
                asio::write(sock, asio::buffer(response_buf));

                // Shutting down the socket to let the
                // client know that we've sent the whole
                // response.
                sock.shutdown(asio::socket_base::shutdown_send);
        }
int sockShutdownServer(){
    unsigned short port_num = 3333;

    try {
            asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(),
                    port_num);

            asio::io_service ios;

            asio::ip::tcp::acceptor acceptor(ios, ep);

            asio::ip::tcp::socket sock(ios);

            acceptor.accept(sock);

            processRequest(sock);
    }
    catch (system::system_error &e) {
            std::cout << "Error occured! Error code = " << e.code()
                    << ". Message: " << e.what();

            return e.code().value();
    }

    return 0;
}

        struct Session_write {
            // Keeps objects we need in a callback to
            // identify whether all data has been written
            // to the socket and to initiate next async
            // writing operatino if needed.
                std::shared_ptr<asio::ip::tcp::socket> sock;
                std::string buf;
                std::size_t total_bytes_written;
        };
        void callback2(const boost::system::error_code& ec,
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
                        std::bind(callback2, std::placeholders::_1,
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
                        std::bind(callback2,
                        std::placeholders::_1,
                        std::placeholders::_2,
                        s));
        }
int writingToTCPSockAsync(){
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try {
            asio::ip::tcp::endpoint
                    ep(asio::ip::address::from_string(raw_ip_address),
                    port_num);

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
int writingToTCPSockAsyncEnhanced(){
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try {
            asio::ip::tcp::endpoint
                    ep(asio::ip::address::from_string(raw_ip_address),
                    port_num);

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
int writingToTCPSockSync(){}
