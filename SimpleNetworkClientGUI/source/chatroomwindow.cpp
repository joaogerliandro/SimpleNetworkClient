#include <windows/chatroomwindow.h>
#include "ui_chatroomwindow.h"

ChatRoomWindow::ChatRoomWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRoomWindow)
{
    ui->setupUi(this);
}

ChatRoomWindow::~ChatRoomWindow()
{
    delete ui;
}
