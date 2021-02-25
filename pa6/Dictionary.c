#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include "Dictionary.h"
#define RED 1
#define BLACK 0


//-------- Structs --------------------------------------------
typedef struct NodeObj{
    KEY_TYPE key;
    VAL_TYPE val;
    struct NodeObj* left;
    struct NodeObj* right;
    struct NodeObj* parent;
    int color;
}NodeObj;

// --- Private Node type ----------
typedef struct NodeObj* Node;

// --- Private DictionaryObj type ----

typedef struct DictionaryObj{
    int unique;
    int size ;
    Node Root;
    Node NIL;
    Node current;
}DictionaryObj;

// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary 
// will accept duplicate keys, i.e. distinct pairs with identical keys. If 
// unique==true (1 or any non-zero value), then duplicate keys will not be 
// accepted. In this case, the operation insert(D, k) will enforce the 
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique){
    Dictionary D = calloc(1,sizeof(DictionaryObj));
    D->unique = unique;
    Node NIL = calloc(1,sizeof(NodeObj));
    NIL->parent = NULL;
    NIL->key = "u";
    NIL->val = NULL;
    NIL->right = NULL;
    NIL->left = NULL;
    NIL->color = BLACK;
    D->NIL= NIL;
    D->current = NULL;
    D->Root = D->NIL;
    return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
    makeEmpty(*pD);
    Dictionary D = *pD;
    free(D->NIL);
    free(*pD);
    pD = NULL;
}

// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D){
    return D->size;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D){
   
    return D->unique;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
    
    if(D->size <= 0 ){
        return VAL_UNDEF;
    }
    else{

 Node temp = NULL;
 
temp = D->Root;

        int i = 1;
        while(i == 1){
            if(KEY_CMP(temp->key, k) == 0){
                return temp->val;
            }
            else if(KEY_CMP(k ,temp->key) < 0){
                if(temp->left == D->NIL){
                    return VAL_UNDEF;
                }
                else{
                    temp = temp->left;
                }
            }
            else if(KEY_CMP(k ,temp->key) > 0){
                if(temp->right == D->NIL){
                    return VAL_UNDEF;
                }
                else{
                    temp = temp->right;
                }
            }
        }
        return VAL_UNDEF;
    }
}

// -------------- RBT Helper functions ---------------------------------------

void InOrderTreeWalk(Dictionary D, Node x, FILE* out){

    if(x != D->NIL){
        if(x->left != D->NIL){
            InOrderTreeWalk(D, x->left, out);
        }
        fprintf(out, "%s\n", x->key);
        if(x->right != D->NIL){
            InOrderTreeWalk(D, x->right, out);
        }
    }

}

void PreOrderTreeWalk(Dictionary D, Node x, FILE* out){

    if(x != D->NIL){
        fprintf(out,"%s\n", x->key);
        if(x->left != D->NIL){
            PreOrderTreeWalk(D,x->left, out);
        }
        if(x->right != D->NIL){
            PreOrderTreeWalk(D, x->right, out);
        }
    }
}

void PostOrderTreeWalk(Dictionary D, Node x, FILE* out){

    if(x != D->NIL){
        if(x->left != D->NIL){
            PostOrderTreeWalk(D, x->left, out);
        }
        if(x->right != D->NIL){
            PostOrderTreeWalk(D, x->right, out);
        }
        fprintf(out ,"%s\n", x->key);
    }
}

Node TreeMinimum(Dictionary D, Node x){
    if(x == D->NIL){
        printf("precondition for Tree minimum faild\n");
        exit(EXIT_FAILURE); 
    }
    while(x->left != D->NIL){
        x = x->left;
    }
    return x;
}

Node TreeMaximum(Dictionary D, Node x){
    if(x == D->NIL){
        printf("precondition for Tree maximum faild\n");
        exit(EXIT_FAILURE); 
    }
    while(x->right != D->NIL){
        x = x->right;
    }
    return x;
}

