#ifndef __libfixmath_fix16_hpp__
#define __libfixmath_fix16_hpp__

class Fix16 
{
public:
  fix16_t value;

  inline Fix16() { value = 0; }
  inline Fix16(const Fix16 &inValue)  { value = inValue.value;             }
  inline Fix16(const fix16_t inValue) { value = inValue;                   }
  inline Fix16(const float inValue)   { value = fix16_from_float(inValue); }
  inline Fix16(const int16_t inValue) { value = fix16_from_int(inValue);   }

  inline operator fix16_t() const { return value;                 }
  inline float asFloat()    const { return fix16_to_float(value); }
  inline int asInt()        const { return fix16_to_int(value);   }

  inline Fix16 & operator=(const Fix16 &rhs)  { value = rhs.value;             return *this; }
  inline Fix16 & operator=(const fix16_t rhs) { value = rhs;                   return *this; }
  inline Fix16 & operator=(const float rhs)   { value = fix16_from_float(rhs); return *this; }
  inline Fix16 & operator=(const int16_t rhs) { value = fix16_from_int(rhs);   return *this; }

  inline Fix16 & operator+=(const Fix16 &rhs)  { value += rhs.value;             return *this; }
  inline Fix16 & operator+=(const fix16_t rhs) { value += rhs;                   return *this; }
  inline Fix16 & operator+=(const float rhs)   { value += fix16_from_float(rhs); return *this; }
  inline Fix16 & operator+=(const int16_t rhs) { value += fix16_from_int(rhs);   return *this; }

  inline Fix16 & operator-=(const Fix16 &rhs)  { value -= rhs.value; return *this; }
  inline Fix16 & operator-=(const fix16_t rhs) { value -= rhs; return *this; }
  inline Fix16 & operator-=(const float rhs)   { value -= fix16_from_float(rhs); return *this; }
  inline Fix16 & operator-=(const int16_t rhs) { value -= fix16_from_int(rhs); return *this; }

  inline Fix16 & operator*=(const Fix16 &rhs)  { value = fix16_mul(value, rhs.value); return *this; }
  inline Fix16 & operator*=(const fix16_t rhs) { value = fix16_mul(value, rhs); return *this; }
  inline Fix16 & operator*=(const float rhs)   { value = fix16_mul(value, fix16_from_float(rhs)); return *this; }
  inline Fix16 & operator*=(const int16_t rhs) { value *= rhs; return *this; }

  inline Fix16 & operator/=(const Fix16 &rhs)  { value = fix16_div(value, rhs.value); return *this; }
  inline Fix16 & operator/=(const fix16_t rhs) { value = fix16_div(value, rhs); return *this; }
  inline Fix16 & operator/=(const float rhs)   { value = fix16_div(value, fix16_from_float(rhs)); return *this; }
  inline Fix16 & operator/=(const int16_t rhs) { value /= rhs; return *this; }

  inline const Fix16 operator+(const Fix16 &other) const  { Fix16 ret = *this; ret += other; return ret; }
  inline const Fix16 operator+(const fix16_t other) const { Fix16 ret = *this; ret += other; return ret; }
  inline const Fix16 operator+(const float other) const   { Fix16 ret = *this; ret += other; return ret; }
  inline const Fix16 operator+(const int16_t other) const { Fix16 ret = *this; ret += other; return ret; }

  inline const Fix16 sadd(const Fix16 &other)  const { Fix16 ret = fix16_sadd(value, other.value);             return ret; }
  inline const Fix16 sadd(const fix16_t other) const { Fix16 ret = fix16_sadd(value, other);                   return ret; }
  inline const Fix16 sadd(const float other)   const { Fix16 ret = fix16_sadd(value, fix16_from_float(other)); return ret; }
  inline const Fix16 sadd(const int16_t other) const { Fix16 ret = fix16_sadd(value, fix16_from_int(other));   return ret; }

  inline const Fix16 operator-(const Fix16 &other) const  { Fix16 ret = *this; ret -= other; return ret; }
  inline const Fix16 operator-(const fix16_t other) const { Fix16 ret = *this; ret -= other; return ret; }
  inline const Fix16 operator-(const float other) const   { Fix16 ret = *this; ret -= other; return ret; }
  inline const Fix16 operator-(const int16_t other) const { Fix16 ret = *this; ret -= other; return ret; }

  inline const Fix16 ssub(const Fix16 &other)  const { Fix16 ret = fix16_sadd(value, -other.value);             return ret; }
  inline const Fix16 ssub(const fix16_t other) const { Fix16 ret = fix16_sadd(value, -other);                   return ret; }
  inline const Fix16 ssub(const float other)   const { Fix16 ret = fix16_sadd(value, -fix16_from_float(other)); return ret; }
  inline const Fix16 ssub(const int16_t other) const { Fix16 ret = fix16_sadd(value, -fix16_from_int(other));   return ret; }

  inline const Fix16 operator*(const Fix16 &other) const  { Fix16 ret = *this; ret *= other; return ret; }
  inline const Fix16 operator*(const fix16_t other) const { Fix16 ret = *this; ret *= other; return ret; }
  inline const Fix16 operator*(const float other) const   { Fix16 ret = *this; ret *= other; return ret; }
  inline const Fix16 operator*(const int16_t other) const { Fix16 ret = *this; ret *= other; return ret; }

  inline const Fix16 smul(const Fix16 &other)  const { Fix16 ret = fix16_smul(value, other.value);             return ret; }
  inline const Fix16 smul(const fix16_t other) const { Fix16 ret = fix16_smul(value, other);                   return ret; }
  inline const Fix16 smul(const float other)   const { Fix16 ret = fix16_smul(value, fix16_from_float(other)); return ret; }
  inline const Fix16 smul(const int16_t other) const { Fix16 ret = fix16_smul(value, fix16_from_int(other));   return ret; }

