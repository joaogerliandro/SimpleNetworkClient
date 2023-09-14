#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <standard_libs.h>

#include <common.h>

#include <windows/roommenuwindow.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(boost::asio::ip::tcp::socket &socket, boost::asio::ip::tcp::resolver &resolver, QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;

        RoomMenuWindow *room_menu;

        boost::asio::ip::tcp::socket &main_socket;

        boost::asio::ip::tcp::resolver &main_resolver;

    private slots:
        void on_Connect_clicked();
};
#endif // MAINWINDOW_H