Node TreeSuccesor(Dictionary D, Node x){

    if(x->right != D->NIL){
        return TreeMinimum(D ,x->right);
    }
    Node y = x->parent;
    while( y != D->NIL && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;

}
Node TreePredecessor(Dictionary D, Node x){
    
        if(x->left != D->NIL){
           return TreeMaximum(D, x->left);
        }
        Node y = x->parent;
        while(y != D-> NIL && x == y->left){
            x = y;
            y = y->parent;
        }
        return y;
    
}

// -- spl RB tree functions -------------------------

void LeftRotate(Dictionary D, Node x){
   if(x != D->NIL){

    Node y = x->right;

    // turn y's left subtree into x's right subtree
   x->right = y->left; 
   if (y->left != D->NIL){     // not necessary if using sentinal nil node
      y->left->parent = x;
    }
   // link y's parent to x
   y->parent = x->parent; 
   if( x->parent == D->NIL){
      D->Root = y;
    }
   else if( x ==  x->parent->left){
      x->parent->left = y;
    }
   else{ 
      x->parent->right = y;
    }
   // put x on y's left
   y->left = x; 
   x->parent = y;
   }
   
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

void RightRotate(Dictionary D, Node x){
   if(x != D->NIL){
    // set y
   Node y = x->left; 
   
   // turn y's right subtree into x's left subtree
   x->left = y->right;

   if(y->right != D->NIL){  // not necessary if using sentinal nil node
      y->right->parent = x;
    }
   // link y's parent to x
   y->parent = x->parent; 
   if (x->parent == D->NIL){
      D->Root = y;
    }
   else if(x == x->parent->right){
      x->parent->right = y;
    }
   else{
      x->parent->left = y;
    }
   
   // put x on y's right
   y->right = x; 
   x->parent = y;
   }
}


//----------------- RB_InsertFixUp()-------------------------------------

void RB_InsertFixUp(Dictionary D,Node z){

    while(z->parent->color == RED){

      if(z->parent == z->parent->parent->left){
         Node y = z->parent->parent->right;
         if(y->color == RED){
            z->parent->color = BLACK;              // case 1
            y->color = BLACK;                      // case 1
            z->parent->parent->color = RED;         // case 1
            z = z->parent->parent;
            }                 // case 1
         else{ 
            if(z == z->parent->right){
               z = z->parent;                     // case 2
               LeftRotate(D, z);                 // case 2
            }
            z->parent->color = BLACK;              // case 3
            z->parent->parent->color = RED;         // case 3
            RightRotate(D, z->parent->parent);     // case 3
        }
      }
      else{ 
         Node y = z->parent->parent->left;
         if(y->color == RED){
            z->parent->color = BLACK;              // case 4
            y->color = BLACK;                     // case 4
            z->parent->parent->color = RED;         // case 4
            z = z->parent->parent;                 // case 4
         }
         else{ 
            if(z == z->parent->left){
               z = z->parent;                     // case 5
               RightRotate(D, z);                // case 5
            }
            z->parent->color = BLACK;              // case 6
            z->parent->parent->color = RED;         // case 6
            LeftRotate(D, z->parent->parent);     // case 6
         }
      }
   }
   D->Root->color = BLACK;
}
//--------------------- RB - Tree insert block ----------------------------

void RB_Insert(Dictionary D, Node z){
   Node y = D->NIL;
   Node x = D->Root;
     
   while( x != D->NIL){
      
      y = x;
      if (KEY_CMP(z->key, x->key) < 0){
         x = x->left;
        }
      else{ 
         x = x->right;
        }
    }
  
   z->parent = y;
   if( y == D->NIL){
      D->Root = z;
    }
   else if( KEY_CMP(z->key , y->key) < 0){
      y->left = z;
    }
   else{
      y->right = z;
    }
   z->left = D->NIL;
   z->right = D->NIL;
   z->color = RED;
   RB_InsertFixUp(D, z);
   D->size++;
}


// insert()
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
    if(getUnique(D) != 0){
       if(lookup(D, k) != VAL_UNDEF){   
            printf("Pre condition for uniqe insert failed\n");
            exit(EXIT_FAILURE);
        } 

    }

    Node x = calloc(1,sizeof(NodeObj));

    x->parent = D->NIL;
    x->color = BLACK;
    x->left = D->NIL;
    x->right = D->NIL;
    x->key = k;
    x->val = v;
	 
   // printf("%s\n", x->key);
    RB_Insert(D, x);
    
}

//--------------- Transplant -------------------------------------------------

void RB_Transplant(Dictionary D, Node u, Node v){
   if(u->parent == D->NIL){
      D->Root = v;
    }
   else if(u == u->parent->left){
  //    printf("clause check\n");
      u->parent->left = v;
//	printf(" after work\n");
    }
   else{
//	printf("uncharted teritory\n");
      u->parent->right = v;
    }
   if(v != D->NIL){
   //printf("still in bad area\n");
   v->parent = u->parent;
   }
//printf("Transplant complete\n");
}


//------------ RB fixup for delete ---------------------------------------

void RB_DeleteFixUp(Dictionary D, Node x){
if(x != D->NIL){
   while(x != D->Root && x->color == BLACK){
      if(x == x->parent->left){
         Node w = x->parent->right;
         if(w->color == RED){
            w->color = BLACK;                        // case 1
            x->parent->color = RED;                   // case 1
            LeftRotate(D, x->parent);                // case 1
            w = x->parent->right;                     // case 1
         }
         if(w->left->color == BLACK && w->right->color == BLACK){
            w->color = RED;                          // case 2
            x = x->parent;                           // case 2
         }
         else{ 
            if(w->right->color == BLACK){
               w->left->color = BLACK;                // case 3
               w->color = RED;                       // case 3
               RightRotate(D, w);                   // case 3
               w = x->parent->right;                  // case 3
            }
            w->color = x->parent->color;               // case 4
            x->parent->color = BLACK;                 // case 4
            w->right->color = BLACK;                  // case 4
            LeftRotate(D, x->parent);                // case 4
            x = D->Root;                             // case 4
         }
        }
      else{
         Node w = x->parent->left;
         if(w->color == RED){
            w->color = BLACK;                        // case 5
            x->parent->color = RED;                   // case 5
            RightRotate(D, x->parent);               // case 5
            w = x->parent->left;                      // case 5
         }
         if(w->right->color == BLACK && w->left->color == BLACK){
            w->color = RED;                          // case 6
            x = x->parent;                           // case 6
          }
         else{ 
            if(w->left->color == BLACK){
               w->right->color = BLACK;               // case 7
               w->color = RED;                       // case 7
               LeftRotate(D, w);                    // case 7
               w = x->parent->left;                   // case 7
            }
            w->color = x->parent->color;               // case 8
            x->parent->color = BLACK;                 // case 8
            w->left->color = BLACK;                   // case 8
            RightRotate(D, x->parent);               // case 8
            x = D->Root;                             // case 8
         }
      }
   }
   x->color = BLACK;
}
}
// ----------------- RB Delete -------------------------------------------------

void RB_Delete(Dictionary D, Node z){
   Node y = z;
   int y_original_color = y->color;
   if(z->left == D->NIL){
//      printf(" nil test passed\n");
      Node x = z->right;
      Node del = z;
      RB_Transplant(D, z, x);
//      printf(" pblm after transplant\n");
      if(y_original_color == BLACK){
         RB_DeleteFixUp(D, x);
      }
          del->parent = NULL;
          del->right = del->left = NULL;
          free(del);
          D->size--;
      
   }
   else if(z->right == D->NIL){
      Node x = z->left;
      Node del = z;
      RB_Transplant(D, z, x);
      if(y_original_color == BLACK){
         RB_DeleteFixUp(D, x);
      }
          del->parent = NULL;
          del->right = del->left = NULL;
          free(del);
          D->size--;
      
   }
   else{
      y = TreeMinimum(D, z->right);
      y_original_color = y->color;
      Node x = y->right;
      if(y->parent == z){
         if(x != D->NIL){
          x->parent = y;
         }
      }
      else{
         RB_Transplant(D, y, y->right);
         y->right = z->right;
         y->right->parent = y;
      }
      Node del = z;
      RB_Transplant(D, z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
      if(y_original_color == BLACK){
         RB_DeleteFixUp(D, x);
      }
          del->parent = NULL;
          del->right = del->left = NULL;
          free(del);
          D->size--;
   }
   
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){

    if(lookup(D,k) == VAL_UNDEF){
       printf(" precondition for delete failed\n");
        exit(EXIT_FAILURE);
    }
    if(D->Root == NULL){
        printf(" empty dictionary\n");
        exit(EXIT_FAILURE);
    }

    Node temp = D->Root;


    int i = 1;
    while(i == 1){
        if(KEY_CMP(k, temp->key) < 0 && temp->left != D->NIL){
            temp =  temp->left;
        }
        else if(KEY_CMP(k ,temp->key) > 0 && temp->right != D->NIL){
            temp = temp->right;
        }
        if(KEY_CMP(k , temp->key) == 0){
            break;
        }

    }
    Node z = temp;  

    if(D->current == z){
        D->current = NULL;
    }
    //printf("%s\n", z->key);
    RB_Delete(D, z);
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){

    D->current = NULL;
    while(D->size > 0){
        Node N = TreeMinimum(D, D->Root);
	//printf("min working\n");
        delete(D, N->key);
    }

}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Dictionary D){
    if(D->size == 0){
        return VAL_UNDEF;
    }
    Node min = TreeMinimum(D, D->Root);

    D->current = min;

    return min->val;
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
    if(D->size == 0){
        return VAL_UNDEF;
    }
    Node max = TreeMaximum(D, D->Root);

    D->current = max;

    return max->val;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the 
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
   if(D->current != NULL){    
        return D->current->key;
   }
   return KEY_UNDEF; 
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
 
    if(D->current != NULL){
       return D->current->val;
   }
   return VAL_UNDEF;
}
// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D){
    if(D->current == NULL){
        return VAL_UNDEF;
    }
    Node max = TreeMaximum(D, D->Root);
    
    if(D->current == max){
        D->current = NULL;
        return VAL_UNDEF;
    }
    D->current = TreeSuccesor(D ,D->current);
    return D->current->val;
    
}

// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF. 
VAL_TYPE prev(Dictionary D){
    if(D->current == NULL){
        return VAL_UNDEF;
    }
    
    Node min = TreeMinimum(D, D->Root);
    if(D->current == min){
        D->current = NULL;
        return VAL_UNDEF;
    }
    D->current = TreePredecessor(D ,D->current);
    return D->current->val;
}

// Other operations -----------------------------------------------------------

// printDictionary()
// Prints the keys (only) of D in an order determined by the parameter ord.
// If ord is "pre", "in" or "post", executes the corresponding tree traversal
// on the underlying RBT, printing keys only (no values).  If ord is some
// other string, prints nothing.
void printDictionary(FILE* out, Dictionary D, const char* ord){
   if(KEY_CMP(ord, "pre") == 0){
      PreOrderTreeWalk(D, D->Root, out);
   }
   else if(KEY_CMP(ord, "in") == 0){
      InOrderTreeWalk(D, D->Root, out);
   }
   else if(KEY_CMP(ord, "post") == 0){
      PostOrderTreeWalk(D, D->Root, out);
   }
}
