#include "dllist.h"
#include <stdio.h>

void print_int(void* num){
    printf("%i\t", *(int*)num);
}

void increment(void* num){
    ++*(int*)num;
}

int main() {
    int num[5] = {1, 2, 3, 4, 5};

    dllist *my_list = list_new(sizeof(int));
    list_insert(my_list, num, 0);
    list_append(my_list, num+1);
    list_insert(my_list, num + 2, 1);
    list_append(my_list, num+3);
    list_insert(my_list, num + 4, 4);

    printf("my_list length: %i\n", list_length(my_list));
    printf("my_list: %i, %i, %i, %i, %i\n",
            *(int*)list_get(my_list, 0),
            *(int*)list_get(my_list, 1),
            *(int*)list_get(my_list, 2),
            *(int*)list_get(my_list, 3),
            *(int*)list_get(my_list, 4));

    list_foreach(my_list, print_int);
    list_foreach(my_list, increment);
    printf("\n");
    list_foreach(my_list, print_int);
    list_remove(my_list, 0);
    printf("\n");
    list_foreach(my_list, print_int);
    list_remove(my_list, 3);
    printf("\n");
    list_foreach(my_list, print_int);
    list_remove(my_list, 1);
    printf("\n");
    list_foreach(my_list, print_int);

    list_delete(my_list);

    return 0;
}