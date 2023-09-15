#include <windows/chatroomwindow.h>
#include "ui_chatroomwindow.h"

void listen_server(boost::asio::ip::tcp::socket &socket)
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
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

ChatRoomWindow::ChatRoomWindow(Room chat_room, boost::asio::ip::tcp::socket &socket, QWidget *parent)
    : server_socket(socket),
    QWidget(parent),
    ui(new Ui::ChatRoomWindow)
{
    ui->setupUi(this);

    setup_chatroom(chat_room);
}

ChatRoomWindow::~ChatRoomWindow()
{
    delete ui;
}

void ChatRoomWindow::setup_chatroom(Room chat_room)
{
    boost::asio::write(server_socket, boost::asio::buffer(std::to_string(chat_room.get_id()) + "\n"));

    this->setWindowTitle(QString::fromStdString(chat_room.get_name()));

    std::thread(listen_server, std::ref(server_socket)).detach();
}
