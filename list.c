#include "list.h"

void push( struct memsys * memsys, int *  node_ptr,void*src, size_t width )
{
    //declaring node to be pushed
    struct Node new;
    new.data = memmalloc(memsys, width);
    new.next = *node_ptr;
    setval(memsys, src, width,new.data);
    *node_ptr  = memmalloc(memsys, sizeof(struct Node));
    setval(memsys, &new, sizeof(struct Node), *node_ptr );
    
}

/********************************************************************************/

void insert( struct memsys * memsys, int * node_ptr, void * src, size_t width )
{
    //the node after which we insert
    void* node1;
    //the node to be inserted
    struct Node new;

    //get the first node, the one before the insert 
    getval(memsys, node1, sizeof(struct Node), *node_ptr);
    
    // setting the values in the new node and savind it malloc 
    new.data = memmalloc(memsys, width);
    new.next = node1->next;
    setval(memsys, src ,width , new.data);

    //saving the value of the inserted node to memsys and saving the address of the 
    //inserted node in the next of node
    node1->next = memmalloc(memsys, sizeof(struct Node));
    setval(memsys, &new, sizeof(struct Node), node1->next);
    
    //saving the modified value of the first node back to memsys
    setval(memsys, node1, sizeof(struct Node), *node_ptr);

}

/********************************************************************************/


void delete( struct memsys * memsys, int * node_ptr )
{
    //function to delete node 2
    // node 1 is the node before, node 2 is the node to delete
    void* node1, node2;
    //address of the node to delete
    int addr;
    getval(memsys, node1, sizeof(struct Node), *node_ptr);
    addr = nodea->next;
    getval(memsys, node2, sizeof(struct Node), addr);
    node1->next = node2->next;
    setval(memsys, node1, sizeof(struct Node), *node_ptr);
    //freeing the data associated with the node and then freeing the node
    memefree(memsys, node->data);
    memfree(memsys, addr);
    
}

/********************************************************************************/

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

/********************************************************************************/


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

/********************************************************************************/


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

/********************************************************************************/
Indore4056273
Indore4056273

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




