/*===========================================================================*\
 |
 | Ninja Code Framework
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | 2D Vector support
 |
 | $Author: Harry Denholm $ 
 | $Revision: 3 $
 | $Date: 5/06/01 0:42 $ 
 | $Archive: /base/vector2.h $
 |
\*===========================================================================*/


#ifndef	__NJFW_VECTOR2_
#define	__NJFW_VECTOR2_


/*===========================================================================*\
 | x,y 2D coorindate
\*===========================================================================*/

typedef struct sVector2
{
	sFloat	x,y;

	// constructors
	inline sVector2(void) { x = 0.0f; y = 0.0f; };
	inline sVector2(const sFloat ix, const sFloat iy);
	inline sVector2(const sInt32 ix, const sInt32 iy);
	inline sVector2(const sVector2 &v);

	// unary operators
	inline sVector2	operator - (void) const;

	// binary operators
	inline sVector2	&operator = (const sVector2 &v);
	inline sVector2	operator + (const sVector2 &v) const;
	inline sVector2	operator - (const sVector2 &v) const;
	inline sVector2	operator * (const sFloat s) const;
	inline sVector2	operator / (const sFloat s) const;

	// comparison operators
	inline sBool		operator == (const sVector2 &v) const;
	inline sBool		operator != (const sVector2 &v) const;

} sVector2;

const sVector2 vector2Zero(0.0f, 0.0f);


/*===========================================================================*\
 | implimentation of sVector2 inline functions
\*===========================================================================*/

inline sVector2::sVector2(const sFloat ix, const sFloat iy)
{
	x = ix;
	y = iy;
}

inline sVector2::sVector2(const sInt32 ix, const sInt32 iy)
{
	x = intToFloat(ix);
	y = intToFloat(iy);
}

inline sVector2::sVector2(const sVector2 &v)
{
	x = v.x;
	y = v.y;
}

inline sVector2 sVector2::operator - (void) const
{
	return sVector2(-x,-y);
}

inline sVector2 &sVector2::operator = (const sVector2 &v)
{
	x = v.x;
	y = v.y;
	return *this;
}

inline sVector2 sVector2::operator + (const sVector2 &v) const
{
	return sVector2( x+v.x, y+v.y );
}

inline sVector2 sVector2::operator - (const sVector2 &v) const
{
	return sVector2( x-v.x, y-v.y );
}

inline sVector2 sVector2::operator * (const sFloat s) const
{
	return sVector2( x*s, y*s );
}

inline sVector2 sVector2::operator / (const sFloat s) const
{
	return sVector2( x/s, y/s );
}

inline sBool sVector2::operator == (const sVector2 &v) const
{
	if(x!=v.x) return FALSE;
	if(y!=v.y) return FALSE;
	return TRUE;
}

inline sBool sVector2::operator != (const sVector2 &v) const
{
	if(x!=v.x) return TRUE;
	if(y!=v.y) return TRUE;
	return FALSE;
}



/*===========================================================================*\
 | another alias for a 2D x,y pair - a UV texture coordinate
\*===========================================================================*/

typedef struct sUVCoordinate
{
	sFloat	u,v;

	// constructors
	inline sUVCoordinate (void) { u = 0.0f; v = 0.0f; };
	inline sUVCoordinate (const sFloat iu, const sFloat iv);
	inline sUVCoordinate (const sInt32 iu, const sInt32 iv);
	inline sUVCoordinate (const sUVCoordinate &c);

} sUVCoordinate;

const sUVCoordinate uvTopLeft(0.0f, 0.0f);
const sUVCoordinate uvTopRight(1.0f, 0.0f);
const sUVCoordinate uvBottomLeft(0.0f, 1.0f);
const sUVCoordinate uvBottomRight(1.0f, 1.0f);


/*===========================================================================*\
 | implimentation of sUVCoordinate inline functions
\*===========================================================================*/

inline sUVCoordinate::sUVCoordinate(const sFloat iu, const sFloat iv)
{
	u = iu;
	v = iv;
}

inline sUVCoordinate::sUVCoordinate(const sInt32 iu, const sInt32 iv)
{
	u = intToFloat(iu);
	v = intToFloat(iv);
}

inline sUVCoordinate::sUVCoordinate(const sUVCoordinate &c)
{
	u = c.u;
	v = c.v;
}


#endif