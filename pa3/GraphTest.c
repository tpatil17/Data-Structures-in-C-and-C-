#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

int main(){

	Graph G = newGraph(7);

	addEdge(G, 1,2);
	addEdge(G, 1,4);
	addEdge(G, 2,4);
	addEdge(G, 2,5);
	addEdge(G, 3,6);
	addEdge(G, 3,7);
	addEdge(G, 6,7);

	List S = newList();
	
	for(int i =1; i <= 7; i++){
		append(S, i);
	}
	
	printList(stdout,S);
	printf("\n");
	DFS(G, S);
	printList(stdout, S);
	printf("\n");
	for(int i = 1; i <= 7; i++){

		printf("Parent[%d] = %d\n", i, getParent(G, i));
		printf("Discover time of %d = %d\n", i, getDiscover(G, i));
		printf("Finish time of %d = %d\n", i, getFinish(G, i));
	}
	Graph T = transpose(G);
	printf("*** The original Graph***\n");
	printGraph(stdout, G);
	printf("\n");
	printf("*** transpose of graph G***\n");
	printGraph(stdout,T);
	printf("\n");
	freeGraph(&G);
	freeList(&S);
}

