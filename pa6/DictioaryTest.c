#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Dictionary.h"



int main(){

	// test for insert function
	//
	

	Dictionary D = newDictionary(0);

	printf("%d\n", getUnique(D));

	printf("%d\n", size(D));


	int* p, c;

	c = 5;

	p = &c;	
	
	insert(D, "T", p);

	insert(D, "A", p);

	insert(D, "f", p);

	insert(D, "c", p);

	insert(D, "k", p);


	printf("%d\n", size(D));

	delete(D, "T");

	printf("inorder \n");
	printDictionary(stdout, D, "in");

	delete(D, "c");
	printf("post\n");

	printDictionary(stdout, D, "post");
// *************************************************************************	

	 printf("forward D:\n");
	
    //int x = 0;
        
    for(beginForward(D); currentVal(D)!=VAL_UNDEF; next(D)){
              
 	printf("key: "KEY_FORMAT"\n", currentKey(D));
        
          }

//    printf("\n");

//************************************************************************************
	

	printf("forward D:\n");
	makeEmpty(D);

	printf("%d\n", size(D));

//	freeDictionary(&D);
}
 
