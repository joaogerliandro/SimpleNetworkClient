#include <standard_libs.h>

#include <common.h>

using boost::asio::ip::tcp;

bool server_listened = false;

void listen_server(tcp::socket &socket)
{
    try
    {
        while (true)
        {
            boost::asio::streambuf response_buffer;
            boost::asio::read_until(socket, response_buffer, '\n');

            std::string response_message = boost::asio::buffer_cast<const char *>(response_buffer.data());

            response_message.erase(std::prev(response_message.cend()));

            std::cout << response_message << std::endl;

            server_listened = true;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void reply_server(tcp::socket &socket)
{
    try
    {
        while (true)
        {
            if(server_listened)
            {
                std::string response_message;

                std::cout << "[CLIENT]: Insert a new mensage: ";

                std::getline(std::cin, response_message);

                boost::asio::write(socket, boost::asio::buffer(response_message + "\n"));

                server_listened = false;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main(int argc, char *argv[])
{
    Config config("config.cfg");

    std::string hostname{config.hostname};
    std::string port{config.port};

    try
    {
        boost::asio::io_context io_context;

        tcp::socket socket(io_context);
        tcp::resolver resolver(io_context);

        std::cout << "[CLIENT]: Trying to connect to the server ..." << std::endl;

        connect(socket, resolver.resolve({hostname, port}));

        std::cout << "[CLIENT]: Server connection established !" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        std::thread listen_thread(listen_server, std::ref(socket));
        std::thread reply_thread(reply_server, std::ref(socket));

        listen_thread.join();
        reply_thread.join();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}