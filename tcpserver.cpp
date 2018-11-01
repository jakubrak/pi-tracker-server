#include <iostream>

#include <boost/bind.hpp>

#include "imessagelistener.h"

#include "tcpserver.h"

using boost::asio::ip::tcp;

TcpServer::TcpServer(const short port)
: port{port},
  work{ioContext},
  socket{ioContext},
  acceptor{ioContext, tcp::endpoint(tcp::v4(), port)},
  buffer{streambuf.prepare(BUF_SIZE)} {}

void TcpServer::run() {
    std::cout << "TCP server started on port " << port << std::endl;

    acceptor.async_accept(socket,
        remoteEndpoint,
        boost::bind(&TcpServer::accept,
            this,
            boost::asio::placeholders::error));

    ioContext.run();
}

void TcpServer::send(std::istream &is)  {

}

void TcpServer::addMessageListener(std::shared_ptr<IMessageListener> messageListener) {
    messageListeners.push_back(messageListener);
}

void TcpServer::accept(const boost::system::error_code& error) {
    if (!error) {
        std::cout << "Connected to " << remoteEndpoint.address() << std::endl;

        socket.async_receive(
            buffer,
            boost::bind(&TcpServer::receive,
                this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}

void TcpServer::receive(const boost::system::error_code& error, std::size_t byteCount ) {
    std::cout << "Received " << byteCount << " bytes:" << std::endl;
    streambuf.commit(byteCount);
    std::istream is(&streambuf);
    for (auto& listener : messageListeners) {
        listener->received(is);
    }
}
