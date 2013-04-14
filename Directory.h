#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "QDir"
#include <vector>

class Directory;

class Directory
{
public:
    static Directory*           GetInstance();
    void                        SetPath(std::string path);
    std::string                 GetCurrentPath();
    std::vector<std::string>    GetModels();
    void                        ReadModel(std::string modelName);
private:
    Directory();
    static Directory*           m_Directory;
    QDir                        m_dir;
};

#endif // DIRECTORY_H
