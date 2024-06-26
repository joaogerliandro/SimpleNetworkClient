#ifndef ROOMMENUWINDOW_H
#define ROOMMENUWINDOW_H

#include <common.h>

#include <entities.h>

#include <windows/chatroomwindow.h>

#include <QWidget>
#include <QListWidgetItem>
#include <QMessageBox>

namespace Ui {
class RoomMenuWindow;
}

class RoomMenuWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit RoomMenuWindow(boost::asio::ip::tcp::socket &socket, std::string username, QWidget *parent = nullptr);

        ~RoomMenuWindow();

    private:
        Ui::RoomMenuWindow *ui;

        boost::asio::ip::tcp::socket &server_socket;

        std::string client_username;

        std::vector<Room> room_list;

        ChatRoomWindow *chat_room;

        void connection_handshake();

        void load_roomlist(std::string server_room_list);

        void connect_client_to_room(Room choosed_room);

    private slots:
        void on_RoomList_itemDoubleClicked(QListWidgetItem *item);
};

#endif // ROOMMENUWINDOW_H
