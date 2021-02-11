/*********************************************************************************
 *** Tanishq Patil, tmpatil
 *** 2021 Winter CSE 101 pa4
 *** ListTest.cpp
 *** test for List ADT
 ***********************************************************************************/

#include<iostream>
#include<string>
#include"List.h"

using namespace std;

int main(){

   
   List A, B, C, D, E;

   A.insertBefore(1);
        A.insertAfter(2);
        B.insertBefore(1);
        B.insertBefore(2);
        A.eraseAfter();
        cout<<" A : " << A.size()<< endl;
	cout<<" B : " << B.size()<< endl;

        B.movePrev();
        B.eraseAfter();
        cout<<" A : " << A.size()<< endl;
        cout<<" B : " << B.size()<< endl;


        A.insertAfter(5);
        B.insertAfter(5);
        A.eraseAfter();
        B.eraseAfter();
        cout<<" A : " << A.size()<< endl;
        cout<<" B : " << B.size()<< endl;

  C = A.concat(B);

 cout<<C.position() << endl;

 C.clear();

 cout<<C.size()<<endl;

 A.inserAfter(10);

 A.inserAfter(10);

 A.inserAfter(10);

 cout<< A.FindNext(10)<< endl;

  


}
