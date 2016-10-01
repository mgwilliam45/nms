

#include "../canwork.h"
#if !defined(J_MOC_OUTPUT_REVISION)
#error "The header file 'canwork.h' doesn't include <JObject>."
#elif J_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of J."
#error "(The moc has changed too much.)"
#endif

J_BEGIN_MOC_NAMESPACE
static const uint J_meta_data_canwork[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   17,   16,   16, 0x05,

       0        // eod
};

static const char J_meta_stringdata_canwork[] = {
    "canwork\0\0msg\0msgReceived(JString)\0"
};

const JMetaObject canwork::staticMetaObject = {
    { &Jhread::staticMetaObject, J_meta_stringdata_canwork,
      J_meta_data_canwork, 0 }
};

#ifdef J_NO_DATA_RELOCATION
const JMetaObject &canwork::getStaticMetaObject() { return staticMetaObject; }
#endif //J_NO_DATA_RELOCATION

const JMetaObject *canwork::metaObject() const
{
    return JObject::d_ptr->metaObject ? JObject::d_ptr->metaObject : &staticMetaObject;
}

void *canwork::J_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, J_meta_stringdata_canwork))
        return static_cast<void*>(const_cast< canwork*>(this));
    return Jhread::J_metacast(_clname);
}

int canwork::J_metacall(JMetaObject::Call _c, int _id, void **_a)
{
    _id = Jhread::J_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == JMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: msgReceived((*reinterpret_cast< JString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void canwork::msgReceived(JString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    JMetaObject::activate(this, &staticMetaObject, 0, _a);
}
J_END_MOC_NAMESPACE
