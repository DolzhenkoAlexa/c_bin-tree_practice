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

// Итератор
typedef struct Iterator {
    Node** stack; // стек узлов
    int buffer; // ёмкость стека
    int top; // вершина стека (-1 если пуст)
} Iterator;

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

// Создание итератора для обхода дерева
Iterator* makeIterator(BST* tree);

// Проверка, есть ли следующий элемент
// Если итератор исчерпан, то выведет "Error: no next element" и вернет -1
bool iteratorHasNext(Iterator* it);

// Возвращает следующий элемент
int iteratorNextElem(Iterator* it);

// Освобождение памяти итератора
void iteratorFree(Iterator* it);
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
