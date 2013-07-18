#pragma once

#include <math.h>
#include <stdio.h>

#ifndef assert
#define assert(a) if( !( a ) ) printf( "Fatal error: file[%s] line[%d]\n", __FILE__, __LINE__ );
#endif


#define DEG2RAD(a)            ( (a) * Math::M_DEG2RAD )
#define RAD2DEG(a)            ( (a) * Math::M_RAD2DEG )

#define FLOAT_IS_NAN(x)       (((*(const unsigned long *)&x) & 0x7f800000) == 0x7f800000)
#define FLOAT_IS_INF(x)       (((*(const unsigned long *)&x) & 0x7fffffff) == 0x7f800000)
#define FLOAT_IS_IND(x)       ((*(const unsigned long *)&x) == 0xffc00000)
#define FLOAT_IS_DENORMAL(x)  (((*(const unsigned long *)&x) & 0x7f800000) == 0x00000000 && \
                              ((*(const unsigned long *)&x) & 0x007fffff) != 0x00000000 )

#define FLOATSIGNBITSET(f)    ((*(const unsigned long *)&(f)) >> 31)
#define FLOATSIGNBITNOTSET(f) ((~(*(const unsigned long *)&(f))) >> 31)
#define FLOATNOTZERO(f)       ((*(const unsigned long *)&(f)) & ~(1<<31) )
#define INTSIGNBITSET(i)      (((const unsigned long)(i)) >> 31)
#define INTSIGNBITNOTSET(i)   ((~((const unsigned long)(i))) >> 31)

#define IEEE_FLT_MANTISSA_BITS  23
#define IEEE_FLT_EXPONENT_BITS  8
#define IEEE_FLT_EXPONENT_BIAS  127
#define IEEE_FLT_SIGN_BIT       31
#define KM_INLINE __forceinline

template<class T> KM_INLINE int  MaxIndex( T x, T y ) { return  ( x > y ) ? 0 : 1; }
template<class T> KM_INLINE int  MinIndex( T x, T y ) { return ( x < y ) ? 0 : 1; }

template<class T> KM_INLINE T  Max3( T x, T y, T z ) { return ( x > y ) ? ( ( x > z ) ? x : z ) : ( ( y > z ) ? y : z ); }
template<class T> KM_INLINE T  Min3( T x, T y, T z ) { return ( x < y ) ? ( ( x < z ) ? x : z ) : ( ( y < z ) ? y : z ); }
template<class T> KM_INLINE int  Max3Index( T x, T y, T z ) { return ( x > y ) ? ( ( x > z ) ? 0 : 2 ) : ( ( y > z ) ? 1 : 2 ); }
template<class T> KM_INLINE int  Min3Index( T x, T y, T z ) { return ( x < y ) ? ( ( x < z ) ? 0 : 2 ) : ( ( y < z ) ? 1 : 2 ); }

template<class T> KM_INLINE T  Sign( T f ) { return ( f > 0 ) ? ( T ) 1 : ( ( f < 0 ) ? ( T ) -1 : 0 ); }
template<class T> KM_INLINE T  Square( T x ) { return x * x; }
template<class T> KM_INLINE T  Cube( T x ) { return x * x * x; }

class Math
{
public:
  static void         Init( void );

  static float        RSqrt( float x );      // reciprocal square root, returns huge number when x == 0.0

  static float        InvSqrt( float x );      // inverse square root with 32 bits precision, returns huge number when x == 0.0
  static float        InvSqrt16( float x );    // inverse square root with 16 bits precision, returns huge number when x == 0.0
  static double       InvSqrt64( float x );    // inverse square root with 64 bits precision, returns huge number when x == 0.0

  static float        Sqrt( float x );      // square root with 32 bits precision
  static float        Sqrt16( float x );      // square root with 16 bits precision
  static double       Sqrt64( float x );      // square root with 64 bits precision

