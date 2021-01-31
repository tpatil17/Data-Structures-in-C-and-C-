/*********************************************************************************
 *  * * Tanishq Patil, tmpatil
 *  * * 2021 Winter CSE 101 pa3
 *  * * Graph.c
 *  * * code for Graph ADT
 *  * *********************************************************************************/

//-----------------------------------------------------------------------------
//// Graph.c
//// Implementation file for Graph ADT
////-----------------------------------------------------------------------------


#include "List.h"
#include "Graph.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define W 0
#define Gr 1
#define B 2
static int time = 0;

// private type GraphObj
typedef struct GraphObj{
    List *Array;
    int *colors ;
    int *parent ;
    int *distance ;
    int *disc_time ;
    int *finish_time;
    int vertices ;
    int size ;
    int source ;
}GraphObj;


/*** Constructors-Destructors ***/


Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));

    G->Array = calloc(n+1, sizeof(List));
    G->colors = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->distance = calloc(n+1, sizeof(int));
    G->disc_time = calloc(n+1, sizeof(int));
    G->finish_time = calloc(n+1, sizeof(int));
    for(int i = 1; i <= n; i++){
        G->Array[i] = newList();
	    G->colors[i] = W;
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->disc_time[i] = UNDEF;
        G->finish_time[i] = UNDEF;
        }

    G->vertices = n;
    G->size = 0;
    G->source = NIL;
    return G;
}
void freeGraph(Graph* pG){
    if(*pG != NULL && pG !=NULL){
        Graph G = *pG;
        for(int i = 1; i <= getOrder(G); i++){
                freeList(&(G->Array[i]));
        }
        free(G->Array);
        free(G->colors);
        free(G->parent);
        free(G->distance);
        free(G->disc_time);
        free(G->finish_time);
        free(*pG);
        *pG = NULL;
    }
}
/*** Access functions ***/
int getOrder(Graph G){
    return G->vertices;
}

int getSize(Graph G){
  
    return G->size;
}
int getDiscover(Graph G, int u){ /* Pre: 1<=u<=n=getOrder(G) */
    if( u >=1 && u <= getOrder(G)){
        return G->disc_time[u];
    }
    else{
        printf(" precondition for getDiscover() failed\n");
        exit(EXIT_FAILURE);
    }
}
int getFinish(Graph G, int u){ /* Pre: 1<=u<=n=getOrder(G) */
    if( u >=1 && u <= getOrder(G)){
        return G->finish_time[u];
    }
    else{
        printf(" precondition for getFinish() failed\n");
        exit(EXIT_FAILURE);
    }
}
int getSource(Graph G){
   if(G == NULL){
	printf("G is null: source\n");
	exit(EXIT_FAILURE);
	}
   if(G->source == NIL){
	return NIL;
	}
    return G->source;
}

int getParent(Graph G, int u){
   if(G == NULL){
	printf(" G is null getparent\n");
	exit(EXIT_FAILURE);
	}
   if( u < 1 || u >getOrder(G)){
	printf("u is invalid at get parent\n");
	exit(EXIT_FAILURE);
	}
 //  if(getSource(G) == NIL){
   //     return NIL;
   // }
   if(G->parent[u] == NIL){
	return NIL;
	}
        return G->parent[u];
}

int getDist(Graph G, int u){
   if(G == NULL){
	printf(" Graph is not valid: get dist\n");
	exit(EXIT_FAILURE);
	}
   if(u < 1 || u >getOrder(G)){
	printf(" u is invalid: get dist\n");
	exit(EXIT_FAILURE);
	} 
      if(getSource(G) == NIL){
        return INF;
        }
       return G->distance[u];
      }
   

void getPath(List L, Graph G, int u){
   if(G == NULL){
	printf("Gis invalid: getPath\n");
	exit(EXIT_FAILURE);
	}
    if(u < 1 || u > getOrder(G)){
	printf("u is invalid: getpath\n");
	exit(EXIT_FAILURE);
	} 
    if (getSource(G) == NIL){
        printf("BFS not run!\n");
        exit(EXIT_FAILURE);
    }
 
    else if(G->parent[u] == NIL){

	if(G->colors[u] == W){
           append(L, NIL);
	}
	else{

        append(L, u);
	}
    }
    else{
	getPath(L,G,G->parent[u]);
	
	append(L, u);
	}
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
    for(int i = 1; i <= getOrder(G); i++){
        clear(G->Array[i]);
        free(G->Array[i]);
	G->colors[i] = W;
	G->distance[i] = INF;
	G->parent[i] = NIL;
    }
}
void addEdge(Graph G, int u, int v){

        if(length(G->Array[u])!=0){

        for(moveFront(G->Array[u]);index(G->Array[u]) < length(G->Array[u]);moveNext(G->Array[u])){
        if(index(G->Array[u]) < 0){
                        printf("%d\n", index(G->Array[u]));
                        exit(EXIT_FAILURE);
	}

            if(get(G->Array[u]) > v){
                insertBefore(G->Array[u],v);
               
                break;
            }
            else if(index(G->Array[u]) == (length(G->Array[u])-1)){
                append(G->Array[u], v);
               
                break;
                }
        }
    }
    if(length(G->Array[u]) == 0){
        append(G->Array[u], v);
        
    }
	
	addArc(G, v, u);
}
        

