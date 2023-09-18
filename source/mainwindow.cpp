#include <windows/mainwindow.h>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(boost::asio::ip::tcp::socket &socket, boost::asio::ip::tcp::resolver &resolver, QWidget *parent) :
    main_socket(socket),
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
    std::string hostname{ui->Hostname->text().toStdString()};
    std::string port{ui->Port->text().toStdString()};

    try
    {
        std::cout << "[CLIENT]: Trying to connect to the server ..." << std::endl;

        boost::asio::connect(main_socket, main_resolver.resolve({hostname, port}));

        std::cout << "[CLIENT]: Server connection established !" << std::endl;

        room_menu = new RoomMenuWindow(main_socket);

        room_menu->show();

        this->close();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