  static float        Sin( float a );        // sine with 32 bits precision
  static float        Sin16( float a );      // sine with 16 bits precision, maximum absolute error is 2.3082e-09
  static double       Sin64( float a );      // sine with 64 bits precision

  static float        Cos( float a );        // cosine with 32 bits precision
  static float        Cos16( float a );      // cosine with 16 bits precision, maximum absolute error is 2.3082e-09
  static double       Cos64( float a );      // cosine with 64 bits precision

  static void         SinCos( float a, float &s, float &c );    // sine and cosine with 32 bits precision
  static void         SinCos16( float a, float &s, float &c );  // sine and cosine with 16 bits precision
  static void         SinCos64( float a, double &s, double &c );  // sine and cosine with 64 bits precision

  static float        Tan( float a );        // tangent with 32 bits precision
  static float        Tan16( float a );      // tangent with 16 bits precision, maximum absolute error is 1.8897e-08
  static double       Tan64( float a );      // tangent with 64 bits precision

  static float        ASin( float a );      // arc sine with 32 bits precision, input is clamped to [-1, 1] to avoid a silent NaN
  static float        ASin16( float a );      // arc sine with 16 bits precision, maximum absolute error is 6.7626e-05
  static double       ASin64( float a );      // arc sine with 64 bits precision

  static float        ACos( float a );      // arc cosine with 32 bits precision, input is clamped to [-1, 1] to avoid a silent NaN
  static float        ACos16( float a );      // arc cosine with 16 bits precision, maximum absolute error is 6.7626e-05
  static double       ACos64( float a );      // arc cosine with 64 bits precision

  static float        ATan( float a );      // arc tangent with 32 bits precision
  static float        ATan16( float a );      // arc tangent with 16 bits precision, maximum absolute error is 1.3593e-08
  static double       ATan64( float a );      // arc tangent with 64 bits precision

  static float        ATan( float y, float x );  // arc tangent with 32 bits precision
  static float        ATan16( float y, float x );  // arc tangent with 16 bits precision, maximum absolute error is 1.3593e-08
  static double       ATan64( float y, float x );  // arc tangent with 64 bits precision

  static float        Pow( float x, float y );  // x raised to the power y with 32 bits precision
  static float        Pow16( float x, float y );  // x raised to the power y with 16 bits precision
  static double       Pow64( float x, float y );  // x raised to the power y with 64 bits precision

  static float        Exp( float f );        // e raised to the power f with 32 bits precision
  static float        Exp16( float f );      // e raised to the power f with 16 bits precision
  static double       Exp64( float f );      // e raised to the power f with 64 bits precision

  static float        Log( float f );        // natural logarithm with 32 bits precision
  static float        Log16( float f );      // natural logarithm with 16 bits precision
  static double       Log64( float f );      // natural logarithm with 64 bits precision

  static int          IPow( int x, int y );    // integral x raised to the power y
  static int          ILog2( float f );      // integral base-2 logarithm of the floating point value
  static int          ILog2( int i );        // integral base-2 logarithm of the integer value

  static int          Abs( int x );        // returns the absolute value of the integer value (for reference only)
  static float        Fabs( float f );      // returns the absolute value of the floating point value
  static float        Floor( float f );      // returns the largest integer that is less than or equal to the given value
  static float        Ceil( float f );      // returns the smallest integer that is greater than or equal to the given value
  static float        Rint( float f );      // returns the nearest integer
  static int          Ftoi( float f );      // float to int conversion
  static int          FtoiFast( float f );    // fast float to int conversion but uses current FPU round mode (default round nearest)
  static unsigned long  Ftol( float f );      // float to long conversion
  static unsigned long  FtolFast( float );      // fast float to long conversion but uses current FPU round mode (default round nearest)

  static signed char  ClampChar( int i );
  static signed short ClampShort( int i );
  static int          ClampInt( int min, int max, int value );
  static float        ClampFloat( float min, float max, float value );

