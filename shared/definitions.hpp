//
// Created by kai on 21/02/23.
//

#ifndef MOBIUSCODE_DEFINITIONS_HPP
#define MOBIUSCODE_DEFINITIONS_HPP

#include <cstdint>

#ifndef FAST_INT

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

#else

typedef uint_fast8_t u8;
typedef uint_fast16_t u16;
typedef uint_fast32_t u32;
typedef uint_fast64_t u64;

typedef int_fast8_t s8;
typedef int_fast16_t s16;
typedef int_fast32_t s32;
typedef int_fast64_t s64;

#endif

#endif //MOBIUSCODE_DEFINITIONS_HPP
