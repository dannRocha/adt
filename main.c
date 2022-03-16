#include <stdio.h>
#include <time.h>

#include "adt/adt.h"


struct book {
  char* title;
  char* author;
};

void test_stack();
void test_queue();
void test_list();
void test_integer_stack( stack st );
void test_string_stack( stack st );
void test_struct_stack( stack st );

void free_book_stack( void* memmory ) {
  struct book *book = ( struct book * ) memmory;
  free( book->title );
  free( book->author );
  free( book );
}


int main() {
  test_stack();
  test_queue();
  test_list();
  return 0;
}


void test_integer_stack( stack st ) {

  for( int i = 0; i < 10; i++ ) {
    t_int value = new( int );
    *value = i;
    stack_push( st, value );
  }
  
  printf("\n:: test_integer_stack ::\n");
  printf("[ ");

  while( !stack_is_empty( st ) ) {
    void *mem = NULL;
    stack_pop( st, &mem );
    int value = *( t_int ) mem;

    printf( "%d%s", value, stack_is_empty( st )? " ]" : ", " );
    st->free( mem );
  }

  for( int i = 9; i >= 0; i-- ) {
    t_int value = new(int);
    *value = i;
    stack_push( st, value );
  }
  
  printf("\n[ ");
  
  while( !stack_is_empty(st) ) {
    void *mem = NULL;
    stack_pop(st, &mem);
    int value = *(t_int) mem; 
    printf( "%d%s", value, stack_is_empty( st )?  " ]" : ", " );
    
    st->free( mem );
  }	

  printf("\n");
}

void test_string_stack(stack st) {
	for( int i = 65 ;  i < 65 + 26; i++ ) {
		t_char letter = new_group(char, 9);
		sprintf( letter, "{ %d:%c }", i, i );
		
		stack_push( st, letter );
	}

  printf("\n:: test_string_stack ::\n");

  const int COLLUMN = 3;
  int counter = 0;

	while( !stack_is_empty( st ) ) {

		void *mem = NULL;
		stack_pop( st, &mem );

		t_char letter = ( t_char ) mem;
    if( counter == COLLUMN ) {
      counter = 0;
      printf("\n");
    }
    
    counter++;

		printf( " \"%s\"%s ", letter, stack_is_empty( st )? "" : ", " );

		st->free( letter );
	}

  printf("\n");
}

void test_struct_stack( stack st ) {
  for( int i = 0; i < 5; i++ ) {
    struct book *book = new( struct book );
    
    book->title = new_group( char, 8 );
    book->author = new_group( char, 10 );

		sprintf( book->title, "Book %d", i );
		sprintf( book->author, "Author %d", i );
    
    stack_push( st, book );
  }
  
  printf("\n:: test_struct_stack ::\n");
  printf("[ \n");

  while( !stack_is_empty( st ) ) {
    void *mem = NULL;
		stack_pop( st, &mem );
		
    struct book *book = ( struct book* ) mem;
    printf( "  struct book { title: %s; author: %s;}%s\n", book->title, book->author, stack_is_empty( st )?  "\n]" : ", "  );

		st->free( book );
  }

  printf("\n");
}

void test_stack() {
  stack range_0_to_1000 = NULL;
  stack alphabet = NULL;
  stack books = NULL;
  
  stack_create( &range_0_to_1000, free );
  stack_create( &alphabet, free );
  stack_create( &books, free_book_stack );

  test_integer_stack( range_0_to_1000 );
  test_string_stack( alphabet );
  test_struct_stack( books );

  printf( "stack[range_0_to_1000] len: %ld\n", stack_length( range_0_to_1000 ) );
  printf( "stack[alphabet]        len: %ld\n", stack_length( alphabet ) );
  printf( "stack[books]           len: %ld\n", stack_length( books ) );

  stack_destroy( &alphabet );
  stack_destroy( &range_0_to_1000 );
  stack_destroy( &books );
}

void test_queue() {
  queue supermarket = NULL;

  queue_create(&supermarket, free);

  for( int i = 0; i < 10; i++ ) {
    t_int value = new( int );
    *value = i;
    queue_push( supermarket, value );
  }
  
  printf("\n:: test_integer_queue ::\n");
  printf("[ ");

  while( !queue_is_empty( supermarket ) ) {
    void *mem = NULL;
    queue_remove( supermarket, &mem );

    int value = *( t_int ) mem;
    printf( "%d%s", value, queue_is_empty( supermarket )? " ]\n" : ", " );
    supermarket->free( mem );
  }

  queue_destroy(&supermarket);
}

void consumer( void *mem, int index ) {
  int value =  *(t_int) mem;
  printf( "list of integers: { list[%d]: %d }\n", index, value );
}

void test_list() {

  printf("\n:: test_integer_list ::\n");

  list integers = NULL;
  list_create( &integers, free );

  printf( "\n-- push [ 1..5 ] -- \n" );

  for( int i = 0; i < 5; i++ ) {
    t_int value = new( int );
    *value = (i + 1 );
    list_push( integers, value );
  }

  list_foreach( integers, consumer );

  t_int value = new( int );
  *value = 2021;
  list_insert( integers, value, 0 );

  value = new( int );
  *value = 2022;
  list_insert( integers, value, 3 );

  value = new( int );
  *value = 2023;
  list_insert( integers, value, list_length( integers ) - 1 );

  printf( "\n-- insert [ {0: 2021}, {3: 2022},  {%ld: 2023} ] -- \n", list_length( integers ) - 1 );
  list_foreach( integers, consumer );

  void *mem = NULL;

  printf( "\n-- pop , shirt and remove by index -- \n" );

  list_pop( integers, &mem );
  printf(" * pop   list[%ld]: %d \n", list_length( integers ), *( t_int ) mem);
  integers->free( mem );

  list_remove(integers, &mem, 3);
  printf(" * index list[3]: %d \n", *(t_int) mem);
  integers->free( mem );

  list_shift( integers, &mem );

  printf(" * shift list[0]: %d \n\n", *(t_int) mem);
  integers->free( mem );


  list_foreach( integers, consumer );

  printf( "\n-- access [ asc, desc, rand ] list size: %ld -- \n", list_length( integers ) );

  for( int i = 0; i < list_length( integers ); i++ ) {
    void *mem = NULL;
    list_get(integers, &mem, i);
  }

  for( int i = list_length( integers ) - 1; i >= 0 ; i-- ) {
    void *mem = NULL;
    list_get(integers, &mem, i);
  }

  srand(time(0));

  for( int i = 0; i < list_length( integers ) ; i++ ) {
    void *mem = NULL;
    int index = rand() % ( list_length( integers ) - 1 );
    list_get(integers, &mem,  index );
  }

  printf( "\n-- list contains and index -- \n" );

  int find = 3;
  printf(" * contains: %d [ %s ] \n", find, ( list_contains(integers, &find, int_comparator )) ? "true" : "false" );
  printf(" * index: %d \n", list_index_of(integers, &find, int_comparator ) );

  list_destroy( &integers );
}


