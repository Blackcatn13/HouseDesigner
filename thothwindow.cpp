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
    popUp = new QLabel(this);
    ui->statusBar->addWidget(popUp);
    ui->statusBar->addPermanentWidget(message);
    message->setText("No model selected");
    ui->statusBar->showMessage("Ready", 5000);
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
    RenderManager::GetInstance()->GetRenderMode(EDITOR_2D)->SetCameraProjection(INIT_WIDTH, INIT_HEIGHT);
    connect(this, SIGNAL(changeMouseMove(bool)), RenderManager::GetInstance()->GetRenderMode(EXPLORER), SLOT(setMouseMove(bool)));
    connect(this, SIGNAL(changeCursor(Qt::CursorShape)), ui->contextGL, SLOT(changeCursor(Qt::CursorShape)));
    connect(ui->ColorButton, SIGNAL(clicked(bool)), SLOT(on_colorButton_clicked()));
    connect(this, SIGNAL(newModel(ModelInfo, int)), RenderManager::GetInstance()->GetRenderMode(EXPLORER), SLOT(changeModelTexture(ModelInfo, int)));
    connect(ui->actionOpen_project, SIGNAL(triggered()), this, SLOT(actionOpen_project_triggered()));
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
    QFileInfo info = m_decorateModel->fileInfo(indx);
    if(info.isFile())
    {
        if(info.suffix() == QString("jpg") || info.suffix() == QString("png") ||info.suffix() == QString("gif") ||
            info.suffix() == QString("jpeg") || info.suffix() == QString("bmp") ||info.suffix() == QString("pbm") ||
            info.suffix() == QString("pgm") || info.suffix() == QString("tiff") || info.suffix() == QString("xbm") ||
            info.suffix() == QString("xpm"))
        {
            qDebug("Get texture with path: %s", qPrintable(info.absoluteFilePath()));
            textureName = info.canonicalFilePath().toStdString();
            int namesize = textureName.find_last_of('.') - textureName.find_last_of('/');
            string name = textureName.substr(textureName.find_last_of('/') + 1, namesize - 1);
            message->setText(QString("Selected texture :").append(QString(name.c_str())));
        }
    }
}

void ThothWindow::on_pushButton_7_clicked()
{
    //Delete decorate model
    QModelIndex indx = ui->treeViewDecorate->currentIndex();
    if(indx.isValid())
    {
        if(textureName.compare("") != 0)
        {
            textureName = "";
            message->setText(QString("No texture selected"));
            ui->statusBar->showMessage("Texture unselected...", 2000);
        }
    }
}

void ThothWindow::actionSave_project_triggered()
{
    //Save project
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                        tr("Files (*.txt)"));
    CProjectManager::getInstance()->SaveMap(fileName.toStdString());
}
void ThothWindow::actionOpen_project_triggered()
{
    //Load project
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                         "",
                                                         tr("Files (*.txt)"));
    CProjectManager::getInstance()->LoadMap(fileName.toStdString());
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
    emit changeMouseMove(false);
    emit changeCursor(Qt::ArrowCursor);
}

void ThothWindow::on_colorButton_clicked()
{
    ModelInfo mi;
    int pos = ui->buttonGroup->checkedId();
    int texture;
    popUp->setText("");
    if(pos != -1)
    {
        switch(pos)
        {
        case -2:
            qDebug() << "Pressed 1";
            mi.textureName.color.c1 = CPoint3D(m_color.red()/255.f, m_color.green()/255.f, m_color.blue()/255.f);
            mi.textureName.material.M1 = textureName;
            texture = 1;
            break;
        case -4:
            qDebug() << "Pressed 2";
            mi.textureName.color.c2 = CPoint3D(m_color.red()/255.f, m_color.green()/255.f, m_color.blue()/255.f);
            mi.textureName.material.M2 = textureName;
            texture = 2;
            break;
        case -3:
            qDebug() << "Pressed 3";
            mi.textureName.color.c3 = CPoint3D(m_color.red()/255.f, m_color.green()/255.f, m_color.blue()/255.f);
            mi.textureName.material.M3 = textureName;
            texture = 3;
            break;
        case -5:
            qDebug() << "Pressed 4";
            mi.textureName.color.c4 = CPoint3D(m_color.red()/255.f, m_color.green()/255.f, m_color.blue()/255.f);
            mi.textureName.material.M4 = textureName;
            texture = 4;
            break;

        }
        ui->statusBar->showMessage("Changing texture to the objet...", 2000);
        emit newModel(mi, texture);
    }
    else
    {
        popUp->setText("Select in which texture you want to put it");
    }

}
