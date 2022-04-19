# Estrutura de dados em C

- [Stack - Pilha](#stack)
- [Queue - Fila](#queue)
- [List - Lista](#list)
- [Hashtable - Tabela de espalhamento](#hashtable)
- Tree - Arvore

# Uso
No projeto que fará uso das estruturas de dados, adicione esse repositório como um sub-módulo.
```
git submodule add <repository-url>
```
## Exemplo Github
```
git submodule add https://github.com/<username>/<repository-name>.git <path>
```

## Exemplo Repo

- Criando um diretório para o projeto e acessando o diretório
```
mkdir -p project/src && cd project
```
- Inicializando repositório git
```
git init
```

- Adicionando lib no projeto
```
git submodule add https://github.com/dannRocha/adt.git src/lib/
```

- Criando main.c
```
// project/src/main.c
touch main.c
```
- Conteúdo da main.c
```c
#include <stdio.h>
#include <stdlib.h>
#include "lib/adt.h"


int main() {

  list integers = NULL;
  list_create( &integers, free );

  for( int i = 0; i < 10; i++ )
    list_push( integers, new_int( i ) );


  for( int i = 0; i < list_length( integers ); i++ ) {
    void *value = NULL;
    list_get( integers, &value, i );
    printf( "%d\n", to_int( value ) );
  }

  list_destroy( &integers );

  return 0;
}
```
- Compilando e executando
```
gcc main.c && ./a.out
```


# Stack
São estruturas de dados do tipo LIFO (last-in first-out), onde o último elemento a ser inserido, será o primeiro a ser retirado. Assim, uma pilha permite acesso a apenas um item de dados - o último inserido.

### Funções:
- [stack_create](#stack_create)
- [stack_destroy](#stack_destroy)
- [stack_push](#stack_push)
- [stack_pop](#stack_pop)
- [stack_peek](#stack_peek)
- [stack_clear](#stack_clear)
- [stack_length](#stack_length)
- [stack_is_empty](#stack_is_empty)

## <span id="stack_create">stack_create</span>
Função de inicialização da pilha.

```c
void stack_create( struct stack **__stack, void( *ifree )( void* memory ) );
```

### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct stack *numbers = NULL; // or  stack numbers
  stack_create( &numbers, free );

  return 0;
}
```
Sempre inicialize a ```struct stack *<variable>``` com ```NULL```.
```c
struct stack *numbers = NULL;
//or
stack numbers = NULL;
```

O segundo parametro da função de criação da pilha (```void( *ifree )( void* memory )```) espera uma função que terá a responsabilidade de como será libarada a memória alocada;

### Exemplo:
```c
#include <stdlib.h>
#include "adt.h"

void my_free_function( void* memory );

int main() {

  struct stack *numbers = NULL;
  stack_create( &numbers, my_free_function );

  return 0;
}

void my_free_function( void* memory ) {
  free( memory );
}
```

## <span id="stack_destroy">stack_destroy</span>

Função usada para liberar as memórias armazenadas na pilha.

```c
void stack_destroy( struct stack **__stack );
```

### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {

  struct stack *numbers = NULL;
  stack_create( &numbers, free );

  stack_destroy( &numbers );

  return 0;
}
```

A função ```stack_destroy``` pecorre toda a pilha liberando cada memória alocada chamando a função de liberação de memória customizada passada na ```create_stack```. Levando em consideração o nome da variavel da pilha (```numbers```), a pilha conterá valores numericos, então a função ```void free(void *ptr);``` da ```stdlib.h``` é suficiente.

## <span id="stack_push">stack_push</span>

Adiciona um item para o topo da pilha.

```c
void stack_push( struct stack *__stack, void *value );
```

As estruturas de dados dessa biblioteca armazena endereços de memória e não valores, podendo assim trabalhar com vários tipos de dados. Há um trade-off nessa abordagem pois trocamos o acesso simples dos valores da estrutura pela reusabilidade das estruturas, causando uma grande quantidade do uso de ```casting``` para converter a memória em um tipo que pode ser usado nos algoritmos. É usado a ```heap``` para guarda os contéudos das estruturas de dados, então será necessário alocar dinamicamente a memória para os valores e guarda o endereço alocado nas estruturas de dados.

### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct stack *numbers = NULL;
  stack_create( &numbers, free );

  for( int i = 0; i < 10; i++ ) {
    int* value = new( int );
    *value = i;
    stack_push( numbers, value );
  }

  stack_destroy( &numbers );

  return 0;
}
```

Observe o trecho de código abaixo:
```c
  int* value = new( int );
  *value = i;
  stack_push( numbers, value );
```

Um ponteiro pra inteiro é alocado (``` int* value = new( int );```), então nesse endereço é atribuido o valor da variavel ```i``` do loop ```for```, e em seguida o endereço é adicionado na pilha (```stack_push( numbers, value );```).

### :warning: <span id="new-tip">new</span> 
O ```new( <any> )``` é uma macro para outra macro ```new_group(type, size)``` que apenas contém a expressão para ```calloc``` da ```stdlib.h```.

```c
#define new_group(type, size) (type*) calloc(sizeof(type), size)
#define new(type) new_group(type, 1)
```

Outra versão usando funções da biblioteca.

```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct stack *numbers = NULL;
  stack_create( &numbers, free );

  for( int i = 0; i < 10; i++ ) {
    stack_push( numbers, new_int( i ) );
  }

  stack_destroy( &numbers );

  return 0;
}
```

Funções utilitarias de inicialização de tipos primitivos [clique aqui [ 1 ]](#util-new)

<span id="util-new">Funções utilitárias [ 1 ]</span>
- new_short
- new_u_short
- new_int
- new_u_int
- new_long
- new_llong
- new_float
- new_double
- new_char
- new_string

As funções acima apenas diminui a verbosidade de alocar memória e atribuir valor. Não use fora da estrutura de dados evitando vazamento de memória através de escopo das funções.

Assinatura:
```c
short* new_short( short value );

unsigned short* new_u_short( unsigned short value );

int* new_int( int value );

unsigned int* new_u_int( unsigned int value );

long* new_long (long value );

long long* new_llong (long long value );

float* new_float( float value );

double* new_double( double value );

char* new_char( char value );

char* new_string( const char* value );
```

## <span id="stack_pop">stack_pop</span>

Remove o item no topo da pilha e retorna esse item a endereço de memória armazenado no segundo parametro. 

```c
void stack_pop ( struct stack *__stack, void **value );
```

### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct stack *numbers = NULL;
  stack_create( &numbers, free );

  // push
  stack_push( numbers, new_int( 1 ) );
  stack_push( numbers, new_int( 2 ) );

  // pop
  void *memory = NULL;
  stack_pop( numbers, &memory );
  int content = *( int* ) memory;

  printf( "%d\n", content );
  // output: 2

  numbers->free( memory );

  stack_destroy( &numbers);

  return 0;
}
```

O trecho que consome o valor armazenado na pilha:
```c
  // pop
  void *memory = NULL;
  stack_pop( numbers, &memory );
  
  // casting
  int content = *( int* ) memory;

  printf( "%d\n", content );
  // output: 2
```
Observe que foi necessário realizar o ```cast``` da memória para um tipo manipulável.

Há trecho do código que deve ser levado em consideração:
```c
  numbers->free( memory );
```
É necessário liberar manualmente a memória alocada, pois a estrutura de dados não tem mais a responsabilidade de liberar depois foi removido.


Outra versão usando funções da biblioteca.

```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct stack *numbers = NULL;
  stack_create( &numbers, free );

  // push
  stack_push( numbers, new_int( 1 ) );
  stack_push( numbers, new_int( 2 ) );

  // pop
  void *memory = NULL;
  stack_pop( numbers, &memory );
  
  printf( "%d\n", to_int( memory ) );
  // output: 2

  numbers->free( memory );

  stack_destroy( &numbers);

  return 0;
}
```
Funções utilitárias de casting de tipos primitivos [clique aqui [ 2 ]](#util-to)

<span id="util-to">Funções utilitárias [ 2 ]</span>

- to_short
- to_u_short
- to_int
- to_u_int
- to_float
- to_double
- to_char
- to_string

Assinatura:
```c

short to_short( void* memory );

short to_u_short( void* memory );

int to_int( void* memory );

unsigned int to_u_int( void* memory );

float to_float( void* memory );

double to_double( void* memory );

char to_char( void* memory );

char* to_string( void* memory );
```


## <span id="stack_peek">stack_peek</span>

Olha para o item no topo da pilha sem removê-lo da pilha.
```c
void stack_peek( struct stack *__stack, void **value );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct stack *numbers = NULL;
  stack_create( &numbers, free );

  // push
  stack_push( numbers, new_int( 1 ) );
  stack_push( numbers, new_int( 2 ) );

  // peek
  void *memory = NULL;
  stack_peek( numbers, &memory );
  
  printf( "%d\n", to_int( memory ) );
  // output: 2

  stack_destroy( &numbers );

  return 0;
}
```
Funções utilitárias de casting de tipos primitivos [clique aqui [ 2 ]](#util-to)

## <span id="stack_clear">stack_clear</span>
Remove todos os elemetos da pilha
```c
void stack_clear( struct stack *__stack );
```

### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct stack *numbers = NULL;
  stack_create( &numbers, free );

  // push
  stack_push( numbers, new_int( 1 ) );
  stack_push( numbers, new_int( 2 ) );

  // clear
  stack_clear( numbers );

  stack_destroy( &numbers );

  return 0;
}
```


## <span id="stack_length">stack_length</span>
Retorna o número de elementos na pilha.

```c
size_t stack_length( struct stack *__stack );
```

### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct stack *numbers = NULL;
  stack_create( &numbers, free );

  // push
  stack_push( numbers, new_int( 1 ) );
  stack_push( numbers, new_int( 2 ) );

  // length
  printf( "%ld\n", stack_length( numbers ) );
  // output: 2

  stack_destroy( &numbers );

  return 0;
}
```

## <span id="stack_is_empty">stack_is_empty</span>
Retorna 1 para 'verdadeiro' se a pilha não contiver elementos e 0 para 'falso'.

```c
bool stack_is_empty ( struct stack *__stack );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct stack *numbers = NULL;
  stack_create( &numbers, free );

  // is empty
  printf( "%d\n", stack_is_empty( numbers ) );
  // output: 1

  stack_destroy( &numbers );

  return 0;
}
```

# Queue

Uma fila é uma estrutura linear que segue uma ordem particular na qual as operações são executadas. A ordem é First In First Out (FIFO).

### Funções:
- [queue_create](#queue_create)
- [queue_destroy](#queue_destroy)
- [queue_push](#queue_push)
- [queue_remove](#queue_remove)
- [queue_clear](#queue_clear)
- [queue_length](#queue_length)
- [queue_is_empty](#queue_is_empty)

## <span id="queue_create">queue_create</span>
Função de inicialização da fila.
```c
void queue_create( struct queue **__queue , void( *ifree )( void *memory ) );
```

### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct queue *numbers = NULL; // or  queue numbers
  queue_create( &numbers, free );

  return 0;
}
```
Sempre inicialize a ```struct queue *<variable>``` com ```NULL```.
```c
struct queue *numbers = NULL;
//or
queue numbers = NULL;
```

### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

void my_free_function( void* memory );

int main() {

  struct queue *numbers = NULL;
  queue_create( &numbers, my_free_function );

  return 0;
}

void my_free_function( void* memory ) {
  free( memory );
}
```

## <span id="queue_destroy">queue_destroy</span>
Função usada para liberar as memórias armazenadas na fila.
```c
void queue_destroy( struct queue **__queue );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {

  struct queue *numbers = NULL;
  queue_create( &numbers, free );

  queue_destroy( numbers );

  return 0;
}
```

## <span id="queue_push">queue_push</span>
Adiciona um item para na fila.
```c
void queue_push( struct queue *__queue, void *value );
```

### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct queue *numbers = NULL;
  queue_create( &numbers, free );

  for( int i = 0; i < 10; i++ ) {
    queue_push( numbers, new_int( i ) );
  }

  queue_destroy( &numbers );

  return 0;
}
```

Funções utilitarias de inicialização de tipos primitivos [clique aqui [ 1 ]](#util-new)

## <span id="queue_remove">queue_remove</span>
Recupera e remove o primeiro elemento da fila.
```c
void queue_remove( struct queue *__queue, void **value );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct queue *numbers = NULL;
  queue_create( &numbers, free );

  // push
  queue_push( numbers, new_int( 1 ) );
  queue_push( numbers, new_int( 2 ) );

  // remove
  void *memory = NULL;
  queue_remove( numbers, &memory );

  printf( "%d\n", to_int( memory ) );
  // output: 2

  numbers->free( memory );

  queue_destroy( &numbers);

  return 0;
}
```
Funções utilitárias de casting de tipos primitivos [clique aqui [ 2 ]](#util-to)

## <span id="queue_clear">queue_clear</span>
Remove todos os elemetos da fila
```c
void queue_clear( struct queue *__queue );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct queue *numbers = NULL;
  queue_create( &numbers, free );

  // push
  queue_push( numbers, new_int( 1 ) );
  queue_push( numbers, new_int( 2 ) );

  // clear
  queue_clear( numbers );

  queue_destroy( &numbers);

  return 0;
}
```

## <span id="queue_length">queue_length</span>
Retorna o número de elementos na pilha.
```c
void queue_destroy( struct queue **__queue );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct queue *numbers = NULL;
  queue_create( &numbers, free );

  // push
  queue_push( numbers, new_int( 10 ) );
  queue_push( numbers, new_int( 20 ) );

  // length
  printf( "%ld\n", queue_length( numbers ) );
  // output: 2

  queue_destroy( &numbers );

  return 0;
}
```

## <span id="queue_is_empty">queue_is_empty</span>
Retorna 1 para 'verdadeiro' se a fila não contiver elementos e 0 para 'falso'.
```c
bool queue_is_empty( struct queue *__queue);
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct queue *numbers = NULL;
  queue_create( &numbers, free );

  // is empty
  printf( "%d\n", queue_is_empty( numbers ) );
  // output: 1

  queue_destroy( &numbers );

  return 0;
}
```

# List
lista duplamente ligada é uma estrutura de dados ligada que consiste de um conjunto de registros sequencialmente ligados chamados de nós.

### Funções
- [list_create](#list_create)
- [list_destroy](#list_destroy)
- [list_push](#list_push)
- [list_pop](#list_pop)
- [list_shift](#list_shift)
- [list_insert](#list_insert)
- [list_remove](#list_remove)
- [list_get](#list_get)
- [list_foreach](#list_foreach)
- [list_clear](#list_clear)
- [list_length](#list_length)
- [list_index_of](#list_index_of)
- [list_contains](#list_contains)
- [list_is_empty](#list_is_empty)

## <span id="list_create">list_create</span>
Função de inicialização da lista.
```c
void list_create( struct list **__list , void( *ifree )( void *memory ) );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct list *numbers = NULL;
  list_create( &numbers, free );

  return 0;
}
```

## <span id="list_destroy">list_destroy</span>
Função usada para liberar as memórias armazenadas na lista.
```c
void list_destroy( struct list **__list );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct list *numbers = NULL;
  list_create( &numbers, free );

  list_destroy( &numbers );

  return 0;
}
```

## <span id="list_push">list_create</span>
Adiciona um elemento no final da lista
```c
void list_push( struct list *__list, void *value );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct list *numbers = NULL;
  list_create( &numbers, free );

  for( int i = 0; i < 10; i++ ) {
    list_push( numbers, new_int( i ) );
  }

  list_destroy( &numbers );

  return 0;
}
```

Funções utilitarias de inicialização de tipos primitivos [clique aqui [ 1 ]](#util-new)

### Exemplo
```c
#include <stdio.h>
#include <stdlib.h>
#include "adt.h"

struct book  {
  char* title;
  char* author;
};

void free_book_list ( void* memory );

int main() {
  
  struct list *books = NULL;
  list_create( &books, free_book_list );

  for( int i = 0; i < 10; i++ ) {
    struct book *book = new( struct book );
    
    book->title = ( char* ) malloc( sizeof( char ) * 7 );
    book->author = ( char* ) malloc( sizeof( char ) * 9 );
    
    sprintf( book->title, "Book %d", i );
    sprintf( book->author, "Author %d", i );

    list_push( books, book );
  }

  for( int i = 0; i < list_length( books ); i++ ) {
    void *value = NULL;
    list_get( books, &value, i );
    struct book *book = ( struct book* ) value;

    printf("[ %s : %s ]\n", book->author, book->title );
  }

  list_destroy( &books );

  return 0;
}

void free_book_list ( void* memory ) {
  struck book *book = ( struct book* ) memory;

  free( book->title );
  free( book->author );

  free( book ); // or free( memory );

}
```
***Explicação sobre o "[```new ( <any> ) ```](#new-tip)"***


## <span id="list_pop">list_pop</span>
Retorna e remove o ultimo elemento da lista.
```c
void list_pop( struct list *__list, void **value );
```
Funções utilitárias de casting de tipos primitivos [clique aqui [ 2 ]](#util-to)

## <span id="list_shift">list_shift</span>
Remove o primeiro elemento da lista e retorna esse elemento removido.
```c
void list_shift( struct list *__list, void **value );
```
Funções utilitárias de casting de tipos primitivos [clique aqui [ 2 ]](#util-to)

## <span id="list_insert">list_insert</span>
Insere um elemento em uma posição especificada na lista.
```c
void list_insert( struct list *__list, void *value, int index );
```
Funções utilitarias de inicialização de tipos primitivos [clique aqui [ 1 ]](#util-new)

## <span id="list_remove">list_remove</span>
Remove e retorna um elemento em uma posição especificada da lista.
```c
void list_remove( struct list *__list, void **value, int index );
```
Funções utilitárias de casting de tipos primitivos [clique aqui [ 2 ]](#util-to)

## <span id="list_get">list_get</span>
Retorna um elemento na posição especificada da lista. ***Não libere a memória alocada através dessa função, caso queira remover e consumir um elemento da lista use a função list_remove***.
```c
void list_get ( struct list *__list, void **value, int index );
```
Funções utilitárias de casting de tipos primitivos [clique aqui [ 2 ]](#util-to)

## <span id="list_foreach">list_foreach</span>
Executa uma ação para cada elemento da lista.
```c
void list_foreach( struct list *__list, void( *callback )( void *memory, int index ) );
```

## <span id="list_clear">list_clear</span>
Remove todos os elemetos da lista.
```c
void list_clear( struct list *__list );
```

## <span id="list_length">list_length</span>
Retorna o número de elementos da lista.
```c
size_t list_length( struct list *__list);
```

## <span id="list_index_of">list_index_of</span>
Retorna o índice da primeira ocorrência do elemento especificado na lista, ou -1 se esta lista não contiver o elemento.

```c
int list_index_of( struct list *__list, void *value, bool( *comparator )( void *target_value, void *current_value ) );
```

## <span id="list_contains">list_contains</span>
Retorna 1 para 'verdadeiro' se esta lista contiver o elemento especificado e 0 para 'falso'.
```c
bool list_contains( struct list *__list, void *value, bool( *comparator )( void *target_value, void *current_value ) );
```

## <span id="list_is_empty">list_is_empty</span>
Retorna 1 para 'verdadeiro' se esta lista não contiver elementos e 0 para 'falso'.
```c
bool list_is_empty( struct list *__list );
```

# Hashtable
Uma tabela de hash , também conhecida como mapa de hash , é uma estrutura de dados que implementa um tipo de dados abstrato de matriz associativa , uma estrutura que pode mapear chaves para valores 
### Funções
- [hashtable_create](#hashtable_create)
- [hashtable_destroy](#hashtable_destroy)
- [hashtable_put](#hashtable_put)
- [hashtable_get](#hashtable_get)
- [hashtable_contains](#hashtable_contains)
- [hashtable_replace](#hashtable_replace)
- [hashtable_get_keys](#hashtable_get_keys)
- [hashtable_foreach](#hashtable_foreach)

## <span id="hashtable_create">hashtable_create</span>
Função de inicialização da hashtable.
```c
void hashtable_create( struct hashtable **__hashtable, void( *ifree )( void *memory )  );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct hashtable *table = NULL; 
  // or hashtable table = NULL;
  
  hashtable_create( &table, free );

  return 0;
}
```
## <span id="hashtable_destroy">hashtable_destroy</span>
Função usada para liberar as memórias armazenadas na hashtable.
```c
void hashtable_destroy( struct hashtable **__hashtable );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct hashtable *table = NULL;
  hashtable_create( &table, free );

  hashtable_destroy( table );

  return 0;
}
```

## <span id="hashtable_put">hashtable_put</span>
Mapeia o especificado ```key``` para o especificado ```value``` na tabela de hash.
```c
void hashtable_put( struct hashtable *__hashtable, const char* key, void *value );
```
### Exemplo
```c
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct hashtable *table = NULL;
  hashtable_create( &table, free );

  // put
  hashtable_put( table, "firstname", new_string( "Daniel" ) );

  hashtable_destroy( table );

  return 0;
}
```
Funções utilitarias de inicialização de tipos primitivos [clique aqui [ 1 ]](#util-new)

## <span id="hashtable_get">hashtable_get</span>
Atribui o endereco de memória em (```void **value```) para o qual a chave especificada é mapeada ou ```NULL``` se esse mapa não contém mapeamento para a chave.
```c
void hashtable_get( struct hashtable *__hashtable, const char* key, void **value );
```
### Exemplo
```c
#include <stdio.h>
#include <stdlib.h>
#include "adt.h"

int main() {
  
  struct hashtable *table = NULL;
  hashtable_create( &table, free );

  // put
  hashtable_put( table, "firstname", new_string( "Daniel" ) );

  void *value = NULL;
  hashtable_get( table, "firstname", &value );
  
  printf("FIRSTNAME: %s\n",  to_string( value ) );
  // output: FIRSTNAME: Daniel


  hashtable_destroy( table );

  return 0;
}
```
Funções utilitárias de casting de tipos primitivos [clique aqui [ 2 ]](#util-to)

## <span id="hashtable_contains">hashtable_contains</span>
Testa se uma chave existe na tabela de hash.
```c
bool hashtable_contains( struct hashtable *__hashtable, const char* key );
```

## <span id="hashtable_replace">hashtable_replace</span>
Substitui a entrada da chave especificada somente se ela estiver mapeada atualmente para algum valor.
```c
void hashtable_replace( struct hashtable *__hashtable, const char* key, void *value );
```

## <span id="hashtable_get_keys">hashtable_get_keys</span>
Preenche uma ```struct list *``` previamente inicializa com as chaves da contidas na hashtable.
```c
void hashtable_get_keys( struct hashtable *__hashtable, struct list *__list );
```

## <span id="hashtable_foreach">hashtable_foreach</span>
Executa a ação para cada entrada na hashtable até que todas as entradas tenham sido processadas.
```c
void hashtable_foreach( struct hashtable *__hashtable, void( *consumer )( char* key, void *value ) );
```
