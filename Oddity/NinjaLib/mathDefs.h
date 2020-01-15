/*===========================================================================*\
 |
 | Ninja Code Framework
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Mathematics tools
 |
 | $Author: Harry Denholm $ 
 | $Revision: 2 $
 | $Date: 5/06/01 0:42 $ 
 | $Archive: /base/mathDefs.h $
 |
\*===========================================================================*/


#ifndef	__NJFW_MATHDEFS_
#define	__NJFW_MATHDEFS_


/*===========================================================================*\
 | some fairly standard helper defines
\*===========================================================================*/

#ifndef PI
	#define PI			(3.14159265358f)
#endif
#ifndef TWOPI
	#define TWOPI		(6.28318530717f)
#endif
#ifndef HALFPI
	#define HALFPI		(1.57079632679f)
#endif

const sFloat V_DEGTORAD =  0.01745329251f; 
const sFloat V_RADTODEG = 57.29577951308f; 

#define DEG2RAD(d)	((sFloat)(d*V_DEGTORAD))
#define RAD2DEG(r)	((sFloat)(r*V_RADTODEG))


#define SGN(a)		(((a)<0) ? -1 : 1)
#define SQR(a)		((a)*(a))	

#define MIN(a,b)	(((a)<(b))?(a):(b))	
#define MAX(a,b)	(((a)>(b))?(a):(b))	
#define ABS(a)		(((a)<0) ? -(a) : (a))

// back to mathutils.h
#define FP_SGN(a)	(fSign(a))
#define FP_MIN(a,b)	(fMin(a,b))	
#define FP_MAX(a,b)	(fMax(a,b))	
#define FP_ABS(a)	(fAbs(a))



/*===========================================================================*\
 | floating point disassembly masks and shifts
\*===========================================================================*/

const sUInt32       floatSignMask			= 0x80000000;
const sUInt32       floatExSignMask			= 0x7FFFFFFF;
const sUInt32		floatSignShift			= 31;
const sUInt32		floatExpMask			= 0x7F800000;
const sUInt32		floatExpShift			= 23;
const sUInt32		floatManMask			= 0x007FFFFF;
const sUInt32		floatManShift			= 0;



/*===========================================================================*\
 | some floating point constants
\*===========================================================================*/

const sFloat		Epsilon					= 1.0e-7f;
const sFloat		NegativeEpsilon			= -1.0e-7f;
const sFloat		ZeroPointFive			= 0.5f;
const sFloat		OnePointZero			= 1.0f;
const sFloat		NegativeOnePointZero	= -1.0f;
const sFloat		TwoPointZero			= 2.0f;
const sFloat		NegativeTwoPointZero	= -2.0f;


#endif