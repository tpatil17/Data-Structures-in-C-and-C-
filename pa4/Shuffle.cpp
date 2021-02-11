/*********************************************************************************
 **** Tanishq Patil, tmpatil
 **** 2021 Winter CSE 101 pa4
 **** Shuffle.cpp
 **** Client file for pa4
 ************************************************************************************/


#include<iostream>
#include<string>
#include<fstream>
#include "List.h"

using namespace std;

void shuffle(List& L){

    L.moveFront();

   if(L.size() >  1){

    

    List left;
    List right;
    

    int split = 0;
    
    if(L.size()%2 == 0){
        split = L.size()/2;
    }
    else{
        split = (L.size()-1)/2;
    }

    int i = 1;
    int n = 0;

    n = L.moveNext();

    while(i <= split){

        left.insertBefore(n);
        n = L.moveNext();
        i++;
    }

    while(L.position() <= L.size()){

        right.insertBefore(n);
        
        if(L.position() == L.size()){
            break;
        }
        
        n = L.moveNext();

    }

     L.clear(); // clear the original

     left.moveFront();
     right.moveFront();

     int l_num = left.moveNext();
     int r_num = right.moveNext();

    while(left.position() <= left.size()){

        L.insertBefore(r_num);
        L.insertBefore(l_num);
        
        if(left.position() == left.size()){
            break;
        }

        l_num = left.moveNext();
        r_num = right.moveNext();
    }

    if(right.position() < right.size()){
        r_num = right.moveNext();
        L.insertBefore(r_num);
    }

    left.clear();
    right.clear();

    }
    
}

int main(int argc, char* argv[]){

    if(argc == 1){
        cerr<< " Prpgram argument expected: no input given"<< endl;
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);// the number of cards

    List L, C;

    if(n <= 0){
        cerr<< " the entered number is invalid"<< endl;
        exit(EXIT_FAILURE);
    }

    cout<< "deck size       shuffle count"<< endl;
    cout<< "------------------------------"<< endl;

    for(int i =1 ; i <= n; i++){

	//cout<< " in the first"<< endl;
        
        int shuf_count = 0;
        
         for(int j = 1; j <= i; j++){
		
	  //cout<< " in the second" << endl;

            L.insertBefore(j);    
         }

        C = L;

        shuffle(L);
        shuf_count ++;
        while( L.equals(C) != 1){
            shuffle(L);
            shuf_count++;
        }

        cout<< " "<< L.size() << "                 "<< shuf_count<< endl;
        
        L.clear();
    }


}




