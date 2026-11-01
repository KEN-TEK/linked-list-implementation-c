#include <stdio.h>

#include "linked_list.h"

int main(void) {
    Node *list = NULL;

    printf("--- Building the list ---\n");
    ll_push_front(&list, 20);
    ll_push_front(&list, 10);
    ll_push_back(&list, 20);
    ll_push_back(&list, 30);
    ll_push_back(&list, 40);
    ll_print(list);                                  /* 10 20 20 30 40 */

    printf("\n--- Search and length ---\n");
    printf("length      : %zu\n", ll_length(list));
    printf("index of 30 : %d\n", ll_find(list, 30));
    printf("index of 99 : %d\n", ll_find(list, 99));

    printf("\n--- Insert at position 2 ---\n");
    ll_insert_at(&list, 15, 2);
    ll_print(list);

    printf("\n--- Remove duplicates ---\n");
    ll_remove_duplicates(list);
    ll_print(list);

    printf("\n--- Delete 40 (last) and 10 (head) ---\n");
    ll_delete_value(&list, 40);
    ll_delete_value(&list, 10);
    ll_print(list);

    printf("\n--- Reverse ---\n");
    ll_reverse(&list);
    ll_print(list);

    printf("\n--- Merge two sorted lists ---\n");
    Node *a = NULL, *b = NULL;
    ll_push_back(&a, 1); ll_push_back(&a, 4); ll_push_back(&a, 9);
    ll_push_back(&b, 2); ll_push_back(&b, 3); ll_push_back(&b, 10);
    Node *merged = ll_merge_sorted(a, b);            /* a and b nodes now live in merged */
    ll_print(merged);

    printf("\n--- Cycle detection ---\n");
    printf("cycle in list?   %d\n", ll_has_cycle(list));
    Node *last = list;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = list;                               /* create a cycle on purpose */
    printf("after linking tail to head: %d\n", ll_has_cycle(list));
    last->next = NULL;                               /* break it again before freeing */

    ll_free(&list);
    ll_free(&merged);
    return 0;
}
