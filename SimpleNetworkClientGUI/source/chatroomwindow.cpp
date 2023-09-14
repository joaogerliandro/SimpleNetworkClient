#include <windows/chatroomwindow.h>
#include "ui_chatroomwindow.h"

ChatRoomWindow::ChatRoomWindow(Room chat_room, boost::asio::ip::tcp::socket &socket, QWidget *parent) :
    server_socket(socket),
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
    this->setWindowTitle(QString::fromStdString(chat_room.get_name()));
}
