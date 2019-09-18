/****************************************************************************
** Meta object code from reading C++ file 'alarmcfg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../alarmcfg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'alarmcfg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AlarmCfg_t {
    QByteArrayData data[12];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AlarmCfg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AlarmCfg_t qt_meta_stringdata_AlarmCfg = {
    {
QT_MOC_LITERAL(0, 0, 8), // "AlarmCfg"
QT_MOC_LITERAL(1, 9, 22), // "onItemSelectionChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 22), // "btnAddLinkRule_clicked"
QT_MOC_LITERAL(4, 56, 22), // "btnUpdLinkRule_clicked"
QT_MOC_LITERAL(5, 79, 14), // "OnStateChanged"
QT_MOC_LITERAL(6, 94, 6), // "iState"
QT_MOC_LITERAL(7, 101, 12), // "OnUpdateRule"
QT_MOC_LITERAL(8, 114, 12), // "OnDeleteRule"
QT_MOC_LITERAL(9, 127, 15), // "GetLinkageRules"
QT_MOC_LITERAL(10, 143, 12), // "InitLinkRule"
QT_MOC_LITERAL(11, 156, 28) // "btnAddAccessLinkRule_clicked"

    },
    "AlarmCfg\0onItemSelectionChanged\0\0"
    "btnAddLinkRule_clicked\0btnUpdLinkRule_clicked\0"
    "OnStateChanged\0iState\0OnUpdateRule\0"
    "OnDeleteRule\0GetLinkageRules\0InitLinkRule\0"
    "btnAddAccessLinkRule_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AlarmCfg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x09 /* Protected */,
       3,    0,   60,    2, 0x09 /* Protected */,
       4,    0,   61,    2, 0x09 /* Protected */,
       5,    1,   62,    2, 0x09 /* Protected */,
       7,    0,   65,    2, 0x09 /* Protected */,
       8,    0,   66,    2, 0x09 /* Protected */,
       9,    0,   67,    2, 0x09 /* Protected */,
      10,    0,   68,    2, 0x09 /* Protected */,
      11,    0,   69,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AlarmCfg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AlarmCfg *_t = static_cast<AlarmCfg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onItemSelectionChanged(); break;
        case 1: _t->btnAddLinkRule_clicked(); break;
        case 2: _t->btnUpdLinkRule_clicked(); break;
        case 3: _t->OnStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->OnUpdateRule(); break;
        case 5: _t->OnDeleteRule(); break;
        case 6: _t->GetLinkageRules(); break;
        case 7: _t->InitLinkRule(); break;
        case 8: _t->btnAddAccessLinkRule_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject AlarmCfg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AlarmCfg.data,
      qt_meta_data_AlarmCfg,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AlarmCfg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AlarmCfg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AlarmCfg.stringdata0))
        return static_cast<void*>(const_cast< AlarmCfg*>(this));
    return QWidget::qt_metacast(_clname);
}

int AlarmCfg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
