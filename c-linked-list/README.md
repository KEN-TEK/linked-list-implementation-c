# Singly Linked List in C

A small, tested linked-list library for integers, with a demo program and a
test suite. It is written in standard C11 and compiles without warnings under
`-Wall -Wextra -Wpedantic`. It has been checked with AddressSanitizer and
UndefinedBehaviorSanitizer: no leaks and no memory errors.

## What it demonstrates

| Concept | Where |
|---|---|
| Dynamic memory (`malloc` checked, every node `free`d) | `ll_create_node`, `ll_free` |
| Pointer-to-pointer (`Node **`) so functions can change the caller's head | `ll_push_front`, `ll_delete_value`, `ll_reverse` |
| Handling every edge case: empty list, head, middle, tail, not found | `ll_delete_value`, `ll_insert_at` |
| Iterative reversal by flipping links | `ll_reverse` |
| Cycle detection with Floyd's tortoise and hare, O(1) memory | `ll_has_cycle` |
| Merging two sorted lists with a dummy node, relinking without copying | `ll_merge_sorted` |
| Header / implementation split with a clear API contract | `linked_list.h`, `linked_list.c` |
| Automated tests with `assert` and a Makefile | `tests.c`, `Makefile` |

## API

| Function | Purpose |
|---|---|
| `ll_push_front`, `ll_push_back`, `ll_insert_at` | Insert (0-based position) |
| `ll_delete_value`, `ll_delete_all` | Delete first match / all matches |
| `ll_find`, `ll_length`, `ll_has_cycle` | Queries |
| `ll_reverse` | Reverse in place |
| `ll_remove_duplicates` | Remove duplicates in any order, O(n^2) |
| `ll_remove_adjacent_duplicates` | Remove duplicates in a sorted list, O(n) |
| `ll_merge_sorted` | Merge two sorted lists |
| `ll_print`, `ll_free` | Output and cleanup |

Conventions: an empty list is a `NULL` head. Functions that can fail return
`0` on success and `-1` on failure.

## Build and run

```bash
make          # builds ./demo and ./tests
make run      # runs the demo
make test     # runs the tests
make clean
```

Requires `gcc` (or any C11 compiler) and `make`.

## Design notes

- **Why `Node **head`?** Inserting at the front or deleting the first node changes
  which node is the head. Passing the address of the head pointer lets the function
  update it, so callers never need to write `head = ...`.
- **Why two duplicate removers?** The adjacent version is O(n) but only correct on a
  sorted list. The general version works on any list at the cost of O(n^2).
- **Cycles:** `ll_free` loops until `NULL`, so a list with a cycle must be broken
  before freeing. The tests and the demo do exactly that.

## Possible next steps

- Store generic data with `void *`.
- Keep a tail pointer to make `ll_push_back` O(1).
- Convert to a doubly linked list.