  static float        AngleNormalize360( float angle );
  static float        AngleNormalize180( float angle );
  static float        AngleDelta( float angle1, float angle2 );

  static const float      PI;             // pi
  static const float      TWO_PI;         // pi * 2
  static const float      HALF_PI;        // pi / 2
  static const float      ONEFOURTH_PI;   // pi / 4
  static const float      E;              // e
  static const float      SQRT_TWO;       // sqrt( 2 )
  static const float      SQRT_THREE;     // sqrt( 3 )
  static const float      SQRT_1OVER2;    // sqrt( 1 / 2 )
  static const float      SQRT_1OVER3;    // sqrt( 1 / 3 )
  static const float      M_DEG2RAD;      // degrees to radians multiplier
  static const float      M_RAD2DEG;      // radians to degrees multiplier
  static const float      M_SEC2MS;       // seconds to milliseconds multiplier
  static const float      M_MS2SEC;       // milliseconds to seconds multiplier
  static const float      INFINITY;       // huge number which should be larger than any valid number used
  static const float      FLT_EPSILON_NUM;    // smallest positive number such that 1.0+FLT_EPSILON != 1.0

private:
  union _flint {
    unsigned int  i;
    float         f;
  };

  enum {
    LOOKUP_BITS     = 8,
    EXP_POS         = 23,
    EXP_BIAS        = 127,
    LOOKUP_POS      = (EXP_POS-LOOKUP_BITS),
    SEED_POS        = (EXP_POS-8),
    SQRT_TABLE_SIZE = (2<<LOOKUP_BITS),
    LOOKUP_MASK     = (SQRT_TABLE_SIZE-1)
  };

  static unsigned int      iSqrt[SQRT_TABLE_SIZE];
  static bool       initialized;
};



KM_INLINE float Math::RSqrt( float x ) {

  long i;
  float y, r;

  y = x * 0.5f;
  i = *reinterpret_cast<long *>( &x );
  i = 0x5f3759df - ( i >> 1 );
  r = *reinterpret_cast<float *>( &i );
  r = r * ( 1.5f - r * r * y );
  return r;
}

KM_INLINE float Math::InvSqrt16( float x ) {
  assert( Math::initialized );
  unsigned int a = ((union _flint*)(&x))->i;
  union _flint seed;

  double y = x * 0.5f;
  seed.i = (( ( (3*EXP_BIAS-1) - ( (a >> EXP_POS) & 0xFF) ) >> 1)<<EXP_POS) | iSqrt[(a >> (EXP_POS-LOOKUP_BITS)) & LOOKUP_MASK];
  double r = seed.f;
  r = r * ( 1.5f - r * r * y );
  return (float) r;
}

KM_INLINE float Math::InvSqrt( float x ) {
  assert( Math::initialized );

  unsigned int a = ((union _flint*)(&x))->i;
  union _flint seed;

  double y = x * 0.5f;
  seed.i = (( ( (3*EXP_BIAS-1) - ( (a >> EXP_POS) & 0xFF) ) >> 1)<<EXP_POS) | iSqrt[(a >> (EXP_POS-LOOKUP_BITS)) & LOOKUP_MASK];
  double r = seed.f;
  r = r * ( 1.5f - r * r * y );
  r = r * ( 1.5f - r * r * y );
  return (float) r;
}

KM_INLINE double Math::InvSqrt64( float x ) {
  assert( Math::initialized );

  unsigned int a = ((union _flint*)(&x))->i;
  union _flint seed;

  double y = x * 0.5f;
  seed.i = (( ( (3*EXP_BIAS-1) - ( (a >> EXP_POS) & 0xFF) ) >> 1)<<EXP_POS) | iSqrt[(a >> (EXP_POS-LOOKUP_BITS)) & LOOKUP_MASK];
  double r = seed.f;
  r = r * ( 1.5f - r * r * y );
  r = r * ( 1.5f - r * r * y );
  r = r * ( 1.5f - r * r * y );
  return r;
}

