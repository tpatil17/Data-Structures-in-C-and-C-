#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"


int main(int argc, char *argv[]){

    int line_count =0;
    char ch;
    FILE *in;
    FILE *out;

if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

  in = fopen(argv[1], "r");
      if( in==NULL ){
      printf(" 1 Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

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


    char **string_array;
	string_array = malloc(line_count* sizeof(char*));
	for(int i =0 ;i < line_count; i++){
		string_array[i] = malloc(4096);
		
	}

 int count = 0;// for counting words/ indexing will also serve as data to the list
 
 Dictionary D = newDictionary(0); 

int* p, c;
 c = -1;
 p   = &c;
     while(fgets(string_array[count], 4096, in)){
        
    	string_array[count][strlen(string_array[count])-1] = '\0';

        
        insert(D,string_array[count], p);
        count++;
 
    }
    fprintf(out, "******************************************************\n");
    fprintf(out, "PRE-ORDER:\n");
    fprintf(out, "******************************************************\n");

    printDictionary(out, D, "pre");
    fprintf(out, "\n\n");
 
    fprintf(out, "******************************************************\n");
    fprintf(out, "IN-ORDER:\n");
    fprintf(out, "******************************************************\n");

    printDictionary(out, D, "in");
    fprintf(out, "\n\n");
 

    fprintf(out, "******************************************************\n");
    fprintf(out, "POST-ORDER:\n");
    fprintf(out, "******************************************************\n");

    printDictionary(out, D, "post");
    fprintf(out, "\n\n");
  

    // free the string array
  for(int i = 0; i < line_count; i++){
        free(string_array[i]);
    }
    free(string_array);
   
    freeDictionary(&D);

 fclose(in);    
 fclose(out);
}



