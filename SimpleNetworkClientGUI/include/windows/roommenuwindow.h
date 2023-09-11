#ifndef ROOMMENUWINDOW_H
#define ROOMMENUWINDOW_H

#include <common.h>

#include <QWidget>

namespace Ui {
class RoomMenuWindow;
}

class RoomMenuWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit RoomMenuWindow(boost::asio::ip::tcp::socket &socket, QWidget *parent = nullptr);

        ~RoomMenuWindow();

    private:
        Ui::RoomMenuWindow *ui;

        std::vector<Room> room_list;

        void connection_handshake(boost::asio::ip::tcp::socket &socket);

        void load_roomlist(std::string server_room_list);
};

#endif // ROOMMENUWINDOW_H
