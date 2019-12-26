/*
 * This file contains the definition of the interface for a dynamic array.
 * You can find descriptions of the dynamic array functions, including their
 * parameters and their return values, in dynarray.c.
 */

#ifndef __DYNARRAY_H
#define __DYNARRAY_H

/*
 * Structure used to represent a dynamic array.
 */
struct dynarray;

/*
 * Dynamic array interface function prototypes.  Refer to dynarray.c for
 * documentation about each of these functions.
 */
 int get_logical(struct dynarray* array);
 void increment_logical(struct dynarray* array);
 void decrement_size(struct dynarray* array);
 void edge_case(struct dynarray* array, void* val);
 void* get_value(struct dynarray* array, int idx);
void insert(struct dynarray* array, int idx, void* val);
 int get_capacity(struct dynarray* array);
 void increment_size(struct dynarray* array);
struct dynarray* dynarray_create();
void dynarray_free(struct dynarray* da);
int dynarray_size(struct dynarray* da);
void dynarray_insert(struct dynarray* da, void* val);
void dynarray_remove(struct dynarray* da, int idx);
void* dynarray_get(struct dynarray* da, int idx);
void dynarray_set(struct dynarray* da, int idx, void* val);

#endif
