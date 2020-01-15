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
    function rays(x, y, v1, v2, v3, f1, f2, f3) 
    { 
        var a2 = Math.atan2((15.5 - x), (15.5 - y))
        var ptb = noise.perlin2(f2 + a2 * (1.0 + f1), 12.12 + (f3 * 4.2) ) * 1.2

        var f = (1.0 + (ptb)) * 0.5;
        if (f < 0.5) {
            f = 1.0 - f;
            f *= 1.2;
        }
        var final = (f - 0.5) * 2.0;

        return Math.abs(final)
    }

    function sample(x, y, v1, v2, v3, f1, f2, f3) 
    { 
        var off = 418 + (2.0 * f3)
        var r = rays(off, x,y,v1,v2,v3,f1,f2,f3)
        var r1 = rays(off, x,y,v1,v2,v3,f1,f2 + 0.04,f3)
        var r2 = rays(off, x,y,v1,v2,v3,f1,f2 + 0.12,f3)
        var r3 = rays(off, x,y,v1,v2,v3,f1,f2 - 0.12,f3)
        var r4 = rays(off, x,y,v1,v2,v3,f1,f2 - 0.04,f3)
        var t = ((r * 1.2) + r1 + r2 + r3 + r4) * 0.21

        return t
    }
*/


const uint16_t pcf_rays_1[32 * 32] __IN_FLASH__ = {
0x1e9a, 0x26f7, 0x2fdb, 0x38e8, 0x4187, 0x48ea, 0x4e1c, 0x5020, 0x4e26, 0x47c8, 0x3d45, 0x2fa2, 0x2078, 0x1e16, 0x20e2, 0x38a5, 0x430f, 0x3a3d, 0x284d, 0x2eaf, 0x3c24, 0x5528, 0x6a3a, 0x794d, 0x8190, 0x8338, 0x7f3b, 0x76f7, 0x6be4, 0x5f0b, 0x5143, 0x4305, 
0x215d, 0x1e9a, 0x2790, 0x311b, 0x3ac0, 0x43ba, 0x4b01, 0x4f62, 0x4fb5, 0x4b2e, 0x41b2, 0x341c, 0x242d, 0x1fbc, 0x215d, 0x388c, 0x4303, 0x2f52, 0x1f8e, 0x287a, 0x4427, 0x5dc1, 0x71ce, 0x7e6f, 0x8349, 0x812a, 0x7996, 0x6e5b, 0x60e3, 0x523b, 0x4305, 0x3ea5, 
0x1bff, 0x20ff, 0x1e9a, 0x2841, 0x328b, 0x3cd6, 0x461d, 0x4d07, 0x5016, 0x4dfe, 0x4621, 0x3900, 0x286a, 0x21a6, 0x21e6, 0x386d, 0x385a, 0x2fd8, 0x231f, 0x2f9b, 0x4d1f, 0x66bc, 0x78dd, 0x820f, 0x82ae, 0x7c4c, 0x7115, 0x62fb, 0x5357, 0x4305, 0x3e1c, 0x3612, 
0x2208, 0x1b40, 0x2092, 0x1e9a, 0x290f, 0x3436, 0x3f33, 0x48a8, 0x4ecc, 0x4fc9, 0x4a4c, 0x3e3f, 0x2d43, 0x1a5a, 0x17fa, 0x3845, 0x389c, 0x305c, 0x2752, 0x37f9, 0x5706, 0x6fc4, 0x7ec6, 0x8361, 0x7ef9, 0x7418, 0x6560, 0x54a0, 0x4305, 0x3d7b, 0x34bf, 0x387a, 
0x2e16, 0x218f, 0x1a65, 0x2014, 0x1e9a, 0x2a03, 0x362a, 0x41e2, 0x4b44, 0x4ff5, 0x4dc6, 0x43ae, 0x32ca, 0x1e78, 0x1988, 0x3811, 0x38e4, 0x30d5, 0x2c49, 0x41c4, 0x61b6, 0x7842, 0x829a, 0x8162, 0x7765, 0x6821, 0x5620, 0x4305, 0x3cbe, 0x332d, 0x3828, 0x4805, 
0x3be4, 0x2e74, 0x2100, 0x1965, 0x1f80, 0x1e9a, 0x2b26, 0x387b, 0x44e6, 0x4dbc, 0x4fe1, 0x48f5, 0x3900, 0x2365, 0x1b5e, 0x37ce, 0x3933, 0x2539, 0x322a, 0x4d1f, 0x6cc8, 0x7f39, 0x8310, 0x7af0, 0x6b50, 0x57e7, 0x4305, 0x3bdb, 0x314a, 0x37b4, 0x4ac6, 0x62e4, 
0x49b9, 0x3d1d, 0x3a2d, 0x2da8, 0x1838, 0x1ed0, 0x1e9a, 0x2c89, 0x3b3f, 0x4839, 0x4fa0, 0x4d70, 0x3fca, 0x2955, 0x1d96, 0x2cec, 0x3988, 0x27be, 0x312c, 0x5a02, 0x775e, 0x8320, 0x7e8a, 0x6f03, 0x5a0b, 0x4305, 0x3ac7, 0x2ef9, 0x452a, 0x5a76, 0x69e4, 0x824a, 
0x4d08, 0x4b99, 0x3e2a, 0x3bbc, 0x2e26, 0x2224, 0x1dfa, 0x1e9a, 0x2e43, 0x3e95, 0x4bb2, 0x4ffd, 0x46bf, 0x307e, 0x2057, 0x2cf9, 0x39df, 0x20ae, 0x3dab, 0x6808, 0x7fd8, 0x81bb, 0x7350, 0x5ca9, 0x4305, 0x396f, 0x388a, 0x4875, 0x6212, 0x71a8, 0x8ed0, 0x9f93, 
0x4b31, 0x4ce6, 0x4ce3, 0x4ab5, 0x3d42, 0x396d, 0x216e, 0x1cf2, 0x1e9a, 0x3075, 0x429b, 0x4ecc, 0x4ce2, 0x3900, 0x1a5a, 0x2cf7, 0x3a32, 0x2752, 0x4d1f, 0x75f0, 0x8361, 0x7843, 0x5ff0, 0x4305, 0x37b6, 0x380e, 0x570c, 0x6ad2, 0x8865, 0x9c83, 0xac16, 0xb7b9, 
0x3eab, 0x3fa9, 0x4b00, 0x4cf6, 0x4c97, 0x3e78, 0x3b79, 0x2d89, 0x1ba3, 0x1e9a, 0x3358, 0x475e, 0x5019, 0x4297, 0x21a6, 0x2cde, 0x3a6d, 0x3017, 0x5f87, 0x80bc, 0x7da6, 0x6423, 0x4305, 0x356f, 0x4469, 0x60b9, 0x74c3, 0x984a, 0xab0a, 0xb879, 0xc196, 0xc752, 
0x264e, 0x32a9, 0x3df2, 0x3f7b, 0x4abb, 0x4d09, 0x4bfe, 0x3d7e, 0x2e46, 0x19ea, 0x1e9a, 0x3746, 0x4c8a, 0x4bcd, 0x2b93, 0x2070, 0x3a62, 0x3509, 0x7346, 0x825b, 0x69a9, 0x4305, 0x3247, 0x495c, 0x6c65, 0x9222, 0xa991, 0xb977, 0xc373, 0xc907, 0xcb6d, 0xcb94, 
0x2835, 0x22e0, 0x2942, 0x32d2, 0x326b, 0x3f19, 0x3fb5, 0x4d1b, 0x4ab5, 0x3af3, 0x2271, 0x1e9a, 0x3cd6, 0x5016, 0x3900, 0x21e6, 0x2fd8, 0x4d1f, 0x820f, 0x7115, 0x4305, 0x38b5, 0x5e21, 0x8865, 0xa75e, 0xbad6, 0xc5bc, 0xcab0, 0xcbb3, 0xca32, 0xc724, 0xc32f, 
0x32a2, 0x2c12, 0x30d8, 0x2b08, 0x2473, 0x2942, 0x32c9, 0x3e3b, 0x3fc4, 0x4d21, 0x3dee, 0x2100, 0x1e9a, 0x44e6, 0x48f5, 0x1b5e, 0x2539, 0x6cc8, 0x7af0, 0x4305, 0x37b4, 0x6fa5, 0xa3b6, 0xbcd9, 0xc874, 0xcbb8, 0xca32, 0xc614, 0xc0b1, 0xbaca, 0xb4cf, 0xaefc, 
0x4f46, 0x4a40, 0x4480, 0x3de4, 0x3642, 0x2d70, 0x2fbd, 0x272e, 0x2942, 0x3290, 0x3fbd, 0x4ce3, 0x396d, 0x1e9a, 0x4ecc, 0x1a5a, 0x2752, 0x8361, 0x4305, 0x570c, 0x9c83, 0xc010, 0xcb27, 0xca32, 0xc406, 0xbbfd, 0xb3a0, 0xab9f, 0xa43c, 0x9d88, 0x977f, 0x9214, 
0x6bbb, 0x68e6, 0x659b, 0x61bc, 0x5d21, 0x5795, 0x50cf, 0x486c, 0x3de4, 0x3085, 0x2d0d, 0x2942, 0x3f19, 0x4ab5, 0x1e9a, 0x3900, 0x4d1f, 0x4305, 0x8865, 0xc5bc, 0xca32, 0xbec1, 0xb0e6, 0xa43c, 0x9970, 0x9066, 0x88d7, 0x8278, 0x7d0e, 0x786a, 0x7466, 0x70e4, 
0x8478, 0x83b6, 0x82d5, 0x81cd, 0x8093, 0x7f16, 0x7d41, 0x7af1, 0x77f0, 0x73e4, 0x6e2f, 0x659b, 0x5795, 0x3de4, 0x2942, 0x1e9a, 0x4305, 0xca32, 0xa43c, 0x88d7, 0x786a, 0x6dce, 0x5d83, 0x59dc, 0x5713, 0x54e3, 0x531e, 0x51aa, 0x5071, 0x4f68, 0x4e83, 0x4dbc, 
0x96af, 0x972d, 0x97bb, 0x985c, 0x9914, 0x99e7, 0x9adc, 0x9bfb, 0x9d4e, 0x9ee1, 0xa0c2, 0xa2f7, 0xa568, 0xa7d2, 0xac75, 0x641a, 0xfa1c, 0x2787, 0x3208, 0x290a, 0x2c23, 0x2996, 0x2781, 0x25d7, 0x2480, 0x2368, 0x2280, 0x2ce7, 0x2cd8, 0x2ccb, 0x2cbe, 0x2cb2, 
0xa175, 0xa232, 0xa2f7, 0xa3c3, 0xa495, 0xa568, 0xa639, 0xa705, 0xa7d2, 0xa8ba, 0xaa0a, 0xac75, 0xb058, 0xaca9, 0x641a, 0x6a8b, 0xd112, 0xfa1c, 0x88ba, 0x334f, 0x2787, 0x31d1, 0x3399, 0x3208, 0x2f3e, 0x2c1f, 0x290a, 0x2624, 0x237c, 0x2c23, 0x2b3e, 0x2a63, 
0xa662, 0xa6dd, 0xa756, 0xa7d2, 0xa857, 0xa8f1, 0xa9b8, 0xaad1, 0xac75, 0xaebc, 0xb0f7, 0xaf97, 0x9e9a, 0x641a, 0x39f3, 0x483f, 0xa2a3, 0xfbf4, 0xfa1c, 0xbd63, 0x6b4f, 0x33d4, 0x2cbc, 0x2787, 0x2f30, 0x329e, 0x339d, 0x3336, 0x3208, 0x306e, 0x2ea1, 0x2cc0, 
0xa895, 0xa90a, 0xa997, 0xaa4b, 0xab39, 0xac75, 0xae08, 0xafcc, 0xb124, 0xb051, 0xa92a, 0x9373, 0x641a, 0x2b9d, 0x6894, 0x3510, 0x8bea, 0xe7fa, 0xffe9, 0xfa1c, 0xd37f, 0x9b05, 0x64c1, 0x42e3, 0x2922, 0x2e60, 0x2787, 0x2d89, 0x310d, 0x32e1, 0x3393, 0x3382, 
0xaaac, 0xab78, 0xac75, 0xada8, 0xaf03, 0xb058, 0xb135, 0xb09d, 0xaca9, 0xa1f8, 0x8b7c, 0x641a, 0x2c4b, 0x49e5, 0x6a8b, 0x2973, 0x7f53, 0xd112, 0xf8dd, 0xffff, 0xfa1c, 0xdeb0, 0xb475, 0x88ba, 0x6137, 0x4486, 0x334f, 0x2bf1, 0x2f13, 0x2787, 0x2c73, 0x2fbc, 
0xad6d, 0xae82, 0xafa4, 0xb0a8, 0xb13b, 0xb0c5, 0xae3c, 0xa7f4, 0x9b76, 0x85b0, 0x641a, 0x3751, 0x2c51, 0x64ba, 0x6121, 0x21aa, 0x777b, 0xbdb2, 0xec99, 0xfdb9, 0xffff, 0xfa1c, 0xe52e, 0xc49b, 0xa029, 0x73ef, 0x5f00, 0x4594, 0x339c, 0x29c8, 0x2d50, 0x2f73, 
0xb00f, 0xb0d8, 0xb13e, 0xb0dd, 0xaf14, 0xaaf4, 0xa323, 0x95e5, 0x8153, 0x641a, 0x3ec4, 0x27b7, 0x4c8e, 0x6c00, 0x4db5, 0x23b4, 0x722a, 0xae79, 0xde98, 0xf759, 0xff77, 0xffff, 0xfa1c, 0xe954, 0xcf67, 0xb102, 0x9275, 0x6eec, 0x5d7d, 0x4650, 0x33c2, 0x32fc, 
0xb13f, 0xb0ec, 0xaf97, 0xaca9, 0xa759, 0x9e9a, 0x9133, 0x7df1, 0x641a, 0x441f, 0x2ef1, 0x39f3, 0x6284, 0x6a8b, 0x483f, 0x250b, 0x6e56, 0xa2a3, 0xd112, 0xee88, 0xfbf4, 0xffff, 0xfff2, 0xfa1c, 0xec2c, 0xd6f7, 0xbd63, 0xa293, 0x88ba, 0x6b4f, 0x5c63, 0x46db, 
0xafec, 0xadbb, 0xa9e3, 0xa3bb, 0x9a78, 0x8d3c, 0x7b3f, 0x641a, 0x4827, 0x3458, 0x2d15, 0x4ddb, 0x6a5e, 0x655e, 0x387b, 0x25fa, 0x6b74, 0x9957, 0xc4ec, 0xe4a1, 0xf677, 0xfe24, 0xffff, 0xff9c, 0xfa1c, 0xee3b, 0xdc79, 0xc6b4, 0xaf2f, 0x97ba, 0x8182, 0x6895, 
0xab88, 0xa6fb, 0xa042, 0x96c2, 0x89de, 0x790e, 0x641a, 0x4b4a, 0x2f83, 0x2643, 0x45e7, 0x6120, 0x6c31, 0x5eef, 0x36bc, 0x26a8, 0x6934, 0x91ed, 0xba56, 0xda9f, 0xef96, 0xfaa2, 0xff46, 0xffff, 0xff49, 0xfa1c, 0xefc7, 0xe09f, 0xcdde, 0xb92b, 0xa3fa, 0x8f5a, 
0xa416, 0x9d00, 0x9373, 0x86fa, 0x773d, 0x641a, 0x4dcc, 0x34fa, 0x2b9d, 0x38b5, 0x4e9d, 0x6894, 0x6a8b, 0x4ecc, 0x3510, 0x272a, 0x6768, 0x8bea, 0xb137, 0xd112, 0xe7fa, 0xf5e3, 0xfcf5, 0xffe9, 0xffff, 0xfefd, 0xfa1c, 0xf0fb, 0xe3d6, 0xd37f, 0xc12f, 0xae0e, 
0x99fb, 0x907e, 0x847c, 0x75b5, 0x641a, 0x4fd9, 0x3970, 0x2ff2, 0x2d71, 0x484a, 0x602e, 0x6bbf, 0x670c, 0x4b82, 0x28be, 0x278e, 0x65ef, 0x86f6, 0xa962, 0xc83c, 0xe027, 0xf040, 0xf9a3, 0xfe52, 0xffff, 0xffff, 0xfeb6, 0xfa1c, 0xf1f1, 0xe662, 0xd800, 0xc7b3, 
0x8dda, 0x824f, 0x7467, 0x641a, 0x518e, 0x3d24, 0x3389, 0x2580, 0x39f3, 0x4f1d, 0x6709, 0x6c0e, 0x62ad, 0x483f, 0x292b, 0x1d5a, 0x64b5, 0x82d3, 0xa2a3, 0xc032, 0xd873, 0xea18, 0xf57b, 0xfbf4, 0xff2a, 0xffff, 0xffff, 0xfe76, 0xfa1c, 0xf2ba, 0xe871, 0xdbaa, 
0x8067, 0x7347, 0x641a, 0x5300, 0x4043, 0x2c4b, 0x29bf, 0x2bd1, 0x49e5, 0x5f7f, 0x6abd, 0x6a8b, 0x5dfd, 0x4525, 0x2973, 0x1e0b, 0x63ab, 0x7f53, 0x9ccd, 0xb8f2, 0xd112, 0xe3b6, 0xf0b5, 0xf8dd, 0xfd71, 0xffb6, 0xffff, 0xffff, 0xfe3c, 0xfa1c, 0xf361, 0xea23, 
0x724c, 0x641a, 0x543c, 0x42ee, 0x3082, 0x2d57, 0x2da6, 0x3ac0, 0x4f77, 0x65c5, 0x6c21, 0x67ed, 0x4f41, 0x3821, 0x1fa7, 0x1ea1, 0x62c7, 0x7c54, 0x97b9, 0xb270, 0xca22, 0xdd53, 0xeb8b, 0xf52d, 0xfb1e, 0xfe6d, 0xffff, 0xffff, 0xffff, 0xfe07, 0xfa1c, 0xf3ed, 
0x641a, 0x554e, 0x453c, 0x3425, 0x306e, 0x2507, 0x391f, 0x4b0b, 0x5efa, 0x69a1, 0x6be4, 0x64af, 0x4ced, 0x3714, 0x20be, 0x1f21, 0x6202, 0x79bd, 0x9348, 0xac98, 0xc3ab, 0xd714, 0xe62d, 0xf10a, 0xf841, 0xfca7, 0xff19, 0xffff, 0xffff, 0xffdd, 0xfdd6, 0xfa1c, 
};

