#include "lbuffer.h"
#include "logs.h"
#include "math.h"


LBuffer::LBuffer( int setSize, float setFloatSize )
  :size( setSize ), buffer( new float[ setSize ] ), sizeToFloat( 1.0f / float( setSize ) ), fSize( float( setSize ) ), sizeFloat( setFloatSize ), invSizeFloat( 1.0f / setFloatSize )
{
}


LBuffer::~LBuffer() {
  delete this->buffer;
}


void LBuffer::Clear( float value ) {
  for( int q = this->size; q; ) {
    this->buffer[ --q ] = value;
  }
}//Clear


void LBuffer::__Dump() {
  LOGD( "LBuffer[x%p] size[%d]:\n", this, this->size );
  for( int q = 0; q < this->size; ++q ) {
    LOGD( "[%d] %3.3f\n", q, this->buffer[ q ] );
  }
  LOGD( "LBuffer done\n" );
}//__Dump


/*
===========
  Draw
  Vec2 lineBegin: x - координата точки [0.0; 1.0], y - глубина [0.0; ...]
===========
*/
void LBuffer::Draw( const Vec2& lineBegin, const Vec2& lineEnd ) {
  Vec2  pointBegin,
        pointEnd;
  if( lineBegin.x > lineEnd.x ) {
    pointBegin = lineEnd;
    pointEnd = lineBegin;
  } else {
    pointBegin = lineBegin;
    pointEnd = lineEnd;
  }
  int xBegin = this->Round( this->FloatToSize( pointBegin.x ) ),
        xEnd = this->Round( this->FloatToSize( pointEnd.x ) );
  if( xEnd < 0 || xBegin >= this->size ) {
    return;
  }
  if( xBegin < 0 ) {
    xBegin = 0;
  }
  if( xEnd > this->size - 1 ) {
    xEnd = this->size - 1;
  }

  if( xBegin == xEnd ) { //вырожденная линия
    this->buffer[ xBegin ] = pointBegin.y;
    return;
  }

  float value, t;
  Vec2 delta( 1.0f / ( pointEnd.x - pointBegin.x ), 1.0f / ( pointEnd.y - pointBegin.y ) );
  for( int x = xBegin; x <= xEnd; ++x ) {
    t = float( x - xBegin ) / float( xEnd - xBegin );
    value = pointBegin.y + ( pointEnd.y - pointBegin.y ) * t;
    if( value < 0 ) {
      value = 0.0f;
    }
    if( value < this->buffer[ x ] ) {
      this->buffer[ x ] = value;
    }
  }
}//Draw


float LBuffer::GetValue( float x ) {
  if( x < 0.0f || x > this->sizeFloat ) {
    return 0.0f;
  }
  return this->buffer[ ( int ) this->FloatToSize( x ) ];
}//GetValue
