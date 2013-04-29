#ifndef TREEFILE_H
#define TREEFILE_H

#include "thothwindow.h"
#include "ui_thothwindow.h"
#include <QTreeView>
#include <QFileSystemModel>
#include <QString>

class TreeFile;

class TreeFile
{
public:
    TreeFile(QTreeView* treeWiew, std::string tabName = "");
    ~TreeFile();
private:
    QFileSystemModel*   m_model;
    std::string         modelDir;
};

#endif // TREEFILE_H
