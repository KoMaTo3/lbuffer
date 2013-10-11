#include "logs.h"
#include "lbuffer.h"
#include "klib.h"


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
  buffer = new LBuffer( 16, 10.0f );
  Object obj0;
  obj0.position.Set( 5.0f, 3.0f );
  buffer->Clear( 1000.0f );
  LBufferCacheEntity *cache = NULL;
  if( buffer->IsObjectCached( &obj0, &cache ) ) {
    buffer->WriteFromCache( cache );
  } else {
    cache->Reset( obj0.GetPosition(), obj0.GetSize() );
    buffer->DrawLine( cache, Vec2( 0.2f, 0.5f ), Vec2( 0.5f, 0.5f ) );
    buffer->DrawLine( cache, Vec2( 0.0f, 1.0f ), Vec2( 5.0f, 8.0f ) );
    buffer->DrawLine( cache, Vec2( 5.0f, 2.0f ), Vec2( 10.0f, 3.0f ) );
    buffer->DrawLine( cache, Vec2( 0.0f, 11.0f ), Vec2( 10.0f, 0.1f ) );
    buffer->DrawLine( cache, Vec2( 5.0f, 0.123f ), Vec2( 5.0f, 0.321f ) );
  }
  obj0.position.x += 0.1f;
  if( buffer->IsObjectCached( &obj0, &cache ) ) {
    printf( "write from cache\n" );
    buffer->WriteFromCache( cache );
  } else {
    printf( "cache missed, new draw\n" );
    cache->Reset( obj0.GetPosition(), obj0.GetSize() );
    buffer->DrawLine( cache, Vec2( 0.2f, 0.5f ), Vec2( 0.5f, 0.5f ) );
  }
  if( buffer->IsObjectCached( &obj0, &cache ) ) {
    printf( "write from cache\n" );
    buffer->WriteFromCache( cache );
  } else {
    printf( "cache missed, new draw\n" );
    cache->Reset( obj0.GetPosition(), obj0.GetSize() );
    buffer->DrawLine( cache, Vec2( 0.2f, 0.5f ), Vec2( 0.5f, 0.5f ) );
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
    float x = 4.5f;
    LOGD( "Test: pos[%3.3f] iPos[%d] value[%3.16f] result[%s]\n", x, ( int ) buffer->FloatToSize( x ), buffer->GetValue( x ), ( Math::Fabs( buffer->GetValue( x ) - 0.5385116338729858f ) < Math::FLT_EPSILON_NUM ? "ok" : "failed" ) );
    x = 6.5f;
    LOGD( "Test: pos[%3.3f] iPos[%d] value[%3.16f] result[%s]\n", x, ( int ) buffer->FloatToSize( x ), buffer->GetValue( x ), ( Math::Fabs( buffer->GetValue( x ) - 9.7852468490600586f ) < Math::FLT_EPSILON_NUM ? "ok" : "failed" ) );
  }


  delete buffer;
  LOGD( "\n\nDone: " );
  return 0;
}//main
