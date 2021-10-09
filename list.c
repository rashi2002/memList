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
    void* dest; 
    int addr, addr2;
    getval(memsys, dest, sizeof(struct Node), *node_ptr); 
    addr = memmalloc(memsys, width);
    setval(memsys, src,width , addr);

    struct Node new;
    new.data = addr;
    new.next = dest->next;

    addr2 = memmalloc(memsys, sizeof(struct Node));
    setval(memsys, &new, sizeof(struct Node), addr2);

    dest->next = addr2;
    setval(memsys, dest, sizeof(struct Node, addr));

}

void delete( struct memsys * memsys, int * node_ptr ){
    void* nodea, nodeb;// node a is the node before, node b is the node to delete
    int addrb;
    getval(memsys, nodea, sizeof(struct Node), *node_ptr);
    addrb = nodea->next;
    getval(memsys, nodeb, sizeof(struct Node), addrb);
    nodea->next = nodeb->next;
    setval(memsys, nodea, sizeof(struct Node), *node_ptr);
    /*doubt: do we have to free every part of the structure node or is the 
    following statement good?*/
    memfree(memsys, addrb);
    
}

void readHead( struct memsys * memsys, int * node_ptr ,void * dest, unsigned int width ){
    if(node_ptr == NULL){
        fprinf(stderr, "ERROR: List is empty");
        exit(0);
    }
    else{
        
    }
}



