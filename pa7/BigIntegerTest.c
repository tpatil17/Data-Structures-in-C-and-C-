#include "BigInteger.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "List.h"


int main(){


	BigInteger A, B, D;
   char str1[] = "-12";
   char str3[] = "-1";
   char str2[] = "9876545439874329879874320000000005432";
   
   A = stringToBigInteger(str1);
   printf("A = ");
  
   printBigInteger(stdout, A);
   
  // printf("%d", sign(A));

   printf("\n");

   B = stringToBigInteger(str2);
   printf("B = ");
   printBigInteger(stdout, B);
   printf("\n");

   BigInteger C = sum(A, B);

   add(C, A, B);

   printf("C =");

   printBigInteger(stdout, C);
   printf("\n");
 
   D = diff(A, B);

   printf("D = ");

   printBigInteger(stdout, D);
   printf("\n");


   BigInteger E;

   E = copy(A);

   printf("E =");


   BigInteger new = stringToBigInteger(str3);  

   printBigInteger(stdout, E);

 
  printf("\n"); 
  
   BigInteger ans = prod(new, A);
printf( " ans = \n");
   printBigInteger(stdout, ans);

  printf("\n");

  

  BigInteger pA = stringToBigInteger("+111122223333");
  BigInteger pB = stringToBigInteger("+222211110000");
  BigInteger pC = newBigInteger();

 // printf("3 var properly declared\n");

  BigInteger pD = stringToBigInteger("+333333333333");
            add(pC, pA, pB);
  //printf("problem after add\n");

  printBigInteger(stdout, pD);
	
  printf("\n");
//  printf("problem in printbig\n");

  printBigInteger(stdout, pC);

  printf("\n");


  if(!equals(pC, pD)) printf("true");
  

   pB = stringToBigInteger("-111122223333");
   add(pC, pA, pB);
   printBigInteger(stdout, pC);
   printf("\n");
   if(sign(pC) != 0) printf("%d\n", sign(pC));
            


  freeBigInteger(&pB);
  freeBigInteger(&pD);
 
 
}



