#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTimer"
#include "qextserialenumerator.h"
#include "iostream"
#include "fstream"
#include <sys/time.h>
#include <QThread>
#include <QDebug>
#include <QTime>

#define DEBUG

// 46.073268
// 14.509567


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_PortRefresh_released();

    tmrTimer = new QTimer(this);
    connect(tmrTimer,  SIGNAL(timeout()),this,SLOT(main_slot()));
    tmrTimer->start(30);

    QStringList _baud_rates;
    _baud_rates << "4800" << "9600" << "19200" << "38400" << "57600" << "115200" << "230400";
    //ui->baudBox->addItems(_baud_rates);
    //ui->baudBox->setCurrentIndex(ui->baudBox->findText("57600"));

    _refresh_serial();
    connect_serial();

    this->setWindowTitle("Quest Box");

#ifdef DEBUG
    ui->latEdit->append("46.073268");
    ui->lonEdit->append("14.509567");
    ui->radiusEdit->append("40");
#else
    ui->latEdit->setPlaceholderText("46.073268");
    ui->lonEdit->setPlaceholderText("14.509567");
    ui->radiusEdit->setPlaceholderText("40");
#endif
}

void MainWindow::main_slot()
{
//    QString data_in;
//    while(port->size() > 0){
//        data_in = port->read(64);
//        if (QString::compare(data_in, "Received OK", Qt::CaseInsensitive) == 0){
//            qDebug("Success!!!");
//            ui->serialIn->insertPlainText(data_in);
//        }

//    }

    ui->serialIn->insertPlainText(port->readAll());


}

void MainWindow::on_PortRefresh_released()
{
    _refresh_serial();
}


MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::_refresh_serial(){
    ui->portBox->clear();
    // Serch for serial ports and put them in portBox
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts()){
        ui->portBox->addItem(info.portName);
        ui->portBox->setCurrentIndex(ui->portBox->findText(info.portName));
    }
}

int MainWindow::connect_serial(){

    port->close();

    //port->setBaudRate(ui->baudBox->currentText().toInt());
    port->setBaudRate(57600);
    port->setPortName(ui->portBox->currentText());

    if (!port->open(QIODevice::ReadWrite)){
        qDebug("Connected to %s", ui->portBox->currentText().toStdString());
        return 0;
    }
    else {
        qDebug("Cannot connect to %s", ui->portBox->currentText());
        return 1;
    }
}

void MainWindow::on_connectButton_released() {
    printf("Test");
    if (!ui->connectButton->isChecked()){
        qDebug("Closing port %s", ui->portBox->currentText().toStdString());
        port->close();
    }
    else {
        qDebug("Cannecting to %s", ui->portBox->currentText().toStdString());
        connect_serial();
    }
}

