
void stack_create( struct stack **__stack, void( *ifree )( void* memory ) ) {
  
  if( *__stack != NULL ) {
    fprintf( stderr, "\033[31mstack_create( struct stack **, void( * )( void* ) ). error: pointer to stack does not release at %s line %d\033[0m\n", __FILE__, __LINE__ );
    return;
  }
  
  *__stack = new( struct stack );

  if( *__stack == NULL ) {
    fprintf( stderr, "\033[31mstack_create( struct stack **, void( * )( void* ) ). error: enough memory" );
    return;
  }

  ( *__stack )->free = ifree;
  ( *__stack )->__top = NULL;
  ( *__stack )->__len = 0;
}

void stack_push( struct stack *__stack, void *value ) {

  if( __stack->__top == NULL || stack_length(__stack) == 0) {
    
    __stack->__top = new( struct node );

    if( __stack->__top == NULL ) {
      fprintf( stderr, "\033[31mstack_push( struct stack *, void* ). error: enough memory" );
      return;
    }

    __stack->__top->__value = value;
  	__stack->__len++;
    
    return;
  }

  struct node* old_top = __stack->__top;
  struct node* new_top = new( struct node );

  if( new_top == NULL ) {
    fprintf( stderr, "\033[31mstack_push( struct stack *, void* ). error: enough memory" );
    return;
  }

  new_top->__value = value;
  new_top->__linker = old_top;
  
  __stack->__top = new_top;  
  __stack->__len++;
}

void stack_pop ( struct stack *__stack, void **value ) {

  if( __stack == NULL)  {
    fprintf( stderr, "\033[31mstack_pop(struct stack* ). error: stack don't initialized at %s line %d\033[0m\n", __FILE__, __LINE__ );
    return;
  }

  if( __stack->__len - 1 == (size_t)-1) {
    fprintf(stderr, "\033[31mstack_pop(stack* ). error: index out of bounds exception at %s line %d\033[0m\n", __FILE__, __LINE__);
    return;
  }

  __stack->__len--;

  struct node *current_top = __stack->__top;

  if( current_top != NULL ) {
    __stack->__top = current_top->__linker;
    ( *value ) = current_top->__value;
    free(current_top);
  }
}

void stack_peek( struct stack *__stack, void **value ) {
  
  struct node *current_top = __stack->__top;

  if( current_top != NULL ) {
    ( *value ) = current_top->__value;
  }
}

bool stack_is_empty ( struct stack *__stack ) {
  return ( __stack == NULL ) ? true : __stack->__len == 0;
}

void stack_clear( struct stack *__stack ) {

  while( !stack_is_empty( __stack ) ) {
    void* mem = NULL;
    stack_pop(__stack, &mem);
    __stack->free(mem);
  }
}

void stack_destroy( struct stack **__stack ) {
  
  if( __stack == NULL ) {
    fprintf( stderr, "\033[31mstack_destroy(struct stack* ). error: stack don't initialized\033[0m\n" );
    return;
  }

	stack_clear( *__stack );
	free( *__stack );

  *__stack = NULL;
}

size_t stack_length( struct stack *__stack ) {
  if( __stack == NULL ) {
    fprintf( stderr, "\033[31mstack_length(struct stack* ). error: stack don't initialized\033[0m\n" );
    return 0;
  }

  return __stack->__len;
}