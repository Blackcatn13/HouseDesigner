#include "Directory.h"

#include "iostream"
#include "vector"

Directory::Directory()
{
    m_dir = QDir::currentPath();
}

Directory::~Directory()
{
}

void Directory::SetPath(std::string path)
{
    m_dir.setPath(QString::fromStdString(path));
}

std::string Directory::GetCurrentPath()
{
    return m_dir.path().toStdString();
}

std::vector<std::string> Directory::GetModels()
{
    std::vector<std::string> models;
    //Do a filter only show models.
//    QStringList filters;
//    filters << "*.obj" << "*.skp";
//    m_dir.setNameFilters(filters);
    //Ordered by name.
    m_dir.setSorting(QDir::Name);
    //Save all models into output vector.
    QFileInfoList list = m_dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        //If you want the complete filename + extension
        //use fileInfo.fileName() instead.
        models.push_back(fileInfo.baseName().toStdString());
    }
    return models;
}

void Directory::getHierarchy(){
    QDirIterator iterator(m_dir.absolutePath(), QDirIterator::Subdirectories);
    while (iterator.hasNext()){
        iterator.next();
        QString filename = iterator.fileName();
        if (!iterator.fileInfo().isDir())
        {
            qDebug("Found %s file.", qPrintable(filename));
        }
        else
        {
            if (filename != "." && filename != "..")
            {

                qDebug("Found %s dir.", qPrintable(filename));
            }
        }
    }
}
