#include <windows/mainwindow.h>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(boost::asio::ip::tcp::socket &socket, boost::asio::ip::tcp::resolver &resolver, QWidget *parent) : main_socket(socket),
                                                                                                                          main_resolver(resolver),
                                                                                                                          QMainWindow(parent),
                                                                                                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Connect_clicked()
{
    std::string username{ui->Username->text().toStdString()};
    std::string hostname{ui->Hostname->text().toStdString()};
    std::string port{ui->Port->text().toStdString()};

    if (username.empty())
    {
        QMessageBox *message_box = new QMessageBox(QMessageBox::Icon::Warning, "Invalid Username !", "Username cannot be empty !", QMessageBox::Button::Ok, this);
        message_box->open();

        return;
    }

    if(hostname.empty() || port.empty())
    {
        QMessageBox *message_box = new QMessageBox(QMessageBox::Icon::Warning, "Invalid Connectio Credentials !", "Connection Credentials cannot be empty !", QMessageBox::Button::Ok, this);
        message_box->open();

        return;
    }

    try
    {
        boost::asio::connect(main_socket, main_resolver.resolve({hostname, port}));

        room_menu = new RoomMenuWindow(main_socket, username);

        room_menu->show();

        this->close();
    }
    catch (std::exception &e)
    {
        QMessageBox *message_box = new QMessageBox(QMessageBox::Icon::Warning, "Failed to connect to the specified server !", "Check your connection credentials or try again later !", QMessageBox::Button::Ok, this);
        message_box->open();
    }
}
