/****************************************************************************
** Meta object code from reading C++ file 'addaccesslinkagerule.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../addaccesslinkagerule.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addaccesslinkagerule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AddAccessLinkageRule_t {
    QByteArrayData data[16];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AddAccessLinkageRule_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AddAccessLinkageRule_t qt_meta_stringdata_AddAccessLinkageRule = {
    {
QT_MOC_LITERAL(0, 0, 20), // "AddAccessLinkageRule"
QT_MOC_LITERAL(1, 21, 19), // "OnCbMapStateChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 5), // "state"
QT_MOC_LITERAL(4, 48, 22), // "OnCbTVWallStateChanged"
QT_MOC_LITERAL(5, 71, 23), // "OnCbPreviewStateChanged"
QT_MOC_LITERAL(6, 95, 22), // "OnCbRecordStateChanged"
QT_MOC_LITERAL(7, 118, 23), // "OnCbCaptureStateChanged"
QT_MOC_LITERAL(8, 142, 19), // "OnCbPTZStateChanged"
QT_MOC_LITERAL(9, 162, 19), // "onRadioStateChanged"
QT_MOC_LITERAL(10, 182, 25), // "btnSelAlarmSource_clicked"
QT_MOC_LITERAL(11, 208, 15), // "btnSave_clicked"
QT_MOC_LITERAL(12, 224, 17), // "btnCancel_clicked"
QT_MOC_LITERAL(13, 242, 8), // "ShowMini"
QT_MOC_LITERAL(14, 251, 8), // "FrmClose"
QT_MOC_LITERAL(15, 260, 14) // "onAccessChange"

    },
    "AddAccessLinkageRule\0OnCbMapStateChanged\0"
    "\0state\0OnCbTVWallStateChanged\0"
    "OnCbPreviewStateChanged\0OnCbRecordStateChanged\0"
    "OnCbCaptureStateChanged\0OnCbPTZStateChanged\0"
    "onRadioStateChanged\0btnSelAlarmSource_clicked\0"
    "btnSave_clicked\0btnCancel_clicked\0"
    "ShowMini\0FrmClose\0onAccessChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddAccessLinkageRule[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       4,    1,   82,    2, 0x08 /* Private */,
       5,    1,   85,    2, 0x08 /* Private */,
       6,    1,   88,    2, 0x08 /* Private */,
       7,    1,   91,    2, 0x08 /* Private */,
       8,    1,   94,    2, 0x08 /* Private */,
       9,    0,   97,    2, 0x08 /* Private */,
      10,    0,   98,    2, 0x08 /* Private */,
      11,    0,   99,    2, 0x08 /* Private */,
      12,    0,  100,    2, 0x08 /* Private */,
      13,    0,  101,    2, 0x08 /* Private */,
      14,    0,  102,    2, 0x08 /* Private */,
      15,    1,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void AddAccessLinkageRule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddAccessLinkageRule *_t = static_cast<AddAccessLinkageRule *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnCbMapStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->OnCbTVWallStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->OnCbPreviewStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnCbRecordStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->OnCbCaptureStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->OnCbPTZStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onRadioStateChanged(); break;
        case 7: _t->btnSelAlarmSource_clicked(); break;
        case 8: _t->btnSave_clicked(); break;
        case 9: _t->btnCancel_clicked(); break;
        case 10: _t->ShowMini(); break;
        case 11: _t->FrmClose(); break;
        case 12: _t->onAccessChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject AddAccessLinkageRule::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddAccessLinkageRule.data,
      qt_meta_data_AddAccessLinkageRule,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AddAccessLinkageRule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddAccessLinkageRule::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AddAccessLinkageRule.stringdata0))
        return static_cast<void*>(const_cast< AddAccessLinkageRule*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddAccessLinkageRule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
