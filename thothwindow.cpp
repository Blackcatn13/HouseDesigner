#include "thothwindow.h"
#include "ui_thothwindow.h"

ThothWindow::ThothWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThothWindow)
{
    ui->setupUi(this);
    // ALERT! Use the following code to get keyboard focus at your OpenGL widget
    ui->contextGL->setFocusPolicy(Qt::StrongFocus);
    ui->contextGL->setFocus();
    connect(ui->normalCamera, SIGNAL(clicked()), ui->contextGL, SLOT(usePerspective()));
    connect(ui->fourCameras, SIGNAL(clicked()), ui->contextGL, SLOT(useMultiview()));
    connect(ui->shaderEnable, SIGNAL(stateChanged(int)), ui->contextGL, SLOT(changeShaders(int)));
    connect(ui->actionZoom_in, SIGNAL(triggered()), ui->contextGL, SLOT(zoomIn()));
    connect(ui->actionZoom_out, SIGNAL(triggered()), ui->contextGL, SLOT(zoomOut()));
    connect(ui->textureBox, SIGNAL(stateChanged(int)), ui->contextGL, SLOT(changeTextures(int)));
    connect(ui->multiView, SIGNAL(triggered()), ui->contextGL, SLOT(useMultiview()));
    connect(ui->simpleView, SIGNAL(triggered()), ui->contextGL, SLOT(usePerspective()));
    connect(ui->textureEnabled, SIGNAL(triggered()), ui->contextGL, SLOT(changeTextures()));
}

ThothWindow::~ThothWindow()
{
    delete ui;
}

