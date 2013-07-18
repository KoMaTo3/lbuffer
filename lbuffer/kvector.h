#pragma once

#include "kmath.h"

class Angles;
class Mat3;
class Polar3;

class Vec2 {
public:
  float   x;
  float   y;

  Vec2( void );
  explicit Vec2( const float x, const float y );

  void      Set( const float x, const float y );
  void      Zero( void );

  float     operator[]( int index ) const;
  float &   operator[]( int index );
  Vec2      operator-() const;
  float     operator*( const Vec2 &a ) const;
  Vec2      operator*( const float a ) const;
  Vec2      operator/( const float a ) const;
  Vec2      operator+( const Vec2 &a ) const;
  Vec2      operator-( const Vec2 &a ) const;
  Vec2 &    operator+=( const Vec2 &a );
  Vec2 &    operator-=( const Vec2 &a );
  Vec2 &    operator/=( const Vec2 &a );
  Vec2 &    operator/=( const float a );
  Vec2 &    operator*=( const float a );

  friend Vec2  operator*( const float a, const Vec2 b );

  bool      Compare( const Vec2 &a ) const;              // exact compare, no epsilon
  bool      Compare( const Vec2 &a, const float epsilon ) const;    // compare with epsilon
  bool      operator==(  const Vec2 &a ) const;            // exact compare, no epsilon
  bool      operator!=(  const Vec2 &a ) const;            // exact compare, no epsilon

  float     Length( void ) const;
  float     LengthFast( void ) const;
  float     LengthSqr( void ) const;
  float     Normalize( void );      // returns length
  float     NormalizeFast( void );    // returns length
  Vec2 &    Truncate( float length );  // cap length
  void      Clamp( const Vec2 &min, const Vec2 &max );
  void      Snap( void );        // snap to closest integer value
  void      SnapInt( void );      // snap towards integer (floor)
  void      Rotate90CW(); //k
  void      Rotate90CCW();  //k
  Vec2      Projection( Vec2 &a );  //k
  float     Dot( const Vec2 &a ) const; //k

  int       GetDimension( void ) const;

  const float *  ToFloatPtr( void ) const;
  float *   ToFloatPtr( void );

  void      Lerp( const Vec2 &v1, const Vec2 &v2, const float l );
};

KM_INLINE Vec2::Vec2( void ) {
}

KM_INLINE Vec2::Vec2( const float x, const float y ) {
  this->x = x;
  this->y = y;
}

KM_INLINE void Vec2::Set( const float x, const float y ) {
  this->x = x;
  this->y = y;
}

KM_INLINE void Vec2::Zero( void ) {
  x = y = 0.0f;
}

KM_INLINE void Vec2::Rotate90CCW() {
  this->Set( this->y, -this->x );
}

KM_INLINE void Vec2::Rotate90CW() {
  this->Set( -this->y, this->x );
}

KM_INLINE Vec2 Vec2::Projection( Vec2 &a ) {
  return a * ( a.Dot( *this ) / a.LengthSqr() );
}

KM_INLINE float Vec2::Dot( const Vec2 &a ) const {
  return this->x * a.x + this->y * a.y;
}

KM_INLINE bool Vec2::Compare( const Vec2 &a ) const {
  return ( ( x == a.x ) && ( y == a.y ) );
}

KM_INLINE bool Vec2::Compare( const Vec2 &a, const float epsilon ) const {
  if ( Math::Fabs( x - a.x ) > epsilon ) {
    return false;
  }
      
  if ( Math::Fabs( y - a.y ) > epsilon ) {
    return false;
  }

  return true;
}

KM_INLINE bool Vec2::operator==( const Vec2 &a ) const {
  return Compare( a );
}

KM_INLINE bool Vec2::operator!=( const Vec2 &a ) const {
  return !Compare( a );
}

KM_INLINE float Vec2::operator[]( int index ) const {
  return ( &x )[ index ];
}

KM_INLINE float& Vec2::operator[]( int index ) {
  return ( &x )[ index ];
}

KM_INLINE float Vec2::Length( void ) const {
  return ( float )Math::Sqrt( x * x + y * y );
}

KM_INLINE float Vec2::LengthFast( void ) const {
  float sqrLength;

  sqrLength = x * x + y * y;
  return sqrLength * Math::RSqrt( sqrLength );
}

KM_INLINE float Vec2::LengthSqr( void ) const {
  return ( x * x + y * y );
}

