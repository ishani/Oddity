/*===========================================================================*\
 |
 | Ninja Code Framework
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | 4D Vector support
 |
 | $Author: Harry Denholm $ 
 | $Revision: 2 $
 | $Date: 5/06/01 0:42 $ 
 | $Archive: /base/vector4.h $
 |
\*===========================================================================*/


#ifndef	__NJFW_VECTOR4_
#define	__NJFW_VECTOR4_


/*===========================================================================*\
 | x,y,z,w 4D coorindate
\*===========================================================================*/

typedef struct sVector4
{
	sFloat	x,y,z,w;

	// constructors
	inline sVector4(void) { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; };
	inline sVector4(const sFloat ix, const sFloat iy, const sFloat iz, const sFloat iw = 1.0f);
	inline sVector4(const sInt32 ix, const sInt32 iy, const sInt32 iz, const sInt32 iw = 1);
	inline sVector4(const sVector4 &v);
	inline sVector4(const sVector3 &v);
	inline sVector4(const sVector2 &v);

	// comparison operators
	inline sBool		operator == (const sVector4 &v) const;
	inline sBool		operator != (const sVector4 &v) const;

} sVector4;

const sVector4 vector4Zero(0.0f, 0.0f, 0.0f, 1.0f);


/*===========================================================================*\
 | implimentation of sVector4 inline functions
\*===========================================================================*/

inline sVector4::sVector4(const sFloat ix, const sFloat iy, const sFloat iz, const sFloat iw)
{
	x = ix;
	y = iy;
	z = iz;
	w = iw;
}

inline sVector4::sVector4(const sInt32 ix, const sInt32 iy, const sInt32 iz, const sInt32 iw)
{
	x = intToFloat(ix);
	y = intToFloat(iy);
	z = intToFloat(iz);
	w = intToFloat(iw);
}

inline sVector4::sVector4(const sVector4 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

inline sVector4::sVector4(const sVector3 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = 1.0f;
}

inline sVector4::sVector4(const sVector2 &v)
{
	x = v.x;
	y = v.y;
	z = 0.0f;
	w = 1.0f;
}


inline sBool sVector4::operator == (const sVector4 &v) const
{
	if(x!=v.x) return FALSE;
	if(y!=v.y) return FALSE;
	if(z!=v.z) return FALSE;
	if(w!=v.w) return FALSE;
	return TRUE;
}

inline sBool sVector4::operator != (const sVector4 &v) const
{
	if(x!=v.x) return TRUE;
	if(y!=v.y) return TRUE;
	if(z!=v.z) return TRUE;
	if(w!=v.w) return TRUE;
	return FALSE;
}


#endif