#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "QDir"
#include <vector>

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
private:
    QDir                        m_dir;
};

#endif // DIRECTORY_H
