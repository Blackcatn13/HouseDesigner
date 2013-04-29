#include "TreeFile.h"

TreeFile::TreeFile(QTreeView* treeView, std::string tabName)
{
    modelDir = "/Models/";
    modelDir.append(tabName);
    QString relativePath = QString::fromStdString(modelDir);
    m_model = new QFileSystemModel;
    m_model->setReadOnly(true);
    m_model->setRootPath(QDir::currentPath().append(relativePath));

    QModelIndex index = m_model->index(QDir::currentPath().append(relativePath));
    treeView->setModel(m_model);
    treeView->setRootIndex(index);
    treeView->expand(index);


    //Hide useless information columns.
    for (int i = 1; i < 4; ++i)
        treeView->hideColumn(i);
}

TreeFile::~TreeFile()
{
    delete m_model;
}
