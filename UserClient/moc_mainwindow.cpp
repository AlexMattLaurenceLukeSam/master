/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata[434];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 16),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 15),
QT_MOC_LITERAL(4, 45, 17),
QT_MOC_LITERAL(5, 63, 19),
QT_MOC_LITERAL(6, 83, 30),
QT_MOC_LITERAL(7, 114, 24),
QT_MOC_LITERAL(8, 139, 16),
QT_MOC_LITERAL(9, 156, 18),
QT_MOC_LITERAL(10, 175, 21),
QT_MOC_LITERAL(11, 197, 21),
QT_MOC_LITERAL(12, 219, 20),
QT_MOC_LITERAL(13, 240, 20),
QT_MOC_LITERAL(14, 261, 22),
QT_MOC_LITERAL(15, 284, 22),
QT_MOC_LITERAL(16, 307, 21),
QT_MOC_LITERAL(17, 329, 21),
QT_MOC_LITERAL(18, 351, 30),
QT_MOC_LITERAL(19, 382, 5),
QT_MOC_LITERAL(20, 388, 39),
QT_MOC_LITERAL(21, 428, 4)
    },
    "MainWindow\0on_login_clicked\0\0"
    "on_quit_clicked\0on_logout_clicked\0"
    "on_logout_2_clicked\0on_passwordLogin_returnPressed\0"
    "on_createAccount_clicked\0on_apply_clicked\0"
    "on_apply_2_clicked\0on_addConfKey_clicked\0"
    "on_rmvConfKey_clicked\0on_addAuthor_clicked\0"
    "on_rmvAuthor_clicked\0on_addPaperKey_clicked\0"
    "on_rmvPaperKey_clicked\0on_addAuthKey_clicked\0"
    "on_rmvAuthKey_clicked\0"
    "on_selectPaperAuthor_activated\0index\0"
    "on_selectPaperAuthor_currentTextChanged\0"
    "arg1\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08,
       3,    0,  105,    2, 0x08,
       4,    0,  106,    2, 0x08,
       5,    0,  107,    2, 0x08,
       6,    0,  108,    2, 0x08,
       7,    0,  109,    2, 0x08,
       8,    0,  110,    2, 0x08,
       9,    0,  111,    2, 0x08,
      10,    0,  112,    2, 0x08,
      11,    0,  113,    2, 0x08,
      12,    0,  114,    2, 0x08,
      13,    0,  115,    2, 0x08,
      14,    0,  116,    2, 0x08,
      15,    0,  117,    2, 0x08,
      16,    0,  118,    2, 0x08,
      17,    0,  119,    2, 0x08,
      18,    1,  120,    2, 0x08,
      20,    1,  123,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::QString,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_login_clicked(); break;
        case 1: _t->on_quit_clicked(); break;
        case 2: _t->on_logout_clicked(); break;
        case 3: _t->on_logout_2_clicked(); break;
        case 4: _t->on_passwordLogin_returnPressed(); break;
        case 5: _t->on_createAccount_clicked(); break;
        case 6: _t->on_apply_clicked(); break;
        case 7: _t->on_apply_2_clicked(); break;
        case 8: _t->on_addConfKey_clicked(); break;
        case 9: _t->on_rmvConfKey_clicked(); break;
        case 10: _t->on_addAuthor_clicked(); break;
        case 11: _t->on_rmvAuthor_clicked(); break;
        case 12: _t->on_addPaperKey_clicked(); break;
        case 13: _t->on_rmvPaperKey_clicked(); break;
        case 14: _t->on_addAuthKey_clicked(); break;
        case 15: _t->on_rmvAuthKey_clicked(); break;
        case 16: _t->on_selectPaperAuthor_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_selectPaperAuthor_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
