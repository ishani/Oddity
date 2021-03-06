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

#include "common.h"
#include "pcf.h"

/*
    function sample(x, y) 
    {
        var w = Math.abs(15.5 - x) / 15;
        var h = Math.abs(15.5 - y) / 15;
        return Math.min(w, h)
    }
*/

const uint16_t pcf_axis[32 * 32] __IN_FLASH__ = {
0xffff, 0xf777, 0xe666, 0xd555, 0xc444, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xc444, 0xd555, 0xe666, 0xf777, 0xffff, 
0xf777, 0xf777, 0xe666, 0xd555, 0xc444, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xc444, 0xd555, 0xe666, 0xf777, 0xf777, 
0xe666, 0xe666, 0xe666, 0xd555, 0xc444, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xc444, 0xd555, 0xe666, 0xe666, 0xe666, 
0xd555, 0xd555, 0xd555, 0xd555, 0xc444, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xc444, 0xd555, 0xd555, 0xd555, 0xd555, 
0xc444, 0xc444, 0xc444, 0xc444, 0xc444, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xc444, 0xc444, 0xc444, 0xc444, 0xc444, 
0xb333, 0xb333, 0xb333, 0xb333, 0xb333, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xb333, 0xb333, 0xb333, 0xb333, 0xb333, 
0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 
0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 
0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 
0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 
0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 
0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 
0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 
0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 
0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x0889, 0x0889, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 
0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 
0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 0x0889, 
0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x0889, 0x0889, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 0x199a, 
0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 0x2aab, 
0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 0x3bbc, 
0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 0x4ccd, 
0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 0x5dde, 
0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 0x6eef, 
0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 
0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 0x9111, 
0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 0xa222, 
0xb333, 0xb333, 0xb333, 0xb333, 0xb333, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xb333, 0xb333, 0xb333, 0xb333, 0xb333, 
0xc444, 0xc444, 0xc444, 0xc444, 0xc444, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xc444, 0xc444, 0xc444, 0xc444, 0xc444, 
0xd555, 0xd555, 0xd555, 0xd555, 0xc444, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xc444, 0xd555, 0xd555, 0xd555, 0xd555, 
0xe666, 0xe666, 0xe666, 0xd555, 0xc444, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xc444, 0xd555, 0xe666, 0xe666, 0xe666, 
0xf777, 0xf777, 0xe666, 0xd555, 0xc444, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xc444, 0xd555, 0xe666, 0xf777, 0xf777, 
0xffff, 0xf777, 0xe666, 0xd555, 0xc444, 0xb333, 0xa222, 0x9111, 0x8000, 0x6eef, 0x5dde, 0x4ccd, 0x3bbc, 0x2aab, 0x199a, 0x0889, 0x0889, 0x199a, 0x2aab, 0x3bbc, 0x4ccd, 0x5dde, 0x6eef, 0x8000, 0x9111, 0xa222, 0xb333, 0xc444, 0xd555, 0xe666, 0xf777, 0xffff, 
};