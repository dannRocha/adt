#ifndef ___ADT_LIST___
#define ___ADT_LIST___

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.h"

struct neighbor {
  void *__value;
	struct neighbor *__left;
	struct neighbor *__right;
};

struct list { 
  struct neighbor *__head;
  struct neighbor *__tail;
  void(*free)(void *memory);
  size_t __length;

  size_t __last_index_searched;
  struct neighbor *__last_neighbor_searched;
  bool __direction_ascending;

};

typedef struct list* list;

void list_create( struct list **__list , void( *ifree )( void *memory ) );
void list_push( struct list *__list, void *value );
void list_pop( struct list *__list, void **value );
void list_shift( struct list *__list, void **value );
void list_insert( struct list *__list, void *value, int index );
void list_remove( struct list *__list, void **value, int index );
void list_get ( struct list *__list, void **value, int index );
void list_foreach( struct list *__list, void( *callback )( void *memory, int index ) );
void list_clear( struct list *__list );
void list_destroy( struct list **__list );
size_t list_length( struct list *__list);
int list_index_of( struct list *__list, void *value, bool( *comparator )( void *target_value, void *current_value ) );
bool list_contains( struct list *__list, void *value, bool( *comparator )( void *target_value, void *current_value ) );
bool list_is_empty( struct list *__list );

#include "list.c"

#endif // ___ADT_LIST___