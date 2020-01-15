#ifndef __libfixmath_fix16_h__
#define __libfixmath_fix16_h__

#ifdef __cplusplus
extern "C"
{
#endif

/* These options may let the optimizer to remove some calls to the functions.
 * Refer to http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
 */
#ifndef FIXMATH_FUNC_ATTRS
# ifdef __GNUC__
#   if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6)
#     define FIXMATH_FUNC_ATTRS __attribute__((leaf, nothrow, const))
#   else
#     define FIXMATH_FUNC_ATTRS __attribute__((nothrow, const))
#   endif
# else
#   define FIXMATH_FUNC_ATTRS
# endif
#endif

//#define FIXMATH_SIN_LUT
#define FIXMATH_NO_CACHE
#define FIXMATH_OPTIMIZE_8BIT
#define FIXMATH_NO_64BIT

#include <stdint.h>
#include "common.h"

typedef int32_t fix16_t;

static const fix16_t FOUR_DIV_PI    = 0x145F3;          /*!< Fix16 value of 4/PI */
static const fix16_t _FOUR_DIV_PI2  = 0xFFFF9840;       /*!< Fix16 value of -4/PI² */
static const fix16_t X4_CORRECTION_COMPONENT = 0x399A;  /*!< Fix16 value of 0.225 */
static const fix16_t PI_DIV_4       = 0x0000C90F;       /*!< Fix16 value of PI/4 */
static const fix16_t THREE_PI_DIV_4 = 0x00025B2F;       /*!< Fix16 value of 3PI/4 */

static const fix16_t fix16_maximum  = 0x7FFFFFFF;  /*!< the maximum value of fix16_t */
static const fix16_t fix16_minimum  = 0x80000000;  /*!< the minimum value of fix16_t */
static const fix16_t fix16_overflow = 0x80000000;  /*!< the value used to indicate overflows when FIXMATH_NO_OVERFLOW is not specified */

static const fix16_t fix16_pi       = 205887;      /*!< fix16_t value of pi */
static const fix16_t fix16_recp_pi  = 0x0000517d;  /*!< fix16_t value of 1.0 / pi */
static const fix16_t fix16_two_pi   = 0x0006487f;  /*!< fix16_t value of 2.0 * pi */
static const fix16_t fix16_half_pi  = 0x00019220;  /*!< fix16_t value of 0.5 * pi */

static const fix16_t fix16_e        = 178145;      /*!< fix16_t value of e */

static const fix16_t fix16_one      = 0x00010000;  // 1
static const fix16_t fix16_neg_one  = 0xffff0000;  // -1
static const fix16_t fix16_zero     = 0x00000000;

static const fix16_t c_f16_pt_0025     = 0x000000a4;    // 0.0025
static const fix16_t c_f16_pt_01       = 0x0000028f;    // 0.01 
static const fix16_t c_f16_pt_02       = 0x0000051f;
static const fix16_t c_f16_pt_03       = 0x000007ae;
static const fix16_t c_f16_pt_04       = 0x00000a3d;
static const fix16_t c_f16_pt_05       = 0x00000ccd;
static const fix16_t c_f16_pt_06       = 0x00000f5c;
static const fix16_t c_f16_pt_07       = 0x000011ec;
static const fix16_t c_f16_pt_08       = 0x0000147b;
static const fix16_t c_f16_pt_09       = 0x0000170a;    // 0.09

static const fix16_t c_f16_pt_1        = 0x0000199a;  // 0.1
static const fix16_t c_f16_pt_2        = 0x00003333;  // 0.2
static const fix16_t c_f16_pt_25       = 0x00004000;  // 0.25
static const fix16_t c_f16_pt_3        = 0x00004ccd;  // 0.3
static const fix16_t c_f16_pt_4        = 0x00006666;  // 0.4
static const fix16_t c_f16_pt_5        = 0x00008000;  // 0.5
static const fix16_t c_f16_pt_707      = 0x0000b4fe;  // 0.707
static const fix16_t c_f16_pt_75       = 0x0000c000;  // 0.75
static const fix16_t c_f16_pt_99       = 0x0000fd71;  // 0.99

static const fix16_t c_f16_1_pt_5      = 0x00018000;  // 1.5
static const fix16_t c_f16_15_pt_5     = 0x000f8000;  // 15.5
static const fix16_t c_f16_15_pt_5_recp= 0x00001084;  // 1.0 / 15.5

static const fix16_t c_f16_2           = 0x00020000;
static const fix16_t c_f16_3           = 0x00030000;
static const fix16_t c_f16_4           = 0x00040000;
static const fix16_t c_f16_5           = 0x00050000;
static const fix16_t c_f16_6           = 0x00060000;
static const fix16_t c_f16_8           = 0x00080000;
static const fix16_t c_f16_10          = 0x000a0000;
static const fix16_t c_f16_11          = 0x000b0000;
static const fix16_t c_f16_12          = 0x000c0000;
static const fix16_t c_f16_13          = 0x000d0000;
static const fix16_t c_f16_14          = 0x000e0000;
static const fix16_t c_f16_15          = 0x000f0000;
static const fix16_t c_f16_16          = 0x00100000;
static const fix16_t c_f16_20          = 0x00140000;
static const fix16_t c_f16_24          = 0x00180000;
static const fix16_t c_f16_28          = 0x001c0000;
static const fix16_t c_f16_30          = 0x001e0000;
static const fix16_t c_f16_32          = 0x00200000;

static const fix16_t c_f16_1_over_pt_5 = 0x00020000;
static const fix16_t c_f16_1_over_8    = 0x00002000;    // 1/8.0
static const fix16_t c_f16_1_over_9    = 0x00001c72;
static const fix16_t c_f16_1_over_4    = 0x00004000;
static const fix16_t c_f16_1_over_14   = 0x00001249;
static const fix16_t c_f16_1_over_16   = 0x00001000;
static const fix16_t c_f16_1_over_18   = 0x00000e39;

/* Conversion functions between fix16_t and float/integer.
 * These are inlined to allow compiler to optimize away constant numbers
 */
static inline fix16_t fix16_from_int(int a)     { return a * fix16_one; }
static inline float   fix16_to_float(fix16_t a) { return (float)a / fix16_one; }
static inline double  fix16_to_dbl(fix16_t a)   { return (double)a / fix16_one; }


static inline int fix16_to_int(fix16_t a)
{
#ifdef FIXMATH_NO_ROUNDING
    return (a >> 16);
#else
	if (a >= 0)
		return (a + (fix16_one >> 1)) / fix16_one;
	return (a - (fix16_one >> 1)) / fix16_one;
#endif
}

static inline fix16_t fix16_from_float(float a)
{
	float temp = a * fix16_one;
#ifndef FIXMATH_NO_ROUNDING
	temp += (temp >= 0) ? 0.5f : -0.5f;
#endif
	return (fix16_t)temp;
}

static inline fix16_t fix16_from_dbl(double a)
{
	double temp = a * fix16_one;
#ifndef FIXMATH_NO_ROUNDING
	temp += (temp >= 0) ? 0.5f : -0.5f;
#endif
	return (fix16_t)temp;
}



/* Macro for defining fix16_t constant values.
   The functions above can't be used from e.g. global variable initializers,
   and their names are quite long also. This macro is useful for constants
   springled alongside code, e.g. F16(1.234).

   Note that the argument is evaluated multiple times, and also otherwise
   you should only use this for constant values. For runtime-conversions,
   use the functions above.
*/
#define F16(x) ((fix16_t)(((x) >= 0) ? ((x) * 65536.0 + 0.5) : ((x) * 65536.0 - 0.5)))

static inline fix16_t fix16_abs_nb(fix16_t x)
{ 
    const fix16_t _xmask = ( x >> ( sizeof( fix16_t ) * 7 ) );
    return ( x + _xmask ) ^ _xmask;
}

static inline fix16_t fix16_abs(fix16_t x)
	{ return (x < 0 ? -x : x); }
static inline fix16_t fix16_floor(fix16_t x)
	{ return (x & 0xFFFF0000UL); }
static inline fix16_t fix16_ceil(fix16_t x)
	{ return (x & 0xFFFF0000UL) + (x & 0x0000FFFFUL ? fix16_one : 0); }
static inline fix16_t fix16_min(fix16_t x, fix16_t y)
	{ return (x < y ? x : y); }
static inline fix16_t fix16_max(fix16_t x, fix16_t y)
	{ return (x > y ? x : y); }
static inline fix16_t fix16_clamp(fix16_t x, fix16_t lo, fix16_t hi)
	{ return fix16_min(fix16_max(x, lo), hi); }


static inline int fix16_floor_to_int(fix16_t x)
{ 
    return (int)( fix16_floor(x) >> 16 );
}

static inline int fix16_ceil_to_int(fix16_t x)
{ 
    return (int)( fix16_ceil(x) >> 16 );
}
    
/* Subtraction and addition with (optional) overflow detection. */
#ifdef FIXMATH_NO_OVERFLOW

static inline fix16_t fix16_add(fix16_t inArg0, fix16_t inArg1) { return (inArg0 + inArg1); }
static inline fix16_t fix16_sub(fix16_t inArg0, fix16_t inArg1) { return (inArg0 - inArg1); }

#else

extern fix16_t fix16_add(fix16_t a, fix16_t b) FIXMATH_FUNC_ATTRS;
extern fix16_t fix16_sub(fix16_t a, fix16_t b) FIXMATH_FUNC_ATTRS;

/* Saturating arithmetic */
extern fix16_t fix16_sadd(fix16_t a, fix16_t b) FIXMATH_FUNC_ATTRS;
extern fix16_t fix16_ssub(fix16_t a, fix16_t b) FIXMATH_FUNC_ATTRS;

#endif

/*! Multiplies the two given fix16_t's and returns the result.
*/
extern fix16_t fix16_mul(fix16_t inArg0, fix16_t inArg1) FIXMATH_FUNC_ATTRS;

/*! Divides the first given fix16_t by the second and returns the result.
*/
extern fix16_t fix16_div(fix16_t inArg0, fix16_t inArg1) FIXMATH_FUNC_ATTRS;

#ifndef FIXMATH_NO_OVERFLOW
/*! Performs a saturated multiplication (overflow-protected) of the two given fix16_t's and returns the result.
*/
extern fix16_t fix16_smul(fix16_t inArg0, fix16_t inArg1) FIXMATH_FUNC_ATTRS;

/*! Performs a saturated division (overflow-protected) of the first fix16_t by the second and returns the result.
*/
extern fix16_t fix16_sdiv(fix16_t inArg0, fix16_t inArg1) FIXMATH_FUNC_ATTRS;
#endif

/*! Divides the first given fix16_t by the second and returns the result.
*/
extern fix16_t fix16_mod(fix16_t x, fix16_t y) FIXMATH_FUNC_ATTRS;



/*! Returns the linear interpolation: (inArg0 * (1 - inFract)) + (inArg1 * inFract)
*/
#ifndef FIXMATH_NO_64BIT
extern fix16_t fix16_lerp8(fix16_t inArg0, fix16_t inArg1, uint8_t inFract) FIXMATH_FUNC_ATTRS;
extern fix16_t fix16_lerp16(fix16_t inArg0, fix16_t inArg1, uint16_t inFract) FIXMATH_FUNC_ATTRS;
extern fix16_t fix16_lerp32(fix16_t inArg0, fix16_t inArg1, uint32_t inFract) FIXMATH_FUNC_ATTRS;
#endif

static inline fix16_t p3lerp( const fix16_t t, const fix16_t a, const fix16_t b )
{
	const fix16_t diff = fix16_mul( fix16_sub( b, a ), t );

	return fix16_add( a, diff );
}

/*! Returns the sine of the given fix16_t.
*/
extern fix16_t fix16_sin_parabola(fix16_t inAngle) FIXMATH_FUNC_ATTRS;

/*! Returns the sine of the given fix16_t.
*/
extern fix16_t fix16_sin(fix16_t inAngle) FIXMATH_FUNC_ATTRS;

/*! Returns the cosine of the given fix16_t.
*/
extern fix16_t fix16_cos(fix16_t inAngle) FIXMATH_FUNC_ATTRS;

/*! Returns the tangent of the given fix16_t.
*/
extern fix16_t fix16_tan(fix16_t inAngle) FIXMATH_FUNC_ATTRS;

/*! Returns the arcsine of the given fix16_t.
*/
extern fix16_t fix16_asin(fix16_t inValue) FIXMATH_FUNC_ATTRS;

/*! Returns the arccosine of the given fix16_t.
*/
extern fix16_t fix16_acos(fix16_t inValue) FIXMATH_FUNC_ATTRS;

/*! Returns the arctangent of the given fix16_t.
*/
extern fix16_t fix16_atan(fix16_t inValue) FIXMATH_FUNC_ATTRS;

/*! Returns the arctangent of inY/inX.
*/
extern fix16_t fix16_atan2(fix16_t inY, fix16_t inX) FIXMATH_FUNC_ATTRS;

static const fix16_t fix16_rad_to_deg_mult = 3754936;
static inline fix16_t fix16_rad_to_deg(fix16_t radians)
	{ return fix16_mul(radians, fix16_rad_to_deg_mult); }

static const fix16_t fix16_deg_to_rad_mult = 1144;
static inline fix16_t fix16_deg_to_rad(fix16_t degrees)
	{ return fix16_mul(degrees, fix16_deg_to_rad_mult); }



/*! Returns the square root of the given fix16_t.
*/
extern fix16_t fix16_sqrt(fix16_t inValue) FIXMATH_FUNC_ATTRS;

/*! Returns the square of the given fix16_t.
*/
static inline fix16_t fix16_sq(fix16_t x)
	{ return fix16_mul(x, x); }

/*! Returns the exponent (e^) of the given fix16_t.
*/
extern fix16_t fix16_exp(fix16_t inValue) FIXMATH_FUNC_ATTRS;

/*! Returns the natural logarithm of the given fix16_t.
 */
extern fix16_t fix16_log(fix16_t inValue) FIXMATH_FUNC_ATTRS;

/*! Returns the base 2 logarithm of the given fix16_t.
 */
extern fix16_t fix16_log2(fix16_t x) FIXMATH_FUNC_ATTRS;

/*! Returns the saturated base 2 logarithm of the given fix16_t.
 */
extern fix16_t fix16_slog2(fix16_t x) FIXMATH_FUNC_ATTRS;

/*! Convert fix16_t value to a string.
 * Required buffer length for largest values is 13 bytes.
 */
extern void fix16_to_str(fix16_t value, char *buf, int decimals);

/*! Convert string to a fix16_t value
 * Ignores spaces at beginning and end. Returns fix16_overflow if
 * value is too large or there were garbage characters.
 */
extern fix16_t fix16_from_str(const char *buf);



// ---------------------------------------------------------------------------------------------------------------------
static inline fix16_t fix16_fract(const fix16_t v)
{
   // fix16_t x = v;
  //  fix16_t i = fix16_from_int( fix16_to_int(v) );
  //  return fix16_sub( x, i );
  return v & 0x0000FFFFUL;
}

static inline fix16_t fix16_round(const fix16_t v)
{
  return fix16_to_int(v + 0.5f);
}

static inline fix16_t fix16_inv_fpart(const fix16_t v)
{
  return fix16_sub( fix16_one, fix16_fract(v) );
}


static inline fix16_t  fix16_distance_between_sq(
    const fix16_t x, 
    const fix16_t y, 
    const fix16_t cX, 
    const fix16_t cY) 
{
    const fix16_t dX = fix16_sub( x, cX );
    const fix16_t dY = fix16_sub( y, cY );
    return fix16_add( fix16_mul(dX, dX), fix16_mul(dY, dY) );
}

static inline fix16_t  fix16_distance_between(
    const fix16_t x, 
    const fix16_t y, 
    const fix16_t cX, 
    const fix16_t cY) 
{
    const fix16_t dX = fix16_sub( x, cX );
    const fix16_t dY = fix16_sub( y, cY );
    const fix16_t distance = fix16_add( fix16_mul(dX, dX), fix16_mul(dY, dY) );
    return fix16_sqrt(distance);
}


/** Helper macro for F16C. Replace token with its number of characters/digits. */
#define FIXMATH_TOKLEN(token) ( sizeof( #token ) - 1 )

/** Helper macro for F16C. Handles pow(10, n) for n from 0 to 8. */
#define FIXMATH_CONSTANT_POW10(times) ( \
  (times == 0) ? 1ULL \
        : (times == 1) ? 10ULL \
            : (times == 2) ? 100ULL \
                : (times == 3) ? 1000ULL \
                    : (times == 4) ? 10000ULL \
                        : (times == 5) ? 100000ULL \
                            : (times == 6) ? 1000000ULL \
                                : (times == 7) ? 10000000ULL \
                                    : 100000000ULL \
)


