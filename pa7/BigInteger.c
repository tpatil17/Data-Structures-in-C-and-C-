#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "BigInteger.h"
#include "List.h"
#include<math.h>
#define p 9

// private ListObj type
typedef struct BigIntegerObj{
    int sign;
    List num_list;
} BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
    BigInteger B = calloc(1, sizeof(BigIntegerObj));
    B->sign = 0;// empty state
    B->num_list = newList();// empty list
    return B;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){

    BigInteger B = *pN;
    freeList(&B->num_list);
    free(*pN);
    *pN = NULL;
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero 
// state.
int sign(BigInteger N){
    return N->sign;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){

    // compare length
    if(length(A->num_list) < length(B->num_list)){
        return -1;
    }
    if(length(A->num_list) > length(B->num_list)){
        return 1;
    }

    //compare sign 
    if(A->sign < B->sign){
        return -1;
    }
    if(A->sign > B->sign){
        return 1;
    }

    // compare each node
    moveFront(A->num_list);
    moveFront(B->num_list);
    while(index(A->num_list)<=0 && index(A->num_list) < length(A->num_list)){
        if(get(A->num_list) < get(B->num_list)){
            return -1;
        }
        if(get(A->num_list) > get(B->num_list)){
            return 1;
        }

        moveNext(A->num_list);
        moveNext(B->num_list);    
    }
    // all nodes, lengths and signs are equal
    return 0;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){

    if(compare(A, B) == 0){
        return 1;
    }
    else{
        return 0;
    }
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
    N->sign = 0;
    clear(N->num_list);
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
    if(N->sign != 0){
        N->sign = -1*N->sign;
    }
}


// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s. 
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9} 
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
    // pre condition 1------------------------------------------

    if(strlen(s) == 0){
        printf("pre condition 1 for string to big integer failed\n");
        exit(EXIT_FAILURE);
    }
    long temp =0;

    BigInteger B = newBigInteger();

    char* cpy = malloc(sizeof(int)*strlen(s));
    //char *buf = calloc(1, sizeof(int)*strln(s));

