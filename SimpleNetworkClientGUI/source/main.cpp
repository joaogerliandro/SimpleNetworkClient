#include <common.h>

#include <windows/mainwindow.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    boost::asio::io_context io_context;

    boost::asio::ip::tcp::socket socket(io_context);
    boost::asio::ip::tcp::resolver resolver(io_context);

    QApplication application(argc, argv);

    MainWindow main_window(socket, resolver);
    main_window.show();

    return application.exec();
}
