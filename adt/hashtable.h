#ifndef ___ADT_HASHTABLE___
#define ___ADT_HASHTABLE___

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "util.h"
#include "list.h"

#define HASH_MAP_LENGTH 101
struct hashtable {
  struct list *__table[HASH_MAP_LENGTH];
  void(*free)(void *memory);
};

struct entry {
  char* key;
  void* value;
};

void hashtable_create( struct hashtable **__hashtable, void( *ifree )( void *memory )  );
bool hashtable_contains( struct hashtable *__hashtable, const char* key );
void hashtable_get( struct hashtable *__hashtable, const char* key, void **value );
void hashtable_put( struct hashtable *__hashtable, const char* key, void *value );
void hashtable_replace( struct hashtable *__hashtable, const char* key, void *value );
void hashtable_get_keys( struct hashtable *__hashtable, struct list *__list );
void hashtable_foreach( struct hashtable *__hashtable, void( *consumer )( char* key, void *value ) );
void hashtable_destroy( struct hashtable **__hashtable );

#include "hashtable.c"

#endif // ___ADT_HASHTABLE___