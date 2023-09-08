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

        void connection_handshake(boost::asio::ip::tcp::socket &socket);
};

#endif // ROOMMENUWINDOW_H
