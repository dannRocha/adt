

int __hashtable_hash(const char* key) {
  int number = 0;
  const double a = 0.6180339887;
  const double h = 64;

  double k = 0.0;
  while(*key){
    k += (int)*key++;
  }

  return (int)(h * (k * a));
}

int __hashtable_index(const char* key) {
  return __hashtable_hash(key) % HASH_MAP_LENGTH;
}

bool __hashtable_compare_key( void *a, void* b ) {

  char*_a = (char*) a;
  struct entry _b = to(struct entry)  b;

  return !(bool)strcmp(_a, _b.key);
}

void hashtable_create( struct hashtable **__hashtable, void( *ifree )( void *memory )  ) {

  if( ifree == NULL ) {
    fprintf(stderr, "\033[31mhashtable_create( struct hashtable ** , void( * )( void * ) ). error: hashtable does not release at %s line or free function is null %d\033[0m\n", __FILE__, __LINE__ );
    return;
  }

  if( *__hashtable != NULL ) {
    fprintf(stderr, "\033[31mhashtable_create( struct hashtable ** , void( * )( void * ) ). error: pointer to hashtable does not release at %s line %d\033[0m\n", __FILE__, __LINE__ );
    return ;
  }

  ( *__hashtable ) = new( struct hashtable );

  if( *__hashtable == NULL ) {
    fprintf(stderr, "\033[31mhashtable_create( struct hashtable ** , void( * )( void * ) ). error: enough memory\n" );
    return ;
  }

  ( *__hashtable )->free = ifree;

  for( int i = 0; i < HASH_MAP_LENGTH; i++ ) {
    ( *__hashtable )->__table[i] = NULL;
    list_create(&( *__hashtable )->__table[i], free );
  }
}

bool hashtable_contains( struct hashtable *__hashtable, const char* key ) {
  int index = __hashtable_index(key);
  return list_index_of( __hashtable->__table[ index ], (void* ) key, __hashtable_compare_key ) >= 0;
}

void hashtable_get( struct hashtable *__hashtable, const char* key, void **value ) {

  int index = __hashtable_index( key );
  struct list *__list = __hashtable->__table[index];

  int target_index = list_index_of( __list, (void* ) key, __hashtable_compare_key );

  if( target_index < 0 ) {
    fprintf( stderr, "\n\033[31mkey '%s' undefined on hastable %p\033[0m\n", key, __hashtable );
    ( *value ) = NULL;
    return;
  }

  void *__entry = NULL;
  list_get ( __list, &__entry, target_index );
  ( *value ) = (( struct entry* )__entry)->value;
}

void hashtable_put( struct hashtable *__hashtable, const char* key, void *value ) {

  struct entry *entry = new( struct entry );


  if( entry == NULL ) {
    fprintf(stderr, "\033[31mhashtable_put( struct hashtable **, const char* , void* ). error: enough memory\n" );
    return ;
  }

  entry->key = ( char* ) calloc( sizeof( char ), strlen( key ) + 1 );

  if( entry->key == NULL ) {
    free( entry );
    fprintf(stderr, "\033[31mhashtable_put( struct hashtable **, const char* , void* ). error: enough memory\n" );
    return ;
  }

  entry->value = value;

  strcpy( entry->key, key );

  int index = __hashtable_index( key );

  if( hashtable_contains( __hashtable, key ) ) {
    int target_index = list_index_of( __hashtable->__table[ index ], (void* ) key, __hashtable_compare_key );

    void *memory = NULL;
    list_remove(  __hashtable->__table[ index ], &memory, target_index );

    struct entry *old_entry = ( struct entry* ) memory;

    free( old_entry->key );
    __hashtable->free( old_entry->value );
    free( old_entry );

  }

  list_push( __hashtable->__table[index], entry );
}

void hashtable_replace( struct hashtable *__hashtable, const char* key, void *value ) {
   if( hashtable_contains( __hashtable, key ) ) {
      hashtable_put( __hashtable, key, value );
      return;
   }

   fprintf(stderr, "\033[31mvoid hashtable_replace( struct hashtable **, const char*, void* ). error: hashtable does not contains key '%s'\033[0m\n", key );
}

void hashtable_get_keys( struct hashtable *__hashtable, struct list *__list ) {
  if( __list == NULL ) {
    fprintf( stderr, "\033[31mhashtable_get_keys( struct hashtable **, struct list* ). error: list don't initialized\033[0m\n" );
    return;
  }

  for( int i = 0; i < HASH_MAP_LENGTH; i++ ) {
    struct list *__current_list = __hashtable->__table[i];

    if( list_is_empty ( __current_list ) )
      continue;

    struct neighbor* current_neighbor = __current_list->__head;

    while( current_neighbor != NULL ) {
      struct entry *__entry = (struct entry*) current_neighbor->__value;
      char* key = new_group(char, strlen( __entry->key ) + 1 );

      if( key == NULL ) {
        fprintf(stderr, "\033[31mhashtable_get_keys( struct hashtable *, struct list* ). error: enough memory\n" );
        return ;
      }

      strcpy( key, __entry->key );

      list_push( __list, (void*)key );
      current_neighbor = current_neighbor->__right;
    }
  }
}

void hashtable_foreach( struct hashtable *__hashtable, void( *consumer )( char* key, void *value ) ) {

  if( consumer == NULL )
    return;

  for( int i = 0; i < HASH_MAP_LENGTH; i++ ) {
    struct list *__list = __hashtable->__table[i];

    if( list_is_empty ( __list ) )
      continue;

    struct neighbor* current_neighbor = __list->__head;

    while( current_neighbor != NULL ) {
      struct entry *__entry = (struct entry*) current_neighbor->__value;
      consumer( __entry->key, __entry->value );

      current_neighbor = current_neighbor->__right;
    }
  }
}

void hashtable_destroy( struct hashtable **__hashtable ) {

  if( ( *__hashtable ) == NULL )
    return;

  for( int i = 0; i < HASH_MAP_LENGTH; i++ ) {
    while( !list_is_empty( ( *__hashtable )->__table[i] ) ) {

      void *stored_entry = NULL;
      list_pop( ( *__hashtable )->__table[i], &stored_entry );

      struct entry *__entry = (struct entry *) stored_entry;

      ( *__hashtable )->free( __entry->value );
      free( __entry->key );
      free( __entry );

    }

    list_destroy( &( *__hashtable )->__table[i] );
    ( *__hashtable )->__table[i] = NULL;
  }

  free(( *__hashtable ) );
  ( *__hashtable ) = NULL;
}

