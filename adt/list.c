
static void __get_nearest_neighbor( list __list, struct neighbor **current_neighbor, int *counter, int index );

void list_create( list *__list , void( *ifree )( void *memmory ) ) {

  if( *__list != NULL ) {
    fprintf(stderr, "\033[31mlist_create( list * , void( * )( void * ) ). error: pointer to list does not release at %s line %d\033[0m\n", __FILE__, __LINE__ );
    return ;
  }

    *__list = new( struct list );
  ( *__list )->free = ifree;
  ( *__list )->__head = NULL;
  ( *__list )->__tail = NULL;
  ( *__list )->__length = 0;
  ( *__list )->__last_index_searched = 0;
  ( *__list )->__last_neighbor_searched = NULL;
  ( *__list )->__direction_ascending = true;
}

void list_push( list __list, void *value ) {
  if( __list->__head == NULL || list_length( __list ) == 0 ) {
    __list->__head = new( struct neighbor );
    __list->__head->__left = NULL;
    __list->__head->__right = NULL;
    __list->__head->__value = value;
    __list->__tail = __list->__head;
    __list->__length++;

    return;
  }

  struct neighbor* old_tail = __list->__tail;
  struct neighbor* new_tail = new( struct neighbor );

  new_tail->__left = NULL;
  new_tail->__right = NULL;
  new_tail->__value = value;

  new_tail->__left = old_tail;
  old_tail->__right = new_tail;

  __list->__tail = new_tail;
  __list->__length++;
}

void list_insert( list __list, void *value, int index ) {
   if( index < 0 || index >= list_length( __list ) ) {
      fprintf(stderr, "\033[31mlist_insert( struct list*, void **, int ). error: index out of bounds exception at %s line %d\033[0m\n", __FILE__, __LINE__);
      return;
    }

   if(  list_is_empty( __list ) && index == 0 ) {
     list_push( __list, value );
     return;
   }

   int counter = 0;
   struct neighbor *current_neighbor = __list->__head;

   __get_nearest_neighbor( __list, &current_neighbor, &counter, index );

   while( current_neighbor != NULL ) {
     if( index == counter) break;

     if( __list->__direction_ascending ) {
       counter++;
       current_neighbor = current_neighbor->__right;
     }
     else {
       counter--;
       current_neighbor = current_neighbor->__left;
     }
  }

  if( current_neighbor == NULL ) {
    printf("Inserir em [%d] tamanho da lista [%ld]\n", index, list_length( __list ) );
    return;
  }

  struct neighbor *left_neighbor = current_neighbor->__left;
  struct neighbor *right_neighbor = current_neighbor->__right;

  struct neighbor *new_neighbor = new( struct neighbor );

  new_neighbor->__left = NULL;
  new_neighbor->__right = NULL;
  new_neighbor->__value = value;

  bool is_inserting_in_the_first_position = left_neighbor == NULL;
  bool is_inserting_in_the_last_position = right_neighbor == NULL;

  if( is_inserting_in_the_first_position ) {
    new_neighbor->__right = __list->__head;
    __list->__head->__left = new_neighbor;
    __list->__head = new_neighbor;
  }
  else if( is_inserting_in_the_last_position ) {
     new_neighbor->__left = __list->__tail;
     __list->__tail->__right = new_neighbor;
     __list->__tail = new_neighbor;
  }
  else {
      left_neighbor->__right = new_neighbor;
      new_neighbor->__left = left_neighbor;
      new_neighbor->__right = current_neighbor;
      current_neighbor->__left = new_neighbor;
  }

  __list->__length++;
}

void list_remove( list __list, void **value, int index ) {

  ( *value ) = NULL;

  if( index < 0 || index >= list_length( __list ) ) {
    fprintf(stderr, "\033[31mlist_remove(list*. void*, int ). error: index out of bounds exception at %s line %d\033[0m\n", __FILE__, __LINE__);
    return;
  }

  if(  list_is_empty( __list ) ) {
    fprintf( stderr, "\033[31mlist_remove( struct list*, void**, int ). error: queue don't initialized or empty at %s line %d\033[0m\n", __FILE__, __LINE__ );
    return;
  }

  int counter = 0;
  struct neighbor* current_neighbor = __list->__head;

  while( current_neighbor != NULL ) {
    if( counter == index ) break;

    counter++;
    current_neighbor = current_neighbor->__right;
  }

  struct neighbor *left_neighbor = current_neighbor->__left;
  struct neighbor *right_neighbor = current_neighbor->__right;

  if ( left_neighbor != NULL )
    left_neighbor->__right = right_neighbor;

  if( right_neighbor != NULL )
    right_neighbor->__left = left_neighbor;

  if( index == 0 ) {
    __list->__head = right_neighbor;
  }

  if( list_length( __list ) - 1 == index && list_length( __list ) > 1 ) {
    __list->__tail =  current_neighbor->__left;
    __list->__tail->__right = NULL;
  }

  if( __list->__length - 1 == 0 ) {
    __list->__head = NULL;
    __list->__tail = NULL;
  }


  ( *value ) = current_neighbor->__value;
  free( current_neighbor );
  __list->__length--;

}

