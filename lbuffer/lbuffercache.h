#ifndef __LBUFFERCACHE_H__
#define __LBUFFERCACHE_H__


#include <vector>
#include <deque>
#include <hash_map>
#include "kvector.h"


class LBufferCacheEntity {
public:
  Vec2 position;
  Vec2 size;
  void *object;

  struct Value {
    int index;
    float value;

    Value( int setIndex, float setValue )
    :index( setIndex ), value( setValue ) {
    }
  };
  std::vector< Value > values;
  int lifeTime;

  bool operator==( const LBufferCacheEntity& item ) const;
  void WriteToBuffer( float *buffer );

public:
  LBufferCacheEntity();
  LBufferCacheEntity( void* const setObject, const Vec2& setPosition, const Vec2& setSize );
  void Reset( const Vec2& setPosition, const Vec2& setSize );

private:
  LBufferCacheEntity( const LBufferCacheEntity& object );
  LBufferCacheEntity& operator=( const LBufferCacheEntity& object );
};


class LBufferCache
{
public:
  LBufferCache();
  virtual ~LBufferCache();
  bool CheckCache( void *object, const Vec2& position, const Vec2& size, LBufferCacheEntity **outCacheElement = NULL );
  void Update();

private:
  typedef std::hash_map< void*, LBufferCacheEntity* > ElementList;
  ElementList cache;

  LBufferCacheEntity* AddElement( void *object, const Vec2& position, const Vec2& size );
};


#endif
