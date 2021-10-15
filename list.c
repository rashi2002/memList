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
    //the node to be inserted
    struct Node *new=NULL, *node1=NULL;
    
    //get the first node, the one before the insert 
    getval(memsys, node1, sizeof(struct Node), *node_ptr);
    
    // setting the values in the new node and savind it malloc 
    new->data = memmalloc(memsys, width);
    new->next = node1->next;
    setval(memsys, src ,width , new->data);

    //saving the value of the inserted node to memsys and saving the address of the 
    //inserted node in the next of node
    node1->next = memmalloc(memsys, sizeof(struct Node));
    setval(memsys, new, sizeof(struct Node), node1->next);
    
    //saving the modified value of the first node back to memsys
    setval(memsys, node1, sizeof(struct Node), *node_ptr);

}

/********************************************************************************/


void delete( struct memsys * memsys, int * node_ptr )
{
    //function to delete node 2
    // node 1 is the node before, node 2 is the node to delete
    struct Node *node1=NULL, *node2=NULL;
    //address of the node to delete
    int addr;
    getval(memsys, node1, sizeof(struct Node), *node_ptr);
    addr = node1->next;
    getval(memsys, node2, sizeof(struct Node), addr);
    node1->next = node2->next;
    setval(memsys, node1, sizeof(struct Node), *node_ptr);
    //freeing the data associated with the node and then freeing the node
    memfree(memsys, node2->data);
    memfree(memsys, addr);
    
}

/********************************************************************************/

void readHead( struct memsys * memsys, int * node_ptr ,void * dest, unsigned int width )
{
    struct Node *node1=NULL;
    if(node_ptr == MEMNULL){
        fprintf(stderr, "ERROR: List is empty");
        exit(0);
    }
    else{
        getval(memsys, node1, sizeof(struct Node), *node_ptr);
        getval(memsys, dest, width, node1->data );
    }
}

/********************************************************************************/


void pop( struct memsys * memsys, int * node_ptr )
{
    int addr;//to store the address of the node to delete
    struct Node* node1=NULL;//the head node i.e, the node to delete

    if(node_ptr == MEMNULL){
        fprintf(stderr, "ERROR: List is empty");
        exit(0);
    }
    else{
        addr = *node_ptr;
        getval(memsys, node1, sizeof(struct Node), addr);
        *node_ptr = node1->next; 

        //freeing the data associated with the node and then freeing the node
        memfree(memsys,node1->data);
        memfree(memsys, addr);
    }
}

/********************************************************************************/


int next( struct memsys * memsys, int * node_ptr )
{
    struct Node *node1= MEMNULL;
    if(node_ptr == NULL){
        fprintf(stderr, "ERROR: List is empty");
        exit(0);
    }
    else{
        getval(memsys, node1, sizeof(struct Node), *node_ptr);
        return node1->next ;
    }
}

/********************************************************************************/

int isNull( struct memsys * memsys, int * node_ptr )
{
    if(*node_ptr == MEMNULL){
        return 1;
    }
    return 0; 
}
/********************************************************************************/
//List functions
/********************************************************************************/

struct List *newList( struct memsys *memsys, unsigned int width )
{
    struct List *new = (struct List*)malloc(sizeof (struct List));
    if (new==NULL){
        fprintf(stderr, "ERROR: malloc failed, exiting\n");
        exit(0);
    }
    new->width = width;
    new->head = MEMNULL;
    return new;
}

/********************************************************************************/

void freeList( struct memsys *memsys, struct List *list )
{
    int* temp=NULL;
    struct Node* node=NULL;
    //struct List* head;
    if (list->head == MEMNULL){
        fprintf(stderr, "The list is already empty, exiting the program\n");
        exit(0);
    }
    while (list->head!=MEMNULL){
        temp = &list->head;
        getval(memsys, node, sizeof(struct Node), list->head);
        pop(memsys, temp);
        list->head = node->next;
    }
    free(list);
}


int isEmpty( struct memsys *memsys, struct List *list )
{
    if (list->head == MEMNULL){
        return 1;
    }
    return 0;
}

void readItem( struct memsys *memsys, struct List *list, unsigned int index, void *dest ){
    int head = list->head;
    if (head == MEMNULL)
    {
        fprintf(stderr, "ERROR: the list is empty\n");
        exit(0);
    }
    else
    {
        for (int i = 0; i <index; i++)
        {
            head = next(memsys, &head);
        }
        readHead(memsys, &head, dest, list->width);
    }
}

void appendItem( struct memsys *memsys, struct List *list,void *src ){
    struct Node* lastNode, new;
    int nextaddr = list->head;
    int ptr;
    while (isNULL(memsys, &nextaddr)){
        ptr= nextaddr;
        nextaddr = next(memsys, &ptr);
    }
	insert(memsys, ptr,src, sizeof(struct Node));

}

void insertItem( struct memsys *memsys, struct List *list, unsigned int index, void *src ){
	
}


void prependItem( struct memsys *memsys, struct List *list,void *src ){

}
