#include "list.h"

void push( struct memsys * memsys, int *  node_ptr,void*src, size_t width )
{
    struct Node new;
    new.data = memmalloc(memsys, width);
    new.next = *node_ptr;
    setval(memsys, src, width,new.data);
    *node_ptr  = memmalloc(memsys, sizeof(struct Node));
    setval(memsys, &new, sizeof(struct Node), *node_ptr );
    
}

void insert( struct memsys * memsys, int * node_ptr, void * src, size_t width )
{
    void* dest;  
    int addr, addr2;
    //get the first node, the one before the insert 
    getval(memsys, dest, sizeof(struct Node), *node_ptr);

    addr = memmalloc(memsys, width);
    setval(memsys, src ,width , addr);

    struct Node new;
    new.data = addr;
    new.next = dest->next;
    //saving the valude of the inserted node
    addr2 = memmalloc(memsys, sizeof(struct Node));
    setval(memsys, &new, sizeof(struct Node), addr2);
    //saving value of the first node
    dest->next = addr2;
    setval(memsys, dest, sizeof(struct Node), *node_ptr);

}

void delete( struct memsys * memsys, int * node_ptr )
{
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

void readHead( struct memsys * memsys, int * node_ptr ,void * dest, unsigned int width )
{
    if(node_ptr == NULL){
        fprinf(stderr, "ERROR: List is empty");
        exit(0);
    }
    else{
        getval(memsys, dest, width, node_ptr->data);
    }
}

void pop( struct memsys * memsys, int * node_ptr )
{
    int addr;
    void* nodeh;//the head node
    if(node_ptr == NULL){
        fprinf(stderr, "ERROR: List is empty");
        exit(0);
    }
    else{
        addr = *node_ptr;
        getval(memsys, nodeh, sizeof(struct Node), addr);
        *node_ptr = nodeh->next; 
        memfree(addr);
    }
}

int next( struct memsys * memsys, int * node_ptr )
{
    void* ptr;
    if(node_ptr == NULL){
        fprinf(stderr, "ERROR: List is empty");
        exit(0);
    }
    else{
        
        return node_ptr->next ;
    }
}

int isNull( struct memsys * memsys, int * node_ptr )
{
    if(node_ptr == NULL){
        return 1;
    }
    return 0; 
}

//struct List *newList( struct memsys *memsys, unsigned int width )
//{

//}


/*
void freeList( struct memsys *memsys, struct List *list )
{

}
int isEmpty( struct memsys *memsys, struct List *list )
{

}
void readItem( struct memsys *memsys, struct List *list,unsigned int index, void* dest )
{

}
void appendItem( struct memsys *memsys, struct List *list,void *src )
{

}
void prependItem( struct memsys *memsys, struct List *list,void *src )
{

}
void deleteItem( struct memsys *memsys, struct List *list,unsigned int index )
{

}

//the last 20% 
int findItem( struct memsys *memsys, struct List *list,int(*compar)(const void*, const void*), void * target )
{

}



*/




