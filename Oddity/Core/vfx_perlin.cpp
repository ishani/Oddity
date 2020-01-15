/*
                 __    ___ __       
      ____  ____/ /___/ (_) /___  __
     / __ \/ __  / __  / / __/ / / /    [ LED matrix VFX core ] 
    / /_/ / /_/ / /_/ / / /_/ /_/ / 
    \____/\__,_/\__,_/_/\__/\__, /     [ john & harry ] [ 2012 ]
                           /____/   
*/


#include "oddity.h"
#include "vfx.h"


static const int32_t sPerlinPermutation[512] = 
{ 
  151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
  8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
  35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
  134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
  55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,
  18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,
  226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,
  17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,
  167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,
  246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,
  14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,
  150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,

  151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
  8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
  35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
  134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
  55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,
  18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,
  226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,
  17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,
  167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,
  246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,
  14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,
  150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};


//----------------------------------------------------------------------------------------------------------------------
inline Fix16 grad3(int32_t hash, Fix16 x, Fix16 y, Fix16 z) 
{
  static int16_t g3[16][3] =
  {
    { 1, 1, 0}, {-1, 1, 0}, { 1,-1, 0}, {-1,-1, 0}, // center of cube to edges
    { 1, 0, 1}, {-1, 0, 1}, { 1, 0,-1}, {-1, 0,-1},
    { 0, 1, 1}, { 0,-1, 1}, { 0, 1,-1}, { 0,-1,-1},
    { 1, 1, 0}, {-1, 1, 0}, { 0,-1, 1}, { 0,-1,-1}  // tetrahedron
  };

  int h = hash & 0xf;
  Fix16 _x = Fix16(g3[h][0]);
  Fix16 _y = Fix16(g3[h][1]);
  Fix16 _z = Fix16(g3[h][2]);

  return x * _x + y * _y + z * _z; 
}

//----------------------------------------------------------------------------------------------------------------------
inline Fix16 grad2(int32_t hash, Fix16 x, Fix16 y) 
{
  static int16_t g2[4][2] = 
  {
    { 1, 0}, {-1, 0}, { 0, 1}, { 0, -1}, // center of square to edges 
  };

  int h = hash & 0x3;
  Fix16 _x = Fix16(g2[h][0]);
  Fix16 _y = Fix16(g2[h][1]);

  return x * _x + y * _y;
}


//----------------------------------------------------------------------------------------------------------------------
static Fix16 g_thirty(30.0f);
static Fix16 g_one(1.0f);
static Fix16 g_two(2.0f);
static Fix16 g_six(6.0f);
static Fix16 g_fifteen(15.0f);
static Fix16 g_ten(10.0f);


#define p3deriv(t)        ( g_thirty * t * t * (t * (t - g_two) + g_one) )
#define p3fade(t)         ( t * t * t * (t * (t * g_six - g_fifteen) + g_ten) )
#define p3lerp(t, a, b)   ( a + t * (b - a) )

// ---------------------------------------------------------------------------------------------------------------------
inline Fix16 floor16withRel(Fix16 &v)
{
  Fix16 r(v);
  r.value = (r.value & 0xFFFF0000);
  v.value = (v.value & 0x0000FFFF);
  return r;
}


//----------------------------------------------------------------------------------------------------------------------
Fix16 Perlin3(Fix16 x, Fix16 y, Fix16 z)
{
  Fix16 flrX = floor16withRel(x);
  Fix16 flrY = floor16withRel(y);
  Fix16 flrZ = floor16withRel(z);

  // find unit cube for point
  int16_t X = ((int16_t)flrX.asInt()) & 255,
          Y = ((int16_t)flrY.asInt()) & 255,
          Z = ((int16_t)flrZ.asInt()) & 255;


  // fade curves for x,y,z
  Fix16 u = p3fade(x), v = p3fade(y), w = p3fade(z);

  // hash coordinates of 8 cube corners
  int32_t A = sPerlinPermutation[X  ]+Y, AA = sPerlinPermutation[A]+Z, AB = sPerlinPermutation[A+1]+Z,
          B = sPerlinPermutation[X+1]+Y, BA = sPerlinPermutation[B]+Z, BB = sPerlinPermutation[B+1]+Z;

  // add blended results from 8 corners of cube
  return (
          p3lerp(w, p3lerp(v, p3lerp(u, grad3(sPerlinPermutation[AA  ], x  , y  , z   ),
          grad3(sPerlinPermutation[BA  ], x- g_one, y  , z   )),
          p3lerp(u, grad3(sPerlinPermutation[AB  ], x  , y- g_one, z   ),
          grad3(sPerlinPermutation[BB  ], x- g_one, y- g_one, z   ))),
          p3lerp(v, p3lerp(u, grad3(sPerlinPermutation[AA+1], x  , y  , z- g_one ),
          grad3(sPerlinPermutation[BA+1], x- g_one, y  , z- g_one )),
          p3lerp(u, grad3(sPerlinPermutation[AB+1], x  , y- g_one, z- g_one ),
          grad3(sPerlinPermutation[BB+1], x- g_one, y- g_one, z- g_one ))))
          );
}

//----------------------------------------------------------------------------------------------------------------------
Fix16 Perlin2(Fix16 x, Fix16 y)
{
  Fix16 flrX = floor16withRel(x);
  Fix16 flrY = floor16withRel(y);

  // find unit cube for point
  int16_t X = ((int16_t)flrX.asInt()) & 255,
          Y = ((int16_t)flrY.asInt()) & 255;

  // fade curves for x,y
  Fix16 u = p3fade(x), v = p3fade(y);

  // hash coordinates of the 4 square corners.
  int32_t A = sPerlinPermutation[X  ]+Y, B = sPerlinPermutation[X+1]+Y;

  // add blended results from eight corners of the cube
  return p3lerp(v, p3lerp(u, grad2(sPerlinPermutation[A  ], x  , y ),
    grad2(sPerlinPermutation[B  ], x - g_one, y   )), 
    p3lerp(u, grad2(sPerlinPermutation[A+1], x  , y - g_one ),
    grad2(sPerlinPermutation[B+1], x - g_one, y - g_one )));
}