#pragma once

class RNG
{
public:

  RNG(uint32_t seed = 0);
  ~RNG();

  void reseed(uint32_t newseed);

  // random signed integer
  int32_t genInt32();

  // random signed integer between rmin-rmax
  int32_t genInt32(int32_t rmin, int32_t rmax);

  // get random bool
  bool genBool();

  // random unsigned integer
  uint32_t genUInt32();

  uint32_t genUInt32(uint32_t rmin, uint32_t rmax);

protected:

  uint32_t  m_seed[2];
};