int k = 0; 

        
    if( s[0] == '-'){
        B->sign = -1;
        for( int j =1; s[j] != '\0'; j++){
            cpy[k] = s[j];
	    k++;
        }
        cpy[k] = '\0';
    }
    else{
        B->sign = 1;
        for(int j  =0; s[j] != '\0'; j++){
            cpy[k] = s[j];
	    k++;
        }
        cpy[k] = '\0';
    }
 //   printf("%s\n", s);
    //printf("%s\n", cpy);
    //printf("%d\n", strcmp(s, cpy));
    
    int i = 1;
    long val = 0;
    long buf = 0;
    int ctr =  0;
    char *digit = calloc(1, sizeof(int));
    while(i <= strlen(cpy)){

	digit[0] = cpy[strlen(cpy)-i];
        temp = atoi(digit);
//	printf("%ld\n", temp);
        
        if((temp -10) > 0){
            printf("failed pre condition 2 in string to big integer\n");
            exit(EXIT_FAILURE);
        }
        if(ctr <= p){
            long power = pow(10, (ctr));
            val = temp * power;
            buf = buf + val;
            ctr++; 
            i ++;
        }
        if(ctr >= p || i > strlen(cpy)){
            prepend(B->num_list, buf);
            buf = 0;
            ctr = 0;
        }
        
    }

    free(cpy);
    free(digit);
    return B;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
    BigInteger C = newBigInteger();
    C->sign = N->sign;
    freeList(&C->num_list);
    C->num_list = copyList(N->num_list);
    return C;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state:  S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){

    S = sum(A, B);
    
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
    if(A->sign == 0){
        return B;
    }
    if(B->sign == 0){
        return A;
    }
    if(A->sign != B->sign){
        if(A->sign == -1){
            BigInteger C = copy(A);
            C->sign = 1;
            BigInteger R =  diff(B, C);
            freeBigInteger(&C);
            return R;
        }
        else{
            BigInteger C = copy(B);
            C->sign = 1;
            BigInteger R =  diff(A, C);
            freeBigInteger(&C);
            return R;
        }
    }
    else{
        moveBack(A->num_list);
        moveBack(B->num_list);
        BigInteger R = newBigInteger();
        while(index(A->num_list) != -1 && index(B->num_list) != -1){
            long temp = get(A->num_list)+get(B->num_list);
            prepend(R->num_list, temp);
            movePrev(A->num_list);
            movePrev(B->num_list);
        }
        if(length(A->num_list) != length(B->num_list)){
            if(length(A->num_list) > length(B->num_list)){
                while(index(A->num_list) != -1){
                    prepend(R->num_list, get(A->num_list));
                    movePrev(A->num_list);
                }
            }
            else{
                while(index(B->num_list) != -1){
                    prepend(R->num_list, get(B->num_list));
                    movePrev(B->num_list);
                }
            }
        }
        // Nutralise 
        moveBack(R->num_list);
        int carry = 0;
        long zero = 0;
        long buf = 0;
        long base = pow(10, p);
        while(index(R->num_list) != -1 ){
            if(carry == 1){
                set(R->num_list, get(R->num_list)+1);
            }
            buf = get(R->num_list) - base;
            if(buf >= 0){
                carry = 1;
                set(R->num_list, buf);
                if(index(R->num_list) == 0){
                    prepend(R->num_list, zero);
                }
            }
            else{
                carry = 0;
            }
            movePrev(R->num_list);
        }
        if(A->sign == -1 && B->sign == -1){
            R->sign = -1;
        }
        else{
            R->sign = 1;
        }
        return R;
    }
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting 
// its current state:  D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
    D = diff(A, B);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
    
    if(A->sign == 0){
        negate(B);
        return B;
    }
    else if(B->sign == 0){
        return A;
    }
    else if(A->sign != B->sign){ // (-A)- B = - (A+B)
        if(A->sign == -1){
            BigInteger C = copy(B);
            C->sign = -1;
            BigInteger R = sum(A, C);
            freeBigInteger(&C);
            return R;
        }
        else{                       // A - (- B) = A + B
            BigInteger C = copy(B);
            C->sign = 1;
            BigInteger R = sum(A, C);
            freeBigInteger(&C);
            return R;
        }
    }
    else{
        if(A->sign == -1){          // -A - (-B) = B - A

            BigInteger C = copy(B);
            C->sign = 1;
            BigInteger R = sum(B, A);
            freeBigInteger(&C);
            return R;
        }
        else{                       // A - B = A- B

 	BigInteger R;           
            if(compare(A, B) == -1){
                R  = diff(B, A);
                R->sign = -1;
            }
            else{
                R = newBigInteger();
                moveBack(A->num_list);
                moveBack(B->num_list);
                while(index(A->num_list) != -1 && index(B->num_list) != -1){
                    long temp = get(A->num_list)- get(B->num_list);
                    prepend(R->num_list, temp);
                    movePrev(A->num_list);
                    movePrev(B->num_list);
                }
                if(length(A->num_list) != length(B->num_list)){
                    if(length(A->num_list) > length(B->num_list)){
                        while(index(A->num_list) != -1){
                            prepend(R->num_list, get(A->num_list));
                            movePrev(A->num_list);
			}
                    }
                    else{
                        printf(" in wrong teritory\n");
                        exit(EXIT_FAILURE);
                    }
                }
                // Nutralise

                moveBack(R->num_list);
                int sub_carry = 0;
                long temp = 0;
                long base = pow(10, p);
                while(index(R->num_list) != -1){
                    if(sub_carry == 1){
                        temp = get(R->num_list) - 1;
                        set(R->num_list, temp);
                    }
                    if(get(R->num_list) < 0){
                        if(index(R->num_list) == 0){
                            temp = -1 *  get(R->num_list);
                            set(R->num_list, temp);
                            R->sign = -1;
                        }
                        else{
                            temp = get(R->num_list) + base;
                            set(R->num_list, temp);
                            sub_carry = 1;
                        }
                    }
                    else{
                        sub_carry = 0;
                    }
                    movePrev(R->num_list);
		
                }

                if(R->sign == 0){
                    R->sign = 1;
                }

	    }
 	return R;            
	}
  
    }

}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting 
// its current state:  P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){

    P = prod(A, B);

}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){

    
    if(length(A->num_list) < length(B->num_list)){
        printf("in wrong area");
        return prod(B, A);
    }
    else{
        BigInteger R = newBigInteger();
        if(A->sign == 0 || B->sign == 0){
            R->sign = 0;
            return R;
        }
        else if(A->sign == -1 || B->sign == -1){
            if(A->sign ==-1 && B->sign == -1){
                printf("right sign");
                R->sign = 1;
            }
            else{
                R->sign = -1;
            }
        }
        else{

            R->sign = 1;
        }

        moveBack(A->num_list);
        moveBack(B->num_list);
        long zero = 0;
        BigInteger buf = newBigInteger();
        BigInteger temp = newBigInteger();
        BigInteger temp_out = newBigInteger();
        long inc = 0;
        bool carry = false;
        while(index(B->num_list) != -1){

            BigInteger c = newBigInteger();
            moveBack(A->num_list);

            while(index(A->num_list) != -1){
                BigInteger s;
                long ctr = 1;
                long ctr_2 = 0;
                while(ctr <= get(A->num_list)){
                    add(buf, buf, B);
		    //printf("%ld\n", ctr);
                    ctr++;
                }
                 
               // printList(stdout, buf->num_list);   
                if(carry == true){
                    add(buf, c, buf);
                    makeZero(c);
                }               

                while(ctr_2 < (length(A->num_list)-1 - index(A->num_list))){
                    append(buf->num_list, zero);
                    ctr_2 ++;
                }
                add(temp, temp, buf);// temp stores the sum
                    
		//printBigInteger(stdout, temp);
                //printf("\n");
                s = copy(temp);
                ctr_2 = 0;

                while(ctr_2 < (length(A->num_list)-1 - index(A->num_list)) && length(s->num_list) != 0){
                    //printList(s->num_list);
		    deleteBack(s->num_list);
                    ctr_2 ++;
                }

                if(length(s->num_list) >= 1){ // number needs to be carried forward
                    if(index(A->num_list) == 0){
                        carry = false;
                        makeZero(c);
                    }
                    else{
                        add(c, c, s);
                        while(ctr_2 != 0){
                            append(s->num_list, zero);
                            ctr_2 --;
                        }
                        subtract(temp, temp, s);
                        carry = true;
                    }
                }
                    
                else{
                    carry = false;
                    makeZero(c);
                }
                freeBigInteger(&s);                        
                makeZero(buf);
                movePrev(A->num_list);
            }

            while(inc < length(B->num_list)-1 - index(B->num_list)){
                append(temp->num_list, zero);
                inc++;
            }
	   // printList(stdout, temp->num_list);
            add(temp_out, temp_out, temp);
            makeZero(temp);
            freeBigInteger(&c);
            movePrev(B->num_list);
        }
        
        freeBigInteger(&buf);
        freeBigInteger(&temp);
            
        freeList(&R->num_list);
        R->num_list = copyList(temp_out->num_list);
	//printList(stdout, R->num_list);
        freeBigInteger(&temp_out);
        return R;
    }
}

// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){

    char *str = calloc(1, length(N->num_list)*sizeof(long));
    char* buf = calloc(1, sizeof(long));
    char* buf_2 = calloc(1, sizeof(long));
    long zero = 0;
    sprintf(buf_2, "%ld", zero);
    int i = 0;
    if(N->sign == 0){
        fprintf(out, "%s\n", "0");
    }
    if(N->sign == -1){
        str[0] = '-';
        i ++;
    }
    moveFront(N->num_list);
    while(index(N->num_list) != -1){
        sprintf(buf, "%ld", get(N->num_list));
	if(index(N->num_list) != 0){

		while(strlen(buf) < 9){
			
		strncat(buf_2, buf, strlen(buf));
		
		memcpy(buf, buf_2, strlen(buf_2)+1);
		
		free(buf_2);
		buf_2 = calloc(1, sizeof(long));
		sprintf(buf_2, "%ld", zero);
	
		}
               
		

	}
	
        for(int j = 0; buf[j] != '\0'; j++){
            str[i] = buf[j];
            i++;
        }
	
        moveNext(N->num_list);    
    }
    str[i] = '\0';
    fprintf(out, "%s", str);
    

    
    free(str);
    free(buf);
    free(buf_2);
}