// -2, -20, 12
const uint16_t pcf_rays_2[32 * 32] __IN_FLASH__ = {
0x7d74, 0x8796, 0x9132, 0x99c3, 0xa0a6, 0xa524, 0xa67d, 0xa401, 0x9d2d, 0x91d2, 0x8236, 0x6f26, 0x59e5, 0x43ea, 0x2e60, 0x2ac2, 0x2dd2, 0x4052, 0x5d6c, 0x7fc3, 0x9a00, 0xb1b1, 0xc53e, 0xd39f, 0xdc73, 0xdfea, 0xde9f, 0xd966, 0xd129, 0xc6ca, 0xbb11, 0xaea5, 
0x7280, 0x7d74, 0x8845, 0x9274, 0x9b59, 0xa229, 0xa600, 0xa5f6, 0xa145, 0x9777, 0x8898, 0x755d, 0x5f25, 0x47b3, 0x3091, 0x2b26, 0x2dc4, 0x4cba, 0x60b6, 0x863b, 0xa1b5, 0xb9aa, 0xcc5d, 0xd8e1, 0xdf19, 0xdf8e, 0xdb2e, 0xd311, 0xc851, 0xbbe8, 0xaea5, 0xa128, 
0x6638, 0x71b1, 0x7d74, 0x890e, 0x93df, 0x9d12, 0xa3a6, 0xa67c, 0xa47d, 0x9cd6, 0x8f3c, 0x7c30, 0x6519, 0x4c0d, 0x3317, 0x2b9a, 0x2db3, 0x4edf, 0x647f, 0x8d92, 0xaa2f, 0xc1fd, 0xd330, 0xdd17, 0xe001, 0xdcea, 0xd523, 0xca09, 0xbcdd, 0xaea5, 0xa029, 0x91f9, 
0x58ca, 0x646e, 0x70c3, 0x7d74, 0x89f5, 0x957a, 0x9eee, 0xa505, 0xa652, 0xa18e, 0x95f1, 0x839a, 0x6bdb, 0x511c, 0x360a, 0x2c22, 0x2da0, 0x5164, 0x74f9, 0x95ed, 0xb36d, 0xca70, 0xd93f, 0xdfa0, 0xde7b, 0xd75b, 0xcbfb, 0xbdf7, 0xaea5, 0x9f03, 0x8fc2, 0x814e, 
0x4a79, 0x55e4, 0x6259, 0x6fab, 0x7d74, 0x8b03, 0x974d, 0xa0e7, 0xa616, 0xa50e, 0x9c5e, 0x8b86, 0x7387, 0x570a, 0x3984, 0x2cc2, 0x2d8b, 0x5463, 0x7c40, 0x9f6d, 0xbd55, 0xd297, 0xddda, 0xdfa5, 0xd9b2, 0xce31, 0xbf41, 0xaea5, 0x9da9, 0x8d2d, 0x7db2, 0x656b, 
0x3b92, 0x4669, 0x5285, 0x5fe6, 0x6e5f, 0x7d74, 0x8c42, 0x9963, 0xa2ea, 0xa684, 0xa1ef, 0x93b7, 0x7c30, 0x5e0b, 0x3daf, 0x2d82, 0x2d74, 0x57ff, 0x84df, 0xaa2f, 0xc7a1, 0xd9bd, 0xdffc, 0xdc0f, 0xd0b5, 0xc0c6, 0xaea5, 0x9c0f, 0x8a24, 0x797f, 0x61dc, 0x5851, 
0x2c5d, 0x3657, 0x41b2, 0x4e8e, 0x5cfc, 0x6ccf, 0x7d74, 0x8dbf, 0x9bc4, 0xa4ce, 0xa5b2, 0x9baf, 0x85d2, 0x6662, 0x42c3, 0x2e6e, 0x2d58, 0x5c6b, 0x8f28, 0xb632, 0xd1b8, 0xdeba, 0xde3d, 0xd392, 0xc297, 0xaea5, 0x9a21, 0x8684, 0x748e, 0x5db7, 0x53b7, 0x40e8, 
0x2bce, 0x3199, 0x304f, 0x3c2c, 0x49d6, 0x5973, 0x6ae3, 0x7d74, 0x8f8f, 0x9e74, 0xa636, 0xa276, 0x9032, 0x7058, 0x4914, 0x2f95, 0x3aed, 0x61ea, 0x9b7b, 0xc332, 0xda6d, 0xdfc6, 0xd6ca, 0xc4cc, 0xaea5, 0x97c1, 0x8220, 0x64dd, 0x58d9, 0x4e70, 0x3e0d, 0x2ead, 
0x21aa, 0x26f5, 0x2ce9, 0x2953, 0x35a2, 0x4424, 0x5518, 0x6879, 0x7d74, 0x91ce, 0xa167, 0xa652, 0x9a96, 0x7c30, 0x511c, 0x3111, 0x3bfe, 0x74f9, 0xaa2f, 0xd053, 0xdfa0, 0xda4a, 0xc788, 0xaea5, 0x94c5, 0x7cb5, 0x5fde, 0x5318, 0x3f84, 0x2e83, 0x2f82, 0x27f7, 
0x3501, 0x298c, 0x2148, 0x2764, 0x2e64, 0x2dd0, 0x3d28, 0x4f9c, 0x655b, 0x7d74, 0x94a6, 0xa45c, 0xa33f, 0x89e8, 0x5b93, 0x330e, 0x3d6e, 0x81d4, 0xbb4f, 0xdb73, 0xddbb, 0xcafa, 0xaea5, 0x90e8, 0x75de, 0x59b7, 0x4193, 0x3be0, 0x2f6c, 0x2851, 0x2d77, 0x325d, 
0x428d, 0x35c2, 0x354f, 0x28e7, 0x2bbf, 0x27fc, 0x307e, 0x346d, 0x4884, 0x612d, 0x7d74, 0x984f, 0xa669, 0x9892, 0x6982, 0x2c75, 0x3f74, 0x9305, 0xcdc4, 0xdff4, 0xcf69, 0xaea5, 0x8bb9, 0x63b5, 0x5209, 0x3d4a, 0x2f50, 0x28cc, 0x2ed3, 0x3484, 0x310e, 0x38e4, 
0x4658, 0x459a, 0x4442, 0x4215, 0x359d, 0x27fc, 0x2b6d, 0x28dc, 0x2953, 0x3f0c, 0x5b4e, 0x7d74, 0x9d12, 0xa47d, 0x7c30, 0x3317, 0x4edf, 0xaa2f, 0xdd17, 0xd523, 0xaea5, 0x846f, 0x5b61, 0x3f84, 0x2f27, 0x297c, 0x30c1, 0x2d53, 0x3736, 0x400a, 0x47f3, 0x4f0f, 
0x55ad, 0x54be, 0x5343, 0x4691, 0x45de, 0x4442, 0x4145, 0x3535, 0x2aec, 0x2a45, 0x31e6, 0x5285, 0x7d74, 0xa2ea, 0x93b7, 0x3daf, 0x57ff, 0xc7a1, 0xdc0f, 0xaea5, 0x797f, 0x4fd4, 0x2eea, 0x2a8f, 0x33b9, 0x3481, 0x400a, 0x4a0f, 0x52cd, 0x5a74, 0x612c, 0x6718, 
0x55d9, 0x5640, 0x567d, 0x5678, 0x560a, 0x54f7, 0x52e2, 0x463c, 0x4442, 0x35b4, 0x2a06, 0x2ce9, 0x4424, 0x7d74, 0xa652, 0x511c, 0x74f9, 0xdfa0, 0xaea5, 0x5fde, 0x2e83, 0x2c75, 0x2f65, 0x400a, 0x4db2, 0x5900, 0x626a, 0x6a4f, 0x70fc, 0x76ab, 0x7b8c, 0x7fc5, 
0x45c1, 0x50e8, 0x51d4, 0x52cc, 0x53cb, 0x54c9, 0x55b0, 0x565a, 0x5678, 0x556a, 0x51de, 0x4442, 0x27fc, 0x2953, 0x7d74, 0x7c30, 0xaa2f, 0xaea5, 0x3f84, 0x30c1, 0x400a, 0x5577, 0x6533, 0x70fc, 0x7a00, 0x810d, 0x86ac, 0x8b3d, 0x8f01, 0x9228, 0x94d4, 0x971d, 
0x4151, 0x418a, 0x41ca, 0x4213, 0x4265, 0x42c3, 0x432e, 0x43aa, 0x4439, 0x44db, 0x4588, 0x51d4, 0x54c9, 0x5678, 0x4442, 0x7d74, 0xaea5, 0x400a, 0x70fc, 0x86ac, 0x9228, 0x9917, 0x9dad, 0xa0e9, 0xa34d, 0xa524, 0xa698, 0xa7c5, 0xa8be, 0xa98f, 0xaa40, 0xaad9, 
0x25e3, 0x260b, 0x2637, 0x266a, 0x26a5, 0x26e9, 0x2738, 0x2797, 0x2808, 0x1dd3, 0x1fdf, 0x22b3, 0x26c4, 0x251c, 0x3659, 0x551e, 0x1c51, 0xa012, 0xbbaf, 0xc047, 0xc06c, 0xbf91, 0xbe8a, 0xbd8f, 0xbcaf, 0xbbea, 0xbb3d, 0xbaa6, 0xba22, 0xb9ac, 0xb944, 0xb8e7, 
0x20b6, 0x21a6, 0x22b3, 0x23e3, 0x253c, 0x26c4, 0x2881, 0x209f, 0x251c, 0x2a6e, 0x307a, 0x3659, 0x3839, 0x2885, 0x551e, 0xd896, 0x34ab, 0x1c51, 0x54dc, 0x84cf, 0xa012, 0xaef2, 0xb720, 0xbbaf, 0xbe38, 0xbf98, 0xc047, 0xc08c, 0xc090, 0xc06c, 0xc02f, 0xbfe4, 
0x28e0, 0x1fd1, 0x2253, 0x251c, 0x2834, 0x2b98, 0x2f3b, 0x32f4, 0x3659, 0x3878, 0x373c, 0x2e5a, 0x2788, 0x551e, 0xbbfa, 0xbf30, 0x4d1b, 0x1fac, 0x1c51, 0x3aa6, 0x607c, 0x7d25, 0x91b4, 0xa012, 0xaa0c, 0xb0fd, 0xb5da, 0xb945, 0xbbaf, 0xbd61, 0xbe91, 0xbf62, 
0x299f, 0x2c19, 0x2eb3, 0x315e, 0x33fc, 0x3659, 0x3816, 0x3889, 0x3692, 0x3055, 0x2322, 0x2d28, 0x551e, 0x9eb9, 0xd8ac, 0xac24, 0x53e4, 0x21b0, 0x1ce1, 0x1c51, 0x2e6b, 0x4bec, 0x6523, 0x7997, 0x89c4, 0x965b, 0xa012, 0xa78e, 0xad54, 0xb1cb, 0xb542, 0xb7f3, 
0x328c, 0x348b, 0x3659, 0x37c8, 0x388d, 0x3839, 0x3621, 0x3150, 0x2885, 0x2940, 0x2cf8, 0x551e, 0x8de3, 0xc5ed, 0xd896, 0xa009, 0x5625, 0x34ab, 0x19bf, 0x27b0, 0x1c51, 0x2778, 0x3f44, 0x54dc, 0x67a3, 0x778a, 0x84cf, 0x8fc3, 0x98bd, 0xa012, 0xa60f, 0xaaf2, 
0x378f, 0x385f, 0x3893, 0x37dd, 0x35d2, 0x31e5, 0x2b65, 0x2c8c, 0x2601, 0x2cd2, 0x551e, 0x836a, 0xb311, 0xd658, 0xd0b2, 0x97eb, 0x56f1, 0x40b7, 0x1cf1, 0x1cd1, 0x1da3, 0x1c51, 0x230b, 0x36cf, 0x4966, 0x5a47, 0x6933, 0x7634, 0x816f, 0x8b0d, 0x933c, 0x9a2f, 
0x386d, 0x3787, 0x3598, 0x3247, 0x2d29, 0x25c2, 0x29de, 0x236e, 0x3aff, 0x551e, 0x7c5b, 0xa48e, 0xc963, 0xda6a, 0xc79c, 0x9229, 0x572f, 0x4845, 0x2a40, 0x1bcf, 0x1d33, 0x1e24, 0x1c51, 0x1fff, 0x30ce, 0x4104, 0x501c, 0x5de6, 0x6a44, 0x7545, 0x7efe, 0x8788, 
0x356c, 0x328d, 0x2e5a, 0x2885, 0x2c32, 0x2788, 0x2d1b, 0x3c49, 0x551e, 0x774d, 0x99a7, 0xbbfa, 0xd4f5, 0xd896, 0xbf30, 0x8de1, 0x5733, 0x4d1b, 0x34ab, 0x1ad3, 0x1fac, 0x27a1, 0x1cb1, 0x1c51, 0x1dc9, 0x2c56, 0x3aa6, 0x4835, 0x54dc, 0x607c, 0x6b0a, 0x7494, 
0x2f33, 0x2a6c, 0x242b, 0x2a2f, 0x2588, 0x2d03, 0x3d4c, 0x551e, 0x7383, 0x9154, 0xb059, 0xcb20, 0xd9ae, 0xd433, 0xb7d6, 0x8a94, 0x571d, 0x5048, 0x3c91, 0x24e5, 0x1cef, 0x113d, 0x27b9, 0x1dc6, 0x1c51, 0x1c1c, 0x28e7, 0x35ac, 0x41f0, 0x4d89, 0x5864, 0x626c, 
0x26aa, 0x2bfd, 0x285e, 0x23d2, 0x2cee, 0x3e1d, 0x551e, 0x7091, 0x8ad3, 0xa6b1, 0xc0d7, 0xd413, 0xda4e, 0xcee1, 0xb188, 0x87f6, 0x56fd, 0x526c, 0x4284, 0x2d84, 0x19a2, 0x170c, 0x1d51, 0x1d16, 0x1e9e, 0x1c51, 0x25c2, 0x2630, 0x31ae, 0x3cd9, 0x4784, 0x51a0, 
0x2a61, 0x26bf, 0x2d28, 0x2cdb, 0x3ec9, 0x551e, 0x63d8, 0x85a2, 0x9eb9, 0xb761, 0xcc2a, 0xd8ac, 0xd896, 0xc967, 0xac24, 0x85d5, 0x56da, 0x53e4, 0x4705, 0x34ab, 0x21b0, 0x1da3, 0x1e2c, 0x1ce1, 0x1d79, 0x1f4c, 0x1c51, 0x24de, 0x23fd, 0x2e6b, 0x38a5, 0x4281, 
0x254e, 0x2d17, 0x39c6, 0x3f59, 0x551e, 0x627f, 0x8166, 0x981c, 0xaf0a, 0xc3df, 0xd377, 0xda57, 0xd599, 0xc41f, 0xa783, 0x8413, 0x56b6, 0x54ea, 0x4a75, 0x3a89, 0x28ea, 0x18de, 0x189c, 0x10fd, 0x27ab, 0x1dc8, 0x1fdb, 0x1c51, 0x2420, 0x222e, 0x2bb4, 0x3520, 
0x2d07, 0x3a9e, 0x3fd3, 0x551e, 0x615f, 0x7de4, 0x9292, 0xa7cd, 0xbbfa, 0xccdb, 0xd7c3, 0xda14, 0xd1fa, 0xbf30, 0xa383, 0x8298, 0x5693, 0x55a3, 0x4d1b, 0x3f53, 0x2f3a, 0x1f91, 0x1e1e, 0x1fac, 0x1d61, 0x27ba, 0x1e08, 0x2051, 0x1c51, 0x2381, 0x20aa, 0x296b, 
0x3b5a, 0x4b04, 0x551e, 0x606b, 0x7af1, 0x8de3, 0xa189, 0xb4c1, 0xc5ed, 0xd305, 0xd9df, 0xd896, 0xce18, 0xbaa5, 0xa009, 0x8155, 0x5672, 0x5625, 0x4f2a, 0x433d, 0x34ab, 0x25be, 0x2326, 0x19bf, 0x1d58, 0x1d09, 0x27b0, 0x1e3d, 0x20b6, 0x1c51, 0x22f9, 0x1f61, 
0x4bad, 0x551e, 0x5f9b, 0x786c, 0x89e1, 0x9c19, 0xae44, 0xbf31, 0xcd58, 0xd6fd, 0xda6d, 0xd656, 0xca2e, 0xb67e, 0x9cfd, 0x803e, 0x5654, 0x5682, 0x50c7, 0x4673, 0x3955, 0x2b50, 0x1e0f, 0x1e78, 0x163e, 0x10d9, 0x278d, 0x1d28, 0x11b7, 0x210c, 0x1c51, 0x2284, 
0x551e, 0x5ee6, 0x7641, 0x866c, 0x975d, 0xa87a, 0xb8e1, 0xc768, 0xd2af, 0xd946, 0xd9e2, 0xd3a3, 0xc659, 0xb2b7, 0x9a4d, 0x7f4b, 0x5637, 0x56c3, 0x520e, 0x4918, 0x3d50, 0x3047, 0x236f, 0x22d4, 0x1a9a, 0x1ea8, 0x1d6a, 0x27ae, 0x1d6a, 0x1cfd, 0x1698, 0x1c51, 
};