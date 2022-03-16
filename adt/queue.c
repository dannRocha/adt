
void queue_create( queue *__queue , void( *ifree )( void *memory ) ) {
  *__queue = new( struct queue );
  ( *__queue )->free = ifree;
  ( *__queue )->__first = NULL;
  ( *__queue )->__last = NULL;
  ( *__queue )->__len = 0;
}

void queue_push( queue __queue, void *value ) {
  if( __queue->__first == NULL || queue_length(__queue) == 0) {
    __queue->__first = new( struct node );
    __queue->__first->__value = value;
    __queue->__last = __queue->__first;
  	__queue->__len++;
    
    return;
  }

  struct node* old_last = __queue->__last;
  struct node* new_last = new( struct node );
  
  new_last->__value = value;

  old_last->__linker = new_last;
  __queue->__last = new_last;

  __queue->__len++;
}

void queue_remove( queue __queue, void **value ) {
   if( __queue == NULL)  {
    fprintf( stderr, "\033[31mqueue_remove(struct stack* ). error: queue don't initialized at %s line %d\033[0m\n", __FILE__, __LINE__ );
    return;
  }

  if( __queue->__len - 1 == (size_t)-1) {
    fprintf(stderr, "\033[31mqueue_remove(queue* ). error: index out of bounds exception at %s line %d\033[0m\n", __FILE__, __LINE__);
    return;
  }

   __queue->__len--;

  struct node *current_first = __queue->__first;

  if( current_first != NULL ) {
    __queue->__first = current_first->__linker;
    ( *value ) = current_first->__value;

    free(current_first);
  }
}

bool queue_is_empty( queue __queue) {
  return ( __queue == NULL ) ? true : __queue->__len == 0;
}

size_t queue_length( queue __queue) {
  if( __queue == NULL ) {
    fprintf( stderr, "\033[31mqueue_length(struct queue* ). error: queue don't initialized\033[0m\n" );
    return 0;
  }

  return __queue->__len;
}

void queue_clear( queue __queue ) {
  while( !queue_is_empty( __queue ) ) {
    void* mem = NULL;
    queue_remove(__queue, &mem);
    __queue->free(mem);
  }

  __queue->__first = NULL;
}

void queue_destroy( queue* __queue ) {
   if( __queue == NULL ) {
     fprintf( stderr, "\033[31mqueue_destroy(struct queue* ). error: queue don't initialized\033[0m\n" );
     return;
   }

	 queue_clear( *__queue );
	 free( *__queue );

   *__queue = NULL;
}