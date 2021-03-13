/******************************************************************************
 * Tanishq, Patil, Tmpatil
 *
 * 2021 Winter, cse101, pa7
 *
 * test for BigInteger
 * *******************************************************************************/


#include<stdio.h>
#include<string.h>
#include "BigInteger.h"
#include "List.h"
#include<stdlib.h>

int main(){


	char str1[] = "-43549940394309403949020302930923909434095855999";
	char str2[] = "90234848848846384387582474835934937597946894985888";

	BigInteger A; 
	BigInteger B;

	A = stringToBigInteger(str1);

	B = stringToBigInteger(str2);

	printBigInteger(stdout, A);
	printf("\n");
	printBigInteger(stdout, B);
	printf("\n");

	add(A, A, B);

	printBigInteger(stdout, A);

	subtract(A, A, B);

	printf("\n");

	printBigInteger(stdout, A);

	printf("\n");




	multiply(A, A, B);

	printBigInteger(stdout, A);

	printf("\n");

	freeBigInteger(&A);

	freeBigInteger(&B);


}



