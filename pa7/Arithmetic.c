#include<string.h>
#include<stdio.h>
#include "List.h"
#include<stdlib.h>
#include "BigInteger.h"

int main(int argc, char *argv[]){


	FILE *in = NULL;

	FILE *out = NULL;

    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

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

   char line[300]; 

   fgets(line, 300, in);

   int size_1 = atoi(line);

   char *str_1 = calloc(1, sizeof(size_1)+1);

   fgets(str_1, size_1+1, in);

   BigInteger A = stringToBigInteger(str_1);

   fgets(line, 300, in);

   int size_2 = atoi(line);

   char* str_2 = calloc(1, sizeof(size_2)+1);

   fgets(str_2, size_2 + 1,in); 

   BigInteger B = stringToBigInteger(str_2);


  // 𝐴, 𝐵, 𝐴 + 𝐵, 𝐴 − 𝐵, 𝐴 − 𝐴, 3𝐴 − 2𝐵, 𝐴B, 𝐴2, 𝐵2, 9𝐴4 + 16𝐵5
  //
  


  // print A
  

  printBigInteger(out, A);

  fprintf(out, "\n\n");

  printBigInteger(out, B);

  fprintf(out, "\n\n");

  BigInteger C = sum(A, B);

  printBigInteger(out, C);

  fprintf(out, "\n\n");

  subtract(C, A, B);

  printBigInteger(out, C);

  fprintf(out, "\n\n");

  subtract(C, A, A);

  printBigInteger(out, C);

  fprintf(out, "\n\n");

  BigInteger F = sum(A, A);

  add(F, F, A);

  BigInteger G = sum(B, B);

  subtract(F, F, G);

  printBigInteger(out, F);

  fprintf(out, "\n\n");

  multiply(F, A, B);

  printBigInteger(out, F);

  fprintf(out, "\n\n");

  multiply(F, A, A);

  printBigInteger(out, F);

  fprintf(out, "\n\n");
  
  multiply(G, B, B);

  printBigInteger(out, G);

  fprintf(out, "\n\n");

  // A^4
  //
  multiply(F, F, F);


  multiply(G, G, G);

  multiply(G, G, B);


  int i = 4;

  char buf[300];

  sprintf(buf, "%d", i);

  BigInteger new = stringToBigInteger(buf);

  i = 16;

  BigInteger sec;

  sprintf(buf, "%d", i);
  
  sec = stringToBigInteger(buf);


  multiply(F, F, new);

  multiply(G, G, sec);


  add(F, F, G);


  printBigInteger(out, F);

  fprintf(out, "\n\n");

  freeBigInteger(&F);

  freeBigInteger(&G);

  freeBigInteger(&A);

  freeBigInteger(&B);

  freeBigInteger(&C);

  freeBigInteger(&new);
 
  freeBigInteger(&sec);

  fclose(out);

  fclose(in);

  free(str_1);

  free(str_2);
	

}
