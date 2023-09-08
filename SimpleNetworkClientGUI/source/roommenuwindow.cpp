#include <windows/roommenuwindow.h>
#include "ui_roommenuwindow.h"

RoomMenuWindow::RoomMenuWindow(boost::asio::ip::tcp::socket &socket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomMenuWindow)
{
    connection_handshake(socket);

    ui->setupUi(this);
}

RoomMenuWindow::~RoomMenuWindow()
{
    delete ui;
}

void RoomMenuWindow::connection_handshake(boost::asio::ip::tcp::socket &socket)
{
    try
    {
        boost::asio::streambuf response_buffer;
        boost::asio::read_until(socket, response_buffer, '\n');

        std::string response_message = boost::asio::buffer_cast<const char *>(response_buffer.data());

        response_message.erase(std::prev(response_message.cend()));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}



