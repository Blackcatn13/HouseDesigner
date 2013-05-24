#include "thothwindow.h"
#include "ui_thothwindow.h"
#include <QTreeWidget>
//Important includes
#include <QModelIndex>
#include <QFileSystemModel>
#include <QDir>
#include "ProjectManager.h"
#include "Scenary.h"
#include <qtimer.h>
#include <qpalette.h>
#include "RenderManager.h"

#define TICK_PER_SECOND 1000/40

ThothWindow::ThothWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThothWindow)
{
    ui->setupUi(this);
    // ALERT! Use the following code to get keyboard focus at your OpenGL widget
    ui->contextGL->setFocusPolicy(Qt::StrongFocus);
    ui->contextGL->setFocus();
    message = new QLabel(this);
    ui->statusBar->showMessage("Ready");
    ui->statusBar->addPermanentWidget(message);
    message->setText("No model selected");
    //Tree file.

    //treeview of tabs
    TreeFile *m_build = new TreeFile(ui->treeViewBuild, "Build");
    m_buildModel = m_build->getQFileSystemModel();
    TreeFile *m_decorate = new TreeFile(ui->treeViewDecorate, "Decorate");
    m_decorateModel = m_decorate->getQFileSystemModel();
    TreeFile *m_furnish = new TreeFile(ui->treeViewFurnish, "Furnish");
    m_furnishModel = m_furnish->getQFileSystemModel();
    connect(ui->actionSave_project, SIGNAL(triggered()), this, SLOT(actionSave_project_triggered()));
    QTimer *tim = new QTimer(this);
    connect(tim, SIGNAL(timeout()), ui->contextGL, SLOT(updateGL()));
    tim->start(TICK_PER_SECOND);
    connect(tim, SIGNAL(timeout()), ui->contextGL, SLOT(checkActiveModel()));
    connect(ui->SldR, SIGNAL(valueChanged(int)), SLOT(onColorChanged()));
    connect(ui->SldG, SIGNAL(valueChanged(int)), SLOT(onColorChanged()));
    connect(ui->SldB, SIGNAL(valueChanged(int)), SLOT(onColorChanged()));
    onColorChanged();
    connect(CScenary::getInstance(), SIGNAL(setNameModel(string)), SLOT(getModelName(string)));
    connect(RenderManager::GetInstance(), SIGNAL(sendChangeTab()), SLOT(changeTab()));
}

ThothWindow::~ThothWindow()
{
    delete ui;
    //FIXME: Take care if the user closes the application and i'm not initializated.
    //delete m_buildModel;
    //delete m_decorateModel;
    //delete m_furnishModel;
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
                CScenary::getInstance()->setActiveModel(info.canonicalFilePath().toStdString());
                CScenary::getInstance()->setActiveType(WALL);
            }
            if(info.absoluteFilePath().contains(QString("stair"), Qt::CaseInsensitive))
            {
                CScenary::getInstance()->setActiveModel(info.canonicalFilePath().toStdString());
                CScenary::getInstance()->setActiveType(STAIR);
            }
            string path = info.canonicalFilePath().toStdString();
            int namesize = path.find_last_of('.') - path.find_last_of('/');
            string name = path.substr(path.find_last_of('/') + 1, namesize - 1);
            message->setText(QString("Selected model: ").append(QString(name.c_str())));
        }
    }
    ui->contextGL->setFocus();
}

void ThothWindow::on_pushButton_5_clicked()
{
    //Delete build model
    QModelIndex indx = ui->treeViewBuild->currentIndex();
    if(indx.isValid())
    {
        if(m_buildModel->fileInfo(indx).isFile())
        {
            qDebug("Delete model with path: %s", qPrintable(m_buildModel->fileInfo(indx).absoluteFilePath()));
        }
    }
    ui->contextGL->setFocus();
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
            CScenary::getInstance()->setActiveModel(info.canonicalFilePath().toStdString());
                CScenary::getInstance()->setActiveType(OBJECT);
            string path = info.canonicalFilePath().toStdString();
            int namesize = path.find_last_of('.') - path.find_last_of('/');
            string name = path.substr(path.find_last_of('/') + 1, namesize - 1);
            message->setText(QString("Selected model: ").append(QString(name.c_str())));
        }
    }
    ui->contextGL->setFocus();
}

void ThothWindow::on_pushButton_2_clicked()
{
    //Delete furnish model
    QModelIndex indx = ui->treeViewFurnish->currentIndex();
    if(indx.isValid())
    {
        if(m_furnishModel->fileInfo(indx).isFile())
        {
            qDebug("Delete model with path: %s", qPrintable(m_furnishModel->fileInfo(indx).absoluteFilePath()));
        }
    }
    ui->contextGL->setFocus();
}

void ThothWindow::on_pushButton_6_clicked()
{
    //Select decorate model
    QModelIndex indx = ui->treeViewDecorate->currentIndex();
    if(indx.isValid())
    {
        if(m_decorateModel->fileInfo(indx).isFile())
        {
            qDebug("Create model with path: %s", qPrintable(m_decorateModel->fileInfo(indx).absoluteFilePath()));
        }
    }
    ui->contextGL->setFocus();
}

void ThothWindow::on_pushButton_7_clicked()
{
    //Delete decorate model
    QModelIndex indx = ui->treeViewDecorate->currentIndex();
    if(indx.isValid())
    {
        if(m_decorateModel->fileInfo(indx).isFile())
        {
            qDebug("Delete model with path: %s", qPrintable(m_decorateModel->fileInfo(indx).absoluteFilePath()));
        }
    }
    ui->contextGL->setFocus();
}

void ThothWindow::actionSave_project_triggered()
{
    CProjectManager::getInstance()->SaveMap("zProject.txt");
}

void ThothWindow::on_lineEdit_2_editingFinished()
{
    //New size of x grid.
    QString txt = ui->lineEdit_2->text();
    int maxX = txt.toInt();
    if (maxX > 0 && maxX < 255)
        CScenary::getInstance()->setGridMaxX(maxX);
}

void ThothWindow::on_lineEdit_editingFinished()
{
    //New size of x grid.
    int maxZ = ui->lineEdit->text().toInt();
    if (maxZ > 0 && maxZ < 255)
        CScenary::getInstance()->setGridMaxZ(maxZ);
}

void ThothWindow::on_floorBox_valueChanged(int setFloor)
{
    CScenary *cs =CScenary::getInstance();
    setFloor = min(setFloor, 5);
    setFloor = max(setFloor, 1);
    while (cs->getNFloors() < setFloor)
    {
        cs->addNewFloor();
    }
    cs->ChangeFloor(setFloor-1);
}

void ThothWindow::onColorChanged()
{
    m_color.setRgb(ui->SldR->value(), ui->SldG->value(), ui->SldB->value());
    QPalette pal = ui->ColorW->palette();
    pal.setColor(QPalette::Window, m_color);
    ui->ColorW->setPalette(pal);
    emit colorChanged(m_color);
}

void ThothWindow::getModelName(string path)
{
    int namesize = path.find_last_of('.') - path.find_last_of('/');
    string name = path.substr(path.find_last_of('/') + 1, namesize - 1);
    if(name.compare("") == 0)
        message->setText("No model selected");
    else
        message->setText(QString("Selected model: ").append(QString(name.c_str())));
}

void ThothWindow::changeTab()
{
    ui->tabWidget->setCurrentWidget(ui->decorate_tab);
}