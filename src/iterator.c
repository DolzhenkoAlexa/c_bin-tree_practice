#include "bst.h"
#include <stdlib.h>
#include <stdio.h>
#define INITIAL_STACK_SIZE 32

Iterator* makeIterator(BST* tree) {
    if (tree == NULL) {
        return NULL;
    }

    Iterator* it = (Iterator*)malloc(sizeof(Iterator));
    if (it == NULL) {
        return NULL;
    }

    // Динамическое расшширение стэка
    it->buffer = INITIAL_STACK_SIZE;
    it->stack = (Node**)malloc(sizeof(Node*) * it->buffer);
    if (it->stack == NULL) {
        free(it);
        return NULL;
    }
    it->top = -1;

    Node* current = tree->root;
    while (current != NULL) {
        // Расширяем
        if (it->top + 1 >= it->buffer) {
            it->buffer *= 2;
            it->stack = (Node**)realloc(it->stack, sizeof(Node*) * it->buffer);
            if (it->stack == NULL) {
                free(it);
                return NULL;
            }
        }
        it->stack[++it->top] = current;
        current = current->left;
    }
    return it;
}

bool iteratorHasNext(Iterator* it) {
    if (it == NULL) return false;
    return it->top >= 0;
}

int iteratorNextElem(Iterator* it) {
    if (!iteratorHasNext(it)) {
        fprintf(stderr, "Error: no next element\n");
        return -1;
    }

    Node* node = it->stack[it->top--];
    int result = node->data;

    Node* current = node->right;
    while (current != NULL) {
        if (it->top + 1 >= it->buffer) {
            it->buffer *= 2;
            it->stack = (Node**)realloc(it->stack, sizeof(Node*) * it->buffer);
            if (it->stack == NULL) {
                return result;
            }
        }
        it->stack[++it->top] = current;
        current = current->left;
    }
    return result;
}

void iteratorFree(Iterator* it) {
    if (it != NULL) {
        if (it->stack != NULL) {
            free(it->stack);
        }
        free(it);
    }
}
