#include"Graph.h"
#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main( int argc, char* argv[]){
    FILE *in, *out;
    int n; 
    int u;
    int v;
    int line = 0;


     // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

    // get the number of vertices

    fscanf(in, "%d", &n);

    Graph G =  newGraph(n);



    while(fscanf(in, "%d %d", &u , &v)){
	line++;
        if ( u <= 0 || v <= 0){
            break;
        }
        
            addArc(G, u, v);
        
    }
    fprintf(out, "Adjacency list representation of G:\n")
    printGraph(out, G);
    fprintf(out, "\n");

 // The List of vertices before DFS
    List S = newList();

    for(int i =1; i <= n; i++){
        append(S, i);
    }

 // Run DFS the First time

 DFS(G,S);

 // Run DFS on a transpose Graph

 DFS(T, S);

 // Count the number of scc's 
 int count =0;
 for(moveFront(S); index(S) >= 0; moveNext(S)){
    if(getParent(get(S)== NIL)){
        count++;
    }
 }
 // print the scc'c in atopological order
 fprintf(out, "G contains %d strongly connected compenents:\n",count);

 int ct =1;
 for(moveFront(S); index(S)>=0; moveNext(S)){
    if(getParent(get(S)) != NIL){
        fprintf(out, "%d ", get(S));
    }
    else{
        fprintf(out, "\nCompnent %d:", ct);
        ct++;
        fprintf(out, " %d", get(S));
    }
 }
 

 // Closing all the files and deleting the freeing all the allocated memory
 freeList(&S);
 freeGraph(&G);
 freeGraph(&T);

 fclose(in);
 fclose(out);

}

