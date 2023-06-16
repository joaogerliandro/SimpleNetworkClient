#include <iostream>
#include <string>
#include <thread>
#include <random>
#include <chrono>

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

            response_message.erase(std::remove(response_message.begin(), response_message.end(), '\n'), response_message.cend());

            std::cout << "[SERVER-RESPONSE]: " << response_message << std::endl;
            
            std::cout << "[CLIENT]: Insert a new mensage: "; 

            std::getline(std::cin, response_message);

            boost::asio::write(socket, boost::asio::buffer(response_message + "\n"));
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