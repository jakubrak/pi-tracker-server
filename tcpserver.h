#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <memory>
#include <vector>

#include <boost/asio.hpp>

#include "imessagewriter.h"

class IMessageListener;

class TcpServer : public IMessageWriter {
public:
    TcpServer(const short port);
    virtual ~TcpServer() {}

    void run();

    void send(std::istream &is) override;

    void addMessageListener(std::shared_ptr<IMessageListener> messageListener);

private:
    void accept(const boost::system::error_code& error);

    void receive(const boost::system::error_code& error, std::size_t byteCount );

    short port;
    std::vector<std::shared_ptr<IMessageListener>> messageListeners;
    boost::asio::io_service ioContext;
    boost::asio::io_service::work work;
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::ip::tcp::endpoint remoteEndpoint;
    static const std::size_t BUF_SIZE = 1024;
    boost::asio::streambuf streambuf;
    boost::asio::streambuf::mutable_buffers_type buffer;
};

#endif // TCPSERVER_H