void addArc(Graph G, int u, int v){
    if(length(G->Array[u])!=0){

        for(moveFront(G->Array[u]);index(G->Array[u]) < length(G->Array[u]);moveNext(G->Array[u])){
            if(index(G->Array[u]) < 0){
                printf("%d\n", index(G->Array[u]));
                exit(EXIT_FAILURE);
            }   

            if(get(G->Array[u]) > v){
                insertBefore(G->Array[u],v);
		        G->size++;
                break;
            }
            else if(index(G->Array[u]) == (length(G->Array[u])-1)){
                append(G->Array[u], v);
		        G->size++;
                break;
                }
        }
    }
    if(length(G->Array[u]) == 0){
        append(G->Array[u], v);
	G->size ++;
    }
}
void BFS(Graph G, int s){
  for(int i = 1; i <= getOrder(G); i++){
   
	G->colors[i] = W;
        G->parent[i] = NIL;
        G->distance[i] = INF;
	
  }

    G->colors[s] = Gr;
    G->parent[s] = NIL;
    G->distance[s] = 0;
    
    List L = newList();
    append(L, s);
    
    moveFront(L);
    
    while(length(L) > 0){
	int x = get(L); // store the cursors/source's  value
	
	G->source = get(L);
	deleteFront(L); // the line up and this act similar to dequeue
	moveFront(G->Array[x]);// set the cursor at front
	while(index(G->Array[x]) >= 0){
		int u = get(G->Array[x]); //store the cursor value at u
		if(G->colors[u] == W){
			G->colors[u] = Gr;
			G->distance[u] = G->distance[x] +1;
			G->parent[u] = x;
			append(L, u);
		}
		moveNext(G->Array[x]);
	}
	G->colors[x] = B;
	moveFront(L);
    }
   freeList(&L);
   	
}


void Visit(Graph G, int x){
    time++;
    G->disc_time[x] = time;
    G->colors[x] = Gr;
    moveFront(G->Array[x]);         // Loop trhourg adj list of x
    while(index(G->Array[x])>=0){
//	printf("%d\n",y);
	int y = get(G->Array[x]);
        if(G->colors[y]== W){
            G->parent[y] = x;
            Visit(G,y);
        }
    moveNext(G->Array[x]);          // moving next in the adj list of x
    }
    // if loop exited means x is finished
    G->colors[x]=B;
    time++;
    G->finish_time[x] = time;
}


void DFS(Graph G, List S){ /* Pre: length(S)==getOrder(G) */
if(length(S)!= getOrder(G)){
    printf("precondition for DFS failed\n");
    exit(EXIT_FAILURE);
}
int n = getOrder(G);
    for(int i =1 ; i <= n; i++){
        G->colors[i] = W;
        G->parent[i] = NIL;
    }
    time = 0;
    moveFront(S);
    while(index(S) >=0){
        int x = get(S);
        if(G->colors[x]== W){
            Visit(G,x);
        }
    moveNext(S);
    }

 // After DFS is completed, sort the give List S in assending order based on finish time.
    List L = newList();
    moveFront(S);
    while(index(S)>=0){
        int x = get(S);
        if(length(L) ==0 ){
            append(L,x);
        }
        else{
            moveBack(L);
            while(index(L)>=0 && G->finish_time[x] < G->finish_time[get(L)]){
                movePrev(L);
            }
            if(index(L)<0){
                prepend(L,x);
            }
            else{
                insertAfter(L,x);                
            }

        }
        moveNext(S);
    }
 
    while(length(S) > 0){
	deleteFront(S);
	}
   for(moveFront(L); index(L) >=0; moveNext(L)){
	int x = get(L);
	prepend(S,x);
	}

   freeList(&L);   
    
}

/*** Other operations ***/
Graph transpose(Graph G){
    int n = getOrder(G);
    Graph T = newGraph(n);
    for(int i =1; i <= n; i++){
        moveFront(G->Array[i]);
        while(index(G->Array[i]) >= 0){
            int x = get(G->Array[i]);
            addArc(T, x, i);
            moveNext(G->Array[i]);
        }
    }
    return T;
}

Graph copyGraph(Graph G){
    Graph C = newGraph(getOrder(G));
    for(int i =0; i >= getOrder(G); i++){
        C->Array[i] = copyList(G->Array[i]);
        C->colors[i] = G->colors[i];
        C->parent[i] = G->parent[i];
        C->disc_time[i] = G->disc_time[i];
        C->finish_time[i] = G->finish_time[i];
    }
    C->vertices = G->vertices;
    C->size = G->size;
    C->source = G->source;
return C;    
}

void printGraph(FILE* out, Graph G){
    for(int i = 1; i <= G->vertices; i++){
        fprintf(out, "%d:",i);
        printList(out, G->Array[i]);
        fprintf(out,"\n");
    }

}
