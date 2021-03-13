/*************************************************************************
 *
 * Tanishq Patil, CSE101 Winter 2021, pa7
 *
 * Tmpatil
 *
 * client file for pa7
 * **********************************************************************/


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

   fscanf(in, "%s", line);

   int size_1 = atoi(line);

   char *str_1 = calloc(1, sizeof(size_1)+1);

   fscanf(in, "%s", str_1);

   BigInteger A = stringToBigInteger(str_1);

   fscanf(in, "%s", line);

   int size_2 = atoi(line);

   char* str_2 = calloc(1, sizeof(size_2)+1);

   fscanf(in, "%s", str_2); 

   BigInteger B = stringToBigInteger(str_2);


  // 𝐴, 𝐵, 𝐴 + 𝐵, 𝐴 − 𝐵, 𝐴 − 𝐴, 3𝐴 − 2𝐵, 𝐴B, 𝐴2, 𝐵2, 9𝐴4 + 16𝐵5
  //
  


  // print A
  

  printBigInteger(out, A);

  fprintf(out, "\n\n");

  printBigInteger(out, B);// print B

  fprintf(out, "\n\n");


  BigInteger C = sum(A, B); // A + B

  printBigInteger(out, C);

  fprintf(out, "\n\n");

  subtract(C, A, B);  // A - B

  printBigInteger(out, C);

  fprintf(out, "\n\n");

  
//printf("peoblem in sub\n");
  subtract(C, A, A); // A - A
	
printf(" no problem in subract\n");

  printBigInteger(out, C);

printf(" no problem in pintig 0\n");

  fprintf(out, "\n\n");
// end of first 3
	
free(str_1);
free(str_2);
freeBigInteger(&A);
freeBigInteger(&C);
freeBigInteger(&B);
}