/** Helper macro for F16C, the type uint64_t is only used at compile time and
 *  shouldn't be visible in the generated code.
 *
 * @note We do not use fix16_one instead of 65536ULL, because the
 *       "use of a const variable in a constant expression is nonstandard in C".
 */
#define FIXMATH_CONVERT_MANTISSA(m) \
( (unsigned) \
    ( \
        ( \
            ( \
                (uint64_t)( ( ( 1 ## m ## ULL ) - FIXMATH_CONSTANT_POW10(FIXMATH_TOKLEN(m)) ) * FIXMATH_CONSTANT_POW10(5 - FIXMATH_TOKLEN(m)) ) \
                * 100000ULL * 65536ULL \
            ) \
            + 5000000000ULL /* rounding: + 0.5 */ \
        ) \
        / \
        10000000000LL \
    ) \
)


#define FIXMATH_COMBINE_I_M(i, m) \
( \
    ( \
        (    i ) \
        << 16 \
    ) \
    | \
    ( \
        FIXMATH_CONVERT_MANTISSA(m) \
        & 0xFFFF \
    ) \
)


/** Create int16_t (Q16.16) constant from separate integer and mantissa part.
 *
 * Only tested on 32-bit ARM Cortex-M0 / x86 Intel.
 *
 * This macro is needed when compiling with options like "--fpu=none",
 * which forbid all and every use of float and related types and
 * would thus make it impossible to have fix16_t constants.
 *
 * Just replace uses of F16() with F16C() like this:
 *   F16(123.1234) becomes F16C(123,1234)
 *
 * @warning Specification of any value outside the mentioned intervals
 *          WILL result in undefined behavior!
 *
 * @note Regardless of the specified minimum and maximum values for i and m below,
 *       the total value of the number represented by i and m MUST be in the interval
 *       ]-32768.00000:32767.99999[ else usage with this macro will yield undefined behavior.
 *
 * @param i Signed integer constant with a value in the interval ]-32768:32767[.
 * @param m Positive integer constant in the interval ]0:99999[ (fractional part/mantissa).
 */

#define F16C(i, m) \
( (fix16_t) \
    ( \
      (( #i[0] ) == '-') \
        ? -FIXMATH_COMBINE_I_M((unsigned)( ( (i) * -1) ), m) \
        : FIXMATH_COMBINE_I_M(i, m) \
    ) \
)

#ifdef __cplusplus
}
#endif

#endif
