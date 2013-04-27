#include "thothwindow.h"
#include "ui_thothwindow.h"
#include <QTreeWidget>
#include "Scenary.h"
//Important includes
#include <QModelIndex>
#include <QFileSystemModel>
#include <QDir>

ThothWindow::ThothWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThothWindow)
{
    ui->setupUi(this);
    // ALERT! Use the following code to get keyboard focus at your OpenGL widget
    ui->contextGL->setFocusPolicy(Qt::StrongFocus);
    ui->contextGL->setFocus();

    //Tree file.

    //Build tab
    std::string tab1 = "Build";
    m_buildModel = new QFileSystemModel;

    m_buildModel->setReadOnly(true);
    m_buildModel->setRootPath(QDir::currentPath().append(QString::fromStdString("/Models/")).append(QString::fromStdString(tab1)));


    ui->treeViewBuild->setModel(m_buildModel);
    QModelIndex index1 = m_buildModel->index(QDir::currentPath().append(QString::fromStdString("/Models/")).append(QString::fromStdString(tab1)));
    ui->treeViewBuild->setRootIndex(index1);
    ui->treeViewBuild->expand(index1);
    ui->treeViewBuild->hideColumn(1);
    ui->treeViewBuild->hideColumn(2);
    ui->treeViewBuild->hideColumn(3);


    //Furnish tab
    std::string tab = "Furnish";
    m_furnishModel = new QFileSystemModel;

    m_furnishModel->setReadOnly(true);
    m_furnishModel->setRootPath(QDir::currentPath().append(QString::fromStdString("/Models/")).append(QString::fromStdString(tab)));


    ui->treeViewFurnish->setModel(m_furnishModel);
    QModelIndex index = m_furnishModel->index(QDir::currentPath().append(QString::fromStdString("/Models/")).append(QString::fromStdString(tab)));
    ui->treeViewFurnish->setRootIndex(index);
    ui->treeViewFurnish->expand(index);
    ui->treeViewFurnish->hideColumn(1);
    ui->treeViewFurnish->hideColumn(2);
    ui->treeViewFurnish->hideColumn(3);

    //Decorate tab

    std::string tab2 = "Decorate";
    m_decorateModel = new QFileSystemModel;

    m_decorateModel->setReadOnly(true);
    m_decorateModel->setRootPath(QDir::currentPath().append(QString::fromStdString("/Models/")).append(QString::fromStdString(tab2)));


    ui->treeViewDecorate->setModel(m_decorateModel);
    QModelIndex index2 = m_decorateModel->index(QDir::currentPath().append(QString::fromStdString("/Models/")).append(QString::fromStdString(tab2)));
    ui->treeViewDecorate->setRootIndex(index2);
    ui->treeViewDecorate->expand(index2);
    ui->treeViewDecorate->hideColumn(1);
    ui->treeViewDecorate->hideColumn(2);
    ui->treeViewDecorate->hideColumn(3);



}

ThothWindow::~ThothWindow()
{
    delete ui;
}

void ThothWindow::on_pushButton_4_clicked()
{
    //Select build model
    QModelIndex indx = ui->treeViewBuild->currentIndex();
    QFileInfo info = m_buildModel->fileInfo(indx);
    if(info.isFile())
    {
        if(info.suffix() == QString("obj"))
        {
            qDebug("Create model with path: %s", qPrintable(info.absoluteFilePath()));
            if(info.absoluteFilePath().contains(QString("wall"),Qt::CaseInsensitive))
            {
                CScenary::getInstance()->setActiveModel(info.absoluteFilePath().toStdString());
                CScenary::getInstance()->setActiveType(WALL);
            }
        }
    }
}

void ThothWindow::on_pushButton_5_clicked()
{
    //Delete build model
    QModelIndex indx = ui->treeViewBuild->currentIndex();
    if(m_buildModel->fileInfo(indx).isFile())
    {
        qDebug("Delete model with path: %s", qPrintable(m_buildModel->fileInfo(indx).absoluteFilePath()));
    }
}

void ThothWindow::on_pushButton_clicked()
{
    //Select furnish model
    QModelIndex indx = ui->treeViewFurnish->currentIndex();
    QFileInfo info = m_furnishModel->fileInfo(indx);
    if(info.isFile())
    {
        if(info.suffix() == QString("obj"))
        {
            qDebug("Create model with path: %s", qPrintable(info.absoluteFilePath()));
                CScenary::getInstance()->setActiveModel(info.absoluteFilePath().toStdString());
                CScenary::getInstance()->setActiveType(OBJECT);
        }
    }
}

void ThothWindow::on_pushButton_2_clicked()
{
    //Delete furnish model
    QModelIndex indx = ui->treeViewFurnish->currentIndex();
    if(m_furnishModel->fileInfo(indx).isFile())
    {
        qDebug("Delete model with path: %s", qPrintable(m_furnishModel->fileInfo(indx).absoluteFilePath()));
    }
}

void ThothWindow::on_pushButton_6_clicked()
{
    //Select decorate model
    QModelIndex indx = ui->treeViewDecorate->currentIndex();
    if(m_decorateModel->fileInfo(indx).isFile())
    {
        qDebug("Create model with path: %s", qPrintable(m_decorateModel->fileInfo(indx).absoluteFilePath()));
    }
}

void ThothWindow::on_pushButton_7_clicked()
{
    //Delete decorate model
    QModelIndex indx = ui->treeViewDecorate->currentIndex();
    if(m_decorateModel->fileInfo(indx).isFile())
    {
        qDebug("Delete model with path: %s", qPrintable(m_decorateModel->fileInfo(indx).absoluteFilePath()));
    }
}
