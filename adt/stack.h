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

void stack_create( stack *__stack, void( *ifree )( void* memory ) );
void stack_push( stack __stack, void *value );
void stack_pop ( stack __stack, void **value );
void stack_peek( stack __stack, void **value );
void stack_clear( stack __stack );
void stack_destroy( stack* __stack );
bool stack_is_empty ( stack __stack );
size_t stack_length( stack __stack );

#include "stack.c"


#endif // ___ED_STACK__