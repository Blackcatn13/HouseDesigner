#ifndef THOTHWINDOW_H
#define THOTHWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

#include "TreeFile.h"
namespace Ui {
class ThothWindow;
}

class ThothWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ThothWindow(QWidget *parent = 0);
    ~ThothWindow();
private:
    Ui::ThothWindow *ui;
    QDirModel *treeModel;
};

#endif // THOTHWINDOW_H
