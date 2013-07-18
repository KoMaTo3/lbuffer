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
  void Draw( const Vec2& lineBegin, const Vec2& lineEnd );
  inline float GetSizeToFloatCoefficient() const {
    return this->sizeToFloat;
  }
  inline float FloatToSize( float value ) const {
    return value * this->fSize * this->invSizeFloat;
  }
  inline float SizeToFloat( int value ) const {
    return float( value ) * sizeToFloat * this->sizeFloat;
  }
  int Round( float value ) {
    return int( floorf( value ) - 0.5f );
  }
  float GetValue( float x );

private:
  LBuffer();
  LBuffer( const LBuffer& );
  LBuffer& operator=( const LBuffer& );

  const int size;
  const float sizeFloat;
  const float invSizeFloat;
  const float sizeToFloat;
  const float fSize;
  float *buffer;
};


#endif
