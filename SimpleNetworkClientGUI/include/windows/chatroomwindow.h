#ifndef CHATROOMWINDOW_H
#define CHATROOMWINDOW_H

#include <common.h>

#include <entities/room.h>

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
    class ChatRoomWindow;
}

class ChatRoomWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit ChatRoomWindow(Room chat_room, boost::asio::ip::tcp::socket &socket, QWidget *parent = nullptr);
        ~ChatRoomWindow();

private slots:
    void on_SendButton_clicked();

    void on_InputLine_returnPressed();

private:
        Ui::ChatRoomWindow *ui;

        boost::asio::ip::tcp::socket &server_socket;

        void setup_chatroom(Room chat_room);
};

#endif // CHATROOMWINDOW_H
