#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>
#include "List.h"
#include<math.h>

int main(){

	List A = newList();

	long power = pow(10, 9);
	
	long num = 0;

	long Zero = 0;
	

	for(int i  = 0; i <= 10; i++){

		append(A, num*power);
		num++;
		
	
	}


	deleteBack(A);
	
	
	for(moveFront(A); index(A) != -1; moveNext(A)){

		set(A, get(A)+1);
	} 

        moveFront(A);
 
	delete(A);

	moveFront(A);

	insertAfter(A, Zero);
	
	printf("%d\n", length(A));
	printList(stdout, A);

	freeList(&A);
	
}
