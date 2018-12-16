#include <iostream>

#include <boost/bind.hpp>

#include "irequestmessage.h"
#include "iresponsemessage.h"
#include "imessageparser.h"
#include "imessagehandler.h"

#include "tcpserver.h"

using boost::asio::ip::tcp;

TcpServer::TcpServer(const short port, IMessageParser& messageParser, IMessageHandler& messageHandler)
: port{port},
  work{ioContext},
  socket{ioContext},
  acceptor{ioContext, tcp::endpoint(tcp::v4(), port)},
  messageParser{messageParser},
  messageHandler{messageHandler} {}

void TcpServer::run() {
    std::cout << "TCP server started on port " << port << std::endl;

    acceptor.async_accept(socket,
        remoteEndpoint,
        boost::bind(&TcpServer::accept,
            this,
            boost::asio::placeholders::error));

    ioContext.run();
    std::cout << "TCP server ended on port " << port << std::endl;
}

void TcpServer::send(const std::string& data)  {
    boost::asio::write(socket, boost::asio::buffer(data, data.size()));
}

void TcpServer::accept(const boost::system::error_code& error) {
    if (!error) {
        std::cout << "Connected to " << remoteEndpoint.address() << std::endl;

        socket.async_receive(streambuf.prepare(BUF_SIZE),
            boost::bind(&TcpServer::receive,
                this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    } else {
        ioContext.stop();
    }
}

void TcpServer::receive(const boost::system::error_code& error, std::size_t byteCount ) {
    streambuf.commit(byteCount);

    if (!error) {
        std::cout << "Received " << streambuf.size() << " bytes:" << std::endl;
        std::istream is(&streambuf);
        auto messageQueue = messageParser.parse(is);
        for (const auto& request : messageQueue) {
            auto response = request->handle(messageHandler);
            if (response != nullptr) {
                send(response->unparse(messageParser));
            }
        }

        streambuf.consume(byteCount);

        socket.async_receive(streambuf.prepare(BUF_SIZE),
            boost::bind(&TcpServer::receive,
                this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    } else {
        std::cout << "Error: " << error << std::endl;
        ioContext.stop();
    }
}
