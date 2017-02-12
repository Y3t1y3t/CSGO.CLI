#ifndef _MACROS_FLAGENUM_H_
#define _MACROS_FLAGENUM_H_

#include <type_traits>

#define FLAG_ENUM_OPERATOR(T,X) \
inline T operator X (T lhs, const T& rhs) { \
    return (T) (static_cast<std::underlying_type_t <T>>(lhs) X static_cast<std::underlying_type_t <T>>(rhs)); \
} \
inline T& operator X ## = ## (T& lhs, const T& rhs) { \
    return ( lhs = (T) (static_cast<std::underlying_type_t <T>>(lhs) X static_cast<std::underlying_type_t <T>>(rhs))); \
} 
#define FLAG_ENUM(T) \
enum class T; \
inline T operator ~ (T t) { return (T) (~static_cast<std::underlying_type_t <T>>(t)); } \
FLAG_ENUM_OPERATOR(T,|) \
FLAG_ENUM_OPERATOR(T,^) \
FLAG_ENUM_OPERATOR(T,&) \
enum class T

#endif /* _MACROS_FLAGENUM_H_ */