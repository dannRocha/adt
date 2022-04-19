#ifndef ___ADT_UTIL___
#define ___ADT_UTIL___

typedef int       * t_int;
typedef char      * t_char;
typedef char      * t_string;
typedef double    * t_double;
typedef float     * t_float;
typedef long      * t_long;
typedef long long * t_llong;
typedef short     * t_short;

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define new_group(type, size) (type*) calloc(sizeof(type), size)
#define new(type) new_group(type, 1)

#define i_new( type, value ) ( *((new_group(type, 1) ) = value )

#define to(type) *(type*)
// #define to_string(type) *(type)

struct node {
	void *__value;
	struct node *__linker;
};

int max( int a, int b ) {
  return (a > b ) ? a : b;
}

int min( int a, int b ) {
  return (a < b ) ? a : b;
}

bool short_comparator( void *target, void *current ) {
  return *(t_short)(target) == *(t_short)(current);
}

bool int_comparator( void *target, void *current ) {
  return *(t_int)(target) == *(t_int)(current);
}

bool long_comparator( void *target, void *current ) {
  return *(t_long)(target) == *(t_long)(current);
}

bool long_long_comparator( void *target, void *current ) {
  return *(t_llong)(target) == *(t_llong)(current);
}

bool float_comparator( void *target, void *current ) {
  return *(t_float)(target) == *(t_float)(current);
}

bool double_comparator( void *target, void *current ) {
  return *(t_double)(target) == *(t_double)(current);
}

bool char_comparator( void *target, void *current ) {
  return *(t_char)(target) == *(t_char)(current);
}

bool string_comparator( void *target, void *current ) {
  return strcmp((t_char)(target), (t_char)(current)) == 0;
}


short* new_short( short value ) {
  short* alloc = new( short );
  *alloc = value;
  return alloc;
}

unsigned short* new_u_short( unsigned short value ) {
  unsigned short* alloc = new( unsigned short );
  *alloc = value;
  return alloc;
}

int* new_int( int value ) {
  int* alloc = new( int );
  *alloc = value;
  return alloc;
}

unsigned int* new_u_int( unsigned int value ) {
  unsigned int* alloc = new( unsigned int );
  *alloc = value;
  return alloc;
}

long* new_long (long value ) {
  long* alloc = new( long );
  *alloc = value;
  return alloc;
}

long long* new_llong (long long value ) {
  long long* alloc = new( long long );
  *alloc = value;
  return alloc;
}

float* new_float( float value ) {
  float* alloc = new( float );
  *alloc = value;
  return alloc;
}

double* new_double( double value ) {
  double* alloc = new( double );
  *alloc = value;
  return alloc;
}

char* new_char( char value ) {
  char* alloc = new( char );
  *alloc = value;
  return alloc;
}

char* new_string( const char* value ) {
  char* alloc = new_group( char, strlen( value ) + 1 );
  strcpy( alloc, value );
  return alloc;
}

short to_short( void* memory ) {
  return *( t_short ) memory;
}

short to_u_short( void* memory ) {
  return *( unsigned short* ) memory;
}

int to_int( void* memory ) {
  return *( t_int ) memory;
}

unsigned int to_u_int( void* memory ) {
  return *( unsigned int* ) memory;
}

float to_float( void* memory ) {
  return *( t_float ) memory;
}

double to_double( void* memory ) {
  return *( t_double ) memory;
}

char to_char( void* memory ) {
  return *( t_char ) memory;
}

char* to_string( void* memory ) {
  return ( t_string ) memory;
}

#endif // ___ADT_UTIL___