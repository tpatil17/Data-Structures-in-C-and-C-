#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"

int main(){

    Dictionary D; 

    D = newDictionary(1);

    insert(D, "a", 1);
    insert(D, "A", 2);
    insert(D, "c", 3);
    insert(D, "B", 4);
    insert(D, "d", 5);

    printDictionary(stdout, D);

    makeEmpty(D);

    printf("size : %d\n", size(D));

    if(currentKey(D) == KEY_UNDEF && currentVal(D) == VAL_UNDEF && size(D) == 0){

	printf(" satis fied empty make null\n");
    }

    insert(D, "g", 17);

    insert(D, "b", 15);

    insert(D, "F", 18);

    printf("The new size: %d\n", size(D));

    printDictionary(stdout, D);

    printf("%d\n", lookup(D, "F"));

    delete(D, "F");

    if(currentKey(D) == KEY_UNDEF && currentVal(D) == VAL_UNDEF){

        printf(" test1 \n");
    }


    printf(" The updated dictionary :\n");

    printDictionary(stdout, D);

    insert(D, "l", 19);

    insert(D, "c", 20);

    // forward iteration over A ----------------------------
    printf("forward D:\n");
	
    int x = 0;
        
    for(x=beginForward(D); currentVal(D)!=VAL_UNDEF; x=next(D)){
              
 	printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(D), x);
        
          }

    printf("\n\n");
    
                          // reverse iteratation over B 
               
    printf("reverse D:\n");
				
    int y =0;
                              
    for(y=beginReverse(D); currentVal(D)!=VAL_UNDEF; y=prev(D)){
                                    
 	printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(D), y);
                                         
	}
     
     printf("\n\n");

	
    printDictionary(stdout, D);	
 
    freeDictionary(&D);

}
