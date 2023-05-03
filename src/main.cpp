#include <iostream>
#include <string>
#include <thread>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    std::string hostname{ "localhost" };
    std::string port{ "4444" };
    
    try
    {
        boost::asio::io_context io_context;

        tcp::socket socket(io_context);
        tcp::resolver resolver(io_context);

        std::cout << "[CLIENT]: Trying to connect to the server ..." << std::endl;

        connect(socket, resolver.resolve({hostname, port}));
        
        std::cout << "[CLIENT]: Server connection established !" << std::endl;

        for(;;)
        {
            boost::asio::streambuf response_buffer;
            boost::asio::read_until(socket, response_buffer, '\n');

            std::string response_message = boost::asio::buffer_cast<const char*>(response_buffer.data());

            std::cout << "[SERVER-RESPONSE]: " << response_message << std::endl;
            
            std::string message;
            std::cout << "[CLIENT]: Enter a message to the server: ";
            std::getline(std::cin, message);

            boost::asio::write(socket, boost::asio::buffer(message + "\n"));
        }

        socket.shutdown(tcp::socket::shutdown_both);
        socket.close();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}