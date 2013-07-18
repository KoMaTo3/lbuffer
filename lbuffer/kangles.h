#pragma once

#include "klib.h"

class Vec3;
class Quat;
class Rotation;
class Mat3;
class Mat4;

class Angles {
public:
  float     pitch;
  float     yaw;
  float     roll;

  Angles( void );
  Angles( float pitch, float yaw, float roll );
  explicit Angles( const Vec3 &v );

  void      Set( float pitch, float yaw, float roll );
  Angles &  Zero( void );

  float     operator[]( int index ) const;
  float &   operator[]( int index );
  Angles    operator-() const;      // negate angles, in general not the inverse rotation
  Angles &  operator=( const Angles &a );
  Angles    operator+( const Angles &a ) const;
  Angles &  operator+=( const Angles &a );
  Angles    operator-( const Angles &a ) const;
  Angles &  operator-=( const Angles &a );
  Angles    operator*( const float a ) const;
  Angles &  operator*=( const float a );
  Angles    operator/( const float a ) const;
  Angles &  operator/=( const float a );

  friend Angles  operator*( const float a, const Angles &b );

  bool      Compare( const Angles &a ) const;              // exact compare, no epsilon
  bool      Compare( const Angles &a, const float epsilon ) const;  // compare with epsilon
  bool      operator==(  const Angles &a ) const;            // exact compare, no epsilon
  bool      operator!=(  const Angles &a ) const;            // exact compare, no epsilon

  Angles &  Normalize360( void );  // normalizes 'this'
  Angles &  Normalize180( void );  // normalizes 'this'

  void      Clamp( const Angles &min, const Angles &max );

  int       GetDimension( void ) const;

  void      ToVectors( Vec3 *forward, Vec3 *right = NULL, Vec3 *up = NULL ) const;
  Vec3      ToForward( void ) const;
  Quat      ToQuat( void ) const;
  Rotation  ToRotation( void ) const;
  Mat3      ToMat3( void ) const;
  Mat4      ToMat4( void ) const;
  Vec3      ToAngularVelocity( void ) const;
  const float *  ToFloatPtr( void ) const;
  float *   ToFloatPtr( void );
};

extern Angles ang_zero;

KM_INLINE Angles::Angles( void ) {
}

KM_INLINE Angles::Angles( float pitch, float yaw, float roll ) {
  this->pitch = pitch;
  this->yaw   = yaw;
  this->roll  = roll;
}

KM_INLINE Angles::Angles( const Vec3 &v ) {
  this->pitch = v[0];
  this->yaw   = v[1];
  this->roll  = v[2];
}

KM_INLINE void Angles::Set( float pitch, float yaw, float roll ) {
  this->pitch = pitch;
  this->yaw   = yaw;
  this->roll  = roll;
}

KM_INLINE Angles &Angles::Zero( void ) {
  pitch = yaw = roll = 0.0f;
  return *this;
}

KM_INLINE float Angles::operator[]( int index ) const {
  assert( ( index >= 0 ) && ( index < 3 ) );
  return ( &pitch )[ index ];
}

KM_INLINE float &Angles::operator[]( int index ) {
  assert( ( index >= 0 ) && ( index < 3 ) );
  return ( &pitch )[ index ];
}

KM_INLINE Angles Angles::operator-() const {
  return Angles( -pitch, -yaw, -roll );
}

KM_INLINE Angles &Angles::operator=( const Angles &a ) {
  pitch = a.pitch;
  yaw   = a.yaw;
  roll  = a.roll;
  return *this;
}

KM_INLINE Angles Angles::operator+( const Angles &a ) const {
  return Angles( pitch + a.pitch, yaw + a.yaw, roll + a.roll );
}

KM_INLINE Angles& Angles::operator+=( const Angles &a ) {
  pitch += a.pitch;
  yaw   += a.yaw;
  roll  += a.roll;

  return *this;
}

KM_INLINE Angles Angles::operator-( const Angles &a ) const {
  return Angles( pitch - a.pitch, yaw - a.yaw, roll - a.roll );
}

KM_INLINE Angles& Angles::operator-=( const Angles &a ) {
  pitch -= a.pitch;
  yaw   -= a.yaw;
  roll  -= a.roll;

  return *this;
}

KM_INLINE Angles Angles::operator*( const float a ) const {
  return Angles( pitch * a, yaw * a, roll * a );
}

KM_INLINE Angles& Angles::operator*=( float a ) {
  pitch *= a;
  yaw   *= a;
  roll  *= a;
  return *this;
}

KM_INLINE Angles Angles::operator/( const float a ) const {
  float inva = 1.0f / a;
  return Angles( pitch * inva, yaw * inva, roll * inva );
}

KM_INLINE Angles& Angles::operator/=( float a ) {
  float inva = 1.0f / a;
  pitch *= inva;
  yaw   *= inva;
  roll  *= inva;
  return *this;
}

KM_INLINE Angles operator*( const float a, const Angles &b ) {
  return Angles( a * b.pitch, a * b.yaw, a * b.roll );
}

KM_INLINE bool Angles::Compare( const Angles &a ) const {
  return ( ( a.pitch == pitch ) && ( a.yaw == yaw ) && ( a.roll == roll ) );
}

KM_INLINE bool Angles::Compare( const Angles &a, const float epsilon ) const {
  if ( Math::Fabs( pitch - a.pitch ) > epsilon ) {
    return false;
  }

  if ( Math::Fabs( yaw - a.yaw ) > epsilon ) {
    return false;
  }

  if ( Math::Fabs( roll - a.roll ) > epsilon ) {
    return false;
  }

  return true;
}

KM_INLINE bool Angles::operator==( const Angles &a ) const {
  return Compare( a );
}

KM_INLINE bool Angles::operator!=( const Angles &a ) const {
  return !Compare( a );
}

KM_INLINE void Angles::Clamp( const Angles &min, const Angles &max ) {
  if ( pitch < min.pitch ) {
    pitch = min.pitch;
  } else if ( pitch > max.pitch ) {
    pitch = max.pitch;
  }
  if ( yaw < min.yaw ) {
    yaw = min.yaw;
  } else if ( yaw > max.yaw ) {
    yaw = max.yaw;
  }
  if ( roll < min.roll ) {
    roll = min.roll;
  } else if ( roll > max.roll ) {
    roll = max.roll;
  }
}

KM_INLINE int Angles::GetDimension( void ) const {
  return 3;
}

KM_INLINE const float *Angles::ToFloatPtr( void ) const {
  return &pitch;
}

KM_INLINE float *Angles::ToFloatPtr( void ) {
  return &pitch;
}