KM_INLINE float Vec2::Normalize( void ) {
  float sqrLength, invLength;

  sqrLength = x * x + y * y;
  invLength = Math::InvSqrt( sqrLength );
  x *= invLength;
  y *= invLength;
  return invLength * sqrLength;
}

KM_INLINE float Vec2::NormalizeFast( void ) {
  float lengthSqr, invLength;

  lengthSqr = x * x + y * y;
  invLength = Math::RSqrt( lengthSqr );
  x *= invLength;
  y *= invLength;
  return invLength * lengthSqr;
}

KM_INLINE Vec2 &Vec2::Truncate( float length ) {
  float length2;
  float ilength;

  if ( !length ) {
    Zero();
  }
  else {
    length2 = LengthSqr();
    if ( length2 > length * length ) {
      ilength = length * Math::InvSqrt( length2 );
      x *= ilength;
      y *= ilength;
    }
  }

  return *this;
}

KM_INLINE void Vec2::Clamp( const Vec2 &min, const Vec2 &max ) {
  if ( x < min.x ) {
    x = min.x;
  } else if ( x > max.x ) {
    x = max.x;
  }
  if ( y < min.y ) {
    y = min.y;
  } else if ( y > max.y ) {
    y = max.y;
  }
}

KM_INLINE void Vec2::Snap( void ) {
  x = floor( x + 0.5f );
  y = floor( y + 0.5f );
}

KM_INLINE void Vec2::SnapInt( void ) {
  x = float( int( x ) );
  y = float( int( y ) );
}

KM_INLINE Vec2 Vec2::operator-() const {
  return Vec2( -x, -y );
}
  
KM_INLINE Vec2 Vec2::operator-( const Vec2 &a ) const {
  return Vec2( x - a.x, y - a.y );
}

KM_INLINE float Vec2::operator*( const Vec2 &a ) const {
  return x * a.x + y * a.y;
}

KM_INLINE Vec2 Vec2::operator*( const float a ) const {
  return Vec2( x * a, y * a );
}

KM_INLINE Vec2 Vec2::operator/( const float a ) const {
  float inva = 1.0f / a;
  return Vec2( x * inva, y * inva );
}

KM_INLINE Vec2 operator*( const float a, const Vec2 b ) {
  return Vec2( b.x * a, b.y * a );
}

KM_INLINE Vec2 Vec2::operator+( const Vec2 &a ) const {
  return Vec2( x + a.x, y + a.y );
}

KM_INLINE Vec2 &Vec2::operator+=( const Vec2 &a ) {
  x += a.x;
  y += a.y;

  return *this;
}

KM_INLINE Vec2 &Vec2::operator/=( const Vec2 &a ) {
  x /= a.x;
  y /= a.y;

  return *this;
}

KM_INLINE Vec2 &Vec2::operator/=( const float a ) {
  float inva = 1.0f / a;
  x *= inva;
  y *= inva;

  return *this;
}

KM_INLINE Vec2 &Vec2::operator-=( const Vec2 &a ) {
  x -= a.x;
  y -= a.y;

  return *this;
}

KM_INLINE Vec2 &Vec2::operator*=( const float a ) {
  x *= a;
  y *= a;

  return *this;
}

KM_INLINE int Vec2::GetDimension( void ) const {
  return 2;
}

KM_INLINE const float *Vec2::ToFloatPtr( void ) const {
  return &x;
}

KM_INLINE float *Vec2::ToFloatPtr( void ) {
  return &x;
}


//===============================================================
//
//  Vec3 - 3D vector
//
//===============================================================

class Vec3 {
public:
  float     x;
  float     y;
  float     z;

  Vec3( void );
  explicit Vec3( const float x, const float y, const float z );

  void      Set( const float x, const float y, const float z );
  void      Zero( void );

  float     operator[]( const int index ) const;
  float &   operator[]( const int index );
  Vec3      operator-() const;
  Vec3 &    operator=( const Vec3 &a );    // required because of a msvc 6 & 7 bug
  float     operator*( const Vec3 &a ) const;
  Vec3      operator*( const float a ) const;
  Vec3      operator/( const float a ) const;
  Vec3      operator+( const Vec3 &a ) const;
  Vec3      operator-( const Vec3 &a ) const;
  Vec3 &    operator+=( const Vec3 &a );
  Vec3 &    operator-=( const Vec3 &a );
  Vec3 &    operator/=( const Vec3 &a );
  Vec3 &    operator/=( const float a );
  Vec3 &    operator*=( const float a );

