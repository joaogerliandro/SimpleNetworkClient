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
    explicit RoomMenuWindow(QWidget *parent = nullptr);

    ~RoomMenuWindow();

private:
    Ui::RoomMenuWindow *ui;
};

#endif // ROOMMENUWINDOW_H
