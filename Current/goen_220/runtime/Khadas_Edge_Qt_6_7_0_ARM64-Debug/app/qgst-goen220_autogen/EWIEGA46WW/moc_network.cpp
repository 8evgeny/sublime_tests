/****************************************************************************
** Meta object code from reading C++ file 'network.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/app/network.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSNetworkENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSNetworkENDCLASS = QtMocHelpers::stringData(
    "Network",
    "frameSendDone",
    "",
    "passParams",
    "pFrame",
    "size",
    "sig_checkCmd",
    "datagram",
    "tvFieldChanged",
    "tvFieldHGrad",
    "tvFieldVGrad",
    "frameSend",
    "procVICAPstatus",
    "CameraStatus",
    "status",
    "procLDCstatus",
    "LDC_STATE",
    "dev_state",
    "procJ200status",
    "J200_DEVSTATE",
    "ds",
    "procUpdateTrackerObject",
    "x",
    "y",
    "width",
    "heigth",
    "procUpdateActiveLockTracking",
    "active",
    "tracking",
    "proc_thread_finished",
    "proc_MINI640_State",
    "MINI640_DEV_STATE",
    "procGspStatus",
    "connected",
    "procGspPositionMode",
    "zero",
    "pohod",
    "pilot",
    "park",
    "stabilization",
    "procGspMotorAngle",
    "z",
    "procGspMotorSpeed"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSNetworkENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x06,    1 /* Public */,
       3,    2,  111,    2, 0x06,    2 /* Public */,
       6,    1,  116,    2, 0x06,    5 /* Public */,
       8,    2,  119,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    0,  124,    2, 0x0a,   10 /* Public */,
      12,    1,  125,    2, 0x0a,   11 /* Public */,
      15,    1,  128,    2, 0x0a,   13 /* Public */,
      18,    1,  131,    2, 0x0a,   15 /* Public */,
      21,    4,  134,    2, 0x0a,   17 /* Public */,
      26,    2,  143,    2, 0x0a,   22 /* Public */,
      29,    0,  148,    2, 0x0a,   25 /* Public */,
      30,    1,  149,    2, 0x0a,   26 /* Public */,
      32,    1,  152,    2, 0x0a,   28 /* Public */,
      34,    5,  155,    2, 0x0a,   30 /* Public */,
      40,    2,  166,    2, 0x0a,   36 /* Public */,
      42,    2,  171,    2, 0x0a,   39 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    9,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort,   22,   23,   24,   25,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,   27,   28,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 31,   17,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   35,   36,   37,   38,   39,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   41,   23,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   41,   23,

       0        // eod
};

Q_CONSTINIT const QMetaObject Network::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSNetworkENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSNetworkENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSNetworkENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Network, std::true_type>,
        // method 'frameSendDone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'passParams'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<void *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'sig_checkCmd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>,
        // method 'tvFieldChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const float, std::false_type>,
        QtPrivate::TypeAndForceComplete<const float, std::false_type>,
        // method 'frameSend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'procVICAPstatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<CameraStatus, std::false_type>,
        // method 'procLDCstatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<LDC_STATE, std::false_type>,
        // method 'procJ200status'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<J200_DEVSTATE, std::false_type>,
        // method 'procUpdateTrackerObject'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ushort, std::false_type>,
        QtPrivate::TypeAndForceComplete<ushort, std::false_type>,
        QtPrivate::TypeAndForceComplete<ushort, std::false_type>,
        QtPrivate::TypeAndForceComplete<ushort, std::false_type>,
        // method 'procUpdateActiveLockTracking'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'proc_thread_finished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'proc_MINI640_State'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<MINI640_DEV_STATE, std::false_type>,
        // method 'procGspStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const bool, std::false_type>,
        // method 'procGspPositionMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const bool, std::false_type>,
        // method 'procGspMotorAngle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const float, std::false_type>,
        QtPrivate::TypeAndForceComplete<const float, std::false_type>,
        // method 'procGspMotorSpeed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const float, std::false_type>,
        QtPrivate::TypeAndForceComplete<const float, std::false_type>
    >,
    nullptr
} };

void Network::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Network *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->frameSendDone(); break;
        case 1: _t->passParams((*reinterpret_cast< std::add_pointer_t<void*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->sig_checkCmd((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 3: _t->tvFieldChanged((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2]))); break;
        case 4: _t->frameSend(); break;
        case 5: _t->procVICAPstatus((*reinterpret_cast< std::add_pointer_t<CameraStatus>>(_a[1]))); break;
        case 6: _t->procLDCstatus((*reinterpret_cast< std::add_pointer_t<LDC_STATE>>(_a[1]))); break;
        case 7: _t->procJ200status((*reinterpret_cast< std::add_pointer_t<J200_DEVSTATE>>(_a[1]))); break;
        case 8: _t->procUpdateTrackerObject((*reinterpret_cast< std::add_pointer_t<ushort>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<ushort>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<ushort>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<ushort>>(_a[4]))); break;
        case 9: _t->procUpdateActiveLockTracking((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 10: _t->proc_thread_finished(); break;
        case 11: _t->proc_MINI640_State((*reinterpret_cast< std::add_pointer_t<MINI640_DEV_STATE>>(_a[1]))); break;
        case 12: _t->procGspStatus((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 13: _t->procGspPositionMode((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5]))); break;
        case 14: _t->procGspMotorAngle((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2]))); break;
        case 15: _t->procGspMotorSpeed((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Network::*)();
            if (_t _q_method = &Network::frameSendDone; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Network::*)(void * , int );
            if (_t _q_method = &Network::passParams; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Network::*)(QByteArray );
            if (_t _q_method = &Network::sig_checkCmd; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Network::*)(const float , const float );
            if (_t _q_method = &Network::tvFieldChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *Network::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Network::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSNetworkENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Network::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Network::frameSendDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Network::passParams(void * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Network::sig_checkCmd(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Network::tvFieldChanged(const float _t1, const float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
