/*
 * This file contains the definition of the interface for a linked list.  You
 * can find descriptions of the linked list functions, including their
 * parameters and their return values, in list.c.
 */

#ifndef __LIST_H
#define __LIST_H

/*
 * Structure used to represent a singly-linked list.
 */
struct list;
//struct link;
/*
 * Linked list interface function prototypes.  Refer to list.c for
 * documentation about each of these functions.
 */
struct list* list_create();
struct link* get_head(struct list* list);
void* get_val(struct list* list);
int compare(void* a, void* b);
void* return_head(struct list* list, void* temp);
void list_free(struct list* list);
void list_insert(struct list* list, void* val);
void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b));
int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b));
void list_reverse(struct list* list);

#endif
