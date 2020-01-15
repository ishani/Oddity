#ifndef __libfixmath_uint32_h__
#define __libfixmath_uint32_h__

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _MSC_VER
#include "pstdint.h"
#else
#include <stdint.h>
#endif

/*! Performs an unsigned log-base2 on the specified unsigned integer and returns the result.
*/
extern uint32_t uint32_log2(uint32_t inVal);

#ifdef __cplusplus
}
#endif

#endif
