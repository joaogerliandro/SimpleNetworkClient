#include <windows/roommenuwindow.h>
#include "ui_roommenuwindow.h"

RoomMenuWindow::RoomMenuWindow(boost::asio::ip::tcp::socket &socket, std::string username, QWidget *parent) :
    server_socket(socket),
    client_username(username),
    QWidget(parent),
    ui(new Ui::RoomMenuWindow)
{
    ui->setupUi(this);

    connection_handshake();
}

RoomMenuWindow::~RoomMenuWindow()
{
    delete ui;
}

void RoomMenuWindow::connection_handshake()
{
    try
    {
        json handshake_content = {{"Username", client_username}};

        Message handshake_message(server_socket.remote_endpoint().address().to_v4().to_string(),
                                  server_socket.remote_endpoint().port(),
                                  handshake_content.dump(),
                                  MESSAGE_TYPE::HANDSHAKING);

        boost::asio::write(server_socket, boost::asio::buffer(handshake_message.to_string() + "\n"));

        boost::asio::streambuf response_buffer;
        boost::asio::read_until(server_socket, response_buffer, '\n');

        std::string response_message_str = boost::asio::buffer_cast<const char *>(response_buffer.data());

        response_message_str.erase(std::prev(response_message_str.cend()));

        Message response_message(response_message_str);

        load_roomlist(response_message.m_content);

        for(Room room : room_list)
        {
            QListWidgetItem *newItem = new QListWidgetItem;

            newItem->setData(Qt::UserRole, room.get_id());

            newItem->setText(QString::fromStdString(room.get_name() + " - " + std::to_string(room.get_connected_clients()) + " / " + std::to_string(room.get_size())));
            newItem->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            ui->RoomList->addItem(newItem);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void RoomMenuWindow::load_roomlist(std::string server_room_list)
{
    json server_room_list_json = (json::parse(server_room_list))["RoomList"];

    for(json room_json : server_room_list_json)
    {
        room_list.push_back(
            Room(room_json["ID"], room_json["Size"], room_json["ConnectedClients"], room_json["Name"])
        );
    }

}

void RoomMenuWindow::on_RoomList_itemDoubleClicked(QListWidgetItem *item)
{
    for(Room room : room_list)
        if(room.get_id() == item->data(Qt::UserRole))
            connect_client_to_room(room);
}

void RoomMenuWindow::connect_client_to_room(Room choosed_room)
{
    if(choosed_room.get_connected_clients() < choosed_room.get_size())
    {
        chat_room = new ChatRoomWindow(server_socket, choosed_room);

        chat_room->show();

        this->close();
    }
    else
    {
        QMessageBox *message_box = new QMessageBox(QMessageBox::Icon::Warning, "This room is current full !", "Try again later or try enter in another room !", QMessageBox::Button::Ok, this);
        message_box->open();
    }
}

