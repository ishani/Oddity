/*===========================================================================*\
 |
 | Ninja Code Framework
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Mathematics functions
 |
 | $Author: Harry Denholm $ 
 | $Revision: 2 $
 | $Date: 5/06/01 0:42 $ 
 | $Archive: /base/mathUtils.h $
 |
\*===========================================================================*/


#ifndef	__NJFW_MATHUTILS_
#define	__NJFW_MATHUTILS_

#pragma inline_recursion(on)
#pragma inline_depth(64)



/*===========================================================================*\
 | convert an integer value to a floating point value
\*===========================================================================*/

inline sFloat intToFloat (const sInt32 i)
{
#ifdef _NJFW_USE_MMXASM
	sFloat f;
	#ifdef _NJFW_USE_SSE
		_asm
		{
			cvtsi2ss	xmm0, i
			movss		f, xmm0
		}
	#else
		_asm
		{
			fild	i
			fstp	f
		}
	#endif
	return f;
#else
	return (sFloat)i;
#endif
}


/*===========================================================================*\
 | convert a floating point value to an integer value
\*===========================================================================*/

inline sInt32 floatToInt (const sFloat f)
{
#ifdef _NJFW_USE_MMXASM
	sInt32 i;
	#ifdef _NJFW_USE_SSE
		_asm
		{
			cvtss2si	eax, f
			mov			i, eax
		}
	#else
		_asm
		{
			fld		f
			fistp	i
		}
	#endif
	return i;
#else
	return (sInt32)f;
#endif
}


/*===========================================================================*\
 | find ceiling of a float value (round up)
\*===========================================================================*/

inline sFloat fCeil(const sFloat f)
{
#ifdef _NJFW_USE_MMXASM
	sFloat x;
	#ifdef _NJFW_USE_SSE
		_asm
		{
			movss		xmm0, f
			addss		xmm0, ZeroPointFive
			cvtss2si	eax, xmm0
			cvtsi2ss	xmm0, eax
			movss		x, xmm0
		}
	#else
		sInt32 i;
		_asm
		{
			fld		f
			fadd	ZeroPointFive
			fistp	i
			fild	i
			fstp	x
		}
	#endif
	return x;
#else
	return ceilf(f);
#endif
}


/*===========================================================================*\
 | find floor of a float value (round down)
\*===========================================================================*/

inline sFloat fFloor(const sFloat f)
{
#ifdef _NJFW_USE_MMXASM
	sFloat x;
	#ifdef _NJFW_USE_SSE
		_asm
		{
			movss		xmm0, f
			subss		xmm0, ZeroPointFive
			cvtss2si	eax, xmm0
			cvtsi2ss	xmm0, eax
			movss		x, xmm0
		}
	#else
		sInt32 i;
		_asm
		{
			fld		f
			fsub	ZeroPointFive
			fistp	i
			fild	i
			fstp	x
		}
	#endif
	return x;
#else
	return floorf(f);
#endif
}


/*===========================================================================*\
 | invert a floating point value
\*===========================================================================*/

inline sFloat fNegate(const sFloat f)
{
#ifdef _NJFW_USE_MMXASM
	sFloat x;
    __asm
    {
        mov     eax,f
        xor     eax,floatSignMask
        mov     x,eax
    }
	return x;
#else
	return -f;
#endif
}


/*===========================================================================*\
 | square root of floating point value
\*===========================================================================*/

inline sFloat fSqrt(const sFloat f)
{
#ifdef _NJFW_USE_MMXASM
	sFloat x;
	#ifdef _NJFW_USE_SSE
		_asm
		{
			sqrtss	xmm0, f
			movss	x, xmm0
		}
	#else
		_asm
			{
			fld		f
			fsqrt				// ST = sqrt(ST)
			fstp	x
		}
	#endif
	return x;
#else
	return sqrtf(f);
#endif
}



/*===========================================================================*\
 | reciprocal square root of floating point value
\*===========================================================================*/

inline sFloat Rcp(const sFloat f)
{
#ifdef _NJFW_USE_SSE
	sFloat x;
	_asm
	{
		rcpss	xmm0, f
		movss	x, xmm0
	}
	return x;
#else
	return 1.0f / f;
#endif
}

inline sFloat fRSqrt (const sFloat f)
{
#ifdef _NJFW_USE_MMXASM
	sFloat x;
	#ifdef _NJFW_USE_SSE
		_asm
		{
			rsqrtss	xmm0, x
			movss	x, xmm0
		}
	#else
		_asm
		{
			fld1
			fld		f
			fsqrt				// ST = sqrt(ST)
			fdivp	st(1), st	// ST(1) /= ST and pop ST (replace 1 with 1/sqrt(x))
			fstp	x
		}
	#endif
	return x;
#else
	return Rcp(fSqrt(f));
#endif
}


/*===========================================================================*\
 | find absolute value of passed floating point value
\*===========================================================================*/

inline sFloat fAbs(const sFloat f)
{
#ifdef _NJFW_USE_MMXASM
	sFloat x;
    __asm
    {
        mov     eax,f
        and     eax,floatExSignMask
        mov     x,eax
    }
	return x;
#else
	return fabsf(f);
#endif
}


