/*********************************************************************************
 * * Tanishq Patil, tmpatil
 * * 2021 Winter CSE 101 pa5
 * * Lex.c
 * * The main client file for pa5
 * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"


int main(int argc, char *argv[]){

    int line_count =0;
    char ch;
    FILE *in;
    FILE *out;


    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    // open files for reading and writing 
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf(" 1 Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
    // count the number of lines
    while((ch=fgetc(in))!=EOF) {
        if(ch=='\n'){
		
            line_count++;
        }
  }
 rewind(in);

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
    // An array of strings
    char **string_array;
	string_array = malloc(line_count* sizeof(char*));
	for(int i =0 ;i < line_count; i++){
		string_array[i] = malloc(4096);
		
	}


    int count = 0;// for counting words/ indexing will also serve as data to the list
    Dictionary D = newDictionary(0);

    // Read in the words and put them in array, also create a list of its indices.
    while(fgets(string_array[count], 4096, in)){
        
    	string_array[count][strlen(string_array[count])-1] = '\0';

        
        insert(D,string_array[count], count);
        count++;
 
    }

    // Print the input in a orderly manner 

    for(beginForward(D); currentVal(D) != VAL_UNDEF; next(D)){
        fprintf(out,"%s\n", string_array[currentVal(D)]);
    }
    

    // free the string array
    for(int i = 0; i < line_count; i++){
        free(string_array[i]);
    }
    free(string_array);
    // free the list
    freeDictionary(&D);

// close the files
 fclose(in);    
 fclose(out);
}


