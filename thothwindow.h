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
private slots:
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void actionSave_project_triggered();

    void on_lineEdit_editingFinished();
    void on_lineEdit_2_editingFinished();

    void on_floorBox_valueChanged(int arg1);

private:
    Ui::ThothWindow     *ui;
    QDirModel           *treeModel;

    QFileSystemModel    *m_buildModel;
    QFileSystemModel    *m_furnishModel;
    QFileSystemModel    *m_decorateModel;

};

#endif // THOTHWINDOW_H
