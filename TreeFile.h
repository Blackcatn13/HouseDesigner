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
    TreeFile(QTreeWidget* treeWidget, std::string tabName = "");
    ~TreeFile();
    void SetHeaderName(std::string name);
    void SetTree(std::string path, bool recursive = true, bool showRoot = true);
private:
    Directory*          m_dir;
    QTreeWidget*        m_tree;
    std::string         modelDir = "/Models/";
    QTreeWidgetItem*     AddRoot(std::string name);
    QTreeWidgetItem*     AddChild(QTreeWidgetItem *parent, std::string name);
};

#endif // TREEFILE_H
