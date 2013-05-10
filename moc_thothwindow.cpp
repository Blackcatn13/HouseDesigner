/****************************************************************************
** Meta object code from reading C++ file 'thothwindow.h'
**
** Created: Thu May 9 15:31:19 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "thothwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'thothwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ThothWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      39,   12,   12,   12, 0x08,
      65,   12,   12,   12, 0x08,
      91,   12,   12,   12, 0x08,
     117,   12,   12,   12, 0x08,
     141,   12,   12,   12, 0x08,
     167,   12,   12,   12, 0x08,
     198,   12,   12,   12, 0x08,
     228,   12,   12,   12, 0x08,
     265,  260,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ThothWindow[] = {
    "ThothWindow\0\0on_pushButton_7_clicked()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "actionSave_project_triggered()\0"
    "on_lineEdit_editingFinished()\0"
    "on_lineEdit_2_editingFinished()\0arg1\0"
    "on_floorBox_valueChanged(int)\0"
};

void ThothWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ThothWindow *_t = static_cast<ThothWindow *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_7_clicked(); break;
        case 1: _t->on_pushButton_6_clicked(); break;
        case 2: _t->on_pushButton_5_clicked(); break;
        case 3: _t->on_pushButton_4_clicked(); break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on_pushButton_2_clicked(); break;
        case 6: _t->actionSave_project_triggered(); break;
        case 7: _t->on_lineEdit_editingFinished(); break;
        case 8: _t->on_lineEdit_2_editingFinished(); break;
        case 9: _t->on_floorBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ThothWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ThothWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ThothWindow,
      qt_meta_data_ThothWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ThothWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ThothWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ThothWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ThothWindow))
        return static_cast<void*>(const_cast< ThothWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ThothWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
