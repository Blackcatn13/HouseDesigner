#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "QDir"
#include <vector>
#include <QDirIterator>
#include <map>

class Directory;

class Directory
{
public:
    Directory();
    ~Directory();
    void                        SetPath(std::string path);
    std::string                 GetCurrentPath();
    std::vector<std::string>    GetModels();
    void                        ReadModel(std::string modelName);
    void                        getHierarchy();
private:
    QDir                        m_dir;
};

#endif // DIRECTORY_H
