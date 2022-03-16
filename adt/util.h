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

#include<string.h>
#include<stdbool.h>

#define new_group(type, size) (type*) calloc(sizeof(type), size)
#define new(type) new_group(type, 1)

#define i_new( type, value ) ( *((new_group(type, 1) ) = value )

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

#endif // ___ADT_UTIL___