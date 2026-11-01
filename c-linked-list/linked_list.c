#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

/* ---------- creation and insertion ---------- */

Node *ll_create_node(int value) {
    Node *node = malloc(sizeof *node);
    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->next = NULL;
    return node;
}

int ll_push_front(Node **head, int value) {
    Node *node = ll_create_node(value);
    if (node == NULL) {
        return -1;
    }
    node->next = *head;
    *head = node;
    return 0;
}

int ll_push_back(Node **head, int value) {
    Node *node = ll_create_node(value);
    if (node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = node;
        return 0;
    }
    Node *tail = *head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
    return 0;
}

int ll_insert_at(Node **head, int value, size_t position) {
    if (position == 0) {
        return ll_push_front(head, value);
    }

    /* walk to the node just before the insertion point */
    Node *prev = *head;
    for (size_t i = 1; i < position && prev != NULL; i++) {
        prev = prev->next;
    }
    if (prev == NULL) {
        return -1;                      /* position is beyond the end of the list */
    }

    Node *node = ll_create_node(value);
    if (node == NULL) {
        return -1;
    }
    node->next = prev->next;
    prev->next = node;
    return 0;
}

/* ---------- deletion ---------- */

int ll_delete_value(Node **head, int value) {
    Node *prev = NULL;
    Node *curr = *head;

    while (curr != NULL && curr->data != value) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        return -1;                      /* not found */
    }

    if (prev == NULL) {
        *head = curr->next;             /* deleting the head */
    } else {
        prev->next = curr->next;        /* deleting a middle or last node */
    }
    free(curr);
    return 0;
}

size_t ll_delete_all(Node **head, int value) {
    size_t removed = 0;
    Node **link = head;                 /* points at the pointer we may rewrite */

    while (*link != NULL) {
        if ((*link)->data == value) {
            Node *dead = *link;
            *link = dead->next;
            free(dead);
            removed++;
        } else {
            link = &(*link)->next;
        }
    }
    return removed;
}

/* ---------- queries ---------- */

int ll_find(const Node *head, int value) {
    int index = 0;
    for (const Node *n = head; n != NULL; n = n->next, index++) {
        if (n->data == value) {
            return index;
        }
    }
    return -1;
}

size_t ll_length(const Node *head) {
    size_t count = 0;
    for (const Node *n = head; n != NULL; n = n->next) {
        count++;
    }
    return count;
}

int ll_has_cycle(const Node *head) {
    const Node *slow = head;
    const Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return 1;
        }
    }
    return 0;
}

/* ---------- transformations ---------- */

void ll_reverse(Node **head) {
    Node *prev = NULL;
    Node *curr = *head;

    while (curr != NULL) {
        Node *next = curr->next;        /* remember the rest */
        curr->next = prev;              /* flip the arrow */
        prev = curr;
        curr = next;
    }
    *head = prev;
}

void ll_remove_duplicates(Node *head) {
    for (Node *outer = head; outer != NULL; outer = outer->next) {
        Node *prev = outer;
        while (prev->next != NULL) {
            if (prev->next->data == outer->data) {
                Node *dead = prev->next;
                prev->next = dead->next;
                free(dead);
            } else {
                prev = prev->next;
            }
        }
    }
}

void ll_remove_adjacent_duplicates(Node *head) {
    Node *curr = head;
    while (curr != NULL && curr->next != NULL) {
        if (curr->data == curr->next->data) {
            Node *dead = curr->next;
            curr->next = dead->next;
            free(dead);
        } else {
            curr = curr->next;          /* only advance when nothing was removed */
        }
    }
}

Node *ll_merge_sorted(Node *a, Node *b) {
    Node dummy = {0, NULL};             /* placeholder so we never special-case the first node */
    Node *tail = &dummy;

    while (a != NULL && b != NULL) {
        if (a->data <= b->data) {       /* <= keeps the merge stable */
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = (a != NULL) ? a : b;   /* append whatever is left */
    return dummy.next;
}

/* ---------- output and cleanup ---------- */

void ll_print(const Node *head) {
    for (const Node *n = head; n != NULL; n = n->next) {
        printf("%d -> ", n->data);
    }
    printf("NULL\n");
}

void ll_free(Node **head) {
    Node *curr = *head;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    *head = NULL;
}
