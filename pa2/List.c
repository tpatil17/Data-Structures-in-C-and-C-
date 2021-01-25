/*********************************************************************************
 * * Tanishq Patil, tmpatil
 * * 2021 Winter CSE 101 pa2
 * * List.c
 * * code for List ADT
 * *********************************************************************************/

//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include  "List.h"


// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
List newList(void){ // Creates and returns a new empty List.
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}



void freeList(List* pL){ // Frees all heap memory associated with *pL, and sets
// *pL to NULL.
    if(pL!=NULL && *pL!=NULL) { 
        clear(*pL); 
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------
int length(List L){ // Returns the number of elements in L.
    return L->length;
}
int index(List L){ // Returns index of cursor element if defined, -1 otherwise.
    if(L->cursor == NULL){
        return -1;
    }
    return L->index;
}
int front(List L){ // Returns front element of L. Pre: length()>0
    if(length(L) <= 0){
        printf("\n Length of the entered list is less than or equal to 0.\n");
        return -1;
    }
    return L->front->data;
}

int back(List L){ // Returns back element of L. Pre: length()>0
    if(length(L) <= 0){
        printf("\n Length of list is 0 or less\n");
        return -1;
    }
    return L->back->data;
}
int get(List L){ // Returns cursor element of L. Pre: length()>0, index()>=0
    if(length(L) <= 0){
        printf("\n length of the given list is 0  or less\n");
        return -1;
    }
    if(index(L) < 0){
        printf("\n index invalid\n");
        return -1;
    }
    return L->cursor->data;
}

int equals(List A, List B){// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
    int eq =0;
    Node N = NULL;
    Node M = NULL;

    if(A == NULL || B == NULL){
        printf("\n Error List/lists are null\n");
        exit(EXIT_FAILURE);
    }
    eq = ( A->length == B->length );
    N = A->front;
    M = B->front;
    while( eq && N!=NULL){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
   }
   return eq;
}
// Manipulation procedures ----------------------------------------------------
void clear(List L){ // Resets L to its original empty state.
    if(L != NULL && length(L) >0){
        while(length(L) != 0){
            deleteBack(L);
        }
    }
}
void set(List L, int x){ // Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
    if(length(L) <= 0){
        printf("\n Error encountered in set(), len is 0  or less\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("\n Error encountered in set(), len is 0  or less\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

void moveFront(List L){ // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
    if(length(L)>0){
	L->index = 0;
        L->cursor = L->front;	
    }
}
void moveBack(List L){ // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
    if(length(L)>0){
        L->cursor = L->back;
	L->index = (L->length - 1);
    }
}
void movePrev(List L){ // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
    if(L->cursor != NULL){
        if(L->cursor != L->front){
            L->index --;
            L->cursor = L->cursor->prev;
        }
        else{
            L->cursor = NULL;
	    L->index = -1;
        }
    }
    
}

void moveNext(List L){ // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
    if(L->cursor != NULL){
        if(L->cursor != L->back){
            L->cursor = L->cursor->next;
	    L->index = L->index + 1;
        }
        else{
            L->cursor = NULL;
	    L->index = -1;
        }
    }
}
void prepend(List L, int x){ // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
    Node N = malloc(sizeof(NodeObj));
    N->data = x;
    N->prev = NULL;
    N->next = NULL;
    if(length(L)>0){
        L->front->prev = N; // attach the new nodes tail to the previous front
        N->next = L->front;
        L->front = N; // Now shift the new front to N.
    }
    
    else{
        L->front = L->back = N;
	
    }
    if(index(L) >= 0){
	L->index ++;
	}
    L->length++;
}
void append(List L, int x){ // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
    Node N = malloc(sizeof(NodeObj));
    N->data = x;
    N->next = NULL;
    N->prev = NULL;
    if(length(L)>0){
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    }
    else{
        L->front = L->back = N;
    }
    L->length++;

}
void insertBefore(List L, int x){ // Insert new element before cursor.
 // Pre: length()>0, index()>=0
	Node N = malloc(sizeof(NodeObj));
	N->data = x;
	N->prev = NULL;
	N->next = NULL;
    	if(length(L)<=0){
        	printf("\nError cursor is not valid or list is empty\n");
        	exit(EXIT_FAILURE);
    	}
   	if(index(L) < 0){
        	printf("\nError index is less than 0\n");
        	exit(EXIT_FAILURE);    
    	}
    	if(L->front == L->cursor){
        	N->next = L->cursor;
        	L->cursor->prev = N;
        	L->front = N;
		L->index ++;
		
    	}
    	else{
        	Node temp = NULL;
        	temp = L->cursor->prev;
        	temp->next = N;
        	N->prev = temp;
        	N->next = L->cursor;
        	L->cursor->prev = N;
		L->index ++;
    	}
    L->length++;
}
void insertAfter(List L, int x){ // Insert new element after cursor.
 // Pre: length()>0, index()>=0
    Node N = malloc(sizeof(NodeObj));
    N->data = x;
    N->next = NULL;
    N->prev = NULL;
    if(length(L)<=0){
        printf("\nError cursor is not valid or list is empty\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("\nError index is less than 0\n");
        exit(EXIT_FAILURE);    
    }
    if(L->cursor == L->back){
        L->cursor->next = N;
        N->prev = L->cursor;
        L->back = N;
	N->next = NULL;
    }
    else{
        Node temp = NULL;
        temp = L->cursor->next;
        N->next = temp;
        N->prev = L->cursor;
        temp->prev = N;
        L->cursor->next = N;
    }
    L->length++;
}

void deleteFront(List L){ // Delete the front element. Pre: length()>0
    if(length(L)<= 0){
        printf("\nError in deleteFront: list is of 0 length.\n");
        exit(EXIT_FAILURE);
    }
    Node temp = NULL;
    temp = L->front;
    if(length(L) >1){
        L->front = L->front->next;
        L->front->prev = NULL;
    }
    else{ 
	
        L->front = NULL;
	L->back = NULL;
	L->front = L->back;
    }
    if(index(L) == 0){
	L->cursor = NULL;
	}
    if(index(L) > 0){
	L->index --;
	}
    L->length --;
    free(temp);
}
void deleteBack(List L){ // Delete the back element. Pre: length()>0
    if(length(L)<= 0){
        printf("\nError in deleteFront: list is of 0 length.\n");
        exit(EXIT_FAILURE);
    }
    Node temp = NULL;
    temp = L->back;
    if(length(L) >1){
        L->back = L->back->prev;
        L->back->next = NULL;
    }
    else{ 
        L->front = NULL;
	L->back = L->front;
    }
    if(index(L) == (length(L)-1)){
	L->cursor = NULL;
	L->index = -1;
	}
    L->length --;
    free(temp);
}
void delete(List L){ // Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
	    if(length(L) <= 0){
		printf("\nError ind delete, list size is 0 or less\n");
		exit(EXIT_FAILURE);
	    }
	    if(index(L)< 0){
		printf("\n Error in delete, index is less than 0.\n");
		exit(EXIT_FAILURE);
	    }
	    Node temp1 = NULL;
	    Node temp2 = NULL;
	if(L->front == L->cursor && L->back == L->cursor){
	L->cursor->prev = NULL;
	L->cursor->next = NULL;
	free(L->cursor);
	L->cursor = NULL;
	L->index = -1;
	L->length --;
	}
    else if(L->front == L->cursor){
	deleteFront(L);
	L->index = -1;
	L->cursor = NULL;
	}
    else if(L->back == L->cursor){
	deleteBack(L);
	L->index = -1;
	L->cursor = NULL;
	}
    else{ 
 	 temp1 = L->cursor->prev;
   	 temp2 = L->cursor->next;
   	 temp1->next = temp2;
    	 temp2->prev = temp1;
   	 free(L->cursor);
   	 L->cursor = NULL;
	 L->index = -1;
	L->length --;
	}
    
}
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){ // Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated seLuence of integers,
// with front on left.
    Node N = NULL;

    if(L != NULL){
        for(N= L->front; N != NULL; N= N->next){
            fprintf(out," %d",N->data);
        }
    }
}
List copyList(List L){ // Returns a new List representing the same integer
 // seLuence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
    List R = newList();
    Node N = NULL;
    if(L != NULL){
        for (N= L->front; N != NULL; N = N->next){
            append(R,N->data);
        }
    }
    R->cursor = NULL;
    return R;
}
