#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStringListModel"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /////////////////////////遍历可用串口//////////////////////////
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       QSerialPort serial;
       serial.setPort(info);
       if(serial.open(QIODevice::ReadWrite))
       {
           ui->portBox->addItem(serial.portName());
           serial.close();          //不占用串口
       }
    }
    ui->baudBox->setCurrentIndex(6);
    ui->SendDButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clearRecvButton_clicked()
{

}

void MainWindow::on_SendDButton_clicked()
{
    //QString qSendData = ui->lineEdit->text();
    //serial->write(&qSendData);
    serial->write(ui->sendtextEdit->toPlainText().toLatin1());
}

void MainWindow::on_OpenSeriButton_clicked()
{
    if(ui->OpenSeriButton->text() == tr("打开串口"))
    {
        serial = new QSerialPort;
        serial->setPortName(ui->portBox->currentText());
        serial->open(QIODevice::ReadWrite);
        serial->setBaudRate(ui->baudBox->currentText().toInt());
        switch (ui->BitNumBox->currentIndex())
        {
            case 8:
            {
               serial->setDataBits(QSerialPort::Data8);
               qDebug()<<"Now DataBite is Data8";
               break;
            }
            default:
                break;
        }

        //设置奇偶校验
        switch (ui->ParityBox->currentIndex())
        {
            case 0:
                serial->setParity(QSerialPort::NoParity);break;
                break;
            default:
                break;
        }

        switch (ui->stopBox->currentIndex())
        {
            case 1:
                serial->setStopBits(QSerialPort::OneStop);
                break;
            case 2:
                serial->setStopBits(QSerialPort::TwoStop);
                break;
            default:
                break;
        }

        serial->setFlowControl(QSerialPort::NoFlowControl);

        ui->portBox->setEnabled(false);
        ui->baudBox->setEnabled(false);
        ui->BitNumBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->stopBox->setEnabled(false);
        ui->OpenSeriButton->setText(tr("关闭串口"));
        ui->SendDButton->setEnabled(true);

        QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::Read_Data);
    }
    else
    {
        serial->clear();
        serial->close();
        serial->deleteLater();

        ui->portBox->setEnabled(true);
        ui->baudBox->setEnabled(true);
        ui->BitNumBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->stopBox->setEnabled(true);
        ui->OpenSeriButton->setText(tr("打开串口"));
        ui->SendDButton->setEnabled(false);
    }
}

void MainWindow::Read_Data()
{
    QByteArray buf;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {
        QString str = ui->RectextEdit->toPlainText();
        str += tr(buf);
        str += tr("\n");
        ui->RectextEdit->clear();
        ui->RectextEdit->append(str);
    }
    buf.clear();
}
