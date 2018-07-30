#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStringListModel"
#include "QDir"
#include "QMessageBox"
#include "QThread"

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
    ui->FindFileButton->setEnabled(false);


    myThread = new WorkThread;
    thread = new QThread(this);
    myThread->moveToThread(thread);
    qDebug()<<"主线程ID:"<<QThread::currentThreadId();
    connect(this,SIGNAL(startMyThread(QString)),myThread,SLOT(MyFunction(QString)));
    connect(this,&MainWindow::destroyed,this,&MainWindow::dealClose);
    connect(myThread,SIGNAL(MySignal(QString)),this,SLOT(dealMySignal(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clearRecvButton_clicked()
{

}

void MainWindow::RunThread()
{
    for (int i = 0; i < 5; i++)
    {
        CreateNewWorkThread();
    }
}

void MainWindow::on_SendDButton_clicked()
{
    //QString qSendData = ui->lineEdit->text();
    //serial->write(&qSendData);
    int icount = 2;
    int i = 0;
    while(i < icount)
    {
        QString strTemp = ui->sendtextEdit->toPlainText();
        strTemp += QString::number(i);
        serial->write(strTemp.toLatin1());
        i++;
    }
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
        ui->FindFileButton->setEnabled(true);

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
        ui->FindFileButton->setEnabled(false);
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
void MainWindow::dealMySignal(QString str)
{
    qDebug()<< "dealMySignal Recive data:" << str;
    serial->write(str.toLatin1());
}
void MainWindow::dealClose()
{
    qDebug()<<"-----------------------";
    thread->quit();
    thread->wait();
    delete myThread;
}

void MainWindow::on_FindFileButton_clicked()
{
    //emit startwriteThread();

    QString strPath = ui->pathEdit->text();
    thread->start();
    emit startMyThread(strPath);
}

void MainWindow::InitThreadPools()
{
    for(int i = 0; i < 5; i++)
    {
        QThread * pNewThread = new QThread(this);
        m_IdleThreadPool.append(pNewThread);
    }
}

void MainWindow::CreateNewWorkThread()
{
    QThread *thread = m_IdleThreadPool.at(0);
    m_IdleThreadPool.removeAt(1);
    moveToThread(thread);
    connect(this, SIGNAL(startwriteThread(QString)),this,SLOT(writeThread(QString)));
}
void MainWindow::writeThread(QString str)
{
    qDebug()<< "--------------子线程ID:" << QThread::currentThreadId();
}

void MainWindow::on_TestButton_clicked()
{
    thread->start();
    myThread->setFlage(false);
    QString strData = "fuck";
    emit startMyThread(strData);
}
