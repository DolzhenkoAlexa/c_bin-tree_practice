#pragma once

#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct BST {
    Node* root;
} BST;

// Создание дерева
BST* createBST(void);

// Проверка существования элемента в дереве
bool bstContains(BST* tree, int data);

// Вставка
void bstInsert(BST* tree, int data);

// Удаление дерева
void bstFree(BST* tree);

// Печать (для дебаггинга)
void bstPrint(Node* node);

// Симметричный обход (левое поддерево, корень, правое поддерево)
void bstInorder(Node* root);

// Прямой обход (корень, левое поддерево, правое поддерево)
void bstPreorder(Node* root);

// Обратный обход (левое поддерево, правое поддерево, корень)
void bstPostorder(Node* root);