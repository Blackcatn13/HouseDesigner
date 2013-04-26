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
//    TreeFile *tf = new TreeFile(ui->treeWidget, "Build");
//    tf->SetHeaderName("Model explorer");

    std::string lash = "Furnish";
    QFileSystemModel *model = new QFileSystemModel;
    model->setReadOnly(true);
    model->setRootPath(QDir::currentPath().append(QString::fromStdString("/Models/")).append(QString::fromStdString(lash)));


    ui->treeView->setModel(model);
    QModelIndex index = model->index(QDir::currentPath().append(QString::fromStdString("/Models/")).append(QString::fromStdString(lash)));
    ui->treeView->setRootIndex(index);
    ui->treeView->expand(index);

}

ThothWindow::~ThothWindow()
{
    delete ui;
}


void ThothWindow::on_pushButton_clicked()
{
    //Select model
}

void ThothWindow::on_pushButton_2_clicked()
{
    //Delete model
}
