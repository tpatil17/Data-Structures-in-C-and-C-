#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include "Dictionary.h"


//-------- Structs --------------------------------------------
typedef struct NodeObj{
    KEY_TYPE key;
    VAL_TYPE val;
    struct NodeObj* left;
    struct NodeObj* right;
    struct NodeObj* parent;
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
    Dictionary D = malloc(sizeof(DictionaryObj));
    D->unique = unique;
    Node NIL = malloc(sizeof(NodeObj));
    NIL->parent = NULL;
    NIL->key = -1;
    NIL->val = -1;
    NIL->right = NULL;
    NIL->left = NULL;
    D->NIL= NIL;
    D->current = NULL;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
    makeNull(*pD);
    free(*pD->NIL);
    free(*pD);
    pD = NULL;
}
//---------------------- BST felper functions----------------------------------

void InOrderTreeWalk(Dictionary D, Node x, FILE* out){

    if(x != D->NIL){
        if(x->left != D->NIL){
            InOrderTreeWalk(D, x->left, out);
        }
        fprintf(out, "%s %d\n", x->key, x->val);
        if(x->right != D->NIL){
            InOrderTreeWalk(D, x->right, out);
        }
    }

}

void PreOrderTreeWalk(Dictionary D, Node x, FILE* out){

    if(x != D->NIL){
        fprintf(out,"%s %d\n", x->key, x->val);
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
        fprintf(out ,"%s %d\n", x->key, x->val);
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
if(x != D->NIL){
    if(x->right != D->NIL){
        TreeMinimum(D ,x->right);
    }
    Node y = x->parent;
    while( y != D->NIL && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}
}
Node TreePredecessor(Dictionary D, Node x){
    if(x != D->NIL){
        if(x->left != D->NIL){
            TreeMaximum(D, x->left);
        }
        Node y = x->parent;
        while(y != D-> NIL && x == y->left){
            x = y;
            y = y->parent;
        }
        return y;
    }
}

// manupulation helper function BST-----------------

void Transplant(Dictionary D,Node u,Node v){
    if(u->parent == D->NIL){
         D->Root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    if(v != D->NIL){
        v->parent = u->parent;
    }
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
    if(D->unique != 0){
        return true;
    }
    return false;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
    Node temp = D->Root;
    if(D->size <= 0 ){
        return VAL_UNDEF;
    }
    else{
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
    }
}

// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
    if(getUnique(D) == 0){
        Node N = malloc(sizeof(NodeObj));
            N->key = k;
            N->val = v;
            N->parent = D->NIL;
            N->right = D->NIL;
            N->left = D->NIL;
        if(D->size == 0){
            D->Root = N;
            D->size++;
        }
        else{
            Node temp = D->Root;
            int i = 1;
            while(i ==1){
                if(KEY_CMP( k, temp->key) > 0){
                    if(temp->right == D->NIL){
                        N->parent = temp;
                        temp->right = N;
                        D->size++;
                        break;
                    }
                    temp = temp->right;
                }
                else if(KEY_CMP(k, temp->key) < 0){
                    if(temp->left == D->NIL){
                        N->parent = temp;
                        temp->left = N;
                        D->size++;
                        break;
                    }
                    temp = temp->left
                }
            }

        }

    }   
    
    else{
        if(lookup(D, k) != VAL_UNDEF){
            
            printf("Pre condition for uniqe insert failed\n");
            exit(EXIT_FAILURE);
        }
        Node N = malloc(sizeof(NodeObj));
        N->key = k;
        N->val = v;
        N->parent = D->NIL;
        N->right = D->NIL;
        N->left = D->NIL;
        if(D->size == 0){
        D->Root = N;
        D->size++;
        
        
            Node temp = D->Root;
            int i = 1;
            while(i == 1){
                if(KEY_CMP(k, temp->key) > 0){
                    if(temp->right == D->NIL){
                        N->parent = temp;
                        temp->right = N;
                        D->size++;
                        break;
                    }
                    temp = temp->right;
                }
                else{
                    
                    if(temp->left == D->NIL){
                        N->parent = temp;
                        temp->left = N;
                        D->size ++;
                        break;
                    }
                    temp = temp->left
                
                }
            }

        
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

    if(z->left == D->NIL){
        Node del = z;
        Transplant(D,z, z->right);
        del->parent = NULL;
        del->right = del->left = NULL;
        free(del);
        D->size--;
    }
    else if(z->right == D->NIL){
        Node del = z;
        Transplant(D, z, z->left);
        del->parent = del->right = del->left = NULL;
        free(del);
        D->size--;
    }
    else{
        Node y = TreeMinimum(D, z->right);
        if(y->parent != z){
            Transplant(D,y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(D , z, y);
        y->left = z->left;
        y->left->parent = y;
        z->parent = z->left = z->right = NULL;
        free(z);
        D->size--;
    }
            
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
    while(D->size > 0){
        Node N = TreeMinimum(D, D->Root);
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
    return D->current->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
    return D->current->val;
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
    Node min = TreeMinimum(D, D->Root);
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
    Node max = TreeMaximum(D, D->Root);
    Node min = TreeMinimum(D, D->Root);
    if(D->current == min){
        D->current = NULL;
        return VAL_UNDEF;
    }
    D->current = TreePredecessor(D ,D->current);
    return D->current->val;
}

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D){
    InOrderTreeWalk(D, D->Root, out);
}