/*===========================================================================*\
 | find absolute difference value of two passed floating point values
\*===========================================================================*/

inline sFloat fAbsDiff(const sFloat fa, const sFloat fb)
{
	return(fAbs(fa - fb));
}


/*===========================================================================*\
 | return whether or not floating point value is signed (- or not)
\*===========================================================================*/

inline sBool fSign(const sFloat s)
{
#ifdef _NJFW_USE_MMXASM
	sBool x;
    __asm
    {
        mov     eax,s
        and     eax,floatSignMask
		shr		eax,0x1f
        mov     x,eax
    }
	return x;
#else
	return s < 0.0f;
#endif
}


/*===========================================================================*\
 | find minimum / maximum of two floating point values
\*===========================================================================*/

inline sFloat fMax(const sFloat s1, const sFloat s2)
{
#ifdef _NJFW_USE_SSE
	sFloat x;
	_asm
	{
		movss	xmm0, s1
		maxss	xmm0, s2
		movss	x, xmm0
	}
	return x;
#else
	return (s1 >= s2) ? s1 : s2;
#endif
}

inline sFloat fMin(const sFloat s1, const sFloat s2)
{
#ifdef _NJFW_USE_SSE
	sFloat x;
	_asm
	{
		movss	xmm0, s1
		minss	xmm0, s2
		movss	x, xmm0
	}
	return x;
#else
	return (s1 <= s2) ? s1 : s2;
#endif
}


/*===========================================================================*\
 | sine
\*===========================================================================*/

inline sFloat fSin (const sFloat f)
{
#ifdef _NJFW_USE_MMXASM
	sFloat x;
	_asm
	{
		fld		f
		fsin
		fstp	x
	}
	return x;
#else
	return sinf(f);
#endif
}


/*===========================================================================*\
 | cosine
\*===========================================================================*/

inline sFloat fCos (const sFloat f)
{
#ifdef _NJFW_USE_MMXASM
	sFloat x;
	_asm
	{
		fld		f
		fcos
		fstp	x
	}
	return x;
#else
	return cosf(f);
#endif
}


/*===========================================================================*\
 | tangent
\*===========================================================================*/

inline sFloat fTan (const sFloat f)
{
#ifdef _NJFW_USE_MMXASM
	sFloat x;
	_asm
	{
		fld		f
		fptan			// Calculates tan and pushes 1.0
		fstp	st		// Pop ST (the unwanted 1.0)
		fstp	x
	}
	return x;
#else
	return cosf(f);
#endif
}


/*===========================================================================*\
 | atan
\*===========================================================================*/

inline sFloat fATan(const sFloat f)
{
#ifdef _NJFW_USE_MMXASM
	sFloat x;
	_asm
	{
		fld		f
		fld1			// push constant 1 onto register stack
		fpatan			// calculates atan and pops FP register stack
		fstp	x
	}
	return x;
#else
	return atanf(f);
#endif
}


/*===========================================================================*\
 | atan2
\*===========================================================================*/

inline sFloat fATan2(const sFloat y, const sFloat x)
{
#ifdef _NJFW_USE_MMXASM
	sFloat a;
	_asm
	{
		fld		y       // ST(0) = y
		fld		x		// ST(0) = x ST(1) = y
		fpatan			// calculates atan into ST(1) and pops FP register stack
		fstp	a
	}
	return a;
#else
	return atan2f(y, x);
#endif
}


/*===========================================================================*\
 | generate sine and cosine in parallel
\*===========================================================================*/

inline void fSinCos (const sFloat f, sFloat &s, sFloat &c)
{
#ifdef _NJFW_USE_MMXASM
	sFloat _c, _s;
	_asm
	{
		fld		f
		fsincos
		fstp	_c
		fstp	_s
	}
	c = _c;
	s = _s;
#else
	s = sinf(f);
	c = cosf(f);
#endif
}



/*===========================================================================*\
 | disassemble a floating point value
\*===========================================================================*/

inline sUInt32 fMantissa(const sFloat f)
{
	return ((*(sUInt32 *)&f) & floatManMask) >> floatManShift;
}

inline sUInt32 fExponent(const sFloat f)
{
	return ((*(sUInt32 *)&f) & floatExpMask) >> floatExpShift;
}



/*===========================================================================*\
 | general bit wise operations on an sUInt32
\*===========================================================================*/

inline sBool bitTest(const sUInt32 bits, const sUInt32 index)
{
	return bits & (1 << index);
}

inline void bitSet(sUInt32 &bits, const sUInt32 index)
{
	bits |= (1 << index);
}

inline void bitClr(sUInt32 &bits, const sUInt32 index)
{
	bits &= ~(1 << index);
}

inline void bitToggle(sUInt32 &bits, const sUInt32 index)
{
	bits ^= (1 << index);
}


/*===========================================================================*\
 | linearly interpolate between two floating point values
 | input value i is unit value, 0.0f -> 1.0f
\*===========================================================================*/

inline sFloat fLerp(const sFloat s1, const sFloat s2, const sFloat i)
{
	return (s1 + ((s2 - s1) * i));
}


#pragma inline_depth()
#pragma inline_recursion(off)


#endif
