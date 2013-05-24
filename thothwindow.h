#ifndef THOTHWINDOW_H
#define THOTHWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "TreeFile.h"
#include <qcolor.h>

namespace Ui {
class ThothWindow;
}

class ThothWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
public:
    explicit ThothWindow(QWidget *parent = 0);
    QColor color() const
    {
        return m_color;
    }

    ~ThothWindow();
signals:
    void colorChanged(QColor arg);
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

    void onColorChanged();
    void getModelName(string name);

private:
    Ui::ThothWindow     *ui;
    QDirModel           *treeModel;

    QFileSystemModel    *m_buildModel;
    QFileSystemModel    *m_furnishModel;
    QFileSystemModel    *m_decorateModel;
    QColor m_color;
    QLabel *message;
    QLabel *popUp;
};

#endif // THOTHWINDOW_H
