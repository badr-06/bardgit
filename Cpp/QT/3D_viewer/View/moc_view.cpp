/****************************************************************************
** Meta object code from reading C++ file 'view.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[34];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 9), // "loadModel"
QT_MOC_LITERAL(21, 0), // ""
QT_MOC_LITERAL(22, 20), // "resetTransformations"
QT_MOC_LITERAL(43, 11), // "updateMoveX"
QT_MOC_LITERAL(55, 5), // "value"
QT_MOC_LITERAL(61, 11), // "updateMoveY"
QT_MOC_LITERAL(73, 11), // "updateMoveZ"
QT_MOC_LITERAL(85, 13), // "updateRotateX"
QT_MOC_LITERAL(99, 13), // "updateRotateY"
QT_MOC_LITERAL(113, 13), // "updateRotateZ"
QT_MOC_LITERAL(127, 11), // "updateScale"
QT_MOC_LITERAL(139, 21), // "changeBackgroundColor"
QT_MOC_LITERAL(161, 15), // "toggleWireframe"
QT_MOC_LITERAL(177, 7), // "enabled"
QT_MOC_LITERAL(185, 14), // "toggleTextures"
QT_MOC_LITERAL(200, 5) // "about"

    },
    "MainWindow\0loadModel\0\0resetTransformations\0"
    "updateMoveX\0value\0updateMoveY\0updateMoveZ\0"
    "updateRotateX\0updateRotateY\0updateRotateZ\0"
    "updateScale\0changeBackgroundColor\0"
    "toggleWireframe\0enabled\0toggleTextures\0"
    "about"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x08,    1 /* Private */,
       3,    0,   93,    2, 0x08,    2 /* Private */,
       4,    1,   94,    2, 0x08,    3 /* Private */,
       6,    1,   97,    2, 0x08,    5 /* Private */,
       7,    1,  100,    2, 0x08,    7 /* Private */,
       8,    1,  103,    2, 0x08,    9 /* Private */,
       9,    1,  106,    2, 0x08,   11 /* Private */,
      10,    1,  109,    2, 0x08,   13 /* Private */,
      11,    1,  112,    2, 0x08,   15 /* Private */,
      12,    0,  115,    2, 0x08,   17 /* Private */,
      13,    1,  116,    2, 0x08,   18 /* Private */,
      15,    1,  119,    2, 0x08,   20 /* Private */,
      16,    0,  122,    2, 0x08,   22 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->loadModel(); break;
        case 1: _t->resetTransformations(); break;
        case 2: _t->updateMoveX((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 3: _t->updateMoveY((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 4: _t->updateMoveZ((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 5: _t->updateRotateX((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 6: _t->updateRotateY((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 7: _t->updateRotateZ((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 8: _t->updateScale((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 9: _t->changeBackgroundColor(); break;
        case 10: _t->toggleWireframe((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->toggleTextures((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->about(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
