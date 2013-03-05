#ifndef THOTHWINDOW_H
#define THOTHWINDOW_H

#include <QMainWindow>

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
};

#endif // THOTHWINDOW_H
