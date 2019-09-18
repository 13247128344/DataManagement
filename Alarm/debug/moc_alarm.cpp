/****************************************************************************
** Meta object code from reading C++ file 'alarm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../alarm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'alarm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Alarm_t {
    QByteArrayData data[10];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Alarm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Alarm_t qt_meta_stringdata_Alarm = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Alarm"
QT_MOC_LITERAL(1, 6, 23), // "getAlarmInfoByCondition"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 8), // "getFirst"
QT_MOC_LITERAL(4, 40, 7), // "getLast"
QT_MOC_LITERAL(5, 48, 7), // "getNext"
QT_MOC_LITERAL(6, 56, 7), // "getPrev"
QT_MOC_LITERAL(7, 64, 13), // "onBtnAlarmLog"
QT_MOC_LITERAL(8, 78, 14), // "onBtnAccessLog"
QT_MOC_LITERAL(9, 93, 21) // "on_pushButton_clicked"

    },
    "Alarm\0getAlarmInfoByCondition\0\0getFirst\0"
    "getLast\0getNext\0getPrev\0onBtnAlarmLog\0"
    "onBtnAccessLog\0on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Alarm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x09 /* Protected */,
       3,    0,   55,    2, 0x09 /* Protected */,
       4,    0,   56,    2, 0x09 /* Protected */,
       5,    0,   57,    2, 0x09 /* Protected */,
       6,    0,   58,    2, 0x09 /* Protected */,
       7,    0,   59,    2, 0x09 /* Protected */,
       8,    0,   60,    2, 0x09 /* Protected */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Alarm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Alarm *_t = static_cast<Alarm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getAlarmInfoByCondition(); break;
        case 1: _t->getFirst(); break;
        case 2: _t->getLast(); break;
        case 3: _t->getNext(); break;
        case 4: _t->getPrev(); break;
        case 5: _t->onBtnAlarmLog(); break;
        case 6: _t->onBtnAccessLog(); break;
        case 7: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Alarm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Alarm.data,
      qt_meta_data_Alarm,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Alarm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Alarm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Alarm.stringdata0))
        return static_cast<void*>(const_cast< Alarm*>(this));
    return QWidget::qt_metacast(_clname);
}

int Alarm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
