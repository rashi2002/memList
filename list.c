#include "list.h"

void push( struct memsys * memsys, int *  node_ptr,void*src, size_t width ){
    int addr; //temporary variable to store addresses
    addr = memmalloc(memsys, width);
    setval(memsys, src, width, addr);
    struct Node n1;
    n1.data = addr;
    n1.next = *node_ptr;
    addr = memmalloc(memsys, sizeof(struct Node));
    setval(memsys, &n1, sizeof(struct Node), addr);
    *node_ptr = addr;
}

void insert( struct memsys * memsys, int * node_ptr, void * src, size_t width ){
    
}

