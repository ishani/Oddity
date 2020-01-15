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

const uint16_t pcf_webbing[32 * 32] __IN_FLASH__ = {
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1b1b, 0xb4b5, 0x2323, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1d1d, 0xbabb, 0x2525, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0606, 0x5050, 0xa9aa, 0x1e1e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1616, 0x9a9b, 0x1d1d, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1d1d, 0xa1a2, 0x1e1e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1f1f, 0xa1a2, 0x1e1e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1313, 0x8d8e, 0x2727, 0x0101, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0303, 0x3b3b, 0x9091, 0x1919, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1717, 0x9fa0, 0x1e1e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0f0f, 0x898a, 0x6969, 0x0d0d, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1212, 0x8283, 0xa8a9, 0x2121, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1717, 0xa4a5, 0x1f1f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0707, 0x2b2b, 0xc9ca, 0xdbdc, 0x4141, 0x1515, 0x0505, 0x0000, 0x0404, 0x1818, 0x5e5e, 0xdadb, 0xe2e3, 0x7272, 0x1b1b, 0x0808, 0x0000, 0x0000, 0x0000, 0x0101, 0x2929, 0xc8c9, 0x2f2f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x1a1a, 0x1414, 0x0c0c, 0x1b1b, 0x5656, 0xa7a8, 0x9091, 0x7a7a, 0xa3a4, 0x9e9f, 0x4646, 0x2828, 0x4747, 0x9a9b, 0x7777, 0x3333, 0x3030, 0x6868, 0x9697, 0x5a5a, 0x2222, 0x1b1b, 0x1919, 0x2828, 0x9596, 0xf7f8, 0x8f90, 0x2020, 0x0e0e, 0x0808, 0x1616, 0x1c1c, 
  0x9596, 0x9293, 0x8a8b, 0xaeaf, 0x7e7e, 0x2929, 0x1111, 0x0c0c, 0x1d1d, 0x3030, 0xa0a1, 0xeced, 0xb3b4, 0x3131, 0x1111, 0x0101, 0x0000, 0x0e0e, 0x2121, 0x7777, 0xd1d2, 0xcacb, 0xaeaf, 0x9697, 0x5b5b, 0x4646, 0x8081, 0xacad, 0x8e8f, 0x7070, 0xa1a2, 0xacad, 
  0x1b1b, 0x4e4e, 0xe8e9, 0x5757, 0x1313, 0x0101, 0x0000, 0x0000, 0x0000, 0x0101, 0x2f2f, 0xc9ca, 0x3c3c, 0x0202, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2020, 0xb4b5, 0xbabb, 0x3535, 0x1a1a, 0x0a0a, 0x0000, 0x1111, 0x2929, 0x9fa0, 0xf2f3, 0x6767, 0x2222, 
  0x0000, 0x1919, 0xa2a3, 0x2020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1717, 0xa5a6, 0x1e1e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1515, 0x9e9f, 0x4444, 0x0404, 0x0000, 0x0000, 0x0000, 0x0000, 0x0101, 0x3737, 0xc6c7, 0x2929, 0x0000, 
  0x0000, 0x1111, 0x7a7a, 0x1616, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1919, 0xaaab, 0x2c2c, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1717, 0x9c9d, 0x1e1e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1e1e, 0xa3a4, 0x1e1e, 0x0000, 
  0x0000, 0x0f0f, 0x7474, 0x1515, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1c1c, 0xc8c9, 0x9b9c, 0x2222, 0x0404, 0x0000, 0x0000, 0x0000, 0x0000, 0x1616, 0x9b9c, 0x1d1d, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0101, 0x2929, 0x9697, 0x1b1b, 0x0000, 
  0x0000, 0x0f0f, 0x7878, 0x1616, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0202, 0x3737, 0xd7d8, 0xc1c2, 0x9495, 0x3636, 0x1111, 0x0303, 0x0000, 0x0000, 0x1f1f, 0x9b9c, 0x1d1d, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0404, 0x3838, 0x9091, 0x1919, 0x0000, 
  0x0000, 0x1515, 0x9495, 0x1b1b, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1818, 0x9495, 0x4646, 0x2121, 0x2323, 0x6565, 0x7878, 0x2d2d, 0x1818, 0x1b1b, 0x7c7c, 0x8586, 0x1313, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0707, 0x5454, 0x9394, 0x1818, 0x0000, 
  0x1717, 0x4141, 0xe0e1, 0x4444, 0x0404, 0x0000, 0x0000, 0x0000, 0x0909, 0x5e5e, 0x6f6f, 0x0f0f, 0x0000, 0x0101, 0x0f0f, 0x2020, 0x7777, 0xaaab, 0xb4b5, 0xf2f3, 0x9596, 0x1212, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1d1d, 0xa3a4, 0xc1c2, 0x2424, 0x0000, 
  0xa7a8, 0xb1b2, 0xc1c2, 0xc2c3, 0x4b4b, 0x1515, 0x0101, 0x0303, 0x3131, 0xa5a6, 0x2626, 0x0101, 0x0000, 0x0000, 0x0000, 0x0101, 0x1414, 0x4d4d, 0xf3f4, 0xfdfe, 0xe8e9, 0x5959, 0x1b1b, 0x0808, 0x0000, 0x0e0e, 0x2525, 0x9192, 0xe3e4, 0xebec, 0x7070, 0x1717, 
  0x2929, 0x2222, 0x1d1d, 0x3838, 0x9fa0, 0x9a9b, 0x3737, 0x3b3b, 0xc8c9, 0xa5a6, 0x1d1d, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0101, 0x3434, 0xd8d9, 0x7474, 0x5353, 0x9b9c, 0xb0b1, 0x6565, 0x3737, 0x8384, 0xb0b1, 0x6464, 0x2f2f, 0x3b3b, 0x999a, 0x9596, 
  0x0000, 0x0000, 0x0000, 0x0202, 0x1e1e, 0x6e6e, 0xedee, 0xc6c7, 0x9e9f, 0xb6b7, 0x6c6c, 0x1919, 0x0909, 0x0000, 0x0000, 0x0000, 0x1717, 0x8f90, 0x4848, 0x0808, 0x0303, 0x1a1a, 0x3434, 0xbcbd, 0xf6f7, 0x9697, 0x2929, 0x0b0b, 0x0000, 0x0101, 0x1e1e, 0x6262, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2424, 0xcbcc, 0x4141, 0x1414, 0x2020, 0x4545, 0x7c7c, 0x5454, 0x1818, 0x0d0d, 0x1111, 0x6464, 0x6a6a, 0x0e0e, 0x0000, 0x0000, 0x0000, 0x0202, 0x3a3a, 0xdbdc, 0x3737, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0b0b, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1616, 0x9fa0, 0x1d1d, 0x0000, 0x0000, 0x0707, 0x1919, 0x4a4a, 0x8687, 0x7b7b, 0x8586, 0xa4a5, 0x2222, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1919, 0xadae, 0x2121, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1515, 0x9495, 0x1c1c, 0x0000, 0x0000, 0x0000, 0x0000, 0x0909, 0x1d1d, 0x7f7f, 0xf2f3, 0x5151, 0x0202, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1717, 0xa1a2, 0x1e1e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0101, 0x2020, 0x8c8d, 0x1919, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2424, 0xbabb, 0x2525, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1717, 0xa0a1, 0x1e1e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0808, 0x5454, 0x7070, 0x1111, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1212, 0x9192, 0x3737, 0x0202, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1919, 0xadae, 0x2121, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x1c1c, 0xa5a6, 0x8081, 0x1111, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1e1e, 0x9fa0, 0x9798, 0x2222, 0x0101, 0x0000, 0x0000, 0x0000, 0x0202, 0x3a3a, 0xdedf, 0x3f3f, 0x0808, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x1a1a, 0x1111, 0x0c0c, 0x1d1d, 0x7777, 0xe8e9, 0xdbdc, 0x4545, 0x1313, 0x0202, 0x0000, 0x0000, 0x0c0c, 0x2121, 0x8a8b, 0xd3d4, 0xd6d7, 0x9e9f, 0x2c2c, 0x0e0e, 0x0202, 0x1111, 0x3232, 0xc2c3, 0xf5f6, 0xc6c7, 0x5e5e, 0x1d1d, 0x1818, 0x0e0e, 0x1212, 0x1d1d, 
  0xadae, 0x8e8f, 0x8384, 0xb0b1, 0x7a7a, 0x3636, 0x4242, 0x9697, 0x9293, 0x3131, 0x1d1d, 0x2525, 0x7272, 0xa1a2, 0x5454, 0x2929, 0x2929, 0x5050, 0xacad, 0x8687, 0x4949, 0x9293, 0xadae, 0x5959, 0x3434, 0x3636, 0x7c7c, 0xaaab, 0xaeaf, 0x9091, 0x9fa0, 0xbcbd, 
  0x2626, 0x8283, 0xe1e2, 0x4848, 0x0f0f, 0x0000, 0x0202, 0x1a1a, 0x4040, 0xb5b6, 0xd9da, 0xd3d4, 0x6e6e, 0x2323, 0x0808, 0x0000, 0x0000, 0x0606, 0x2a2a, 0xabac, 0xf5f6, 0x7e7e, 0x2424, 0x0606, 0x0000, 0x0101, 0x1313, 0x2020, 0x4646, 0xe4e5, 0xcfd0, 0x3b3b, 
  0x0000, 0x2020, 0x9c9d, 0x1c1c, 0x0000, 0x0000, 0x0000, 0x0000, 0x0404, 0x3a3a, 0xe4e5, 0x7676, 0x1212, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0101, 0x3737, 0xd7d8, 0x3232, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1919, 0xb2b3, 0x6b6b, 0x0a0a, 
  0x0000, 0x0e0e, 0x7474, 0x1515, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1919, 0xb3b4, 0x2929, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1919, 0xafb0, 0x2121, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1818, 0xa5a6, 0x2727, 0x0000, 
  0x0000, 0x0e0e, 0x6d6d, 0x1414, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1414, 0x9495, 0x2d2d, 0x0101, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1919, 0xa7a8, 0x2020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1818, 0xa6a7, 0x2020, 0x0000, 
  0x0101, 0x1b1b, 0x6868, 0x1212, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0f0f, 0x7e7e, 0x4545, 0x0707, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1d1d, 0xa1a2, 0x1e1e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1818, 0xa6a7, 0x2020, 0x0000, 
  0x0303, 0x3131, 0x7a7a, 0x1515, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0c0c, 0x6a6a, 0x6060, 0x0d0d, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0202, 0x3636, 0xa3a4, 0x1e1e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1a1a, 0xadae, 0x2222, 0x0000, 
  0x0505, 0x4e4e, 0xb7b8, 0x2222, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0909, 0x5d5d, 0x7d7d, 0x1414, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0a0a, 0x6e6e, 0xbbbc, 0x2121, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2f2f, 0xcacb, 0x2828, 0x0000, 
};