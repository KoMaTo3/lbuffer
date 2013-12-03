#include "lib/logs.h"
#include "lbuffer.h"
#include "lib/klib.h"


LBuffer *buffer = nullptr;


class Object: public ILBufferProjectedObject {
public:
  Vec2 position;
  Vec2 size;

  virtual const Vec2& GetPosition() const {
    return this->position;
  }

  virtual const Vec2& GetSize() const {
    return this->size;
  }
};


int main() {
  Math::Init();
  buffer = new LBuffer( 16 );
  Object obj0;
  obj0.position.Set( 5.0f, 3.0f );
  buffer->Clear( 1000.0f );
  LBufferCacheEntity *cache = NULL;
  if( buffer->IsObjectCached( &obj0, &cache ) ) {
    printf( "write from cache [1]\n" );
    buffer->WriteFromCache( cache );
  } else {
    printf( "cache missed, new draw [1]\n" );
    cache->Reset( obj0.GetPosition(), obj0.GetSize() );
    buffer->DrawLine( cache, Vec2( 20.0, 5.0f ), Vec2( 25.0f, 35.5f ) );
    buffer->DrawLine( cache, Vec2( 0.0f, 10.0f ), Vec2( 45.0f, 48.0f ) );
    buffer->DrawLine( cache, Vec2( 50.0f, 20.0f ), Vec2( 10.0f, 53.0f ) );
    buffer->DrawLine( cache, Vec2( 0.0f, 11.0f ), Vec2( 10.0f, 60.1f ) );
    buffer->DrawLine( cache, Vec2( 55.0f, 12.3f ), Vec2( 15.0f, 70.321f ) );
  }
  if( buffer->IsObjectCached( &obj0, &cache ) ) {
    printf( "write from cache [2]\n" );
    buffer->WriteFromCache( cache );
  } else {
    printf( "cache missed, new draw [2]\n" );
    cache->Reset( obj0.GetPosition(), obj0.GetSize() );
    buffer->DrawLine( cache, Vec2( 0.2f, 0.5f ), Vec2( 0.5f, 0.5f ) );
  }
  obj0.position.x += 0.5f;
  //buffer->ClearCache();
  if( buffer->IsObjectCached( &obj0, &cache ) ) {
    printf( "write from cache [3]\n" );
    buffer->WriteFromCache( cache );
  } else {
    printf( "cache missed, new draw [3]\n" );
    cache->Reset( obj0.GetPosition(), obj0.GetSize() );
    buffer->DrawLine( cache, Vec2( 10.0f, 4.0f ), Vec2( -10.0f, -9.0f ) );
  }
  buffer->__Dump();

  /*
  {//DrawPolarLine test
    float x = 3.0f;
    LOGD( "Test: pos[%3.3f] iPos[%d] value[%3.3f] result[%s]\n", x, ( int ) buffer->FloatToSize( x ), buffer->GetValue( x ), ( buffer->GetValue( x ) == 5.0f ? "ok" : "failed" ) );
    x = 7.0f;
    LOGD( "Test: pos[%3.3f] iPos[%d] value[%3.3f] result[%s]\n", x, ( int ) buffer->FloatToSize( x ), buffer->GetValue( x ), ( buffer->GetValue( x ) == 2.5f ? "ok" : "failed" ) );
  }
  */

  {//DrawLine test
    float x = 0.7f;
    LOGD( "Test: pos[%3.3f] iPos[%d] value[%3.16f] result[%s]\n", x, ( int ) buffer->FloatToSize( x ), buffer->GetValue( x ), ( Math::Fabs( buffer->GetValue( x ) - 2.1987860202789307f ) < Math::FLT_EPSILON_NUM ? "ok" : "failed" ) );
    x = 0.3f;
    LOGD( "Test: pos[%3.3f] iPos[%d] value[%3.16f] result[%s]\n", x, ( int ) buffer->FloatToSize( x ), buffer->GetValue( x ), ( Math::Fabs( buffer->GetValue( x ) - 2.8490004539489746f ) < Math::FLT_EPSILON_NUM ? "ok" : "failed" ) );
  }


  delete buffer;
  LOGD( "\n\nDone: " );
  return 0;
}//main
