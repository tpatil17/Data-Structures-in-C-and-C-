
/*********************************************************************************
 *  * * Tanishq Patil, tmpatil
 *  * * 2021 Winter CSE 101 pa2
 *  * * Graph.h
 *  * * header for Graph ADT
 *  * *********************************************************************************/

//-----------------------------------------------------------------------------
//// Graph.h

////-----------------------------------------------------------------------------
#ifndef GRAPH_H_
#define GRAPH_H_
#include "List.h"
#include<stdio.h>
#define NIL -1
#define INF -2
#define W 0
#define Gr 1
#define B 2

//Grpah.h 
typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);

#endif
