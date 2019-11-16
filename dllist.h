#ifndef DLLIST_H
#define DLLIST_H

#include <zconf.h>

typedef struct dllist dllist;

// Creates a new list
dllist* list_new(size_t type_size);

// Gets the length of a list
int list_length(dllist* list);

// Adds an item to the end of the list
void list_append(dllist* list, void* item);

// Gets an item in the list at a given index
void* list_get(dllist* list, int index);

// Adds an item to the list at a given index
void list_insert(dllist *list, void *item, int index);

// Applies a procedure on each element of the list
void list_foreach(dllist *list, void (*func)(void*));

// Removes an item in the list at a given index
void list_remove(dllist* list, int index);

// Deletes the list and frees all allocated memory
void list_delete(dllist* list);

#endif