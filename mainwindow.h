#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QDebug"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_clearRecvButton_clicked();

    void on_SendDButton_clicked();

    void on_OpenSeriButton_clicked();

    void Read_Data();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
};

#endif // MAINWINDOW_H