void list_pop( list __list, void **value ) {
  list_remove( __list, value, list_length( __list ) - 1 );
}

void list_shift( list __list, void **value ) {
  list_remove( __list, value, 0);
}

static void __get_nearest_neighbor( list __list, struct neighbor **current_neighbor, int *counter, int index ) {

  bool startFindByLeftNeighborIsMoreFast = ( index >= __list->__last_index_searched ) && ( __list->__last_neighbor_searched != NULL );
  if( startFindByLeftNeighborIsMoreFast ) {
    *counter = __list->__last_index_searched;
    *current_neighbor = __list->__last_neighbor_searched;
    __list->__direction_ascending = true;

    bool leftOptimizerIsSlow = ( index > __list->__last_index_searched )
                               && ( index > list_length( __list ) / 2 )
                               && ( __list->__last_index_searched < list_length( __list ) / 2 )
                               && ( __list->__last_index_searched + 1 != index || __list->__last_index_searched < ( list_length( __list ) / 2 - list_length( __list ) / 3 ) );

    if( leftOptimizerIsSlow ) {
      *counter = list_length ( __list ) - 1;
      *current_neighbor = __list->__tail;
      __list->__direction_ascending = false;
    }
  }

  bool startFindByRightNeighborIsMoreFast = ( index <= __list->__last_index_searched ) && ( __list->__last_neighbor_searched != NULL );
  if( startFindByRightNeighborIsMoreFast ) {
    *counter = __list->__last_index_searched;
    *current_neighbor = __list->__last_neighbor_searched;
    __list->__direction_ascending = false;

    bool rightOptimizerIsSlow = ( index < __list->__last_index_searched )
                                  && ( index < list_length( __list ) / 2 )
                                  && ( __list->__last_index_searched > list_length( __list ) / 2 )
                                  && ( __list->__last_index_searched - 1 != index || __list->__last_index_searched > ( list_length( __list ) / 2 + list_length( __list ) / 3 ) );
    if( rightOptimizerIsSlow )  {

          *counter = 0;
          *current_neighbor = __list->__head;
          __list->__direction_ascending = true;
    }
  }
}

void list_get ( list __list, void **value, int index ) {

  if( index < 0 ||  index >= list_length( __list ) ) {
    fprintf(stderr, "\033[31mget_list_index_of(list*. void*, int ). error: index out of bounds exception at %s line %d\033[0m\n", __FILE__, __LINE__);
    return;
  }

  if(  list_is_empty( __list ) ) {
    fprintf( stderr, "\033[31mget_list_index_of ( struct list*, void**, int ). error: queue don't initialized or empty at %s line %d\033[0m\n", __FILE__, __LINE__ );
    return;
  }

  int counter = 0;
  struct neighbor *current_neighbor = __list->__head;

  __get_nearest_neighbor( __list, &current_neighbor, &counter, index );

  while( current_neighbor != NULL ) {

      if( index == counter) break;

      if( __list->__direction_ascending ) {
        counter++;
        current_neighbor = current_neighbor->__right;
      }
      else {
        counter--;
        current_neighbor = current_neighbor->__left;
      }

      __list->__last_index_searched = counter;
      __list->__last_neighbor_searched = current_neighbor;
    }

  ( *value ) = current_neighbor->__value;
}

int list_index_of( list __list, void *value, bool( *comparator )( void *target_value, void *current_value ) ) {

    const int NOT_FOUND = -1;

    int index = 0;
    struct neighbor *current_neighbor = __list->__head;

    while( current_neighbor != NULL ) {
      if( comparator( value, current_neighbor->__value ) )
        return index;

      current_neighbor = current_neighbor->__right;
      index++;
    }

    return NOT_FOUND;
}

bool list_contains( list __list, void *value, bool( *comparator )( void *target_value, void *current_value ) ) {

  struct neighbor *current_neighbor = __list->__head;

  while( current_neighbor != NULL ) {
    if( comparator( value, current_neighbor->__value ) )
      return true;

    current_neighbor = current_neighbor->__right;
  }

  return false;
}

void list_foreach( list __list, void( *callback )( void *memory, int index ) ) {
  struct neighbor *current_neighbor = __list->__head;

  for( int counter = 0; current_neighbor != NULL; counter++ ) {
    callback( current_neighbor->__value, counter );
    current_neighbor = current_neighbor->__right;
  }
}

size_t list_length( list __list) {
  if( __list == NULL ) {
    fprintf( stderr, "\033[31mlist_length(struct list* ). error: list don't initialized\033[0m\n" );
    return 0;
  }

  return __list->__length;
}

bool list_is_empty( list __list) {
  return ( __list == NULL ) ? true : __list->__length == 0;
}

void list_clear( list __list ) {
  while( !list_is_empty( __list ) ) {
    void* mem = NULL;
    list_remove( __list, &mem, 0 );
    __list->free(mem);
  }
  
  __list->__head = NULL;
  __list->__tail = NULL;
}

void list_destroy( list *__list ) {

  if( *__list == NULL ) {
    fprintf( stderr, "\033[31mlist_destroy(struct list* ). error: list don't initialized\033[0m\n" );
    return;
  }

	list_clear( *__list );
	free( *__list );

  *__list = NULL;
}
