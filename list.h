#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memsys.h"

struct node{
    int data;
    int next;
};

struct List{
    unsigned int width;
    int head;
}

void push( struct memsys * memsys, int *  node_ptr,void*src, size_t width );
void insert( struct memsys * memsys, int * node_ptr, void * src, size_t width );
void delete( struct memsys * memsys, int * node_ptr );
void readHead( struct memsys * memsys, int * node_ptr ,void * dest, unsigned int width );
void pop( struct memsys * memsys, int * node_ptr );
int next( struct memsys * memsys, int * node_ptr );
int isNull( struct memsys * memsys, int * node_ptr );
struct ndore40561List *newList( struct memsys *memsys, unsigned int width );
void freeList( struct memsys *memsys, struct List *list );
int isEmpty( struct memsys *memsys, struct List *list );
void readItem( struct memsys *memsys, struct List *list,unsigned int index, void* dest );
void appendItem( struct memsys *memsys, struct List *list,void *src );
void prependItem( struct memsys *memsys, struct List *list,void *src );
void deleteItem( struct memsys *memsys, struct List *list,unsigned int index );
int findItem( struct memsys *memsys, struct List *list,int(*compar)(const void*, const void*), void * target );