#include "List.h"
#include "Graph.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define NIL -1
#define INF -2
#define W 0
#define Gr 1
#define B 2

// private type GraphObj
typedef struct GraphObj{
    List *Array;
    int *colors ;
    int *parent ;
    int *distance ;
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
    for(int i = 1; i <= n; i++){
	G->Array[i] = newList();
	G->colors[i] = W;
	G->parent[i] = NIL;
	G->distance[i] = INF;
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
        free(*pG);
        *pG = NULL;
    }
}
/*** Access functions ***/
int getOrder(Graph G){
    return G->vertices;
}

int getSize(Graph G){
    int tot= 0;
    for(int i = 0; i <= getOrder(G);i++){
        tot = tot + length(G->Array[i]);
    }
    G->size = tot/2;
    return G->size;
}
int getSource(Graph G){
    return G->source;
}
int getParent(Graph G, int u){
    if( u <= 0 || u > getOrder(G)){
        printf("u is invalid\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G) == NIL){
        return NIL;
    }
        return G->parent[u];
}
int getDist(Graph G, int u){
    if( u <= 0 || u > getOrder(G)){
        printf("u is invalid\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G)!= NIL){
        return G->distance[u];
    }
    return INF;
}
void getPath(List L, Graph G, int u){
    if( u <= 0 || u > getOrder(G)){
        printf("u is invalid\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL){
        printf("BFS not run!\n");
        exit(EXIT_FAILURE);
    }
    if(u == getSource(G)){
        append(L,u);
        return;
    }
    else if(G->parent[u] == NIL){
        append(L,NIL);
    }
    else{
        getPath(L, G, getParent(G, u));
	append(L,u);
    }
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
    for(int i = 1; i <= getOrder(G); i++){
        clear(G->Array[i]);
	free(G->Array[i]);	
	
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
	    if(index(G->Array[u]) == (length(G->Array[u])-1)){
		append(G->Array[u], v);
		break;
		}
        }
    }
    if(length(G->Array[u]) == 0){
        append(G->Array[u], v);
    }
    if(length(G->Array[v])!=0){

        for(moveFront(G->Array[v]);index(G->Array[v]) < length(G->Array[v]);moveNext(G->Array[v])){
        	if(index(G->Array[v]) < 0){
                        printf("%d\n", index(G->Array[v]));
                        exit(EXIT_FAILURE);
		}    
	
		if(get(G->Array[v]) > u){
                insertBefore(G->Array[v], u);
                break;
            }
            if(index(G->Array[v]) == (length(G->Array[v])-1)){
                append(G->Array[v], u);
                break;
                }
        }
    }
    if(length(G->Array[v]) == 0){
        append(G->Array[v], u);
    }
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
                break;
            }
	    if(index(G->Array[u]) == (length(G->Array[u])-1)){
                append(G->Array[u], v);
                break;
                }
        }
    }
    if(length(G->Array[u]) == 0){
        append(G->Array[u], v);
    }
}
void BFS(Graph G, int s){
    G->distance[s] = 0;
    G->parent[s] = NIL;
    G->colors[s] = Gr;
    List L;
    L = newList();
    append(L,s);
    moveFront(L);
    while(length(L) >0){
	if(index(L) < 0){
	 printf("error found\n");
	exit(EXIT_FAILURE);
        }
	int x = get(L);
        G->source = get(L);
        deleteFront(L);
        for(moveFront(G->Array[x]); index(G->Array[x]) >= 0 && index(G->Array[x]) < length(G->Array[x]);moveNext(G->Array[x])){
		if(index(G->Array[x]) < 0){
        	 printf("error found\n");
       	 	exit(EXIT_FAILURE);
        	}
		

            if(G->colors[get(G->Array[x])] == W){ // if cursor undiscovered 
                G->colors[get(G->Array[x])] = Gr; // discover
                G->distance[get(G->Array[x])] = G->distance[x] + 1;
                G->parent[get(G->Array[x])] = x;
                append(L,get(G->Array[x]));
            }
        }
        G->colors[x] = B;
        moveFront(L);
    }
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    for(int i = 1; i <= G->vertices; i++){
        fprintf(out, "%d:",i);
        printList(out, G->Array[i]);
	printf("\n");
    }
  
}
