


/*********************************************************************************
 * * Tanishq Patil, tmpatil
 * * * 2021 Winter CSE 101 pa2
 * * * GraphTest.c
 * * * Basic Test for Graph ADT
 * * *********************************************************************************/
#include "List.h"
#include "Graph.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(){

 int n= 7;
//   List  C = newList(); // central vertices 
  // List  P = newList(); // peripheral vertices 
   List  E; // eccentricities 
   Graph G = NULL;

   G = newGraph(n);
	
   addEdge(G, 1, 2);

   addEdge(G, 1, 6);

    addEdge(G, 2, 3);
 
   addEdge(G, 2, 4);

   addEdge(G, 3, 5);

   addEdge(G, 3, 6);

   addEdge(G, 4, 5);

   addEdge(G, 5, 7);

   addEdge(G, 6, 7);

   BFS(G, 5);

   printf("order: %d\n", getOrder(G));

   printf("size: %d\n", getSize(G));

   for(int i = 1; i <= n; i++){
     printf("%d parent: %d\n", i, getParent(G, i));

     }
   for(int i =1 ; i <= n; i++){
	E = newList();

	getPath(E, G, i);

	printList(stdout, E);

	printf("\n");

	freeList(&E);

	}

freeGraph(&G);
}


