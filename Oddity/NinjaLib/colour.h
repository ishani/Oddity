/*===========================================================================*\
 |
 | Ninja Code Framework
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Colour (f/i) and light support
 |
 | $Author: Harry Denholm $ 
 | $Revision: 1 $
 | $Date: 5/06/01 0:41 $ 
 | $Archive: /base/colour.h $
 |
\*===========================================================================*/


#ifndef	__NJFW_COLOUR_
#define	__NJFW_COLOUR_


/*===========================================================================*\
 | r,g,b,a unit float colour storage
\*===========================================================================*/

typedef struct sColour
{
	sFloat	r,g,b,a;

	// constructors
	inline sColour(void) { r = 0.0f; g = 0.0f; b = 0.0f; a = 0.0f; };
	inline sColour(const sFloat ir, const sFloat ig, const sFloat ib, const sFloat ia = 1.0f);
	inline sColour(const sInt32 ir, const sInt32 ig, const sInt32 ib, const sInt32 ia = 1);
	inline sColour(const sColour &v);
	inline sColour(const sVector4 &v);

	// comparison operators
	inline sBool		operator == (const sColour &v) const;
	inline sBool		operator != (const sColour &v) const;

	// expose colour by given coeff
	inline void			expose(const sFloat &exps);

	// clamp all components to 0.0f -> 1.0f
	inline void			clamp();

} sColour;

const sColour fColourBlack(0.0f, 0.0f, 0.0f, 1.0f);
const sColour fColourWhite(1.0f, 1.0f, 1.0f, 1.0f);
const sColour fColourRed(1.0f, 0.0f, 0.0f, 1.0f);
const sColour fColourGreen(0.0f, 1.0f, 0.0f, 1.0f);
const sColour fColourBlue(0.0f, 0.0f, 1.0f, 1.0f);



/*===========================================================================*\
 | implimentation of sColour inline functions
\*===========================================================================*/

inline sColour::sColour(const sFloat ir, const sFloat ig, const sFloat ib, const sFloat ia)
{
	r = ir;
	g = ig;
	b = ib;
	a = ia;
}

inline sColour::sColour(const sInt32 ir, const sInt32 ig, const sInt32 ib, const sInt32 ia)
{
	r = intToFloat(ir);
	g = intToFloat(ig);
	b = intToFloat(ib);
	a = intToFloat(ia);
}

inline sColour::sColour(const sColour &v)
{
	r = v.r;
	g = v.g;
	b = v.b;
	a = v.a;
}

inline sColour::sColour(const sVector4 &v)
{
	r = v.x;
	g = v.y;
	b = v.z;
	a = v.w;
}


inline sBool sColour::operator == (const sColour &v) const
{
	if(r!=v.r) return FALSE;
	if(g!=v.g) return FALSE;
	if(b!=v.b) return FALSE;
	if(a!=v.a) return FALSE;
	return TRUE;
}

inline sBool sColour::operator != (const sColour &v) const
{
	if(r!=v.r) return TRUE;
	if(g!=v.g) return TRUE;
	if(b!=v.b) return TRUE;
	if(a!=v.a) return TRUE;
	return FALSE;
}


inline void sColour::expose(const sFloat &exps)
{
	r = ( 1.0f - (sFloat)exp(r * -exps) );
	g = ( 1.0f - (sFloat)exp(g * -exps) );
	b = ( 1.0f - (sFloat)exp(b * -exps) );
}

inline void sColour::clamp()
{
	CLAMP(r,0.0f,1.0f);
	CLAMP(g,0.0f,1.0f);
	CLAMP(b,0.0f,1.0f);
	CLAMP(a,0.0f,1.0f);
}


/*===========================================================================*\
 | b,g,r inverted order unsigned color structure
 | for use with windows bitmaps, targas and the like
\*===========================================================================*/

typedef struct sBGRColour
{
	sUChar8	b,g,r;

	// constructors
	inline sBGRColour(void) { r = 0; g = 0; b = 0; };
	inline sBGRColour(const sFloat ir, const sFloat ig, const sFloat ib);
	inline sBGRColour(const sUChar8 ir, const sUChar8 ig, const sUChar8 ib);

	// comparison operators
	inline sBool		operator == (const sBGRColour &v) const;
	inline sBool		operator != (const sBGRColour &v) const;

} sBGRColour;


/*===========================================================================*\
 | implimentation of sVector4 inline functions
\*===========================================================================*/

inline sBGRColour::sBGRColour(const sFloat ir, const sFloat ig, const sFloat ib)
{
	r = floatToInt(ir);
	g = floatToInt(ig);
	b = floatToInt(ib);
}

inline sBGRColour::sBGRColour(const sUChar8 ir, const sUChar8 ig, const sUChar8 ib)
{
	r = ir;
	g = ig;
	b = ib;
}


inline sBool sBGRColour::operator == (const sBGRColour &v) const
{
	if(r!=v.r) return FALSE;
	if(g!=v.g) return FALSE;
	if(b!=v.b) return FALSE;
	return TRUE;
}

inline sBool sBGRColour::operator != (const sBGRColour &v) const
{
	if(r!=v.r) return TRUE;
	if(g!=v.g) return TRUE;
	if(b!=v.b) return TRUE;
	return FALSE;
}


#endif