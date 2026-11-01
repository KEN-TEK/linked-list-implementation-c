#include <assert.h>
#include <stdio.h>

#include "linked_list.h"

/* Build a list from an array. */
static Node *from_array(const int *values, size_t n) {
    Node *head = NULL;
    for (size_t i = 0; i < n; i++) {
        assert(ll_push_back(&head, values[i]) == 0);
    }
    return head;
}

/* Check that a list holds exactly the expected values, in order. */
static int equals(const Node *head, const int *expected, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (head == NULL || head->data != expected[i]) {
            return 0;
        }
        head = head->next;
    }
    return head == NULL;
}

#define LEN(a) (sizeof(a) / sizeof((a)[0]))

static void test_push_and_length(void) {
    Node *l = NULL;
    assert(ll_length(l) == 0);
    ll_push_front(&l, 2);
    ll_push_front(&l, 1);
    ll_push_back(&l, 3);
    int exp[] = {1, 2, 3};
    assert(equals(l, exp, LEN(exp)));
    assert(ll_length(l) == 3);
    ll_free(&l);
    assert(l == NULL);
}

static void test_insert_at(void) {
    int init[] = {1, 3};
    Node *l = from_array(init, LEN(init));
    assert(ll_insert_at(&l, 2, 1) == 0);            /* middle */
    assert(ll_insert_at(&l, 0, 0) == 0);            /* front  */
    assert(ll_insert_at(&l, 4, 4) == 0);            /* end    */
    assert(ll_insert_at(&l, 99, 10) == -1);         /* out of range */
    int exp[] = {0, 1, 2, 3, 4};
    assert(equals(l, exp, LEN(exp)));
    ll_free(&l);
}

static void test_delete(void) {
    int init[] = {5, 1, 5, 2, 5};
    Node *l = from_array(init, LEN(init));
    assert(ll_delete_value(&l, 99) == -1);          /* absent */
    assert(ll_delete_value(&l, 5) == 0);            /* head   */
    int exp1[] = {1, 5, 2, 5};
    assert(equals(l, exp1, LEN(exp1)));
    assert(ll_delete_all(&l, 5) == 2);
    int exp2[] = {1, 2};
    assert(equals(l, exp2, LEN(exp2)));
    assert(ll_delete_all(&l, 5) == 0);
    ll_free(&l);

    Node *empty = NULL;
    assert(ll_delete_value(&empty, 1) == -1);       /* empty list must not crash */
}

static void test_find(void) {
    int init[] = {10, 20, 30};
    Node *l = from_array(init, LEN(init));
    assert(ll_find(l, 10) == 0);
    assert(ll_find(l, 30) == 2);
    assert(ll_find(l, 99) == -1);
    ll_free(&l);
}

static void test_reverse(void) {
    Node *empty = NULL;
    ll_reverse(&empty);
    assert(empty == NULL);

    int one[] = {1};
    Node *l1 = from_array(one, LEN(one));
    ll_reverse(&l1);
    assert(equals(l1, one, LEN(one)));
    ll_free(&l1);

    int init[] = {1, 2, 3, 4};
    Node *l = from_array(init, LEN(init));
    ll_reverse(&l);
    int exp[] = {4, 3, 2, 1};
    assert(equals(l, exp, LEN(exp)));
    ll_free(&l);
}

static void test_duplicates(void) {
    int unsorted[] = {3, 1, 3, 2, 1, 3};
    Node *u = from_array(unsorted, LEN(unsorted));
    ll_remove_duplicates(u);
    int expu[] = {3, 1, 2};
    assert(equals(u, expu, LEN(expu)));
    ll_free(&u);

    int sorted[] = {1, 1, 2, 2, 2, 3};
    Node *s = from_array(sorted, LEN(sorted));
    ll_remove_adjacent_duplicates(s);
    int exps[] = {1, 2, 3};
    assert(equals(s, exps, LEN(exps)));
    ll_free(&s);
}

static void test_merge(void) {
    int ai[] = {1, 4, 9};
    int bi[] = {2, 3, 10, 11};
    Node *m = ll_merge_sorted(from_array(ai, LEN(ai)), from_array(bi, LEN(bi)));
    int exp[] = {1, 2, 3, 4, 9, 10, 11};
    assert(equals(m, exp, LEN(exp)));
    ll_free(&m);

    Node *only = ll_merge_sorted(NULL, from_array(ai, LEN(ai)));
    assert(equals(only, ai, LEN(ai)));
    ll_free(&only);

    assert(ll_merge_sorted(NULL, NULL) == NULL);
}

static void test_cycle(void) {
    assert(ll_has_cycle(NULL) == 0);

    int init[] = {1, 2, 3, 4};
    Node *l = from_array(init, LEN(init));
    assert(ll_has_cycle(l) == 0);

    Node *last = l;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = l->next;                            /* 4 points back to 2 */
    assert(ll_has_cycle(l) == 1);

    last->next = NULL;                               /* break the cycle before freeing */
    assert(ll_has_cycle(l) == 0);
    ll_free(&l);
}

int main(void) {
    test_push_and_length();
    test_insert_at();
    test_delete();
    test_find();
    test_reverse();
    test_duplicates();
    test_merge();
    test_cycle();
    printf("All tests passed.\n");
    return 0;
}
