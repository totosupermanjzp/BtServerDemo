#ifndef OPENFILE_H
#define OPENFILE_H

#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

class OpenFileData;

class OpenFile
{
public:
    OpenFile();
    OpenFile(QString strFilePath);
    ~OpenFile();
    bool bIsExsitFolder();
    void setFilters(const QString strFormat);
    int ifileCount();
    QStringList fileNameList(int i);
    bool reNameFile();

private:
    QSharedDataPointer<OpenFileData> data;
    QString strfilePath;
    QDir fileDir;
    QStringList strListName;
};

#endif // OPENFILE_H
