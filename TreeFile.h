#ifndef TREEFILE_H
#define TREEFILE_H

#include "thothwindow.h"
#include "ui_thothwindow.h"
#include <QTreeWidget>
#include "Directory.h"

class TreeFile;

class TreeFile
{
public:
    TreeFile(QTreeWidget* treeWidget, int nColumns = 1);
    ~TreeFile();
    void setHeaderName(std::string name);
    void setTree(std::string path, bool recursive = true, bool showRoot = true);
private:
    Directory*      m_dir;
    QTreeWidget*    m_tree;
};

#endif // TREEFILE_H
