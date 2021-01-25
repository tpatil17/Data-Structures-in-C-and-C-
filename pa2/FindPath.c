#include "List.h"
#include "Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main(int argc, char* argv[]){

    FILE *in, *out;
    int n; 
    int u;
    int v;


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

    fscanf(in, "%d", n);

    fseek(in, 1, SEEK_SET);

    while(fscanf(in, "%d %d", u , v)){
        if ( u <= 0 || v <= 0){
            break;
        }
        else{
            addArc(G, u, v);
        }
    }

    printGraph(out, G);
    fprintf(out, "\n");

    while(fscanf(in, "%d %d", u ,v)){
        if ( u <= 0 || v <= 0){
            break;
        }
        List L = newList();
        BFS(G, u);

        getPath(L, G, v);

        if(getDist(G,v) == INF){
            fprintf(out, "The distance from %d to %d is infinty\n", u, v);
            fprintf(out, "No %d-%d path exists\n", u , v);
        }
        else{
            fprintf(out, "The distance from %d to %d is %d\n", u, v, getDist(G,v));
            fprintf(out, "A shortest %d-%d path is: ", u,v);
            fprintList(out, L);
            fprintf(out, "\n");
        }
        freeList(&L);

    }
    freeGraph(&G);
}
