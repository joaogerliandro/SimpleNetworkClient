#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    std::string hostname{ "localhost" };
    std::string port{ "4444" };
    
    try
    {
        boost::asio::io_service io_service;

        tcp::socket socket(io_service);
        tcp::resolver resolver(io_service);

        std::cout << "[CLIENT]: Trying to connect to the server ..." << std::endl;

        connect(socket, resolver.resolve({hostname, port}));

        std::cout << "[CLIENT]: Server connection established !" << std::endl;

        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\n");

        std::string message = boost::asio::buffer_cast<const char*>(response.data());

        std::cout << "[RESPONSE]: " << message << std::endl;

        socket.shutdown(tcp::socket::shutdown_both);
        socket.close();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}