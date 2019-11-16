#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element* element;

struct element{
    element next;
    element prev;
    void* data;
};

struct dllist{
    int length;
    size_t element_size;
    element head;
    element tail;
};


dllist* list_new(size_t element_size){
    dllist* list = malloc(sizeof(struct dllist));

    list->length = 0;
    list->element_size = element_size;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

int list_length(dllist* list){
    return list->length;
}

static element copy_data(void* item, size_t size){
    element new_e = malloc(sizeof(struct element));
    new_e->data = malloc(size);
    memcpy(new_e->data, item, size);

    return new_e;
}

static void error(char text[]){
    printf("=> List ERROR: %s", text);
    fflush(stdout);

}

void list_append(dllist* list, void* item){
    if (!list) {
        error("no list given");
        return;
    }

    element e = copy_data(item, list->element_size);

    // Check if first element
    if (list->head == NULL) {
        e->prev = NULL;
        list->head = e;
    } else {
        list->tail->next = e;
        e->prev = list->tail;
    }

    list->tail = e;
    list->length++;
    e->next = NULL;
}


void* list_get(dllist* list, int index){
    if (!list) {
        error("no list given");
        return NULL;
    }
    else if (index < 0 || index >= list->length) {
        error("index out of bounds");
        return NULL;
    }
    else {
        element e = list->head;
        for (int i = 0; i < index; i++, e = e->next);
        return e->data;
    }
}


void list_insert(dllist *list, void *item, int index){
    if (!list) {
        error("no list given");
    }
    else if (index < 0 || index > list->length) {
        error("index out of bounds");
    }
    else{
        element e = copy_data(item, list->element_size);

        if (list->length == 0) {
            // Adding first item in the list
            list->head = e;
            list->tail = e;
            e->next = NULL;
            e->prev = NULL;
        }
        else {
            // Find the element you want to insert after
            element prev = list->head;
            for (int i = 0; i < index-1; i++, prev = prev->next);

            // Link with the next element
            e->next = prev->next;
            if (prev->next) {
                // element has a next: link
                prev->next->prev = e;
            }
            else {
                // element is the last in the list
                list->tail = e;
            }


            // Link with the previous element
            e->prev = prev;
            prev->next = e;
        }

        list->length++;
    }
}


void list_foreach(dllist *list, void (*func)(void*)){
    for (element e = list->head; e; (*func)(e->data), e = e->next);
}


static void delete(element e){
    free(e);
}


void list_remove(dllist *list, int index){
    if (!list) {
        error("no list given");
    }
    else if (index < 0 || index > list->length) {
        error("index out of bounds");
    }
    else{
        // Find element you want to remove
        element e = list->head;
        for (int i = 0; i < index; i++, e = e->next);

        if (e->prev && e->next){
            // e is in the middle of the list
            e->prev->next = e->next;
            e->next->prev = e->prev;
        }
        else if (e->prev){
            // e is at the end of the list
            e->prev->next = e->next;
            list->tail = e->prev;
        }
        else if (e->next){
            // e is at the beginning of the list
            list->head = e->next;
            e->next->prev = e->prev;
        }
        else {
            // e is the only element in the list
            list->head = NULL;
            list->tail = NULL;
        }

        delete(e);
        list->length--;
    }
}


void list_delete(dllist* list){
    element e = list->tail;

    while (e){
        element marked = e;
        e = marked->prev;
        free(marked);
    }

    free(list);
}