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
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel(QString::fromStdString("Model explorer"));

    Directory *direct = Directory::GetInstance();
    direct->SetPath(direct->GetCurrentPath()+"/Models/");
    std::vector<std::string> models = direct->GetModels();
    for (int i = 0; i < models.size(); ++i)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, QString::fromStdString(models[i]));
        ui->treeWidget->addTopLevelItem(item);
    }
}

ThothWindow::~ThothWindow()
{
    delete ui;
}

