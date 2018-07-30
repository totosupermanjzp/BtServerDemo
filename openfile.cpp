#include "openfile.h"

class OpenFileData : public QSharedData
{
public:

};

OpenFile::OpenFile() : data(new OpenFileData)
{

}

OpenFile::OpenFile(QString strFilePath)
{
    strfilePath = strFilePath;
}

OpenFile::~OpenFile()
{

}

bool OpenFile::bIsExsitFolder()
{
    QDir dir(strfilePath);
    if(!dir.exists())
    {
        return false;
    }
    else
    {
        fileDir = dir;
        //qDebug()<<strfilePath;
        //qDebug()<<"fileDir"<<fileDir;
        //qDebug()<<"dir"<<dir;
        return true;
    }
}

void OpenFile::setFilters(const QString strFormat)
{
    QStringList filters;
    filters<<strFormat;
    fileDir.setFilter(QDir::Files | QDir::NoSymLinks);      //设置类型过滤器，只为文件格式
    fileDir.setNameFilters(filters);
}

int OpenFile::ifileCount()
{
    int file_count = fileDir.count();
    if(file_count <= 0 )
    {
        return -1;
    }
}

QStringList OpenFile::fileNameList(int dir_count)
{
    QStringList string_list;
    for(int i=0; i<dir_count; i++)
    {
        QString file_name = fileDir[i];  //文件名称
        string_list.append(file_name);
    }
    strListName = string_list;
    return string_list;
}

bool OpenFile::reNameFile()
{
    return false;
}
