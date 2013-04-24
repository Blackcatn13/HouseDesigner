#include "TreeFile.h"
#include "iostream"

#define nCols 1

TreeFile::TreeFile(QTreeWidget* treeWidget, std::string tabName)
{
    m_dir = new Directory();
    m_tree = treeWidget;
    //Set the number of columns.
    m_tree->setColumnCount(nCols);
    std::string str = "Hola";
    std::cout << str[0] << std::endl;
//    m_dir->SetPath(m_dir->GetCurrentPath() + modelDir + tabName);
    m_dir->SetPath(m_dir->GetCurrentPath() + modelDir);
    m_dir->getHierarchy();
    std::vector<std::string> models = m_dir->GetModels();

        QTreeWidgetItem *item = AddRoot("padre1");
        AddChild(item, "hijo1");
        QTreeWidgetItem *child = AddChild(item, "hijo2");
        AddChild(child, "nieto1");
        AddChild(child, "nieto2");
}

TreeFile::~TreeFile()
{
    delete m_dir;
    delete m_tree;
}

void TreeFile::SetHeaderName(std::string name)
{
   m_tree->setHeaderLabel(QString::fromStdString(name));
}
void TreeFile::SetTree(std::string path, bool recursive, bool showRoot)
{
//    if (!PathIsRelative(path))
//    {
//        path = m_dir->GetCurrentPath()+"/Models/";
//    }
}

QTreeWidgetItem* TreeFile::AddRoot(std::string name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(m_tree);
    item->setText(0, QString::fromStdString(name));
    m_tree->addTopLevelItem(item);
    //Handle delete item pointer...
    return item;
}

QTreeWidgetItem* TreeFile::AddChild(QTreeWidgetItem *parent, std::string name)
{
    QTreeWidgetItem *childitem = new QTreeWidgetItem();
    childitem->setText(0, QString::fromStdString(name));
    parent->addChild(childitem);
    return childitem;
}

QTreeWidgetItem* TreeFile::AddChildren(QTreeWidgetItem *parent, std::string name)
{
    QTreeWidgetItem *childitem = new QTreeWidgetItem();
    childitem->setText(0, QString::fromStdString(name));
    return childitem;
}
