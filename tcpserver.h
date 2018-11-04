#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <memory>
#include <vector>

#include <boost/asio.hpp>

class IMessageParser;
class IMessageHandler;

class TcpServer {
public:
    TcpServer(const short port, IMessageParser &messageParser, IMessageHandler &messageHandler);

    ~TcpServer() = default;

    void run();

    void send(const std::string &data);

private:
    void accept(const boost::system::error_code& error);

    void receive(const boost::system::error_code& error, std::size_t byteCount );

    short port;
    boost::asio::io_service ioContext;
    boost::asio::io_service::work work;
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::ip::tcp::endpoint remoteEndpoint;
    static const std::size_t BUF_SIZE = 1024;
    boost::asio::streambuf streambuf;

    IMessageParser& messageParser;
    IMessageHandler& messageHandler;
};

#endif // TCPSERVER_H
