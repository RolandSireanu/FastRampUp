#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const std::string gBadRequest = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
const std::string gMethodNotAllowed = "HTTP/1.1 405 Not allowed\r\nContent-Length: 0\r\n\r\n";
const std::string gOK = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";

void session(tcp::socket socket) {
    try {
        char data[1024];

        // Read from the socket
        boost::system::error_code error;
        size_t length = socket.read_some(boost::asio::buffer(data), error);

        if (error == boost::asio::error::eof) {
            std::cout << "Connection closed by client." << std::endl;
            return; // Connection closed by peer
        } else if (error) {
            throw boost::system::system_error(error);
        }

        std::string received_data(data, length);
        std::cout << "Received: " << received_data << std::endl;

        // Perform some basic validation on the received data
        bool is_valid = received_data.find("key") != std::string::npos ? true : false;

        // Here’s where you could implement your validation logic
        if (received_data.empty() || !is_valid) {
            // Send a response indicating the error            
            boost::asio::write(socket, boost::asio::buffer(gMethodNotAllowed), error);
            std::cerr << "Invalid data received, responded with 405 Method not allow.\n";
            return; // Exit the session after responding
        }

        // If data is valid, send a success response
        boost::asio::write(socket, boost::asio::buffer(gOK), error);

        // Gracefully shutdown the connection
        socket.shutdown(boost::asio::socket_base::shutdown_send, error);
        if (error) {
            std::cerr << "Error during shutdown: " << error.message() << "\n";
        }

    } catch (std::exception& e) {
        std::cerr << "Exception in session: " << e.what() << "\n";
    }

    // The socket will be automatically closed when it goes out of scope
}

int main() {
    try {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

        std::cout << "Server is running on port 12345...\n";

        for (;;) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::cout << "Accepted new connection.\n";
            std::thread(session, std::move(socket)).detach(); // Handle session in a separate thread
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}