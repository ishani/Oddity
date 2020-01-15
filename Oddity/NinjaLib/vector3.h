/*===========================================================================*\
 |
 | Ninja Code Framework
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | 3D Vector support
 |
 | $Author: Harry Denholm $ 
 | $Revision: 1 $
 | $Date: 5/06/01 0:41 $ 
 | $Archive: /base/vector3.h $
 |
\*===========================================================================*/


#ifndef	__NJFW_VECTOR3_
#define	__NJFW_VECTOR3_


/*===========================================================================*\
 | x,y,z 3D coorindate
\*===========================================================================*/

typedef struct sVector3
{
	sFloat	x,y,z;

	// constructors
	inline sVector3(void) { x = 0.0f; y = 0.0f; z = 0.0f; };
	inline sVector3(const sFloat ix, const sFloat iy, const sFloat iz);
	inline sVector3(const sInt32 ix, const sInt32 iy, const sInt32 iz);
	inline sVector3(const sVector3 &v);
	inline sVector3(const sVector2 &v);

	// comparison operators
	inline sBool		operator == (const sVector3 &v) const;
	inline sBool		operator != (const sVector3 &v) const;

} sVector3;

const sVector3 vector3Zero(0.0f, 0.0f, 0.0f);


/*===========================================================================*\
 | implimentation of sVector3 inline functions
\*===========================================================================*/

inline sVector3::sVector3(const sFloat ix, const sFloat iy, const sFloat iz)
{
	x = ix;
	y = iy;
	z = iz;
}

inline sVector3::sVector3(const sInt32 ix, const sInt32 iy, const sInt32 iz)
{
	x = intToFloat(ix);
	y = intToFloat(iy);
	z = intToFloat(iz);
}

inline sVector3::sVector3(const sVector3 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

inline sVector3::sVector3(const sVector2 &v)
{
	x = v.x;
	y = v.y;
	z = 0.0f;
}


inline sBool sVector3::operator == (const sVector3 &v) const
{
	if(x!=v.x) return FALSE;
	if(y!=v.y) return FALSE;
	if(z!=v.z) return FALSE;
	return TRUE;
}

inline sBool sVector3::operator != (const sVector3 &v) const
{
	if(x!=v.x) return TRUE;
	if(y!=v.y) return TRUE;
	if(z!=v.z) return TRUE;
	return FALSE;
}


#endif