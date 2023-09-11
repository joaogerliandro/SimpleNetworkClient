#include <entities/room.h>

#include <windows/roommenuwindow.h>
#include "ui_roommenuwindow.h"

RoomMenuWindow::RoomMenuWindow(boost::asio::ip::tcp::socket &socket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomMenuWindow)
{
    ui->setupUi(this);

    connection_handshake(socket);
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

        load_roomlist(response_message);

        for(Room room : room_list)
        {
            ui->RoomList->addItem(QString::fromStdString(std::to_string(room.get_id()) + " - " + room.get_name() + " - " + std::to_string(room.get_connected_clients()) + " / " + std::to_string(room.get_size())));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void RoomMenuWindow::load_roomlist(std::string server_room_list)
{
    std::stringstream room_list_str_stream(server_room_list);
    std::string room_info;

    while(std::getline(room_list_str_stream, room_info))
    {
        std::stringstream room_info_str_stream(room_info);
        std::string room_entitie_field;

        uint8_t room_id;
        uint8_t room_size;
        uint8_t room_connected_clients;
        std::string room_name;

        while(std::getline(room_info_str_stream, room_entitie_field, ';'))
        {
            std::stringstream room_entitie_field_str_stream(room_entitie_field);

            std::string field_name;
            std::string field_value;

            std::getline(room_entitie_field_str_stream, field_name, ':');
            std::getline(room_entitie_field_str_stream, field_value);

            if(field_name == "ID")
            {
                room_id = static_cast<uint8_t>(std::stoul(field_value));
            }
            else if(field_name == "Name")
            {
                room_name = field_value;
            }
            else if(field_name == "Size")
            {
                room_size = static_cast<uint8_t>(std::stoul(field_value));
            }
            else if(field_name == "Connected")
            {
                room_connected_clients = static_cast<uint8_t>(std::stoul(field_value));
            }
        }

        room_list.push_back(Room(room_id, room_size, room_connected_clients, room_name));
    }
}



