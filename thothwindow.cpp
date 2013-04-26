#include "thothwindow.h"
#include "ui_thothwindow.h"
#include <QTreeWidget>

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
    TreeFile *tf = new TreeFile(ui->treeWidget, "Build");
    tf->SetHeaderName("Model explorer");

    std::string lash = "Furnish";
    m_model = new QFileSystemModel;

    m_model->setReadOnly(true);
    m_model->setRootPath(QDir::currentPath().append(QString::fromStdString("/Models/")).append(QString::fromStdString(lash)));


    ui->treeView->setModel(m_model);
    QModelIndex index = m_model->index(QDir::currentPath().append(QString::fromStdString("/Models/")).append(QString::fromStdString(lash)));
    ui->treeView->setRootIndex(index);
    ui->treeView->expand(index);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);



}

ThothWindow::~ThothWindow()
{
    delete ui;
}


void ThothWindow::on_pushButton_clicked()
{
    //Select model
    QModelIndex indx = ui->treeView->currentIndex();
    if(m_model->fileInfo(indx).isFile())
    {
        qDebug("Model path is: %s", qPrintable(m_model->fileInfo(indx).absoluteFilePath()));
    }
}

void ThothWindow::on_pushButton_2_clicked()
{
    //Delete model
}
