/*===========================================================================*\
 |
 | Ninja Code Framework
 |
 | Copyright© 2000-2001 Harry Denholm. All Rights Reserved.
 |===========================================================================*
 |
 | Basic variable type definitions
 |
 | $Author: Harry Denholm $ 
 | $Revision: 2 $
 | $Date: 5/06/01 0:42 $ 
 | $Archive: /base/baseTypes.h $
 |
\*===========================================================================*/


#ifndef    __NJFW_BASETYPES_
#define    __NJFW_BASETYPES_


/*===========================================================================*\
 | a wealth of variable types
\*===========================================================================*/

// character types
typedef char                sChar;
typedef unsigned char        sUChar;
typedef signed char            sSChar;
typedef unsigned short        sWChar;

// numbered character types
typedef char                sChar8;
typedef unsigned char        sUChar8;
typedef signed short        sChar16;
typedef unsigned short        sUChar16;


// number types
typedef char                sInt8;
typedef unsigned char        sUInt8;
typedef unsigned short        sUInt16;
typedef short                sInt16;
typedef unsigned int        sUInt32;
typedef int                    sInt32;
typedef unsigned __int64    sUInt64;
typedef __int64                sInt64;
typedef unsigned long        sULong;
typedef long                sLong;

// word-size types
typedef sUInt16                sWord;
typedef sUInt32                sDWord;

// floating point types
typedef float                sFloat;
typedef double                sDouble;
typedef sInt32                sFixed;

// boolean types
typedef sUChar                sByte;
typedef BOOL                sBool;


// just in case
#ifndef TRUE
    #define TRUE    (1)
#endif

#ifndef FALSE
    #define FALSE    (0)
#endif

#ifndef NULL
    #define NULL    (0)
#endif

#endif