  inline const Fix16 operator/(const Fix16 &other) const  { Fix16 ret = *this; ret /= other; return ret; }
  inline const Fix16 operator/(const fix16_t other) const { Fix16 ret = *this; ret /= other; return ret; }
  inline const Fix16 operator/(const float other) const   { Fix16 ret = *this; ret /= other; return ret; }
  inline const Fix16 operator/(const int16_t other) const { Fix16 ret = *this; ret /= other; return ret; }

  inline const Fix16 sdiv(const Fix16 &other)  const { Fix16 ret = fix16_sdiv(value, other.value);             return ret; }
  inline const Fix16 sdiv(const fix16_t other) const { Fix16 ret = fix16_sdiv(value, other);                   return ret; }
  inline const Fix16 sdiv(const float other)   const { Fix16 ret = fix16_sdiv(value, fix16_from_float(other)); return ret; }
  inline const Fix16 sdiv(const int16_t other) const { Fix16 ret = fix16_sdiv(value, fix16_from_int(other));   return ret; }

  inline const int operator==(const Fix16 &other)  const { return (value == other.value);             }
  inline const int operator==(const fix16_t other) const { return (value == other);                   }
  inline const int operator==(const float other)   const { return (value == fix16_from_float(other)); }
  inline const int operator==(const int16_t other) const { return (value == fix16_from_int(other));   }

  inline const int operator!=(const Fix16 &other)  const { return (value != other.value);             }
  inline const int operator!=(const fix16_t other) const { return (value != other);                   }
  inline const int operator!=(const float other)   const { return (value != fix16_from_float(other)); }
  inline const int operator!=(const int16_t other) const { return (value != fix16_from_int(other));   }

  inline const int operator<=(const Fix16 &other)  const { return (value <= other.value);             }
  inline const int operator<=(const fix16_t other) const { return (value <= other);                   }
  inline const int operator<=(const float other)   const { return (value <= fix16_from_float(other)); }
  inline const int operator<=(const int16_t other) const { return (value <= fix16_from_int(other));   }

  inline const int operator>=(const Fix16 &other)  const { return (value >= other.value);             }
  inline const int operator>=(const fix16_t other) const { return (value >= other);                   }
  inline const int operator>=(const float other)   const { return (value >= fix16_from_float(other)); }
  inline const int operator>=(const int16_t other) const { return (value >= fix16_from_int(other));   }

  inline const int operator< (const Fix16 &other)  const { return (value <  other.value);             }
  inline const int operator< (const fix16_t other) const { return (value <  other);                   }
  inline const int operator< (const float other)   const { return (value <  fix16_from_float(other)); }
  inline const int operator< (const int16_t other) const { return (value <  fix16_from_int(other));   }

  inline const int operator> (const Fix16 &other)  const { return (value >  other.value);             }
  inline const int operator> (const fix16_t other) const { return (value >  other);                   }
  inline const int operator> (const float other)   const { return (value >  fix16_from_float(other)); }
  inline const int operator> (const int16_t other) const { return (value >  fix16_from_int(other));   }

  inline Fix16  sin() const { return Fix16(fix16_sin(value));  }
  inline Fix16  cos() const { return Fix16(fix16_cos(value));  }
  inline Fix16  tan() const { return Fix16(fix16_tan(value));  }
  inline Fix16 asin() const { return Fix16(fix16_asin(value)); }
  inline Fix16 acos() const { return Fix16(fix16_acos(value)); }
  inline Fix16 atan() const { return Fix16(fix16_atan(value)); }
  inline Fix16 atan2(const Fix16 &inY) const { return Fix16(fix16_atan2(value, inY.value)); }
  inline Fix16 sqrt() const { return Fix16(fix16_sqrt(value)); }

  static inline Fix16  sin(const Fix16& v) { return Fix16(fix16_sin(v));  }
  static inline Fix16  cos(const Fix16& v) { return Fix16(fix16_cos(v));  }
  static inline Fix16  tan(const Fix16& v) { return Fix16(fix16_tan(v));  }
  static inline Fix16 asin(const Fix16& v) { return Fix16(fix16_asin(v)); }
  static inline Fix16 acos(const Fix16& v) { return Fix16(fix16_acos(v)); }
  static inline Fix16 atan(const Fix16& v) { return Fix16(fix16_atan(v)); }
  static inline Fix16 atan2(const Fix16& v, const Fix16 &y) { return Fix16(fix16_atan2(v, y)); }
  static inline Fix16 sqrt(const Fix16& v) { return Fix16(fix16_sqrt(v)); }

  static inline Fix16 abs(const Fix16& v) { return Fix16( (v.value ^ (v.value >> 31)) - (v.value >> 31) ); }

  inline Fix16  sinV(Fix16 v) const { return Fix16(fix16_sin(fix16_add(value, v)));  }
  inline Fix16  cosV(Fix16 v) const { return Fix16(fix16_cos(fix16_add(value, v)));  }
  inline Fix16  sinM(Fix16 m) const { return Fix16(fix16_sin(fix16_mul(value, m)));  }
  inline Fix16  cosM(Fix16 m) const { return Fix16(fix16_cos(fix16_mul(value, m)));  }
  inline Fix16  sinMV(Fix16 m, Fix16 v) const { return Fix16(fix16_sin(fix16_mul(fix16_add(value, v), m)));  }
  inline Fix16  cosMV(Fix16 m, Fix16 v) const { return Fix16(fix16_cos(fix16_mul(fix16_add(value, v), m)));  }
};

#define XORByteSwap(a, b)         (((a) == (b)) || (((a) ^= (b)), ((b) ^= (a)), ((a) ^= b)))


#endif