KM_INLINE float Math::Sqrt16( float x ) {
  return x * InvSqrt16( x );
}

KM_INLINE float Math::Sqrt( float x ) {
  return x * InvSqrt( x );
}

KM_INLINE double Math::Sqrt64( float x ) {
  return x * InvSqrt64( x );
}

KM_INLINE float Math::Sin( float a ) {
  return sinf( a );
}

KM_INLINE float Math::Sin16( float a ) {
  float s;

  if ( ( a < 0.0f ) || ( a >= TWO_PI ) ) {
    a -= floorf( a / TWO_PI ) * TWO_PI;
  }
#if 1
  if ( a < PI ) {
    if ( a > HALF_PI ) {
      a = PI - a;
    }
  } else {
    if ( a > PI + HALF_PI ) {
      a = a - TWO_PI;
    } else {
      a = PI - a;
    }
  }
#else
  a = PI - a;
  if ( fabs( a ) >= HALF_PI ) {
    a = ( ( a < 0.0f ) ? -PI : PI ) - a;
  }
#endif
  s = a * a;
  return a * ( ( ( ( ( -2.39e-08f * s + 2.7526e-06f ) * s - 1.98409e-04f ) * s + 8.3333315e-03f ) * s - 1.666666664e-01f ) * s + 1.0f );
}

KM_INLINE double Math::Sin64( float a ) {
  return sin( a );
}

KM_INLINE float Math::Cos( float a ) {
  return cosf( a );
}

KM_INLINE float Math::Cos16( float a ) {
  float s, d;

  if ( ( a < 0.0f ) || ( a >= TWO_PI ) ) {
    a -= floorf( a / TWO_PI ) * TWO_PI;
  }
#if 1
  if ( a < PI ) {
    if ( a > HALF_PI ) {
      a = PI - a;
      d = -1.0f;
    } else {
      d = 1.0f;
    }
  } else {
    if ( a > PI + HALF_PI ) {
      a = a - TWO_PI;
      d = 1.0f;
    } else {
      a = PI - a;
      d = -1.0f;
    }
  }
#else
  a = PI - a;
  if ( fabs( a ) >= HALF_PI ) {
    a = ( ( a < 0.0f ) ? -PI : PI ) - a;
    d = 1.0f;
  } else {
    d = -1.0f;
  }
#endif
  s = a * a;
  return d * ( ( ( ( ( -2.605e-07f * s + 2.47609e-05f ) * s - 1.3888397e-03f ) * s + 4.16666418e-02f ) * s - 4.999999963e-01f ) * s + 1.0f );
}

KM_INLINE double Math::Cos64( float a ) {
  return cos( a );
}

KM_INLINE void Math::SinCos( float a, float &s, float &c ) {
#ifdef _WIN32
  _asm {
    fld    a
    fsincos
    mov    ecx, c
    mov    edx, s
    fstp  Dword ptr [ecx]
    fstp  Dword ptr [edx]
  }
#else
  s = sinf( a );
  c = cosf( a );
#endif
}

KM_INLINE void Math::SinCos16( float a, float &s, float &c ) {
  float t, d;

  if ( ( a < 0.0f ) || ( a >= Math::TWO_PI ) ) {
    a -= floorf( a / Math::TWO_PI ) * Math::TWO_PI;
  }
#if 1
  if ( a < PI ) {
    if ( a > HALF_PI ) {
      a = PI - a;
      d = -1.0f;
    } else {
      d = 1.0f;
    }
  } else {
    if ( a > PI + HALF_PI ) {
      a = a - TWO_PI;
      d = 1.0f;
    } else {
      a = PI - a;
      d = -1.0f;
    }
  }
#else
  a = PI - a;
  if ( fabs( a ) >= HALF_PI ) {
    a = ( ( a < 0.0f ) ? -PI : PI ) - a;
    d = 1.0f;
  } else {
    d = -1.0f;
  }
#endif
  t = a * a;
  s = a * ( ( ( ( ( -2.39e-08f * t + 2.7526e-06f ) * t - 1.98409e-04f ) * t + 8.3333315e-03f ) * t - 1.666666664e-01f ) * t + 1.0f );
  c = d * ( ( ( ( ( -2.605e-07f * t + 2.47609e-05f ) * t - 1.3888397e-03f ) * t + 4.16666418e-02f ) * t - 4.999999963e-01f ) * t + 1.0f );
}

