/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Melvin Ma
 * Email: mamel@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
  struct dynarray* priority_heap;
  struct dynarray* value_heap;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* priority = malloc(sizeof(struct pq));
  priority->priority_heap = dynarray_create();
  priority->value_heap = dynarray_create();
  return priority;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  dynarray_free(pq->priority_heap);
  dynarray_free(pq->value_heap);
  free(pq);
  return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  int size = dynarray_size(pq->priority_heap);
  if(size == 0){
    return 1;
  }
  else{
    return 0;
  }
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  int size = dynarray_size(pq->priority_heap);
  //printf("size: %d value: %d priority %d \n", size, value, priority);
  dynarray_insert(pq->value_heap, value);
  dynarray_insert(pq->priority_heap, priority);
  if(size !=0){
    int test = 1;
    int parent_index = (size-1)/2;
    int child_index = size;
    while(test ==1){
      int child = dynarray_get(pq->priority_heap, child_index);
      int parent = dynarray_get(pq->priority_heap, parent_index);
      if(parent <= child){
        test = 0;
      }
      else{
        int priority_temp = dynarray_get(pq->priority_heap, parent_index);
        void* value_temp = dynarray_get(pq->value_heap, parent_index);
        dynarray_set(pq->value_heap, parent_index, dynarray_get(pq->value_heap, child_index));
        dynarray_set(pq->value_heap, child_index, value_temp);
        dynarray_set(pq->priority_heap, parent_index, dynarray_get(pq->priority_heap, child_index));
        dynarray_set(pq->priority_heap, child_index, priority_temp);
        child_index = parent_index;
        parent_index = (parent_index-1)/2;
      }
    }
  }
  return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  return dynarray_get(pq->value_heap, 0);
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  return dynarray_get(pq->priority_heap, 0);
}

void printE(struct pq* pq){
  int size = dynarray_size(pq->priority_heap);
  printf("ELEMENT: ");
  for(int i =0;i<size;i++){
    int element = dynarray_get(pq->priority_heap, i);
    printf("%d ", element);
  }
  printf("\n");
}
/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  int size = dynarray_size(pq->priority_heap);
  void* value = dynarray_get(pq->value_heap, 0);
  dynarray_set(pq->priority_heap, 0, dynarray_get(pq->priority_heap, size-1));
  dynarray_set(pq->value_heap, 0, dynarray_get(pq->value_heap, size-1));
  dynarray_remove(pq->priority_heap, size-1);
  dynarray_remove(pq->value_heap, size-1);
  //percolate
  if(size !=0){
    int test = 1;
    int left_child;
    int right_child;
    int left_child_index;
    int right_child_index;
    int parent_index = 0;
    int minimum_index = parent_index;
    void* value_temp;
    int priority_temp;
    while(test == 1){
      left_child_index = parent_index*2+1;
      right_child_index = parent_index*2+2;
      if(left_child_index < size-1){
        left_child = dynarray_get(pq->priority_heap, left_child_index);
        minimum_index = left_child_index;
      }
      if(right_child_index < size-1){
        right_child = dynarray_get(pq->priority_heap, right_child_index);
        if(right_child < left_child){
          minimum_index = right_child_index;
        }
      }
      if(size-1!=0 && (dynarray_get(pq->priority_heap, parent_index) > dynarray_get(pq->priority_heap, minimum_index))){
        value_temp = dynarray_get(pq->value_heap, parent_index);
        priority_temp = dynarray_get(pq->priority_heap, parent_index);
        dynarray_set(pq->value_heap, parent_index, dynarray_get(pq->value_heap, minimum_index));
        dynarray_set(pq->value_heap, minimum_index, value_temp);
        dynarray_set(pq->priority_heap, parent_index, dynarray_get(pq->priority_heap, minimum_index));
        dynarray_set(pq->priority_heap, minimum_index, priority_temp);
        parent_index = minimum_index;
      }
      else{
        test=0;
        return value;
      }
    }
  }
}
