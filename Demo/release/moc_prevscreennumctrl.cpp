/****************************************************************************
** Meta object code from reading C++ file 'prevscreennumctrl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../prevscreennumctrl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'prevscreennumctrl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_prevscreennumctrl_t {
    QByteArrayData data[9];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_prevscreennumctrl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_prevscreennumctrl_t qt_meta_stringdata_prevscreennumctrl = {
    {
QT_MOC_LITERAL(0, 0, 17), // "prevscreennumctrl"
QT_MOC_LITERAL(1, 18, 13), // "onSplitWindow"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "onSplit1"
QT_MOC_LITERAL(4, 42, 8), // "onSplit4"
QT_MOC_LITERAL(5, 51, 8), // "onSplit8"
QT_MOC_LITERAL(6, 60, 9), // "onSplit12"
QT_MOC_LITERAL(7, 70, 9), // "onSplit16"
QT_MOC_LITERAL(8, 80, 9) // "onSplit36"

    },
    "prevscreennumctrl\0onSplitWindow\0\0"
    "onSplit1\0onSplit4\0onSplit8\0onSplit12\0"
    "onSplit16\0onSplit36"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_prevscreennumctrl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   52,    2, 0x08 /* Private */,
       4,    0,   53,    2, 0x08 /* Private */,
       5,    0,   54,    2, 0x08 /* Private */,
       6,    0,   55,    2, 0x08 /* Private */,
       7,    0,   56,    2, 0x08 /* Private */,
       8,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void prevscreennumctrl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        prevscreennumctrl *_t = static_cast<prevscreennumctrl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSplitWindow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onSplit1(); break;
        case 2: _t->onSplit4(); break;
        case 3: _t->onSplit8(); break;
        case 4: _t->onSplit12(); break;
        case 5: _t->onSplit16(); break;
        case 6: _t->onSplit36(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (prevscreennumctrl::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&prevscreennumctrl::onSplitWindow)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject prevscreennumctrl::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_prevscreennumctrl.data,
      qt_meta_data_prevscreennumctrl,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *prevscreennumctrl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *prevscreennumctrl::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_prevscreennumctrl.stringdata0))
        return static_cast<void*>(const_cast< prevscreennumctrl*>(this));
    return QWidget::qt_metacast(_clname);
}

int prevscreennumctrl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void prevscreennumctrl::onSplitWindow(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