KM_INLINE void Math::SinCos64( float a, double &s, double &c ) {
#ifdef _WIN32
  _asm {
    fld    a
    fsincos
    mov    ecx, c
    mov    edx, s
    fstp  qword ptr [ecx]
    fstp  qword ptr [edx]
  }
#else
  s = sin( a );
  c = cos( a );
#endif
}

KM_INLINE float Math::Tan( float a ) {
  return tanf( a );
}

KM_INLINE float Math::Tan16( float a ) {
  float s;
  bool reciprocal;

  if ( ( a < 0.0f ) || ( a >= PI ) ) {
    a -= floorf( a / PI ) * PI;
  }
#if 1
  if ( a < HALF_PI ) {
    if ( a > ONEFOURTH_PI ) {
      a = HALF_PI - a;
      reciprocal = true;
    } else {
      reciprocal = false;
    }
  } else {
    if ( a > HALF_PI + ONEFOURTH_PI ) {
      a = a - PI;
      reciprocal = false;
    } else {
      a = HALF_PI - a;
      reciprocal = true;
    }
  }
#else
  a = HALF_PI - a;
  if ( fabs( a ) >= ONEFOURTH_PI ) {
    a = ( ( a < 0.0f ) ? -HALF_PI : HALF_PI ) - a;
    reciprocal = false;
  } else {
    reciprocal = true;
  }
#endif
  s = a * a;
  s = a * ( ( ( ( ( ( 9.5168091e-03f * s + 2.900525e-03f ) * s + 2.45650893e-02f ) * s + 5.33740603e-02f ) * s + 1.333923995e-01f ) * s + 3.333314036e-01f ) * s + 1.0f );
  if ( reciprocal ) {
    return 1.0f / s;
  } else {
    return s;
  }
}

KM_INLINE double Math::Tan64( float a ) {
  return tan( a );
}

KM_INLINE float Math::ASin( float a ) {
  if ( a <= -1.0f ) {
    return -HALF_PI;
  }
  if ( a >= 1.0f ) {
    return HALF_PI;
  }
  return asinf( a );
}

KM_INLINE float Math::ASin16( float a ) {
  if ( FLOATSIGNBITSET( a ) ) {
    if ( a <= -1.0f ) {
      return -HALF_PI;
    }
    a = fabs( a );
    return ( ( ( -0.0187293f * a + 0.0742610f ) * a - 0.2121144f ) * a + 1.5707288f ) * sqrt( 1.0f - a ) - HALF_PI;
  } else {
    if ( a >= 1.0f ) {
      return HALF_PI;
    }
    return HALF_PI - ( ( ( -0.0187293f * a + 0.0742610f ) * a - 0.2121144f ) * a + 1.5707288f ) * sqrt( 1.0f - a );
  }
}

KM_INLINE double Math::ASin64( float a ) {
  if ( a <= -1.0f ) {
    return -HALF_PI;
  }
  if ( a >= 1.0f ) {
    return HALF_PI;
  }
  return asin( a );
}

KM_INLINE float Math::ACos( float a ) {
  if ( a <= -1.0f ) {
    return PI;
  }
  if ( a >= 1.0f ) {
    return 0.0f;
  }
  return acosf( a );
}

