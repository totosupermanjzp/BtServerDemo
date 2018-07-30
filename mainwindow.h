#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QDebug"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "openfile.h"
#include <QTime>
#include <QList>
#include <workthread.h>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void InitThreadPools();
    void CreateNewWorkThread();
    void RunThread();

    ~MainWindow();

private slots:
    void on_clearRecvButton_clicked();

    void on_SendDButton_clicked();

    void on_OpenSeriButton_clicked();

    void Read_Data();

    void on_FindFileButton_clicked();

    void writeThread(QString str);

protected:

    QList<QThread *> m_IdleThreadPool;

signals:
    void startwriteThread(QString str);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QString strFilePath;


public:

signals:
    void startMyThread(QString str);
private:
    WorkThread *myThread;
    QThread *thread;

private slots:
    void dealClose();
    void on_TestButton_clicked();
    void dealMySignal(QString str);
};

#endif // MAINWINDOW_H
