#ifndef __LBUFFER_H__
#define __LBUFFER_H__


#include "klib.h"


class LBuffer
{
public:
  LBuffer( int setSize, float setFloatSize = 1.0f );
  virtual ~LBuffer();
  void Clear( float value );
  void __Dump();
  void DrawPolarLine( const Vec2& lineBegin, const Vec2& lineEnd );
  void DrawLine( const Vec2& point0, const Vec2& point1 );
  inline float GetSizeToFloatCoefficient() const {
    return this->sizeToFloat;
  }
  inline float FloatToSize( float value ) const {
    return value * this->fSize * this->invSizeFloat;
  }
  inline float SizeToFloat( int value ) const {
    return float( value ) * this->sizeToFloat * this->sizeFloat;
  }
  int Round( float value ) {
    return int( floorf( value ) - 0.5f );
  }
  float GetValue( float x );
  inline int GetSize() const {
    return this->size;
  }
  float GetDegreeOfPoint( const Vec2& point );

private:
  LBuffer();
  LBuffer( const LBuffer& );
  LBuffer& operator=( const LBuffer& );
  void _TestLinesIntersect( const Vec2& a0, const Vec2& b0, const Vec2& a1, const Vec2& b1, Vec2 *result );
  void _PushValue( int position, float value );

  const int size;
  const float sizeFloat;
  const float invSizeFloat;
  const float sizeToFloat;
  const float fSize;
  float *buffer;
  static const Vec2 vecAxis;
};


#endif
