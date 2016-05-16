#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qextserialport.h>
#include <qextserialenumerator.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QextSerialPort * port = new QextSerialPort();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    bool success;
    bool time_to_exit;
    QTimer* tmrTimer;
    QTimer *heartbeatTimer;
    QTimer* tmr_serial_timeout;
    Ui::MainWindow *ui;

private slots:

    void main_slot();

    int _refresh_serial();
    int connect_serial();


    void on_PortRefresh_released();
    void on_sendButton_released();
    void on_connectButton_released();
    void on_pushButton_released();
};

#endif // MAINWINDOW_H
