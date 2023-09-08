#include <windows/roommenuwindow.h>
#include "ui_roommenuwindow.h"

RoomMenuWindow::RoomMenuWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomMenuWindow)
{
    ui->setupUi(this);
}

RoomMenuWindow::~RoomMenuWindow()
{
    delete ui;
}
