/*
                 __    ___ __       
      ____  ____/ /___/ (_) /___  __
     / __ \/ __  / __  / / __/ / / /    [ LED matrix VFX core ] 
    / /_/ / /_/ / /_/ / / /_/ /_/ / 
    \____/\__,_/\__,_/_/\__/\__, /     [ john & harry ] [ 2012 ]
                           /____/   
*/

#include "oddity.h"
#include "RNG.h"

//----------------------------------------------------------------------------------------------------------------------
RNG::RNG(uint32_t seed)
{
  reseed(seed);
}

//----------------------------------------------------------------------------------------------------------------------
RNG::~RNG()
{

}

//----------------------------------------------------------------------------------------------------------------------
void RNG::reseed(uint32_t newseed)
{
  m_seed[0] = newseed + !newseed;
  m_seed[1] = ( ( newseed << 16 ) | ( newseed >> 16 ) ) ^ newseed;
}

//----------------------------------------------------------------------------------------------------------------------
int32_t RNG::genInt32()
{
  return (int32_t)genUInt32();
}

//----------------------------------------------------------------------------------------------------------------------
int32_t RNG::genInt32(int32_t rmin, int32_t rmax)
{
  return ((genInt32() % (rmax - rmin+1)) + rmin);
}

//----------------------------------------------------------------------------------------------------------------------
uint32_t RNG::genUInt32(uint32_t rmin, uint32_t rmax)
{
  if (rmax < rmin)
  {
    uint32_t swp = rmin;
    rmin = rmax;
    rmax = swp;
  }
  return ((genUInt32() % (rmax - rmin+1)) + rmin);
}


//----------------------------------------------------------------------------------------------------------------------
bool RNG::genBool()
{
  return (genUInt32() & 1);
}

//----------------------------------------------------------------------------------------------------------------------
uint32_t RNG::genUInt32()
{
  /*
  http://cliodhna.cop.uop.edu/~hetrick/na_faq.html

  [George Marsaglia]:
  Here is a simple version, one so simple and good I predict
  it will be the system generator for many future computers:
  x(n)=a*x(n-1)+carry mod 2^32
  With multiplier 'a' chosen from a large set of easily found
  integers, the period is a*2^31-1, around 2^60, and
  I have yet to find a test it will not pass!

  The 'carry' works like this, which shows how well this
  method will serve as a system RNG:
  Have seed x and c.  Form a*x+c in 64 bits.  All modern
  CPU's have instructions for this: sparc, intel, etc.
  Then the new x is the bottom 32 bits.
  the new carry is the top 32 bits.

  The period is the order of b=2^32 in the group of residues
  relatively prime to m=a*2^32-1.  One need only choose a's
  of some 30 bits for which m=a*2^32-1 is a safeprime:
  both m and (m-1)/2 are prime.  There are thousands of them.

  In general, for any choice of 'a', let m=a*2^32-1.  If both m
  and (m-1)/2 are prime then the period will be (m-1)/2.
  Even if 'a' is, say, your social security number, the
  period will most likely be on the order of 2^50 or more.
  (For mine, it is 2^54.8).

  For 32-bit generators, some possible values of 'a' are:
  1967773755 1517746329 1447497129 1655692410 1606218150
  2051013963 1075433238 1557985959 1781943330 1893513180
  */

  uint64_t temp = (uint64_t)1447497129 * m_seed[0] + m_seed[1];
  m_seed[0] = uint32_t( temp & ~0u );
  m_seed[1] = uint32_t( ( temp >> 32 ) & ~0u );

  return m_seed[0];
}