  friend Vec3  operator*( const float a, const Vec3 b );

  bool      Compare( const Vec3 &a ) const;              // exact compare, no epsilon
  bool      Compare( const Vec3 &a, const float epsilon ) const;    // compare with epsilon
  bool      operator==(  const Vec3 &a ) const;            // exact compare, no epsilon
  bool      operator!=(  const Vec3 &a ) const;            // exact compare, no epsilon

  bool      FixDegenerateNormal( void );  // fix degenerate axial cases
  bool      FixDenormals( void );      // change tiny numbers to zero

  Vec3      Cross( const Vec3 &a ) const;
  Vec3 &    Cross( const Vec3 &a, const Vec3 &b );
  float     Length( void ) const;
  float     LengthSqr( void ) const;
  float     LengthFast( void ) const;
  float     Normalize( void );        // returns length
  float     NormalizeFast( void );      // returns length
  Vec3 &    Truncate( float length );    // cap length
  void      Clamp( const Vec3 &min, const Vec3 &max );
  void      Snap( void );          // snap to closest integer value
  void      SnapInt( void );        // snap towards integer (floor)

  int       GetDimension( void ) const;

  float     ToYaw( void ) const;
  float     ToPitch( void ) const;
  Angles    ToAngles( void ) const;
  Polar3    ToPolar( void ) const;
  Mat3      ToMat3( void ) const;    // vector should be normalized
  const Vec2 &  ToVec2( void ) const;
  Vec2 &    ToVec2( void );
  const float *  ToFloatPtr( void ) const;
  float *   ToFloatPtr( void );

  void      NormalVectors( Vec3 &left, Vec3 &down ) const;  // vector should be normalized
  void      OrthogonalBasis( Vec3 &left, Vec3 &up ) const;

  void      ProjectOntoPlane( const Vec3 &normal, const float overBounce = 1.0f );
  bool      ProjectAlongPlane( const Vec3 &normal, const float epsilon, const float overBounce = 1.0f );
  void      ProjectSelfOntoSphere( const float radius );

  void      Lerp( const Vec3 &v1, const Vec3 &v2, const float l );
  void      SLerp( const Vec3 &v1, const Vec3 &v2, const float l );
};

KM_INLINE Vec3::Vec3( void ) {
}

KM_INLINE Vec3::Vec3( const float x, const float y, const float z ) {
  this->x = x;
  this->y = y;
  this->z = z;
}

KM_INLINE float Vec3::operator[]( const int index ) const {
  return ( &x )[ index ];
}

KM_INLINE float &Vec3::operator[]( const int index ) {
  return ( &x )[ index ];
}

KM_INLINE void Vec3::Set( const float x, const float y, const float z ) {
  this->x = x;
  this->y = y;
  this->z = z;
}

KM_INLINE void Vec3::Zero( void ) {
  x = y = z = 0.0f;
}

KM_INLINE Vec3 Vec3::operator-() const {
  return Vec3( -x, -y, -z );
}

KM_INLINE Vec3 &Vec3::operator=( const Vec3 &a ) {
  x = a.x;
  y = a.y;
  z = a.z;
  return *this;
}

KM_INLINE Vec3 Vec3::operator-( const Vec3 &a ) const {
  return Vec3( x - a.x, y - a.y, z - a.z );
}

KM_INLINE float Vec3::operator*( const Vec3 &a ) const {
  return x * a.x + y * a.y + z * a.z;
}

KM_INLINE Vec3 Vec3::operator*( const float a ) const {
  return Vec3( x * a, y * a, z * a );
}

KM_INLINE Vec3 Vec3::operator/( const float a ) const {
  float inva = 1.0f / a;
  return Vec3( x * inva, y * inva, z * inva );
}

KM_INLINE Vec3 operator*( const float a, const Vec3 b ) {
  return Vec3( b.x * a, b.y * a, b.z * a );
}

KM_INLINE Vec3 Vec3::operator+( const Vec3 &a ) const {
  return Vec3( x + a.x, y + a.y, z + a.z );
}

KM_INLINE Vec3 &Vec3::operator+=( const Vec3 &a ) {
  x += a.x;
  y += a.y;
  z += a.z;

  return *this;
}

