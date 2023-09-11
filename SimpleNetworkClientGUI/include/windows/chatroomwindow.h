#ifndef CHATROOMWINDOW_H
#define CHATROOMWINDOW_H

#include <QWidget>

namespace Ui {
class ChatRoomWindow;
}

class ChatRoomWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoomWindow(QWidget *parent = nullptr);
    ~ChatRoomWindow();

private:
    Ui::ChatRoomWindow *ui;
};

#endif // CHATROOMWINDOW_H
