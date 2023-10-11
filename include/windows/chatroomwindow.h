#ifndef CHATROOMWINDOW_H
#define CHATROOMWINDOW_H

#include <common.h>

#include <entities/room.h>

#include <QWidget>
#include <QKeyEvent>
#include <QScrollBar>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
    class ChatRoomWindow;
}

class ChatRoomWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit ChatRoomWindow(boost::asio::ip::tcp::socket &socket, Room chat_room, QWidget *parent = nullptr);
        ~ChatRoomWindow();

private slots:
    void on_SendButton_clicked();

    void on_InputLine_returnPressed();

    void on_ChatHistory_textChanged();

private:
        Ui::ChatRoomWindow *ui;

        boost::asio::ip::tcp::socket &server_socket;

        QMediaPlayer *media_player;
        QAudioOutput *audio_output;

        void setup_chatroom(Room chat_room);

        void setup_mediaplayer();
};

#endif // CHATROOMWINDOW_H
