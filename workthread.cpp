#include "workthread.h"

WorkThread::WorkThread(QObject *parent)
{
    //connect(this,SIGNAL(MySignal(QString)),this,SLOT(dealMySignal(QString)));
    isStop = false;
}

void WorkThread::MyFunction(QString strPath)
{
    qDebug() <<"子线程ID:"<<QThread::currentThreadId();
    qDebug() <<"Revice data" <<strPath;
    OpenFile file(strPath);
    bool bIsExsit= file.bIsExsitFolder();
    if(!bIsExsit)
    {
        //QMessageBox::information(this,"Error","The file path doesn't exsist");
        qDebug()<<"ErrorThe file path doesn't exsist";
    }
    else
    {
        file.setFilters("*.txt");
        int ifilecount = file.ifileCount();
        if(ifilecount < 0)
        {
            //QMessageBox::information(this,"Error","The file path no txt file or wrong ");
        }
        QStringList strListFileName = file.fileNameList(ifilecount);
        qDebug()<<"strListFileName:"<<strListFileName;
        //QString displayString;
        int icount = 0;
        while(icount < ifilecount)
        {
            QString Path = strPath + "/" + strListFileName[icount];
            qDebug()<<"Path"<<Path;
            QFile qfile(Path);
            if(!qfile.open(QIODevice::ReadWrite | QIODevice::Text)){
                qDebug()<<"Can't open the file!"<<endl;
            }
            while(!qfile.atEnd())
            {
                QByteArray line = qfile.readLine();
                QString str(line);
                QThread::sleep(1);
                qDebug() <<"data:"<<str;
                emit MySignal(str);
//                QTime t;
//                emit startwriteThread(str);
//                t.start();
//                while(t.elapsed()<5000);
                //qint64 ireturn = serial->write(str.toLatin1())



                //qDebug()<<ireturn;

                //qDebug()<<str;
                //displayString.append(str);
                //ui->sendtextEdit->clear();
                //ui->sendtextEdit->setPlainText(displayString);
            }

            qfile.close();
            //bool bIsOk = QFile::rename(Path,Path + "OK");
            //qDebug()<<bIsOk;
            icount++;
        }
    }
}

void WorkThread::setFlage(bool flag)
{
    isStop = flag;
}
