/*===========================================================================*\
 |
 | Ninja Code Framework
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | General code macros
 |
 | $Author: Harry Denholm $ 
 | $Revision: 1 $
 | $Date: 22/05/01 23:18 $ 
 | $Archive: /base/macros.h $
 |
\*===========================================================================*/


#ifndef	__NJFW_MACROS_
#define	__NJFW_MACROS_


// size of an array
#define ARRAY_SIZE(n)	(sizeof(n)/sizeof((n)[0]))


// safe delete & release 
#define SAFE_STDFREE(p)		{ if(p) { free (p);			(p)=NULL; } }
#define SAFE_DELETE(p)		{ if(p) { delete (p);		(p)=NULL; } }
#define SAFE_RELEASE(p)		{ if(p) { (p)->Release();	(p)=NULL; } }

// free using stealth memory library
#define SAFE_FREE(p,k,n)	{ if(p) { stMemFree(p,k,n); (p)=NULL; } }


// align to the nearest DWORD
#define ALIGN8(nb)		((nb+7)&0xfffffff8)


// macros to clamp values between ranges
#define CLAMP(var,low,high)			\
{									\
	if(var<low)						\
		var=low;					\
	else if(var>high)				\
		var=high;					\
}

#define CLAMP_LOW(var,low)			\
{									\
	if(var<low)						\
		var=low;					\
}

#define CLAMP_HIGH(var,high)		\
{									\
	if(var>high)					\
		var=high;					\
}


#endif