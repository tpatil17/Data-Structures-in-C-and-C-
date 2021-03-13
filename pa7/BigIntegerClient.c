//-----------------------------------------------------------------------------
//  BigIntegerClient.c 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"
     
int main(){
   BigInteger A, B, C, S, D, E, F, P, T;
   char str1[] = "12345678912345";
   char str2[] = "-1234567891234";
   char str3[] = "9876545439874329879874320000000005432";
   
   A = stringToBigInteger(str1);
   printf("A = ");
   printBigInteger(stdout, A);
   printf("\n");

   B = stringToBigInteger(str2);
   printf("B = ");
   printBigInteger(stdout, B);
   printf("\n");

   C = newBigInteger();
   add(C, A, B);  // C = A + B
   printf("C = ");
   printBigInteger(stdout, C);
   printf("\n");

   S = sum(A, B); // S = A + B
   printf("S = ");
   printBigInteger(stdout, S);
   printf("\n");

   printf("C==S is %s\n", equals(C, S)?"true":"false");

   add(A, A, B);  // A = A + B
   printf("A = ");
   printBigInteger(stdout, A);
   printf("\n");

   printf("A==S is %s\n", equals(A, S)?"true":"false");

   add(A, A, A);  // A = A + A
   printf("A = ");
   printBigInteger(stdout, A);
   printf("\n");

   add(S, C, S);  // S = C + S
   printf("S = ");
   printBigInteger(stdout, S);
   printf("\n");

   printf("A==S is %s\n", equals(A, S)?"true":"false");

   D = stringToBigInteger(str3);
   printf("D = ");
   printBigInteger(stdout, D);
   printf("\n");

   E = diff(A, D);
   printf("E = ");
   printBigInteger(stdout, E);
   printf("\n");

   F = diff(D, A);
   printf("F = ");
   printBigInteger(stdout, F);
   printf("\n");

   P = newBigInteger();
   multiply(P, E, F);
   printf("P = ");
   printBigInteger(stdout, P);
   printf("\n");

   T = prod(E, F);
   printf("T = ");
   printBigInteger(stdout, T);
   printf("\n");

   freeBigInteger(&A);
   freeBigInteger(&B);
   freeBigInteger(&C);
   freeBigInteger(&S);
   freeBigInteger(&D);
   freeBigInteger(&E);
   freeBigInteger(&F);
   freeBigInteger(&P);
   freeBigInteger(&T);

   return EXIT_SUCCESS;
}

/****************************************************************************** 
output of this program:

A = 12345678912345
B = -1234567891234
C = 11111111021111
S = 11111111021111
C==S is true
A = 11111111021111
A==S is true
A = 22222222042222
S = 22222222042222
A==S is true
D = 9876545439874329879874320000000005432
E = -9876545439874329879874297777777963210
F = 9876545439874329879874297777777963210
P = -97546149825902420296272279959722560175144145908758987919786795096113504100
T = -97546149825902420296272279959722560175144145908758987919786795096113504100

*******************************************************************************/