KM_INLINE Vec3 &Vec3::operator/=( const Vec3 &a ) {
  x /= a.x;
  y /= a.y;
  z /= a.z;

  return *this;
}

KM_INLINE Vec3 &Vec3::operator/=( const float a ) {
  float inva = 1.0f / a;
  x *= inva;
  y *= inva;
  z *= inva;

  return *this;
}

KM_INLINE Vec3 &Vec3::operator-=( const Vec3 &a ) {
  x -= a.x;
  y -= a.y;
  z -= a.z;

  return *this;
}

KM_INLINE Vec3 &Vec3::operator*=( const float a ) {
  x *= a;
  y *= a;
  z *= a;

  return *this;
}

KM_INLINE bool Vec3::Compare( const Vec3 &a ) const {
  return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) );
}

KM_INLINE bool Vec3::Compare( const Vec3 &a, const float epsilon ) const {
  if ( Math::Fabs( x - a.x ) > epsilon ) {
    return false;
  }
      
  if ( Math::Fabs( y - a.y ) > epsilon ) {
    return false;
  }

  if ( Math::Fabs( z - a.z ) > epsilon ) {
    return false;
  }

  return true;
}

KM_INLINE bool Vec3::operator==( const Vec3 &a ) const {
  return Compare( a );
}

KM_INLINE bool Vec3::operator!=( const Vec3 &a ) const {
  return !Compare( a );
}

KM_INLINE float Vec3::NormalizeFast( void ) {
  float sqrLength, invLength;

  sqrLength = x * x + y * y + z * z;
  invLength = Math::RSqrt( sqrLength );
  x *= invLength;
  y *= invLength;
  z *= invLength;
  return invLength * sqrLength;
}

KM_INLINE bool Vec3::FixDegenerateNormal( void ) {
  if ( x == 0.0f ) {
    if ( y == 0.0f ) {
      if ( z > 0.0f ) {
        if ( z != 1.0f ) {
          z = 1.0f;
          return true;
        }
      } else {
        if ( z != -1.0f ) {
          z = -1.0f;
          return true;
        }
      }
      return false;
    } else if ( z == 0.0f ) {
      if ( y > 0.0f ) {
        if ( y != 1.0f ) {
          y = 1.0f;
          return true;
        }
      } else {
        if ( y != -1.0f ) {
          y = -1.0f;
          return true;
        }
      }
      return false;
    }
  } else if ( y == 0.0f ) {
    if ( z == 0.0f ) {
      if ( x > 0.0f ) {
        if ( x != 1.0f ) {
          x = 1.0f;
          return true;
        }
      } else {
        if ( x != -1.0f ) {
          x = -1.0f;
          return true;
        }
      }
      return false;
    }
  }
  if ( Math::Fabs( x ) == 1.0f ) {
    if ( y != 0.0f || z != 0.0f ) {
      y = z = 0.0f;
      return true;
    }
    return false;
  } else if ( Math::Fabs( y ) == 1.0f ) {
    if ( x != 0.0f || z != 0.0f ) {
      x = z = 0.0f;
      return true;
    }
    return false;
  } else if ( Math::Fabs( z ) == 1.0f ) {
    if ( x != 0.0f || y != 0.0f ) {
      x = y = 0.0f;
      return true;
    }
    return false;
  }
  return false;
}

KM_INLINE bool Vec3::FixDenormals( void ) {
  bool denormal = false;
  if ( fabs( x ) < 1e-30f ) {
    x = 0.0f;
    denormal = true;
  }
  if ( fabs( y ) < 1e-30f ) {
    y = 0.0f;
    denormal = true;
  }
  if ( fabs( z ) < 1e-30f ) {
    z = 0.0f;
    denormal = true;
  }
  return denormal;
}

KM_INLINE Vec3 Vec3::Cross( const Vec3 &a ) const {
  return Vec3( y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x );
}

KM_INLINE Vec3 &Vec3::Cross( const Vec3 &a, const Vec3 &b ) {
  x = a.y * b.z - a.z * b.y;
  y = a.z * b.x - a.x * b.z;
  z = a.x * b.y - a.y * b.x;

  return *this;
}

KM_INLINE float Vec3::Length( void ) const {
  return ( float )Math::Sqrt( x * x + y * y + z * z );
}

KM_INLINE float Vec3::LengthSqr( void ) const {
  return ( x * x + y * y + z * z );
}

