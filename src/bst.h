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

// Удаление узла с заданным значением
void bstDelete(BST* tree, int value);

// Удаление дерева
void bstFree(BST* tree);

// Печать (для дебаггинга)
void bstPrint(Node* node);

// Высота дерева
int bstHeight(BST* tree);

// Количество узлов
int bstSize(BST* tree);

// Минимальное значение
// Если дерево пусто, возвращает -1
int bstMin(BST* tree);

// Максимальное значение
// Если дерево пусто, возвращает -1
int bstMax(BST* tree);

// Симметричный обход (левое поддерево, корень, правое поддерево)
void bstInorder(Node* root);

// Прямой обход (корень, левое поддерево, правое поддерево)
void bstPreorder(Node* root);

// Обратный обход (левое поддерево, правое поддерево, корень)
void bstPostorder(Node* root);

// Слияние двух деревьев
BST* bstMerge(BST* tree1, BST* tree2);

// Проверка, является ли дерево корректным бинарным деревом поиска (BST)
bool bstIsValid(BST* tree);