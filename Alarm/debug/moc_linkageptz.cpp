/****************************************************************************
** Meta object code from reading C++ file 'linkageptz.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../linkageptz.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'linkageptz.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LinkagePTZ_t {
    QByteArrayData data[12];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LinkagePTZ_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LinkagePTZ_t qt_meta_stringdata_LinkagePTZ = {
    {
QT_MOC_LITERAL(0, 0, 10), // "LinkagePTZ"
QT_MOC_LITERAL(1, 11, 13), // "onTreeChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14), // "TreeChangeType"
QT_MOC_LITERAL(4, 41, 4), // "type"
QT_MOC_LITERAL(5, 46, 23), // "CMS_CONNECT_PARSE_Node*"
QT_MOC_LITERAL(6, 70, 14), // "btnAdd_clicked"
QT_MOC_LITERAL(7, 85, 17), // "btnDelete_clicked"
QT_MOC_LITERAL(8, 103, 13), // "btnOK_clicked"
QT_MOC_LITERAL(9, 117, 17), // "btnCancel_clicked"
QT_MOC_LITERAL(10, 135, 8), // "ShowMini"
QT_MOC_LITERAL(11, 144, 8) // "FrmClose"

    },
    "LinkagePTZ\0onTreeChanged\0\0TreeChangeType\0"
    "type\0CMS_CONNECT_PARSE_Node*\0"
    "btnAdd_clicked\0btnDelete_clicked\0"
    "btnOK_clicked\0btnCancel_clicked\0"
    "ShowMini\0FrmClose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LinkagePTZ[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x08 /* Private */,
       6,    0,   54,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    0,   56,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,
      10,    0,   58,    2, 0x08 /* Private */,
      11,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LinkagePTZ::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LinkagePTZ *_t = static_cast<LinkagePTZ *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTreeChanged((*reinterpret_cast< TreeChangeType(*)>(_a[1])),(*reinterpret_cast< CMS_CONNECT_PARSE_Node*(*)>(_a[2]))); break;
        case 1: _t->btnAdd_clicked(); break;
        case 2: _t->btnDelete_clicked(); break;
        case 3: _t->btnOK_clicked(); break;
        case 4: _t->btnCancel_clicked(); break;
        case 5: _t->ShowMini(); break;
        case 6: _t->FrmClose(); break;
        default: ;
        }
    }
}

const QMetaObject LinkagePTZ::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LinkagePTZ.data,
      qt_meta_data_LinkagePTZ,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LinkagePTZ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LinkagePTZ::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LinkagePTZ.stringdata0))
        return static_cast<void*>(const_cast< LinkagePTZ*>(this));
    return QDialog::qt_metacast(_clname);
}

int LinkagePTZ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
