#include "list.h"

void push( struct memsys * memsys, int *  node_ptr,void*src, size_t width )
{
    //declaring node to be pushed
    struct Node new;
	int a; 
    new.data = memmalloc(memsys, width);
    new.next = *node_ptr;
    setval(memsys, src, width,new.data);
    a = memmalloc(memsys, sizeof(struct Node));
    setval(memsys, &new, sizeof(struct Node), a );
	*node_ptr = a;
}

/********************************************************************************/

void insert( struct memsys * memsys, int * node_ptr, void * src, size_t width )
{
    //the node to be inserted
    struct Node new, node1;
	int temp;
    
    //get the first node, the one before the insert 
    getval(memsys, &node1, sizeof(struct Node), *node_ptr);
    
    // setting the values in the new node and savind it malloc 
    new.data = memmalloc(memsys, width);
    new.next = node1.next;
    setval(memsys, src ,width , new.data);

    //saving the value of the inserted node to memsys and saving the address of the 
    //inserted node in the next of node
    temp= memmalloc(memsys, sizeof(struct Node));
    setval(memsys, &new, sizeof(struct Node), temp);
    node1.next = temp;
    //saving the modified value of the first node back to memsys
    setval(memsys, &node1, sizeof(struct Node), *node_ptr);

}

/********************************************************************************/


void delete( struct memsys * memsys, int * node_ptr )
{
    //function to delete node 2
    // node 1 is the node before, node 2 is the node to delete
    struct Node node1, node2;
    //address of the node to delete
    int addr;
    getval(memsys, &node1, sizeof(struct Node), *node_ptr);
    addr = node1.next;
    getval(memsys, &node2, sizeof(struct Node), addr);
    node1.next = node2.next;
    setval(memsys, &node1, sizeof(struct Node), *node_ptr);
    //freeing the data associated with the node and then freeing the node
    memfree(memsys, node2.data);
    memfree(memsys, addr);
    
}

/********************************************************************************/

void readHead( struct memsys * memsys, int * node_ptr ,void * dest, unsigned int width )
{
    struct Node node1;
    if(*node_ptr == MEMNULL){
        fprintf(stderr, "ERROR: List is empty");
        exit(0);
    }
    else{
        getval(memsys, &node1, sizeof(struct Node), *node_ptr);
        getval(memsys, dest, width, node1.data );
    }
}

/********************************************************************************/


void pop( struct memsys * memsys, int * node_ptr )
{
    int addr;//to store the address of the node to delete
    struct Node node1;//the head node i.e, the node to delete

    if(*node_ptr == MEMNULL){
        fprintf(stderr, "ERROR: List is empty");
        exit(0);
    }
    else{
        addr = *node_ptr;
        getval(memsys, &node1, sizeof(struct Node), addr);
        *node_ptr = node1.next; 

        //freeing the data associated with the node and then freeing the node
        memfree(memsys,node1.data);
        memfree(memsys, addr);
    }
}

/********************************************************************************/


int next( struct memsys * memsys, int * node_ptr )
{
    struct Node node1;
    if(*node_ptr == MEMNULL){
        fprintf(stderr, "ERROR: List is empty");
        exit(0);
    }
    else{
        getval(memsys, &node1, sizeof(struct Node), *node_ptr);
        return node1.next ;
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
    struct List *new = malloc(sizeof (struct List));
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
    if (list->head == MEMNULL){
        fprintf(stderr, "The list is already empty, exiting the program\n");
        exit(0);
    }
    while (list->head!=MEMNULL){
        temp = &list->head;
        pop(memsys, temp);
    }
    free(list);
}

/********************************************************************************/

int isEmpty( struct memsys *memsys, struct List *list )
{
    if (list->head == MEMNULL){
        return 1;
    }
	return 0;
}

void readItem( struct memsys *memsys, struct List *list, unsigned int index, void *dest ){
    int head = list->head;
    if (isEmpty(memsys, list))
    {
        fprintf(stderr, "ERROR: the list is empty\n");
        exit(0);
    }
    else
    {
        for (int i = 1; i <=index; i++)
        {
            head = next(memsys, &head);
        }
        readHead(memsys, &head, dest, list->width);
    }
}

void appendItem( struct memsys *memsys, struct List *list,void *src )
{
    int nextaddr = list->head;
    int ptr;
	if(isEmpty(memsys, list)){
		push(memsys, &(list->head) ,src, list->width );
		return;
	}
    while (!isNull(memsys, &nextaddr)){
        ptr= nextaddr;
        nextaddr = next(memsys, &nextaddr);
    }
	insert(memsys, &ptr,src, list->width);

}

void insertItem( struct memsys *memsys, struct List *list, unsigned int index, void *src )
{
	int ptr = list->head;
	if(index==0){
		push(memsys, &(list->head), src, list->width);
		return;
	}
	else{
		for(int i = 1; i<index; i++){
			ptr = next(memsys, &ptr);
		}
		insert(memsys, &ptr,src, list->width);
	}
}


void prependItem( struct memsys *memsys, struct List *list,void *src )
{
	insertItem( memsys,list, 0,src );
}

void deleteItem( struct memsys *memsys, struct List *list,unsigned int index )
{
	int ptr= list->head; 
	if(index==0){
		pop(memsys, &(list->head));
	}
	else{
		for(int i = 1 ; i < index; i++){
			ptr = next(memsys, &ptr);
		}
		delete(memsys, &ptr);
	}
}

int findItem( struct memsys *memsys, struct List *list,int (*compar)(const void *, const void *), void *target )
{
	int ptr = list->head;
	int counter = 0;
	void* dest = malloc(list->width);
	if(isEmpty(memsys, list)){
		fprintf(stderr, "ERROR: the list is empty\n");
		exit(0);
	}
	else{
		while (!isNull(memsys,&ptr)){
			readHead(memsys, &ptr, dest, list->width);
			if((*compar)(dest, target)==0){
				free(dest);
				return counter;
			}
			else{
				counter++;
				ptr = next(memsys, &ptr);
			}
			
		}
		free(dest);
		return -1;
	}
}
