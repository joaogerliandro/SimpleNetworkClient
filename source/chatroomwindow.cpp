#include <windows/chatroomwindow.h>
#include "ui_chatroomwindow.h"

void listen_server(boost::asio::ip::tcp::socket &socket, Ui::ChatRoomWindow *ui)
{
    try
    {
        while (true)
        {
            boost::asio::streambuf response_buffer;
            boost::asio::read_until(socket, response_buffer, '\n');

            std::string response_message = boost::asio::buffer_cast<const char *>(response_buffer.data());

            response_message.erase(std::prev(response_message.cend()));

            ui->ChatHistory->append(QString::fromStdString(response_message));            
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

ChatRoomWindow::ChatRoomWindow(boost::asio::ip::tcp::socket &socket, Room chat_room, QWidget *parent)
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

    std::thread(listen_server, std::ref(server_socket), ui).detach();
}

void ChatRoomWindow::on_SendButton_clicked()
{  
    std::string reply_message = ui->InputLine->text().toStdString();

    if(!reply_message.empty())
    {
        ui->InputLine->clear();
        ui->InputLine->setCursorPosition(0);
        ui->InputLine->setFocus();

        boost::asio::write(server_socket, boost::asio::buffer(reply_message + "\n"));
    }
}

void ChatRoomWindow::on_InputLine_returnPressed()
{
    std::string reply_message = ui->InputLine->text().toStdString();

    if(!reply_message.empty())
    {
        ui->InputLine->clear();
        ui->InputLine->setCursorPosition(0);
        ui->InputLine->setFocus();

        boost::asio::write(server_socket, boost::asio::buffer(reply_message + "\n"));
    }
}

void ChatRoomWindow::on_ChatHistory_textChanged()
{
    QScrollBar *chat_scrollbar = ui->ChatHistory->verticalScrollBar();

    chat_scrollbar->setValue(chat_scrollbar->maximum());
}

