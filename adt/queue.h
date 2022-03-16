#ifndef ___ADT_QUEUE___
#define ___ADT_QUEUE___

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.h"

struct queue { 
  struct node *__first;
  struct node *__last;
  void(*free)(void *memmory);
  size_t __len;
};

typedef struct queue* queue;

void queue_create( queue *__queue , void( *ifree )( void *memory ) );
void queue_push( queue __queue, void *value );
void queue_remove( queue __queue, void **value );
void queue_clear( queue __queue );
void queue_destroy( queue* __queue );
bool queue_is_empty( queue __queue);
size_t queue_length( queue __queue);

#include "queue.c"

#endif // ___ADT_QUEUE___