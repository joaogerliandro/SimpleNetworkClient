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

            widget->media_player->play();

            std::string response_message_str = boost::asio::buffer_cast<const char *>(response_buffer.data());
            response_message_str.erase(std::prev(response_message_str.cend()));

            Message response_message(response_message_str);

            json message_content = json::parse(response_message.m_content);

            ui->ChatHistory->append(QString::fromStdString(message_content["Message"]));

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
    json message_content_json = {{"RoomId", chat_room.get_id()}};

    Message enter_room_message(server_socket.remote_endpoint().address().to_v4().to_string(), server_socket.remote_endpoint().port(), message_content_json.dump(), MESSAGE_TYPE::ROOM_CHOICE);

    boost::asio::write(server_socket, boost::asio::buffer(enter_room_message.to_string() + "\n"));

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
    std::string reply_message_str = ui->InputLine->text().toStdString();

    if(!reply_message_str.empty())
    {
        ui->InputLine->clear();
        ui->InputLine->setCursorPosition(0);
        ui->InputLine->setFocus();

        json reply_message_json = {{"Message", reply_message_str}};

        Message reply_message(server_socket.remote_endpoint().address().to_v4().to_string(), server_socket.remote_endpoint().port(), reply_message_json.dump(), MESSAGE_TYPE::FORWARD);

        boost::asio::write(server_socket, boost::asio::buffer(reply_message.to_string() + "\n"));
    }
}

void ChatRoomWindow::on_InputLine_returnPressed()
{
    std::string reply_message_str = ui->InputLine->text().toStdString();

    if(!reply_message_str.empty())
    {
        ui->InputLine->clear();
        ui->InputLine->setCursorPosition(0);
        ui->InputLine->setFocus();

        json reply_message_json = {{"Message", reply_message_str}};

        Message reply_message(server_socket.remote_endpoint().address().to_v4().to_string(), server_socket.remote_endpoint().port(), reply_message_json.dump(), MESSAGE_TYPE::FORWARD);

        boost::asio::write(server_socket, boost::asio::buffer(reply_message.to_string() + "\n"));
    }
}

void ChatRoomWindow::on_ChatHistory_textChanged()
{
    QScrollBar *chat_scrollbar = ui->ChatHistory->verticalScrollBar();

    chat_scrollbar->setValue(chat_scrollbar->maximum());
}

void ChatRoomWindow::closeEvent(QCloseEvent *event)
{
    std::cout << "TO-DO: Implement room exiting !" << std::endl;
}

