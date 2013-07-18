#include "logs.h"
#include "lbuffer.h"
#include "klib.h"


LBuffer *buffer = nullptr;


int main() {
  Math::Init();
  buffer = new LBuffer( 16 );
  buffer->Clear( 1000.0f );
  //buffer->Draw( Vec2( 0.2f, 0.5f ), Vec2( 0.5f, 0.5f ) );
  buffer->Draw( Vec2( 0.0f, 1.0f ), Vec2( 0.5f, 8.0f ) );
  buffer->Draw( Vec2( 0.5f, 2.0f ), Vec2( 1.0f, 3.0f ) );
  buffer->Draw( Vec2( 0.0f, 11.0f ), Vec2( 1.0f, 0.0f ) );
  buffer->Draw( Vec2( 0.5f, 0.123f ), Vec2( 0.5f, 0.321f ) );
  buffer->__Dump();

  float x = 0.3f;
  LOGD( "Test: pos[%3.3f] iPos[%d] value[%3.3f] result[%s]\n", x, ( int ) buffer->FloatToSize( x ), buffer->GetValue( x ), ( buffer->GetValue( x ) == 5.0f ? "ok" : "failed" ) );
  x = 0.7f;
  LOGD( "Test: pos[%3.3f] iPos[%d] value[%3.3f] result[%s]\n", x, ( int ) buffer->FloatToSize( x ), buffer->GetValue( x ), ( buffer->GetValue( x ) == 2.5f ? "ok" : "failed" ) );

  delete buffer;
  LOGD( "\n\nDone: " );
  return 0;
}//main
