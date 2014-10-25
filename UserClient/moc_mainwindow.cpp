/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      31,   11,   11,   11, 0x08,
      49,   11,   11,   11, 0x08,
      69,   11,   11,   11, 0x08,
      91,   11,   11,   11, 0x08,
     124,   11,   11,   11, 0x08,
     151,   11,   11,   11, 0x08,
     170,   11,   11,   11, 0x08,
     191,   11,   11,   11, 0x08,
     215,   11,   11,   11, 0x08,
     239,   11,   11,   11, 0x08,
     262,   11,   11,   11, 0x08,
     285,   11,   11,   11, 0x08,
     310,   11,   11,   11, 0x08,
     335,   11,   11,   11, 0x08,
     359,   11,   11,   11, 0x08,
     389,  383,   11,   11, 0x08,
     430,  425,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_login_clicked()\0"
    "on_quit_clicked()\0on_logout_clicked()\0"
    "on_logout_2_clicked()\0"
    "on_passwordLogin_returnPressed()\0"
    "on_createAccount_clicked()\0"
    "on_apply_clicked()\0on_apply_2_clicked()\0"
    "on_addConfKey_clicked()\0on_rmvConfKey_clicked()\0"
    "on_addAuthor_clicked()\0on_rmvAuthor_clicked()\0"
    "on_addPaperKey_clicked()\0"
    "on_rmvPaperKey_clicked()\0"
    "on_addAuthKey_clicked()\0on_rmvAuthKey_clicked()\0"
    "index\0on_selectPaperAuthor_activated(int)\0"
    "arg1\0on_selectPaperAuthor_currentTextChanged(QString)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
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

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
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
    }
    return _id;
}
QT_END_MOC_NAMESPACE
