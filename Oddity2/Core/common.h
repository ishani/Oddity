/*
  .oooooo.         .o8        .o8   o8o      .               
 d8P'  `Y8b       "888       "888   `"'    .o8               
888      888  .oooo888   .oooo888  oooo  .o888oo oooo    ooo 
888      888 d88' `888  d88' `888  `888    888    `88.  .8'  
888      888 888   888  888   888   888    888     `88..8'   
`88b    d88' 888   888  888   888   888    888 .    `888'    
 `Y8bood8P'  `Y8bod88P" `Y8bod88P" o888o   "888"     .8'  2.0
                                                 .o..P'      
                                                 `Y8P'       
                                                             
*/

#ifndef _COMMON_H
#define _COMMON_H


#ifdef _MSC_VER
#define ON_HARDWARE		0
#else
#define ON_HARDWARE		1
#endif // _MSC_VER

// attribute to store data in user flash section
#if ON_HARDWARE
#define __IN_FLASH__ __attribute__((section (".USER_FLASH")))
#else
#define __IN_FLASH__
#endif // ON_HARDWARE

// ---------------------------------------------------------------------------------------------------------------------
typedef signed char					s8;
typedef signed short				s16;
typedef signed int					s32;
typedef unsigned char				u8;
typedef unsigned short			u16;
typedef unsigned int				u32;

// ---------------------------------------------------------------------------------------------------------------------
// enable the text scroller code
// #define OXP_FONT16 // for the 16x16 font data
// #define OXP_SCROLL


#endif // _COMMON_H