KM_INLINE float Vec3::LengthFast( void ) const {
  float sqrLength;

  sqrLength = x * x + y * y + z * z;
  return sqrLength * Math::RSqrt( sqrLength );
}

KM_INLINE float Vec3::Normalize( void ) {
  float sqrLength, invLength;

  sqrLength = x * x + y * y + z * z;
  invLength = Math::InvSqrt( sqrLength );
  x *= invLength;
  y *= invLength;
  z *= invLength;
  return invLength * sqrLength;
}

KM_INLINE Vec3 &Vec3::Truncate( float length ) {
  float length2;
  float ilength;

  if ( !length ) {
    Zero();
  }
  else {
    length2 = LengthSqr();
    if ( length2 > length * length ) {
      ilength = length * Math::InvSqrt( length2 );
      x *= ilength;
      y *= ilength;
      z *= ilength;
    }
  }

  return *this;
}

KM_INLINE void Vec3::Clamp( const Vec3 &min, const Vec3 &max ) {
  if ( x < min.x ) {
    x = min.x;
  } else if ( x > max.x ) {
    x = max.x;
  }
  if ( y < min.y ) {
    y = min.y;
  } else if ( y > max.y ) {
    y = max.y;
  }
  if ( z < min.z ) {
    z = min.z;
  } else if ( z > max.z ) {
    z = max.z;
  }
}

KM_INLINE void Vec3::Snap( void ) {
  x = floor( x + 0.5f );
  y = floor( y + 0.5f );
  z = floor( z + 0.5f );
}

KM_INLINE void Vec3::SnapInt( void ) {
  x = float( int( x ) );
  y = float( int( y ) );
  z = float( int( z ) );
}

KM_INLINE int Vec3::GetDimension( void ) const {
  return 3;
}

KM_INLINE const Vec2 &Vec3::ToVec2( void ) const {
  return *reinterpret_cast<const Vec2 *>(this);
}

KM_INLINE Vec2 &Vec3::ToVec2( void ) {
  return *reinterpret_cast<Vec2 *>(this);
}

KM_INLINE const float *Vec3::ToFloatPtr( void ) const {
  return &x;
}

KM_INLINE float *Vec3::ToFloatPtr( void ) {
  return &x;
}

KM_INLINE void Vec3::NormalVectors( Vec3 &left, Vec3 &down ) const {
  float d;

  d = x * x + y * y;
  if ( !d ) {
    left[0] = 1;
    left[1] = 0;
    left[2] = 0;
  } else {
    d = Math::InvSqrt( d );
    left[0] = -y * d;
    left[1] = x * d;
    left[2] = 0;
  }
  down = left.Cross( *this );
}

KM_INLINE void Vec3::OrthogonalBasis( Vec3 &left, Vec3 &up ) const {
  float l, s;

  if ( Math::Fabs( z ) > 0.7f ) {
    l = y * y + z * z;
    s = Math::InvSqrt( l );
    up[0] = 0;
    up[1] = z * s;
    up[2] = -y * s;
    left[0] = l * s;
    left[1] = -x * up[2];
    left[2] = x * up[1];
  }
  else {
    l = x * x + y * y;
    s = Math::InvSqrt( l );
    left[0] = -y * s;
    left[1] = x * s;
    left[2] = 0;
    up[0] = -z * left[1];
    up[1] = z * left[0];
    up[2] = l * s;
  }
}

KM_INLINE void Vec3::ProjectOntoPlane( const Vec3 &normal, const float overBounce ) {
  float backoff;
  
  backoff = *this * normal;
  
  if ( overBounce != 1.0 ) {
    if ( backoff < 0 ) {
      backoff *= overBounce;
    } else {
      backoff /= overBounce;
    }
  }

  *this -= backoff * normal;
}

KM_INLINE bool Vec3::ProjectAlongPlane( const Vec3 &normal, const float epsilon, const float overBounce ) {
  Vec3 cross;
  float len;

  cross = this->Cross( normal ).Cross( (*this) );
  // normalize so a fixed epsilon can be used
  cross.Normalize();
  len = normal * cross;
  if ( Math::Fabs( len ) < epsilon ) {
    return false;
  }
  cross *= overBounce * ( normal * (*this) ) / len;
  (*this) -= cross;
  return true;
}


//===============================================================
//
//  Vec4 - 4D vector
//
//===============================================================

class Vec4 {
public:
  float     x;
  float     y;
  float     z;
  float     w;

  Vec4( void );
  explicit Vec4( const float x, const float y, const float z, const float w );

