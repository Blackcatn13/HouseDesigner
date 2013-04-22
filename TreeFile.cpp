#include "TreeFile.h"
#include "iostream"

TreeFile::TreeFile(QTreeWidget* treeWidget, int nColumns)
{
    m_dir = new Directory();
    m_tree = treeWidget;
    //Set the number of columns.
    m_tree->setColumnCount(nColumns);
    std::string str = "Hola";
    std::cout << str[0] << std::endl;
    Directory *direct = new Directory();
    direct->SetPath(direct->GetCurrentPath()+"/Models/");
    std::vector<std::string> models = direct->GetModels();
    for (int i = 0; i < models.size(); ++i)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(m_tree);
        item->setText(0, QString::fromStdString(models[i]));
        m_tree->addTopLevelItem(item);
    }
}

TreeFile::~TreeFile()
{
    delete m_dir;
    delete m_tree;
}

void TreeFile::setHeaderName(std::string name)
{
   m_tree->setHeaderLabel(QString::fromStdString(name));
}

void TreeFile::setTree(std::string path, bool recursive, bool showRoot)
{
    if (!PathIsRelative(path))
    {
        path = m_dir->GetCurrentPath()+"/Models/";
    }

}