KM_INLINE float Math::ACos16( float a ) {
  if ( FLOATSIGNBITSET( a ) ) {
    if ( a <= -1.0f ) {
      return PI;
    }
    a = fabs( a );
    return PI - ( ( ( -0.0187293f * a + 0.0742610f ) * a - 0.2121144f ) * a + 1.5707288f ) * sqrt( 1.0f - a );
  } else {
    if ( a >= 1.0f ) {
      return 0.0f;
    }
    return ( ( ( -0.0187293f * a + 0.0742610f ) * a - 0.2121144f ) * a + 1.5707288f ) * sqrt( 1.0f - a );
  }
}

KM_INLINE double Math::ACos64( float a ) {
  if ( a <= -1.0f ) {
    return PI;
  }
  if ( a >= 1.0f ) {
    return 0.0f;
  }
  return acos( a );
}

KM_INLINE float Math::ATan( float a ) {
  return atanf( a );
}

KM_INLINE float Math::ATan16( float a ) {
  float s;

  if ( fabs( a ) > 1.0f ) {
    a = 1.0f / a;
    s = a * a;
    s = - ( ( ( ( ( ( ( ( ( 0.0028662257f * s - 0.0161657367f ) * s + 0.0429096138f ) * s - 0.0752896400f )
        * s + 0.1065626393f ) * s - 0.1420889944f ) * s + 0.1999355085f ) * s - 0.3333314528f ) * s ) + 1.0f ) * a;
    if ( FLOATSIGNBITSET( a ) ) {
      return s - HALF_PI;
    } else {
      return s + HALF_PI;
    }
  } else {
    s = a * a;
    return ( ( ( ( ( ( ( ( ( 0.0028662257f * s - 0.0161657367f ) * s + 0.0429096138f ) * s - 0.0752896400f )
      * s + 0.1065626393f ) * s - 0.1420889944f ) * s + 0.1999355085f ) * s - 0.3333314528f ) * s ) + 1.0f ) * a;
  }
}

KM_INLINE double Math::ATan64( float a ) {
  return atan( a );
}

KM_INLINE float Math::ATan( float y, float x ) {
  return atan2f( y, x );
}

KM_INLINE float Math::ATan16( float y, float x ) {
  float a, s;

  if ( fabs( y ) > fabs( x ) ) {
    a = x / y;
    s = a * a;
    s = - ( ( ( ( ( ( ( ( ( 0.0028662257f * s - 0.0161657367f ) * s + 0.0429096138f ) * s - 0.0752896400f )
        * s + 0.1065626393f ) * s - 0.1420889944f ) * s + 0.1999355085f ) * s - 0.3333314528f ) * s ) + 1.0f ) * a;
    if ( FLOATSIGNBITSET( a ) ) {
      return s - HALF_PI;
    } else {
      return s + HALF_PI;
    }
  } else {
    a = y / x;
    s = a * a;
    return ( ( ( ( ( ( ( ( ( 0.0028662257f * s - 0.0161657367f ) * s + 0.0429096138f ) * s - 0.0752896400f )
      * s + 0.1065626393f ) * s - 0.1420889944f ) * s + 0.1999355085f ) * s - 0.3333314528f ) * s ) + 1.0f ) * a;
  }
}

KM_INLINE double Math::ATan64( float y, float x ) {
  return atan2( y, x );
}

KM_INLINE float Math::Pow( float x, float y ) {
  return powf( x, y );
}

KM_INLINE float Math::Pow16( float x, float y ) {
  return Exp16( y * Log16( x ) );
}

KM_INLINE double Math::Pow64( float x, float y ) {
  return pow( x, y );
}

KM_INLINE float Math::Exp( float f ) {
  return expf( f );
}