  void      Set( const float x, const float y, const float z, const float w );
  void      Zero( void );

  float     operator[]( const int index ) const;
  float &   operator[]( const int index );
  Vec4      operator-() const;
  float     operator*( const Vec4 &a ) const;
  Vec4      operator*( const float a ) const;
  Vec4      operator/( const float a ) const;
  Vec4      operator+( const Vec4 &a ) const;
  Vec4      operator-( const Vec4 &a ) const;
  Vec4 &    operator+=( const Vec4 &a );
  Vec4 &    operator-=( const Vec4 &a );
  Vec4 &    operator/=( const Vec4 &a );
  Vec4 &    operator/=( const float a );
  Vec4 &    operator*=( const float a );

  friend Vec4  operator*( const float a, const Vec4 b );

  bool      Compare( const Vec4 &a ) const;              // exact compare, no epsilon
  bool      Compare( const Vec4 &a, const float epsilon ) const;    // compare with epsilon
  bool      operator==(  const Vec4 &a ) const;            // exact compare, no epsilon
  bool      operator!=(  const Vec4 &a ) const;            // exact compare, no epsilon

  float     Length( void ) const;
  float     LengthSqr( void ) const;
  float     Normalize( void );      // returns length
  float     NormalizeFast( void );    // returns length

  int       GetDimension( void ) const;

  const Vec2 &  ToVec2( void ) const;
  Vec2 &    ToVec2( void );
  const Vec3 &  ToVec3( void ) const;
  Vec3 &    ToVec3( void );
  const float *  ToFloatPtr( void ) const;
  float *   ToFloatPtr( void );

  void      Lerp( const Vec4 &v1, const Vec4 &v2, const float l );
};

KM_INLINE Vec4::Vec4( void ) {
}

KM_INLINE Vec4::Vec4( const float x, const float y, const float z, const float w ) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

KM_INLINE void Vec4::Set( const float x, const float y, const float z, const float w ) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

KM_INLINE void Vec4::Zero( void ) {
  x = y = z = w = 0.0f;
}

KM_INLINE float Vec4::operator[]( int index ) const {
  return ( &x )[ index ];
}

KM_INLINE float& Vec4::operator[]( int index ) {
  return ( &x )[ index ];
}

KM_INLINE Vec4 Vec4::operator-() const {
  return Vec4( -x, -y, -z, -w );
}

KM_INLINE Vec4 Vec4::operator-( const Vec4 &a ) const {
  return Vec4( x - a.x, y - a.y, z - a.z, w - a.w );
}

KM_INLINE float Vec4::operator*( const Vec4 &a ) const {
  return x * a.x + y * a.y + z * a.z + w * a.w;
}

KM_INLINE Vec4 Vec4::operator*( const float a ) const {
  return Vec4( x * a, y * a, z * a, w * a );
}

KM_INLINE Vec4 Vec4::operator/( const float a ) const {
  float inva = 1.0f / a;
  return Vec4( x * inva, y * inva, z * inva, w * inva );
}

KM_INLINE Vec4 operator*( const float a, const Vec4 b ) {
  return Vec4( b.x * a, b.y * a, b.z * a, b.w * a );
}

KM_INLINE Vec4 Vec4::operator+( const Vec4 &a ) const {
  return Vec4( x + a.x, y + a.y, z + a.z, w + a.w );
}

KM_INLINE Vec4 &Vec4::operator+=( const Vec4 &a ) {
  x += a.x;
  y += a.y;
  z += a.z;
  w += a.w;

  return *this;
}

KM_INLINE Vec4 &Vec4::operator/=( const Vec4 &a ) {
  x /= a.x;
  y /= a.y;
  z /= a.z;
  w /= a.w;

  return *this;
}

KM_INLINE Vec4 &Vec4::operator/=( const float a ) {
  float inva = 1.0f / a;
  x *= inva;
  y *= inva;
  z *= inva;
  w *= inva;

  return *this;
}

KM_INLINE Vec4 &Vec4::operator-=( const Vec4 &a ) {
  x -= a.x;
  y -= a.y;
  z -= a.z;
  w -= a.w;

  return *this;
}

KM_INLINE Vec4 &Vec4::operator*=( const float a ) {
  x *= a;
  y *= a;
  z *= a;
  w *= a;

  return *this;
}

KM_INLINE bool Vec4::Compare( const Vec4 &a ) const {
  return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) && w == a.w );
}

