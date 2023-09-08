#include <standard_libs.h>

#include <common.h>

#include <windows/mainwindow.h>
#include "./ui_mainwindow.h"

using boost::asio::ip::tcp;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Connect_clicked()
{
    std::string hostname{ui->Hostname->text().toStdString()};
    std::string port{ui->Port->text().toStdString()};

    try
    {
        boost::asio::io_context io_context;

        tcp::socket socket(io_context);
        tcp::resolver resolver(io_context);

        std::cout << "[CLIENT]: Trying to connect to the server ..." << std::endl;

        boost::asio::connect(socket, resolver.resolve({hostname, port}));

        std::cout << "[CLIENT]: Server connection established !" << std::endl;

        room_menu = new RoomMenuWindow();

        room_menu->show();

        this->close();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