KM_INLINE float Math::Exp16( float f ) {
  int i, s, e, m, exponent;
  float x, x2, y, p, q;

  x = f * 1.44269504088896340f;    // multiply with ( 1 / log( 2 ) )
#if 1
  i = *reinterpret_cast<int *>(&x);
  s = ( i >> IEEE_FLT_SIGN_BIT );
  e = ( ( i >> IEEE_FLT_MANTISSA_BITS ) & ( ( 1 << IEEE_FLT_EXPONENT_BITS ) - 1 ) ) - IEEE_FLT_EXPONENT_BIAS;
  m = ( i & ( ( 1 << IEEE_FLT_MANTISSA_BITS ) - 1 ) ) | ( 1 << IEEE_FLT_MANTISSA_BITS );
  i = ( ( m >> ( IEEE_FLT_MANTISSA_BITS - e ) ) & ~( e >> 31 ) ) ^ s;
#else
  i = (int) x;
  if ( x < 0.0f ) {
    i--;
  }
#endif
  exponent = ( i + IEEE_FLT_EXPONENT_BIAS ) << IEEE_FLT_MANTISSA_BITS;
  y = *reinterpret_cast<float *>(&exponent);
  x -= (float) i;
  if ( x >= 0.5f ) {
    x -= 0.5f;
    y *= 1.4142135623730950488f;  // multiply with sqrt( 2 )
  }
  x2 = x * x;
  p = x * ( 7.2152891511493f + x2 * 0.0576900723731f );
  q = 20.8189237930062f + x2;
  x = y * ( q + p ) / ( q - p );
  return x;
}

KM_INLINE double Math::Exp64( float f ) {
  return exp( f );
}

KM_INLINE float Math::Log( float f ) {
  return logf( f );
}

KM_INLINE float Math::Log16( float f ) {
  int i, exponent;
  float y, y2;

  i = *reinterpret_cast<int *>(&f);
  exponent = ( ( i >> IEEE_FLT_MANTISSA_BITS ) & ( ( 1 << IEEE_FLT_EXPONENT_BITS ) - 1 ) ) - IEEE_FLT_EXPONENT_BIAS;
  i -= ( exponent + 1 ) << IEEE_FLT_MANTISSA_BITS;  // get value in the range [.5, 1>
  y = *reinterpret_cast<float *>(&i);
  y *= 1.4142135623730950488f;            // multiply with sqrt( 2 )
  y = ( y - 1.0f ) / ( y + 1.0f );
  y2 = y * y;
  y = y * ( 2.000000000046727f + y2 * ( 0.666666635059382f + y2 * ( 0.4000059794795f + y2 * ( 0.28525381498f + y2 * 0.2376245609f ) ) ) );
  y += 0.693147180559945f * ( (float)exponent + 0.5f );
  return y;
}

KM_INLINE double Math::Log64( float f ) {
  return log( f );
}

KM_INLINE int Math::IPow( int x, int y ) {
  int r; for( r = x; y > 1; y-- ) { r *= x; } return r;
}

KM_INLINE int Math::ILog2( float f ) {
  return ( ( (*reinterpret_cast<int *>(&f)) >> IEEE_FLT_MANTISSA_BITS ) & ( ( 1 << IEEE_FLT_EXPONENT_BITS ) - 1 ) ) - IEEE_FLT_EXPONENT_BIAS;
}

KM_INLINE int Math::ILog2( int i ) {
  return ILog2( (float)i );
}

KM_INLINE int Math::Abs( int x ) {
   int y = x >> 31;
   return ( ( x ^ y ) - y );
}

KM_INLINE float Math::Fabs( float f ) {
  int tmp = *reinterpret_cast<int *>( &f );
  tmp &= 0x7FFFFFFF;
  return *reinterpret_cast<float *>( &tmp );
}

KM_INLINE float Math::Floor( float f ) {
  return floorf( f );
}

KM_INLINE float Math::Ceil( float f ) {
  return ceilf( f );
}

KM_INLINE float Math::Rint( float f ) {
  return floorf( f + 0.5f );
}

KM_INLINE int Math::Ftoi( float f ) {
  return (int) f;
}

