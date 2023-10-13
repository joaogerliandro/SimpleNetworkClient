#include <windows/chatroomwindow.h>
#include "ui_chatroomwindow.h"

void listen_server(ChatRoomWindow *widget, Ui::ChatRoomWindow *ui)
{
    try
    {
        widget->media_player->setSource(QUrl::fromLocalFile("resources\\sounds\\steam-notf.mp3"));
        widget->media_player->audioOutput()->setVolume(100);

        while (true)
        {
            boost::asio::streambuf response_buffer;
            boost::asio::read_until(widget->server_socket, response_buffer, '\n');

            std::string response_message = boost::asio::buffer_cast<const char *>(response_buffer.data());

            widget->media_player->play();

            response_message.erase(std::prev(response_message.cend()));

            ui->ChatHistory->append(QString::fromStdString(response_message));

            QApplication::alert(widget);
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

    setup_mediaplayer();

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

    std::thread(listen_server, this, ui).detach();
}

void ChatRoomWindow::setup_mediaplayer()
{
    media_player = new QMediaPlayer;
    audio_output = new QAudioOutput;

    media_player->setAudioOutput(audio_output);
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

