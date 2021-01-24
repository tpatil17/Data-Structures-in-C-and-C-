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
  
    return G->size;
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
   if(getSource(G) == NIL){
        return NIL;
    }
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
    if(u == getSource(G)){
        append(L,u);
       
    }
    else if(G->parent[u] == NIL){
        append(L, NIL);
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
       
    if(i == s){
   	 G->colors[i] = Gr;
   	 G->parent[i] = NIL;
   	 G->distance[i] = 0;
	}
	G->colors[i] = W;
        G->parent[i] = NIL;
        G->distance[i] = INF;

  }
    //G->source = s;
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
			append(L, x);
		}
		moveNext(G->Array[x]);
	}
	G->colors[x] = B;
	moveFront(L);
    }
   freeList(&L);
   	
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    for(int i = 1; i <= G->vertices; i++){
        fprintf(out, "%d:",i);
        printList(out, G->Array[i]);
        printf("\n");
    }

}
