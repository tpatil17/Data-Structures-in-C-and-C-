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
    Graph G = NULL;
    G = calloc(1,sizeof(Graph));
    G->Array = calloc(n + 1, sizeof(List));
    for(int i = 0; i < n+1; i++){
        newList(G->Array[i]);
    }
    G->colors = calloc(n+1,sizeof(int));
    G->parent = calloc(n+1,sizeof(int));
    G->distance = calloc(n+1, sizeof(int));
    G->vertices = n;
    G->size = 0;
    G->source = NIL;
    return G; 
}
void freeGraph(Graph* pG){
    for(int i = 0; i <= pG->vertices; i++){
        freeList(pG->Array[i]);
    }
    free(pG->Array);
    free(pG->colors);
    free(pG->parent);
    free(pG->distnce);
    free(&pG);
    *pG = NULL;
}
/*** Access functions ***/
int getOrder(Graph G){
    return G->vertices;
}

int getSize(Graph G){
    int tot= 0;
    for(int i = 0; i <= getOrder(G);i++){
        tot = tot + Length(G->Array[i]);
    }
    G->size = tot/2;
    return G->size;
}
int getSource(Graph G){
    return G->source;
}
int getParent(Graph G, int u){
    if( u <= 0 || u > gerOrder(G)){
        printf("u is invalid\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G) == NIL){
        return NIL;
    }
        return G->parent[u];
}
int getDist(Graph G, int u){
    if( u <= 0 || u > gerOrder(G)){
        printf("u is invalid\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G)!= NIL){
        return G->distance[u];
    }
    return INF;
}
void getPath(List L, Graph G, int u){
    if( u <= 0 || u > gerOrder(G)){
        printf("u is invalid\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NULL){
        printf("BFS not run!\n");
        exit(EXIT_FAILURE);
    }
    if(u == getSource(G)){
        append(L,u);
        return;
    }
    else if(G->parent[u] == NULL){
        printf("%d Not reachable from %d\n", u ,getSource(G));
        exit(EXIT_FAILURE);
    }
    else{
        getPath(L, G, getParent(G, u));
    }
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
    for(int i = 0; i <= getOrder(G); i++){
        clear(G->Array[i]);
    }
}
void addEdge(Graph G, int u, int v){
    if(Length(G->Array[u])!=0){

        for(moveFront(G->Array[u]);Index(G->Array[u]) < Length(G->array[u]);moveNext(G->Array[u])){
            if(get(G->Array[u]) > v){
                insertBefore(G->Array[u],v);
                break;
            }
        }
    }
    if(Length(G->Array[u]) == 0){
        append(G->Array[u], v);
    }
    if(Length(G->Array[v])!=0){

        for(moveFront(G->Array[v]);Index(G->Array[v]) < Length(G->array[v]);moveNext(G->Array[v])){
            if(get(G->Array[v]) > u){
                insertBefore(G->Array[v], u);
                break;
            }
        }
    }
    if(Length(G->Array[v]) == 0){
        append(G->Array[v], u);
    }
}
void addArc(Graph G, int u, int v){
    if(Length(G->Array[u])!=0){

        for(moveFront(G->Array[u]);Index(G->Array[u]) < Length(G->array[u]);moveNext(G->Array[u])){
            
            if(get(G->Array[u]) > v){
                insertBefore(G->Array[u],v);
                break;
            }
        }
    }
    if(Length(G->Array[u]) == 0){
        append(G->Array[u], v);
    }
}
void BFS(Graph G, int s){
    for(int i = 1; i <= getOrder(G); i++){
        if(i == s){
            i++;
            continue;
        }
        G->distance[i] = INF;
        G->colors[i]= W;
        G->parent[i] = NIL;
    }
    G->distance[s] = 0;
    G->parent[s] = NIL;
    G->colors[s] = Gr;
    List L;
    newList(L);
    append(L,s);
    moveFront(L);
    while(L != NULL){
        int x = get(L);
        G->source = get(L);
        deleteFront(L);
        for(moveFront(G->Array[x]); Index(G->Array[x]) < Length(G->Array[x]);moveNext(G->Array[x])){
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
        printList(out, G->Array[i])
    }
}
