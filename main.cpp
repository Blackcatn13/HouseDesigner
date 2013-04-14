#include <QApplication>
#include "thothwindow.h"
#include "Util.h"
#include "Directory.h"
#include "iostream"
#include "vector"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThothWindow w;

    glutInit(&argc, argv);

    w.show();

    return a.exec();
}
