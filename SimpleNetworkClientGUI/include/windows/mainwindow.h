#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows/roommenuwindow.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;

        RoomMenuWindow *room_menu;

    private slots:
        void on_Connect_clicked();
};
#endif // MAINWINDOW_H
