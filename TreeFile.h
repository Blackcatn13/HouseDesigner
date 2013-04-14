#ifndef TREEFILE_H
#define TREEFILE_H

#include <QtCore>
#include <QtGui>
#include "Directory.h"

#define NULL 0
class TreeFile;

class TreeFile
{
public:
    static TreeFile*    GetInstance();
private:
    TreeFile();
    static TreeFile*    m_TreeFile;
    Directory*          m_dir;
};

#endif // TREEFILE_H
