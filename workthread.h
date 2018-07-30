#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <openfile.h>
class WorkThread :public QThread
{
    Q_OBJECT
public:
    explicit WorkThread(QObject *parent = 0);



    void setFlage(bool flag = true);//设置标志位，何时关闭子程序
signals:
    void MySignal(QString);

public slots:
    void MyFunction(QString str);//线程处理的函数
protected:
    bool isStop;
};

#endif // WORKTHREAD_H
