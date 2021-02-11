/*********************************************************************************
 **** Tanishq Patil, tmpatil
 **** 2021 Winter CSE 101 pa4
 **** List.cpp
 **** implementation for List ADT
 ************************************************************************************/




#include<iostream>
#include<string>
#include "List.h"

using namespace std;

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(int x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

List::List(){
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    frontDummy->prev = nullptr;
    backDummy->next = nullptr;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor.
List::List(const List& L){

    // make this an empty List

    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    frontDummy->prev = nullptr;
    backDummy->next = nullptr;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    // load elements of L into this
    
   
    Node* N = L.frontDummy->next;
    while(N!= L.backDummy){
        this->insertBefore(N->data);
        N = N->next;
    }
    
this->moveFront();

}

// Destructor
List::~List(){
   moveBack();
   while(size() > 0){
       eraseBefore();
   }
   
    beforeCursor = nullptr;
    afterCursor = nullptr;
    delete frontDummy;
    delete backDummy;
}

// Access functions -----------------------------------------------------------

// isEmpty()
// Returns true if List is empty, otherwise returns false.
bool List::isEmpty(){
   if(size() == 0){
       return true;
   }
   else{
       return false;
   }
}

// size()
// Returns the size of this List.
int List::size(){
    return(num_elements);
}

// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position(){
    return(pos_cursor);
}

// Manipulation procedures ----------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    if(size() == 0){

        beforeCursor = frontDummy;
        afterCursor =  backDummy;
        pos_cursor = 0;
    }
    else{
        beforeCursor = frontDummy;
        afterCursor = frontDummy->next;
        pos_cursor = 0;
    }
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack(){
    if(size() == 0){


        beforeCursor = frontDummy;
        afterCursor =  backDummy;
        pos_cursor = 0;
    }
    else{
        beforeCursor = backDummy->prev;
        afterCursor = backDummy;
        pos_cursor = size();
    }
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext(){
    if(position()>=size()){
        cerr << "List Error: calling PeekNext() at the end of a List" << endl;
        exit(EXIT_FAILURE);
    }
    return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev(){
    if( position()<=0){
        cerr << "List Error: calling PeekPrev() at the start of a List" << endl;
        exit(EXIT_FAILURE);
    }
    return(beforeCursor->data);
}  

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<size() 
int List::moveNext(){
    if(position()>=size()){
        cerr << "List Error: calling moveNext() at the end of a List" << endl;
        exit(EXIT_FAILURE);
    }
    
    afterCursor = afterCursor->next;
    beforeCursor = afterCursor->prev;
    pos_cursor++;
    return(beforeCursor->data);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
int List::movePrev(){
    if( position()<=0){
        cerr << "List Error: calling movePrev() at the start of a List" << endl;
        exit(EXIT_FAILURE);
    }
    beforeCursor = beforeCursor->prev;
    afterCursor = beforeCursor->next;
    pos_cursor--;
    return(afterCursor->data);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(int x){
    // create a new node
    Node* N = new Node(x);

    // node is inserted between before cursor and after cursor
    N->prev = beforeCursor;
    beforeCursor->next = N;
    N->next = afterCursor;
    afterCursor->prev = N;
    
    // cursor is before the new element, aka aftercursor points to the new node
    afterCursor = N;
    
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(int x){
    // create a new node
    Node* N = new Node(x);

    // node is inserted between before cursor and after cursor
    N->prev = beforeCursor;
    beforeCursor->next = N;
    N->next = afterCursor;
    afterCursor->prev = N;
    
    
    
    //beforeCursor points at new node
    beforeCursor = N;
    
    num_elements++;
    pos_cursor++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter(){

	if(position() < size()){

	  Node* N = afterCursor;
	  beforeCursor->next =afterCursor->next;
	  N->next->prev = beforeCursor;
	  afterCursor = N->next;

	delete N;

 	num_elements--;
	}
	else{

	cerr << "List Error: pre condition failed eraseAfter() "<<endl;
	exit(EXIT_FAILURE);
	}    
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if( position()<=0){
        cerr << "List Error: calling eraseBefore() at the start of a List" << endl;
        exit(EXIT_FAILURE);
    }

    // disconnect the node before Cursor
    Node* temp = beforeCursor;

    beforeCursor = beforeCursor->prev;
    afterCursor->prev= beforeCursor;
    beforeCursor->next = afterCursor;

    temp->next = nullptr;
    temp->prev = nullptr;

    // delete the node pointed by beforeCursor
    delete temp;

    pos_cursor--;

    num_elements--;

    
}

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so 
// eraseBefore() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1. 
int List::findNext(int x){
     
    Node* N;

    if(position() == size()){
	return(-1);
	}

    N = afterCursor;
    

    beforeCursor = afterCursor;
    afterCursor = beforeCursor->next;
    pos_cursor++;

    while(pos_cursor < num_elements){
        if(N->data == x){
            return(pos_cursor);
        }

        N = N->next;
        beforeCursor = N;
        afterCursor = N->next;
        pos_cursor++;
    }
    if(afterCursor == backDummy && beforeCursor->data == x){
        return(pos_cursor);
    }

    // if x not found 
   
    afterCursor = backDummy;
    pos_cursor = size();
    beforeCursor = backDummy->prev;
  
    return(-1);

}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so 
// eraseAfter() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position 0, and 
// returns -1. 
int List::findPrev(int x){

    Node* N = nullptr;
    
    if(position() == 0){
	return(-1);
	}

    N = beforeCursor;

    pos_cursor--;

    while(N != frontDummy){
        if(N->data == x){
            beforeCursor = N->prev;
            afterCursor = N;
            return(pos_cursor);
        }
        N = N->prev;
        pos_cursor --;
    }

    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;

    return(-1);
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other 
// occurances. The cursor is not moved with respect to the retained 
// elements, i.e. it lies between the same two retained elements that it 
// did before cleanup() was called.
void List::cleanup(){
    
    Node* local_cursor;
    Node* refrance;

    local_cursor = frontDummy->next;

    refrance = frontDummy->next;
    

    local_cursor = refrance->next;
    
    int local_pos = 1;

    int ctr = 1;
    while(refrance != backDummy){
        while(local_cursor != backDummy){

            if(local_cursor->data == refrance->data){
                

                if(local_cursor == afterCursor){
                    afterCursor = afterCursor->next;
                    beforeCursor->next = afterCursor;
                    afterCursor->prev = beforeCursor;
                    
                    Node* del = local_cursor;
                    local_cursor = local_cursor->next;
                    

                    del->next = nullptr;
                    del->prev = nullptr;

                    delete del;

                    num_elements --;

                    continue;
                }
                else if( local_cursor == beforeCursor){

                    beforeCursor = beforeCursor->prev;
                    afterCursor->prev = beforeCursor;
                    beforeCursor->next = afterCursor;

                    Node* del = local_cursor;
                    local_cursor = local_cursor->next;
                    

                    del->next = nullptr;
                    del->prev = nullptr;

                    delete del;

                    num_elements--;
                    pos_cursor--;

                    continue;
                }

                else{

                    if(local_pos >= pos_cursor){

                        Node* del = local_cursor;

                        local_cursor->prev->next = local_cursor->next;
                        local_cursor->next->prev = local_cursor->prev;
                        local_cursor = local_cursor->next;

                        del->next = nullptr;
                        del->prev = nullptr;

                        delete del;
                        num_elements--;

                        continue;
                    }
                    else{
                        Node* del = local_cursor;

                        local_cursor->prev->next = local_cursor->next;
                        local_cursor->next->prev = local_cursor->prev;
                        local_cursor = local_cursor->next;

                        del->next = nullptr;
                        del->prev = nullptr;

                        delete del;

                        num_elements--;
                        pos_cursor--;

                        continue;
                    }

                }
            }

            local_cursor = local_cursor->next;
            local_pos ++;

        }

                
        refrance = refrance->next;
        if(refrance == backDummy){
            break;
        }
        local_cursor = refrance->next;
        local_pos = ctr +1;
        ctr++;
    }
    

}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    
    moveFront();
    while(size()>0){
        eraseAfter();
    }
    
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L){
    List ret_list;
    
    Node* N = this->frontDummy->next;
    Node* M = L.frontDummy->next;

   
	while(N != this->backDummy){
        ret_list.insertBefore(N->data);
        N = N->next;
    }

    while(M != L.backDummy){
        ret_list.insertBefore(M->data);
        M = M->next;
    }
    
    ret_list.beforeCursor = ret_list.frontDummy;
    ret_list.afterCursor = ret_list.frontDummy->next;
    ret_list.pos_cursor = 0;

    return(ret_list);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
   std::string List::to_string(){
            Node* N = nullptr;
            string s = "";
            for(N = frontDummy->next; N != backDummy; N = N->next){
                s += std::to_string(N->data)+" ";
            }
            return s;
   }

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R){
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = (this->num_elements == R.num_elements);
    N = this->frontDummy->next;
    M = R.frontDummy->next;

    while(eq && N != this->backDummy){
        eq= (N->data == M->data);
        N = N->next;
        M= M->next;
    }
    return(eq);

}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged are unchanged.
bool operator==( List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if( this != &L ){ // not self assignment
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this

      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(pos_cursor, temp.pos_cursor);

   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}


