/****************************************************************************
** Meta object code from reading C++ file 'addlinkagerule.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../addlinkagerule.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addlinkagerule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AddLinkageRule_t {
    QByteArrayData data[19];
    char stringdata0[314];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AddLinkageRule_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AddLinkageRule_t qt_meta_stringdata_AddLinkageRule = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AddLinkageRule"
QT_MOC_LITERAL(1, 15, 13), // "onTreeChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 14), // "TreeChangeType"
QT_MOC_LITERAL(4, 45, 4), // "type"
QT_MOC_LITERAL(5, 50, 23), // "CMS_CONNECT_PARSE_Node*"
QT_MOC_LITERAL(6, 74, 19), // "OnCbMapStateChanged"
QT_MOC_LITERAL(7, 94, 5), // "state"
QT_MOC_LITERAL(8, 100, 22), // "OnCbTVWallStateChanged"
QT_MOC_LITERAL(9, 123, 23), // "OnCbPreviewStateChanged"
QT_MOC_LITERAL(10, 147, 22), // "OnCbRecordStateChanged"
QT_MOC_LITERAL(11, 170, 23), // "OnCbCaptureStateChanged"
QT_MOC_LITERAL(12, 194, 19), // "OnCbPTZStateChanged"
QT_MOC_LITERAL(13, 214, 21), // "onCurrentIndexChanged"
QT_MOC_LITERAL(14, 236, 25), // "btnSelAlarmSource_clicked"
QT_MOC_LITERAL(15, 262, 15), // "btnSave_clicked"
QT_MOC_LITERAL(16, 278, 17), // "btnCancel_clicked"
QT_MOC_LITERAL(17, 296, 8), // "ShowMini"
QT_MOC_LITERAL(18, 305, 8) // "FrmClose"

    },
    "AddLinkageRule\0onTreeChanged\0\0"
    "TreeChangeType\0type\0CMS_CONNECT_PARSE_Node*\0"
    "OnCbMapStateChanged\0state\0"
    "OnCbTVWallStateChanged\0OnCbPreviewStateChanged\0"
    "OnCbRecordStateChanged\0OnCbCaptureStateChanged\0"
    "OnCbPTZStateChanged\0onCurrentIndexChanged\0"
    "btnSelAlarmSource_clicked\0btnSave_clicked\0"
    "btnCancel_clicked\0ShowMini\0FrmClose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddLinkageRule[] = {

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
       1,    2,   79,    2, 0x08 /* Private */,
       6,    1,   84,    2, 0x08 /* Private */,
       8,    1,   87,    2, 0x08 /* Private */,
       9,    1,   90,    2, 0x08 /* Private */,
      10,    1,   93,    2, 0x08 /* Private */,
      11,    1,   96,    2, 0x08 /* Private */,
      12,    1,   99,    2, 0x08 /* Private */,
      13,    1,  102,    2, 0x08 /* Private */,
      14,    0,  105,    2, 0x08 /* Private */,
      15,    0,  106,    2, 0x08 /* Private */,
      16,    0,  107,    2, 0x08 /* Private */,
      17,    0,  108,    2, 0x08 /* Private */,
      18,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    2,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AddLinkageRule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddLinkageRule *_t = static_cast<AddLinkageRule *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTreeChanged((*reinterpret_cast< TreeChangeType(*)>(_a[1])),(*reinterpret_cast< CMS_CONNECT_PARSE_Node*(*)>(_a[2]))); break;
        case 1: _t->OnCbMapStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->OnCbTVWallStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnCbPreviewStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->OnCbRecordStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->OnCbCaptureStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->OnCbPTZStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->btnSelAlarmSource_clicked(); break;
        case 9: _t->btnSave_clicked(); break;
        case 10: _t->btnCancel_clicked(); break;
        case 11: _t->ShowMini(); break;
        case 12: _t->FrmClose(); break;
        default: ;
        }
    }
}

const QMetaObject AddLinkageRule::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddLinkageRule.data,
      qt_meta_data_AddLinkageRule,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AddLinkageRule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddLinkageRule::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AddLinkageRule.stringdata0))
        return static_cast<void*>(const_cast< AddLinkageRule*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddLinkageRule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
