#include "thothwindow.h"
#include "ui_thothwindow.h"
#include <QTreeWidget>



ThothWindow::ThothWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThothWindow)
{
    ui->setupUi(this);
    // ALERT! Use the following code to get keyboard focus at your OpenGL widget
    ui->contextGL->setFocusPolicy(Qt::StrongFocus);
    ui->contextGL->setFocus();

    //Tree file.
    TreeFile *tf = new TreeFile(ui->treeWidget);
    tf->setHeaderName("Model explorer");
}

ThothWindow::~ThothWindow()
{
    delete ui;
}