KM_INLINE int Math::FtoiFast( float f ) {
#ifdef _WIN32
  int i;
  __asm fld    f
  __asm fistp    i    // use default rouding mode (round nearest)
  return i;
#elif 0            // round chop (C/C++ standard)
  int i, s, e, m, shift;
  i = *reinterpret_cast<int *>(&f);
  s = i >> IEEE_FLT_SIGN_BIT;
  e = ( ( i >> IEEE_FLT_MANTISSA_BITS ) & ( ( 1 << IEEE_FLT_EXPONENT_BITS ) - 1 ) ) - IEEE_FLT_EXPONENT_BIAS;
  m = ( i & ( ( 1 << IEEE_FLT_MANTISSA_BITS ) - 1 ) ) | ( 1 << IEEE_FLT_MANTISSA_BITS );
  shift = e - IEEE_FLT_MANTISSA_BITS;
  return ( ( ( ( m >> -shift ) | ( m << shift ) ) & ~( e >> 31 ) ) ^ s ) - s;
//#elif defined( __i386__ )
#elif 0
  int i = 0;
  __asm__ __volatile__ (
              "fld %1\n" \
              "fistp %0\n" \
              : "=m" (i) \
              : "m" (f) );
  return i;
#else
  return (int) f;
#endif
}

KM_INLINE unsigned long Math::Ftol( float f ) {
  return (unsigned long) f;
}

KM_INLINE unsigned long Math::FtolFast( float f ) {
#ifdef _WIN32
  // FIXME: this overflows on 31bits still .. same as FtoiFast
  unsigned long i;
  __asm fld    f
  __asm fistp    i    // use default rouding mode (round nearest)
  return i;
#elif 0            // round chop (C/C++ standard)
  int i, s, e, m, shift;
  i = *reinterpret_cast<int *>(&f);
  s = i >> IEEE_FLT_SIGN_BIT;
  e = ( ( i >> IEEE_FLT_MANTISSA_BITS ) & ( ( 1 << IEEE_FLT_EXPONENT_BITS ) - 1 ) ) - IEEE_FLT_EXPONENT_BIAS;
  m = ( i & ( ( 1 << IEEE_FLT_MANTISSA_BITS ) - 1 ) ) | ( 1 << IEEE_FLT_MANTISSA_BITS );
  shift = e - IEEE_FLT_MANTISSA_BITS;
  return ( ( ( ( m >> -shift ) | ( m << shift ) ) & ~( e >> 31 ) ) ^ s ) - s;
//#elif defined( __i386__ )
#elif 0
  // for some reason, on gcc I need to make sure i == 0 before performing a fistp
  int i = 0;
  __asm__ __volatile__ (
              "fld %1\n" \
              "fistp %0\n" \
              : "=m" (i) \
              : "m" (f) );
  return i;
#else
  return (unsigned long) f;
#endif
}

KM_INLINE signed char Math::ClampChar( int i ) {
  if ( i < -128 ) {
    return -128;
  }
  if ( i > 127 ) {
    return 127;
  }
  return i;
}

KM_INLINE signed short Math::ClampShort( int i ) {
  if ( i < -32768 ) {
    return -32768;
  }
  if ( i > 32767 ) {
    return 32767;
  }
  return i;
}

KM_INLINE int Math::ClampInt( int min, int max, int value ) {
  if ( value < min ) {
    return min;
  }
  if ( value > max ) {
    return max;
  }
  return value;
}

KM_INLINE float Math::ClampFloat( float min, float max, float value ) {
  if ( value < min ) {
    return min;
  }
  if ( value > max ) {
    return max;
  }
  return value;
}

KM_INLINE float Math::AngleNormalize360( float angle ) {
  if ( ( angle >= 360.0f ) || ( angle < 0.0f ) ) {
    angle -= floor( angle / 360.0f ) * 360.0f;
  }
  return angle;
}

KM_INLINE float Math::AngleNormalize180( float angle ) {
  angle = AngleNormalize360( angle );
  if ( angle > 180.0f ) {
    angle -= 360.0f;
  }
  return angle;
}

KM_INLINE float Math::AngleDelta( float angle1, float angle2 ) {
  return AngleNormalize180( angle1 - angle2 );
}
