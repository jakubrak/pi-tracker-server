#include <iostream>
#include <istream>
#include <string>
#include <stack>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::asio::ip::tcp;

class GetStreamSettingsMsg { };

class StartStreamingMsg {
public:
	StartStreamingMsg(const std::string& remoteAddress) : 
		remoteAddress(remoteAddress) {

	}

	const std::string getRemoteAddress() const {
		return remoteAddress;
	}

private:
	std::string remoteAddress;
};

class IMessageListener {
public:
    virtual void received(std::istream &is) = 0;
};

class IMessageWriter {
public:
    virtual void send(std::istream &is) = 0;
};

class IMessageHandler {
public:
    virtual void handle(const GetStreamSettingsMsg &getStreamSettingsMsg) = 0;

    virtual void handle(const StartStreamingMsg &startStreamingMsg) = 0;
};

class MessageParser : public IMessageListener{
public:
    void received(std::istream &is) override {
        parse(is);
    }

    void parse(std::istream &is) {
        char c;
        while(is.get(c)) {
            buffer << c;
            if (c == '{') {
		        stack.push(c);
            } else if (c == '}') {
		        stack.pop();
		        if (stack.empty()) {
			        // got complete json document
			        boost::property_tree::ptree pt;
                    boost::property_tree::json_parser::read_json(buffer, pt);
                    parse(pt);
		        }
            }
        }
    }

    void addMessageHandler(std::shared_ptr<IMessageHandler> messageHandler) {
        messageHandlers.push_back(messageHandler);
    }

private:
    void parse(const boost::property_tree::ptree &pt) {
        std::string messageId = pt.get<std::string>("msgid");
        if (messageId == "GET_STREAM_SETTINGS") {
            GetStreamSettingsMsg message;
            notifyHandlers(message);
        } else if (messageId == "START_STREAMING") {
            StartStreamingMsg message("192.168.0.158");
            notifyHandlers(message);
        }
    }

    template<typename T>
    void notifyHandlers(const T& message) {
        for (auto &h : messageHandlers) {
            h->handle(message);
        }
    }

    std::stringstream buffer;
    std::stack<char> stack;
    std::vector<std::shared_ptr<IMessageHandler>> messageHandlers;
};

class MessageHandler : public IMessageHandler {
public:
    void handle(const GetStreamSettingsMsg &getStreamSettingsMsg) override {
        std::cout << "GetStreamSettingsMsg" << std::endl;
    }

    void handle(const StartStreamingMsg &startStreamingMsg) override {
        std::cout << "StartStreamingMsg" << std::endl;
    }


    void addMessageWriter(std::shared_ptr<IMessageWriter> messageWriter) {
        messageWriters.push_back(messageWriter);
    }

private:
    std::vector<std::shared_ptr<IMessageWriter>> messageWriters;
};

class TcpServer : public IMessageWriter {
public:
    TcpServer(const short port) 
    : port{port},
      work{ioContext},
      socket{ioContext},
      acceptor{ioContext, tcp::endpoint(tcp::v4(), port)},
      buffer{streambuf.prepare(BUF_SIZE)} {}

    void run() {
        std::cout << "TCP server started on port " << port << std::endl;

        acceptor.async_accept(socket, 
            remoteEndpoint, 
            boost::bind(&TcpServer::accept, 
                this, 
                boost::asio::placeholders::error));   

        ioContext.run();
    }

    void send(std::istream &is) override {

    }
    
    void addMessageListener(std::shared_ptr<IMessageListener> messageListener) {
        messageListeners.push_back(messageListener);
    }

private:
    void accept(const boost::system::error_code& error) {
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

    void receive(const boost::system::error_code& error, 
        std::size_t byteCount ) {
        std::cout << "Received " << byteCount << " bytes:" << std::endl;
        streambuf.commit(byteCount);
        std::istream is(&streambuf); 
        for (auto& listener : messageListeners) {
            listener->received(is);
        }
    }

    short port;
    std::vector<std::shared_ptr<IMessageListener>> messageListeners;
    boost::asio::io_service ioContext;
    boost::asio::io_service::work work;
    boost::asio::ip::tcp::socket socket;
    tcp::acceptor acceptor;
    boost::asio::ip::tcp::endpoint remoteEndpoint;
    static const std::size_t BUF_SIZE = 1024;
    boost::asio::streambuf streambuf;
    boost::asio::streambuf::mutable_buffers_type buffer;
};

int main(int argc, char** argv) {
    try {
        auto server = std::make_shared<TcpServer>(5002);
        auto messageParser = std::make_shared<MessageParser>();
        auto messageHandler = std::make_shared<MessageHandler>();

        server->addMessageListener(messageParser);
        messageParser->addMessageHandler(messageHandler);
        messageHandler->addMessageWriter(server);

        server->run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

	std::cout << "Exit" << std::endl;
	return 0;
}

