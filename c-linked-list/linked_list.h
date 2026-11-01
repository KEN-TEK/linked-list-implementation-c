#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

/*
 * Singly linked list of ints.
 *
 * Conventions used by every function:
 *  - An empty list is represented by a NULL head pointer.
 *  - Functions that can change which node is first take a Node ** (pointer to
 *    the head pointer), so the caller's head is updated automatically.
 *  - Functions that can fail return 0 on success and -1 on failure.
 *  - Positions are 0-based.
 */

typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* Creation and insertion */
Node  *ll_create_node(int value);
int    ll_push_front(Node **head, int value);
int    ll_push_back(Node **head, int value);
int    ll_insert_at(Node **head, int value, size_t position);

/* Deletion */
int    ll_delete_value(Node **head, int value);   /* first match; -1 if absent  */
size_t ll_delete_all(Node **head, int value);     /* returns how many removed   */

/* Queries */
int    ll_find(const Node *head, int value);      /* index, or -1 if not found  */
size_t ll_length(const Node *head);
int    ll_has_cycle(const Node *head);            /* Floyd's tortoise and hare  */

/* Transformations */
void   ll_reverse(Node **head);
void   ll_remove_duplicates(Node *head);          /* any order, O(n^2)          */
void   ll_remove_adjacent_duplicates(Node *head); /* sorted list only, O(n)     */
Node  *ll_merge_sorted(Node *a, Node *b);         /* relinks nodes, no copying  */

/* Output and cleanup */
void   ll_print(const Node *head);
void   ll_free(Node **head);                      /* list must not contain a cycle */

#endif