KM_INLINE bool Vec4::Compare( const Vec4 &a, const float epsilon ) const {
  if ( Math::Fabs( x - a.x ) > epsilon ) {
    return false;
  }
      
  if ( Math::Fabs( y - a.y ) > epsilon ) {
    return false;
  }

  if ( Math::Fabs( z - a.z ) > epsilon ) {
    return false;
  }

  if ( Math::Fabs( w - a.w ) > epsilon ) {
    return false;
  }

  return true;
}

KM_INLINE bool Vec4::operator==( const Vec4 &a ) const {
  return Compare( a );
}

KM_INLINE bool Vec4::operator!=( const Vec4 &a ) const {
  return !Compare( a );
}

KM_INLINE float Vec4::Length( void ) const {
  return ( float )Math::Sqrt( x * x + y * y + z * z + w * w );
}

KM_INLINE float Vec4::LengthSqr( void ) const {
  return ( x * x + y * y + z * z + w * w );
}

KM_INLINE float Vec4::Normalize( void ) {
  float sqrLength, invLength;

  sqrLength = x * x + y * y + z * z + w * w;
  invLength = Math::InvSqrt( sqrLength );
  x *= invLength;
  y *= invLength;
  z *= invLength;
  w *= invLength;
  return invLength * sqrLength;
}

KM_INLINE float Vec4::NormalizeFast( void ) {
  float sqrLength, invLength;

  sqrLength = x * x + y * y + z * z + w * w;
  invLength = Math::RSqrt( sqrLength );
  x *= invLength;
  y *= invLength;
  z *= invLength;
  w *= invLength;
  return invLength * sqrLength;
}

KM_INLINE int Vec4::GetDimension( void ) const {
  return 4;
}

KM_INLINE const Vec2 &Vec4::ToVec2( void ) const {
  return *reinterpret_cast<const Vec2 *>(this);
}

KM_INLINE Vec2 &Vec4::ToVec2( void ) {
  return *reinterpret_cast<Vec2 *>(this);
}

KM_INLINE const Vec3 &Vec4::ToVec3( void ) const {
  return *reinterpret_cast<const Vec3 *>(this);
}

KM_INLINE Vec3 &Vec4::ToVec3( void ) {
  return *reinterpret_cast<Vec3 *>(this);
}

KM_INLINE const float *Vec4::ToFloatPtr( void ) const {
  return &x;
}

KM_INLINE float *Vec4::ToFloatPtr( void ) {
  return &x;
}




class Polar3 {
public:
  float     radius, theta, phi;

  Polar3( void );
  explicit Polar3( const float radius, const float theta, const float phi );

  void      Set( const float radius, const float theta, const float phi );

  float     operator[]( const int index ) const;
  float &   operator[]( const int index );
  Polar3    operator-() const;
  Polar3 &  operator=( const Polar3 &a );

  Vec3      ToVec3( void ) const;
};

KM_INLINE Polar3::Polar3( void ) {
}

KM_INLINE Polar3::Polar3( const float radius, const float theta, const float phi ) {
  assert( radius > 0 );
  this->radius = radius;
  this->theta = theta;
  this->phi = phi;
}
  
KM_INLINE void Polar3::Set( const float radius, const float theta, const float phi ) {
  assert( radius > 0 );
  this->radius = radius;
  this->theta = theta;
  this->phi = phi;
}

KM_INLINE float Polar3::operator[]( const int index ) const {
  return ( &radius )[ index ];
}

KM_INLINE float &Polar3::operator[]( const int index ) {
  return ( &radius )[ index ];
}

KM_INLINE Polar3 Polar3::operator-() const {
  return Polar3( radius, -theta, -phi );
}

KM_INLINE Polar3 &Polar3::operator=( const Polar3 &a ) { 
  radius = a.radius;
  theta = a.theta;
  phi = a.phi;
  return *this;
}

KM_INLINE Vec3 Polar3::ToVec3( void ) const {
  float sp, cp, st, ct;
  Math::SinCos( phi, sp, cp );
  Math::SinCos( theta, st, ct );
   return Vec3( cp * radius * ct, cp * radius * st, radius * sp );
}


extern Vec2 Vec2Null;
extern Vec2 Vec2One;
extern Vec3 Vec3Null;
extern Vec3 Vec3One;
extern Vec4 Vec4Null;
extern Vec4 Vec4One;
