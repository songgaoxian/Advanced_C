#ifndef TypeDef_H
#define TypeDef_H
//change type T to corresponding unsigned type
template<typename T>
using UnsignedType = typename std::make_unsigned<T>::type;

//change type T to corresponding signed type
template<typename T>
using SignedType = typename std::make_signed<T>::type;

//add const specifier to type T
template<typename T>
using ConstType = typename std::add_const<T>::type;

//remove const specifier from type T
template<typename T>
using NonConstType = typename std::remove_const<T>::type;

//add additional pointer to type T
template<typename T>
using PointerType = typename std::add_pointer<T>::type;

//remove pointer from type T
template<typename T>
using NonPointerType = typename std::remove_pointer<T>::type;

//add volatile specifier to type T
template<typename T>
using VolatileType = typename std::add_volatile<T>::type;

//remove volatile specifier from type T
template<typename T>
using NonVolatileType = typename std::remove_volatile<T>::type;
#endif

