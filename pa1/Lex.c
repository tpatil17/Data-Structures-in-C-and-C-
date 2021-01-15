#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"


int main(int argc, char * argv[]){

    int line_count = 0;
    char word[300];
    char ch;
    FILE *in_ct =NULL;
    FILE *in_read = NULL;
    FILE *out = NULL;


    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    // open files for reading and writing 
   in_ct = fopen(argv[1], "r");
      if( in_ct==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
    // count the number of lines
    while((ch=fgetc(in_ct))!=EOF) {
        if(ch=='\n'){
            line_count++;
        }
    }
    // Close the file
    fclose(in_ct);

    // Re open to read
    in_read = fopen(argv[1], "r");
      if( in_read==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
      }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
    // An array of strings
    char **string_array;

    string_array = malloc(line_count);
    string_array = NULL;
    for(int i = 0; i < line_count; i++){
        string_array[i] = malloc(300 * sizeof(char));
        string_array[i] = NULL;
    }
    int count = 0;// for counting words/ indexing will also serve as data to the list
    List L = newList();

    // Read in the words and put them in array, also create a list of its indices.
    while(fscanf(in_read, "%s", word) != EOF){
        string_array[count] = word;
        if(length(L) ==0){ // append the element if list is empty
            append(L, count);
            count++;
            continue;
        }
        moveBack(L);// Set the cursor to the back of list
        while(index(L)>=0 && strcmp(word,string_array[get(L)])<0){ /* loop backward until
        word >= the element compared.*/
            movePrev(L);// move cursor back a step
        }
        if(index(L) < 0){// it means the word is smaller than the first ele, sp prepend
            prepend(L, count);
        }
        if(index(L)>=0 && strcmp(word, string_array[get(L)]>=0)){ /* it means the current
            cursor element is greater than the new element.*/
            insertAfter(L, count);//insert after the cursor.
        } 
        count ++;
    }

    // Print the input in a orderly manner 

    moveFront(L);
    while(index(L)>=0 && index(L)< length(L)){
        fprintf(out,"%s\n", string_array[get(L)]);
        moveNext(L);
    }
    fclose(out);

    // free the string array
    for(int i = 0; i < line_count; i++){
        free(string_array[i]);
    }
    free(string_array);
    // free the list
    freeList(&L);
      
}
