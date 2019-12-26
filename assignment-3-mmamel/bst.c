/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>

#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */

struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

int recursive_size(struct bst_node* node){
  if(node == NULL){
    return 0;
  }
  else{
    return 1+recursive_size(node->left)+recursive_size(node->right);
  }
}
void recursive_free(struct bst_node* node){
  if(node->left == NULL && node->right == NULL){
    free(node);
  }
  else{
    if(node->left != NULL){
       recursive_free(node->left);
    }
    if(node->right != NULL){
       recursive_free(node->right);
    }
    free(node);
  }
}

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  struct bst* pointer = malloc(sizeof(struct bst));
  pointer->root = NULL;
  return pointer;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  recursive_free(bst->root);
  free(bst);
  return;
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  return recursive_size(bst->root);
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
  int loop = 1;
  struct bst_node* iter;
  struct bst_node* temp = malloc(sizeof(struct bst_node));
  temp->key = key;
  temp->value = value;
  temp->right = NULL;
  temp->left = NULL;
  if(bst->root == NULL){
    bst->root = temp;
  }
  else{
    iter = bst->root;
    while(loop == 1){
    if(temp->key < iter->key){
      if(iter->left == NULL){
        iter->left = temp;
        loop = 0;
      }
      else{
        iter = iter->left;
      }
    }
    else if(temp->key >= iter->key){
      if(iter->right==NULL){
        loop = 0;
        iter->right = temp;
      }
      else{
        iter = iter->right;
      }
    }
  }
  }
  return;
}
struct bst_node* in_order_suc(struct bst_node* node){
  struct bst_node* parent;
  if(node->right==NULL){
    if(node->left==NULL){
      return NULL;
    }
    else if(node->left!=NULL){
      return node->left;
    }
  }
  else{
    node=node->right;
    parent=node;
    if(node->left!=NULL){
      node=node->left;
    }
    while(node->left!=NULL){
      parent=parent->left;
      node=node->left;
    }
    if(node->right!=NULL){
      parent->left = node->right;
    }
    else{
      parent->left = NULL;
    }
    return node;
  }
}
/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  int loop = 1;
  //0 is left 1 is right;
  int direction = 0;
  struct bst_node* successor;
  struct bst_node* iter;
  iter = bst->root;
  struct bst_node* back;
  back = bst->root;
  //edge case for deleting root
  if(bst->root->key==key){
    loop = 0;
    successor = in_order_suc(bst->root);
  //  printf("this is successor ley %d", successor->key);
    if(bst->root->right!=successor){
      successor->right=bst->root->right;
    }
    successor->left = bst->root->left;
    //printf("this is successor right %d", successor->right->left->key);
    free(bst->root);
    bst->root = successor;




    //printf("this is successor left %d", successor->left->key);
  //  printf("this is root  %d", bst->root->key);

   }
  while(loop == 1){
    // printf("this is iter key %d", iter->key);
    if(iter->key==key){
      successor = in_order_suc(iter);
      if(direction == 0){
        if(successor == NULL){
          free(iter);
          back->left = NULL;
        }
        else{
          back->left=successor;
          successor->left = iter->left;
          if(iter->right != successor){
            successor->right = iter->right;
          }
          successor->left = iter->left;
          free(iter);
        }
        loop=0;
      }
      else if(direction == 1){
        if(successor==NULL){
          free(iter);
          back->right = NULL;


        }
        else{
          back->right = successor;
          successor->left = iter->left;
          if(iter->right != successor){
            successor->right = iter->right;
          }
          free(iter);
        }
        loop=0;
      }
    }
    else if(key < iter->key){
      back = iter;
      iter = iter->left;
      direction = 0;
    }
    else if(key >= iter->key){
      back=iter;
      iter = iter->right;
      direction = 1;
    }
   }
  return;
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  int loop = 1;
  struct bst_node* temp;
  //printf("this is root %d", bst->root->key);
  temp = bst->root;
  //printf("this is temp %d", temp->key);

  while(loop == 1){
    if(key == temp->key){
      return temp->value;
    }
    else if(key < temp->key){
      if(temp->left == NULL){
        return NULL;
      }
      else{
        temp = temp->left;
        //printf("LOOK AT ME %d", temp->key);

      }
    }
    else if(key >= temp->key){
      if(temp->right== NULL){
        //printf("found 56");
        return NULL;
      }
      else{
        temp = temp->right;
        //if(temp == NULL){

      //  }
      }
      }
  }
}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
  return NULL;
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  return;
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  return 0;
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
  if (value) {
    *value = NULL;
  }
  return 0;
}
