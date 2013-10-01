#include "lbuffer.h"
#include "math.h"
#include "file.h"
#include "logs.h"


const Vec2 LBuffer::vecAxis( 1.0f, 0.0f );


LBuffer::LBuffer( int setSize, float setFloatSize )
  :size( setSize ), buffer( new float[ setSize ] ), sizeToFloat( 1.0f / float( setSize ) ), fSize( float( setSize ) ), sizeFloat( setFloatSize ), invSizeFloat( 1.0f / setFloatSize ), lightRadius( 1000.0f )
{
}


LBuffer::~LBuffer() {
  delete this->buffer;
}


void LBuffer::Clear( float value ) {
  for( int q = this->size; q; ) {
    this->buffer[ --q ] = value;
  }
  this->lightRadius = value;
}//Clear


void LBuffer::__Dump() {
  __log.PrintInfo( Filelevel_DEBUG, "LBuffer[x%p] size[%d]:", this, this->size );
  for( int q = 0; q < this->size; ++q ) {
    __log.PrintInfo( Filelevel_DEBUG, "[%d] %3.3f", q, this->buffer[ q ] );
  }
  __log.PrintInfo( Filelevel_DEBUG, "LBuffer done" );
}//__Dump


/*
===========
  DrawPolarLine
  проецирование линии, заданной в полярной системе координат
  Vec2 lineBegin: x - угол, y - радиус (полярные координаты)
===========
*/
void LBuffer::DrawPolarLine( const Vec2& lineBegin, const Vec2& lineEnd ) {
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
  //begin
  this->_PushValue( xBegin, pointBegin.y );
  //middle
  for( int x = xBegin + 1; x < xEnd; ++x ) {
    t = float( x - xBegin ) / float( xEnd - xBegin );
    value = pointBegin.y * ( 1.0f - t ) + pointEnd.y * t;
    this->_PushValue( x, value );
  }
  //end
  this->_PushValue( xEnd, pointEnd.y );
}//DrawPolarLine



void LBuffer::_PushValue( int position, float value ) {
  if( value < 0.0f ) {
    value = 0.0f;
  }
  if( value < this->buffer[ position ] ) {
    this->buffer[ position ] = value;
  }
}//_PushValue



/*
===========
  DrawLine
  проецировании линии, заданной в декартовых координатах
===========
*/
void LBuffer::DrawLine( const Vec2& point0, const Vec2& point1 ) {
  Vec2
    lineBegin( Vec2( this->GetDegreeOfPoint( point0 ), point0.LengthFast() ) ),
    lineEnd( Vec2( this->GetDegreeOfPoint( point1 ), point1.LengthFast() ) );
  Vec2 linearPointBegin, linearPointEnd;

  Vec2  pointBegin,
        pointEnd;
  if( lineBegin.x > lineEnd.x ) {
    pointBegin = lineEnd;
    pointEnd = lineBegin;
    linearPointBegin = point1;
    linearPointEnd = point0;
  } else {
    pointBegin = lineBegin;
    pointEnd = lineEnd;
    linearPointBegin = point0;
    linearPointEnd = point1;
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

  float value;
  Vec2 intersectPoint;
  bool firstIntersectFinded = false;
  for( int x = xBegin - 2; x <= xEnd + 2; ++x ) {
    float a = this->SizeToFloat( x, 0.001f );
    if( Vec2::TestIntersect(
      Vec2Null,
      Vec2( Math::Cos( a ) * this->lightRadius, -Math::Sin( a ) * this->lightRadius ),
      linearPointBegin,
      linearPointEnd,
      &intersectPoint,
      0.01f
    ) ) {
      value = intersectPoint.LengthFast();
      this->_PushValue( x, value );
    }
  }
}//DrawLine


float LBuffer::GetDegreeOfPoint( const Vec2& point ) {
  if( point.x > 0.0f && Math::Fabs( point.y ) < 0.01f ) {
    return ( point.y < 0.0f ? 0.0f : Math::TWO_PI );
  }
  Vec2 tmp( -point );
  tmp.NormalizeFast();
  float v = this->vecAxis * tmp;
  float deg = Math::ACos16( v );
  if( point.y < 0.0f ) {
    deg = Math::TWO_PI - deg;
  }
  deg += Math::PI;
  if( deg > Math::TWO_PI ) {
    deg -= Math::TWO_PI;
  }
  if( deg < 0.01f ) {
    deg = 0.0f;
  } else if( deg > Math::TWO_PI - 0.01f ) {
    deg = Math::TWO_PI;
  }
  return deg;
}//GetDegreeOfPoint


float LBuffer::GetValue( float x ) {
  if( x < 0.0f || x > this->sizeFloat ) {
    return 0.0f;
  }
  return this->buffer[ ( int ) this->FloatToSize( x ) ];
}//GetValue


float LBuffer::GetValueByIndex( int index ) {
  if( index < 0 || index >= this->size ) {
    return this->buffer[ 0 ];
  }
  return this->buffer[ index ];
}//GetValueByIndex
