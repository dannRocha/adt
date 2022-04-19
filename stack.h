#ifndef ___ADT_STACK___
#define ___ADT_STACK___

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.h"

struct stack { 
  struct node *__top;
  void(*free)(void *memory);
  size_t __len;
};

typedef struct stack* stack;

void stack_create( struct stack **__stack, void( *ifree )( void* memory ) );
void stack_push( struct stack *__stack, void *value );
void stack_pop ( struct stack *__stack, void **value );
void stack_peek( struct stack *__stack, void **value );
void stack_clear( struct stack *__stack );
void stack_destroy( struct stack **__stack );
bool stack_is_empty ( struct stack *__stack );
size_t stack_length( struct stack *__stack );

#include "stack.c"


#endif // ___ED_STACK__