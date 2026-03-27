#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Создание дерева
BST* createBST(void)
{
    BST* newTree = (BST*)malloc(sizeof(BST));
    if (newTree) {
        newTree->root = NULL;
    }
    return newTree;
}

// Служебные функции (статичные, видны только в этом файле)

// Поиск
static bool bstSearch(Node* node, int data)
{
    if (node == NULL)
        return false;
    if (node->data == data)
        return true;
    if (data < node->data)
        return bstSearch(node->left, data);
    else
        return bstSearch(node->right, data);
}

// Создание узла
static Node* createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

// Удаление узла
static void freeNode(Node* node)
{
    if (node == NULL)
        return;
    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

// Функции для пользователя (объявлены в заголовочном файле)

// Проверка существования элемента в дереве
bool bstContains(BST* tree, int data)
{
    if (tree == NULL)
        return false;
    return bstSearch(tree->root, data);
}

// Вставка
void bstInsert(BST* tree, int data)
{
    if (tree == NULL)
        return;

    Node* current = tree->root;
    Node* parent = NULL;
    int goLeft = 0;

    while (current != NULL) {
        if (data == current->data)
            return;
        parent = current;
        if (data < current->data) {
            current = current->left;
            goLeft = 1;
        } else {
            current = current->right;
            goLeft = 0;
        }
    }

    Node* newNode = createNode(data);
    if (parent == NULL) {
        tree->root = newNode;
    } else {
        if (goLeft)
            parent->left = newNode;
        else
            parent->right = newNode;
    }
}

// Удаление дерева
void bstFree(BST* tree)
{
    if (tree == NULL)
        return;
    freeNode(tree->root);
    free(tree);
}

// Печать (для дебаггинга)
void bstPrint(Node* node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    bstPrint(node->left);
    bstPrint(node->right);
}

// Функции для итератора
Iterator* makeIterator(BST* tree)
{
    if (tree == NULL) {
        return NULL;
    }

    Iterator* it = (Iterator*)malloc(sizeof(Iterator));
    if (it == NULL) {
        return NULL;
    }

    // Динамическое расшширение стека
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
            Node** new_stack = (Node**)realloc(it->stack, sizeof(Node*) * it->buffer);
            if (new_stack == NULL) {
                free(it->stack);
                free(it);
                return NULL;
            }
            it->stack = new_stack;
        }
        it->stack[++it->top] = current;
        current = current->left;
    }
    return it;
}

bool iteratorHasNext(Iterator* it)
{
    if (it == NULL) {
        return false;
    }
    return it->top >= 0;
}

int iteratorNextElem(Iterator* it)
{
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
            Node** new_stack = (Node**)realloc(it->stack, sizeof(Node*) * it->buffer);
            if (new_stack == NULL) {
                return result;
            }
            it->stack = new_stack;
        }
        it->stack[++it->top] = current;
        current = current->left;
    }
    return result;
}

void iteratorFree(Iterator* it)
{
    if (it != NULL) {
        if (it->stack != NULL) {
            free(it->stack);
        }
        free(it);
    }
}