void MainWindow::on_sendButton_released()
{
    std::string data;
    ui->serialIn->clear();

    bool ok = 0;
    bool error = 0;
    int lines = 0;
    QString data_in, serial_text, serial_line;
    data_in.clear();
    serial_text.clear();

    while (!ok){
        data.append("#########");
        data.append(ui->latEdit->toPlainText().toLatin1());
        data.append("#");
        data.append(ui->lonEdit->toPlainText().toLatin1());
        data.append("#");
        data.append(ui->radiusEdit->toPlainText().toLatin1());
        data.append("$");

        //port->write()
        port->write(data.c_str());

        QTime timer;
        timer.start();

//        while (timer.elapsed() < 500){
//            while(port->size() > 10 && !ok){
//                data_in = port->readAll();
//                serial_text.append(data_in);
//                if (QString::compare(data_in, "Received OK", Qt::CaseInsensitive) == 0){
//                    qDebug("Success!!!");
//                    ok = 1;
//                }
//            }
//        }






//        while (timer.elapsed() < 5000) {
//            while (port->size() < 10) {}


//            QString msg;

//            do {
//                msg = port->read(1);
//                serial_line.append(msg);
//            } while (msg.compare("\n") != 0);

//            qDebug() << "msg:" << serial_line;

//            if (serial_line.contains("Received lat")) {
//                if (serial_line.contains(ui->latEdit->toPlainText().toLatin1())) {
//                    lines++;
//                }
//                else {
//                    error = 1;
//                }
//            }

//            do {
//                msg = port->read(1);
//                serial_line.append(msg);
//            } while (msg.compare("\n") != 0);

//            if (serial_line.contains("Received lon")) {
//                if (serial_line.contains(ui->lonEdit->toPlainText().toLatin1())) {
//                    lines++;
//                }
//                else {
//                    error = 1;
//                }
//            }

//            do {
//                msg = port->read(1);
//                serial_line.append(msg);
//            } while (msg.compare("\n") != 0);


//            if (serial_line.contains("Received rad")) {
//                if (serial_line.contains(ui->radiusEdit->toPlainText().toLatin1())) {
//                    lines++;
//                }
//                else {
//                    error = 1;
//                }
//            }

//            if (lines >= 3 && error == 0) {
//                qDebug() << "Success";
//                break;
//            }

//            if (msg)



//            if (msg.contains("Unrecognised")) {
//                    qDebug() << "Error";
//                    serial_text.clear();
//                    break;
//            }
//            else if (msg.contains("Received OK")) {
//                ok = 1;
//                qDebug() << "Success";
//                break;
//            }
//        }
//        ui->serialIn->insertPlainText(serial_text);

//        if (error = 0) break;



//        bool lat = 0;
//        bool lon = 0;
//        bool rad = 0;
//        QString msg;

//        while (timer.elapsed() < 5000) {
//            while (port->size() < 6) {}

//            do {
//                msg = port->read(1);
//                serial_line.append(msg);
//            } while (msg.compare("\n") != 0 && timer.elapsed() < 5000);

//            serial_text.append(msg);
//            qDebug() << "msg:" << msg;

//            if (msg.contains("Unrecognised")) {
//                qDebug() << "Error";
//                serial_text.clear();
//                port->flush();
//                break;
//            }

//            else if (msg.contains("Received lat")) {
//                if (serial_line.contains(ui->latEdit->toPlainText().toLatin1())) {
//                    qDebug() << "Lat OK";
//                    lat = 1;
//                }
//                else {
//                    qDebug() << "Error in lat";
//                    break;
//                }
//            }

//            else if (msg.contains("Received lon")) {
//                if (serial_line.contains(ui->lonEdit->toPlainText().toLatin1())) {
//                    qDebug() << "Lon OK";
//                    lon = 1;
//                }
//                else {
//                    qDebug() << "Error in lon";
//                    break;
//                }
//            }

//            else if (msg.contains("Received rad")) {
//                if (serial_line.contains(ui->radiusEdit->toPlainText().toLatin1())) {
//                    qDebug() << "Rad OK";
//                    rad = 1;
//                }
//                else {
//                    qDebug() << "Error in rad";
//                    break;
//                }
//            }
//            else if (msg.contains("Received OK") && lat && lon && rad) {
//                ok = 1;
//                qDebug() << "Success";
//                ui->serialIn->insertPlainText(serial_text);
//                break;
//            }
//        }








/* to dela */
        while (timer.elapsed() < 5000) {
            while (port->size() < 10) {}
            QString msg = port->readLine();
            serial_text.append(msg);
            qDebug() << "msg:" << msg;
            if (msg.contains("Unrecognised")) {
                    qDebug() << "Error";
                    serial_text.clear();
                    port->flush();
                    break;
            }
            else if (msg.contains("Received OK")) {
                ok = 1;
                qDebug() << "Success";
                ui->serialIn->insertPlainText(serial_text);
                break;
            }
        }


    }
}

void MainWindow::on_pushButton_released()
{
    ui->serialIn->clear();
}
