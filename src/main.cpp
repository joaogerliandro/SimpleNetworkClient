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
            
            std::random_device rd; // Obtém uma semente aleatória para o gerador
            std::mt19937 gen(rd()); // Cria o gerador de números aleatórios
            std::uniform_int_distribution<int> dis(0, 9); // Cria uma distribuição uniforme de inteiros entre 0 e 9
            
            std::string numero;
            
            std::this_thread::sleep_for(std::chrono::seconds(10));

            // Gera 30 dígitos aleatórios
            for (int i = 0; i < 30; i++)
                numero += std::to_string(dis(gen));

            boost::asio::write(socket, boost::asio::buffer(numero + "\n"));
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