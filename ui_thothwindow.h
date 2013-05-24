/********************************************************************************
** Form generated from reading UI file 'thothwindow.ui'
**
** Created: Fri May 24 01:51:46 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THOTHWINDOW_H
#define UI_THOTHWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>
#include "GLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_ThothWindow
{
public:
    QAction *actionExit;
    QAction *simpleView;
    QAction *multiView;
    QAction *actionAkfr;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *textureReload;
    QAction *textureEnabled;
    QAction *actionDisable;
    QAction *actionEnable_2;
    QAction *shaderDisable;
    QAction *actionNew_project;
    QAction *actionOpen_project;
    QAction *actionSave_project;
    QAction *actionExit_2;
    QAction *actionAre_you_sure;
    QAction *actionAbout;
    QWidget *centralWidget;
    GLWidget *contextGL;
    QTabWidget *tabWidget;
    QWidget *build_tab;
    QGridLayout *gridLayout_2;
    QTreeView *treeViewBuild;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QWidget *furnish_tab;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTreeView *treeViewFurnish;
    QWidget *decorate_tab;
    QGridLayout *gridLayout_3;
    QTreeView *treeViewDecorate;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QWidget *properties_tab;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *floorBox;
    QLabel *label_4;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *ThothWindow)
    {
        if (ThothWindow->objectName().isEmpty())
            ThothWindow->setObjectName(QString::fromUtf8("ThothWindow"));
        ThothWindow->resize(999, 671);
        ThothWindow->setMinimumSize(QSize(900, 600));
        ThothWindow->setStyleSheet(QString::fromUtf8(""));
        actionExit = new QAction(ThothWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        simpleView = new QAction(ThothWindow);
        simpleView->setObjectName(QString::fromUtf8("simpleView"));
        multiView = new QAction(ThothWindow);
        multiView->setObjectName(QString::fromUtf8("multiView"));
        actionAkfr = new QAction(ThothWindow);
        actionAkfr->setObjectName(QString::fromUtf8("actionAkfr"));
        actionZoom_in = new QAction(ThothWindow);
        actionZoom_in->setObjectName(QString::fromUtf8("actionZoom_in"));
        actionZoom_out = new QAction(ThothWindow);
        actionZoom_out->setObjectName(QString::fromUtf8("actionZoom_out"));
        textureReload = new QAction(ThothWindow);
        textureReload->setObjectName(QString::fromUtf8("textureReload"));
        textureEnabled = new QAction(ThothWindow);
        textureEnabled->setObjectName(QString::fromUtf8("textureEnabled"));
        actionDisable = new QAction(ThothWindow);
        actionDisable->setObjectName(QString::fromUtf8("actionDisable"));
        actionEnable_2 = new QAction(ThothWindow);
        actionEnable_2->setObjectName(QString::fromUtf8("actionEnable_2"));
        shaderDisable = new QAction(ThothWindow);
        shaderDisable->setObjectName(QString::fromUtf8("shaderDisable"));
        actionNew_project = new QAction(ThothWindow);
        actionNew_project->setObjectName(QString::fromUtf8("actionNew_project"));
        actionOpen_project = new QAction(ThothWindow);
        actionOpen_project->setObjectName(QString::fromUtf8("actionOpen_project"));
        actionSave_project = new QAction(ThothWindow);
        actionSave_project->setObjectName(QString::fromUtf8("actionSave_project"));
        actionExit_2 = new QAction(ThothWindow);
        actionExit_2->setObjectName(QString::fromUtf8("actionExit_2"));
        actionAre_you_sure = new QAction(ThothWindow);
        actionAre_you_sure->setObjectName(QString::fromUtf8("actionAre_you_sure"));
        actionAbout = new QAction(ThothWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(ThothWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        contextGL = new GLWidget(centralWidget);
        contextGL->setObjectName(QString::fromUtf8("contextGL"));
        contextGL->setGeometry(QRect(221, 9, 800, 600));
        contextGL->setMinimumSize(QSize(800, 600));
        contextGL->setStyleSheet(QString::fromUtf8("background-color:black;"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(9, 9, 206, 566));
        tabWidget->setFocusPolicy(Qt::TabFocus);
        tabWidget->setTabPosition(QTabWidget::East);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);
        build_tab = new QWidget();
        build_tab->setObjectName(QString::fromUtf8("build_tab"));
        gridLayout_2 = new QGridLayout(build_tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        treeViewBuild = new QTreeView(build_tab);
        treeViewBuild->setObjectName(QString::fromUtf8("treeViewBuild"));

        gridLayout_2->addWidget(treeViewBuild, 0, 0, 1, 2);

        pushButton_4 = new QPushButton(build_tab);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_5 = new QPushButton(build_tab);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout_2->addWidget(pushButton_5, 1, 1, 1, 1);

        tabWidget->addTab(build_tab, QString());
        furnish_tab = new QWidget();
        furnish_tab->setObjectName(QString::fromUtf8("furnish_tab"));
        gridLayout = new QGridLayout(furnish_tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(furnish_tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(furnish_tab);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 1, 1, 1);

        treeViewFurnish = new QTreeView(furnish_tab);
        treeViewFurnish->setObjectName(QString::fromUtf8("treeViewFurnish"));

        gridLayout->addWidget(treeViewFurnish, 0, 0, 1, 2);

        tabWidget->addTab(furnish_tab, QString());
        decorate_tab = new QWidget();
        decorate_tab->setObjectName(QString::fromUtf8("decorate_tab"));
        gridLayout_3 = new QGridLayout(decorate_tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        treeViewDecorate = new QTreeView(decorate_tab);
        treeViewDecorate->setObjectName(QString::fromUtf8("treeViewDecorate"));

        gridLayout_3->addWidget(treeViewDecorate, 0, 0, 1, 2);

        pushButton_6 = new QPushButton(decorate_tab);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        gridLayout_3->addWidget(pushButton_6, 1, 0, 1, 1);

        pushButton_7 = new QPushButton(decorate_tab);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        gridLayout_3->addWidget(pushButton_7, 1, 1, 1, 1);

        tabWidget->addTab(decorate_tab, QString());
        properties_tab = new QWidget();
        properties_tab->setObjectName(QString::fromUtf8("properties_tab"));
        label = new QLabel(properties_tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 181, 20));
        lineEdit = new QLineEdit(properties_tab);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(50, 60, 127, 25));
        lineEdit->setFocusPolicy(Qt::ClickFocus);
        lineEdit->setContextMenuPolicy(Qt::DefaultContextMenu);
        lineEdit->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        lineEdit->setMaxLength(200);
        lineEdit_2 = new QLineEdit(properties_tab);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(50, 30, 127, 25));
        lineEdit_2->setFocusPolicy(Qt::ClickFocus);
        lineEdit_2->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        lineEdit_2->setMaxLength(200);
        label_2 = new QLabel(properties_tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 40, 21, 16));
        label_3 = new QLabel(properties_tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 70, 21, 16));
        tabWidget->addTab(properties_tab, QString());
        floorBox = new QSpinBox(centralWidget);
        floorBox->setObjectName(QString::fromUtf8("floorBox"));
        floorBox->setGeometry(QRect(160, 581, 43, 25));
        floorBox->setMinimum(1);
        floorBox->setMaximum(5);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 590, 141, 16));
        ThothWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ThothWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 999, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        ThothWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(ThothWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ThothWindow->setStatusBar(statusBar);
        mainToolBar = new QToolBar(ThothWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setStyleSheet(QString::fromUtf8(""));
        ThothWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_project);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen_project);
        menuFile->addAction(actionSave_project);
        menuFile->addSeparator();
        menuFile->addAction(actionExit_2);
        menuHelp->addAction(actionAbout);

        retranslateUi(ThothWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), ThothWindow, SLOT(close()));
        QObject::connect(actionExit_2, SIGNAL(triggered()), ThothWindow, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ThothWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ThothWindow)
    {
        ThothWindow->setWindowTitle(QApplication::translate("ThothWindow", "ThothWindow", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("ThothWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("ThothWindow", "Esc", 0, QApplication::UnicodeUTF8));
        simpleView->setText(QApplication::translate("ThothWindow", "Simple View", 0, QApplication::UnicodeUTF8));
        simpleView->setShortcut(QApplication::translate("ThothWindow", "Shift+F1", 0, QApplication::UnicodeUTF8));
        multiView->setText(QApplication::translate("ThothWindow", "Multiview", 0, QApplication::UnicodeUTF8));
        multiView->setShortcut(QApplication::translate("ThothWindow", "Shift+F2", 0, QApplication::UnicodeUTF8));
        actionAkfr->setText(QApplication::translate("ThothWindow", "akfr", 0, QApplication::UnicodeUTF8));
        actionZoom_in->setText(QApplication::translate("ThothWindow", "Zoom in", 0, QApplication::UnicodeUTF8));
        actionZoom_in->setShortcut(QApplication::translate("ThothWindow", "Ctrl++", 0, QApplication::UnicodeUTF8));
        actionZoom_out->setText(QApplication::translate("ThothWindow", "Zoom out", 0, QApplication::UnicodeUTF8));
        actionZoom_out->setShortcut(QApplication::translate("ThothWindow", "Ctrl+-", 0, QApplication::UnicodeUTF8));
        textureReload->setText(QApplication::translate("ThothWindow", "Reload", 0, QApplication::UnicodeUTF8));
        textureReload->setShortcut(QApplication::translate("ThothWindow", "Ctrl+Shift+T", 0, QApplication::UnicodeUTF8));
        textureEnabled->setText(QApplication::translate("ThothWindow", "(En/Dis)able", 0, QApplication::UnicodeUTF8));
        textureEnabled->setShortcut(QApplication::translate("ThothWindow", "Ctrl+T", 0, QApplication::UnicodeUTF8));
        actionDisable->setText(QApplication::translate("ThothWindow", "Disable", 0, QApplication::UnicodeUTF8));
        actionEnable_2->setText(QApplication::translate("ThothWindow", "Enable", 0, QApplication::UnicodeUTF8));
        shaderDisable->setText(QApplication::translate("ThothWindow", "(En/Dis)able", 0, QApplication::UnicodeUTF8));
        shaderDisable->setShortcut(QApplication::translate("ThothWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionNew_project->setText(QApplication::translate("ThothWindow", "New project", 0, QApplication::UnicodeUTF8));
        actionOpen_project->setText(QApplication::translate("ThothWindow", "Open project", 0, QApplication::UnicodeUTF8));
        actionSave_project->setText(QApplication::translate("ThothWindow", "Save project", 0, QApplication::UnicodeUTF8));
        actionExit_2->setText(QApplication::translate("ThothWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionAre_you_sure->setText(QApplication::translate("ThothWindow", "Are you sure?", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("ThothWindow", "About", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("ThothWindow", "Select", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("ThothWindow", "Delete", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(build_tab), QApplication::translate("ThothWindow", "Build", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ThothWindow", "Select", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("ThothWindow", "Delete", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(furnish_tab), QApplication::translate("ThothWindow", "Furnish", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("ThothWindow", "Select", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("ThothWindow", "Delete", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(decorate_tab), QApplication::translate("ThothWindow", "Decorate", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ThothWindow", "Insert workspace dimesion", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QString());
        lineEdit_2->setText(QString());
        lineEdit_2->setPlaceholderText(QString());
        label_2->setText(QApplication::translate("ThothWindow", "X:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ThothWindow", "Y:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(properties_tab), QApplication::translate("ThothWindow", "Properties", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ThothWindow", "Select current floor:", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("ThothWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("ThothWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ThothWindow: public Ui_ThothWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THOTHWINDOW_H
