#ifndef TREEFILE_H
#define TREEFILE_H

#include <QtCore>
#include <QtGui>
#include "ui_thothwindow.h"
#include "Directory.h"

class TreeFile;

class TreeFile
{
public:
    TreeFile(Ui::ThothWindow *ui);
    ~TreeFile();
private:
    Directory*          m_dir;
    Ui::ThothWindow*    m_ui;
};

#endif // TREEFILE_H
