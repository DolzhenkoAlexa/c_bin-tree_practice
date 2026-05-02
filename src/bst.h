#pragma once

#include <stdbool.h>

typedef struct Node Node;

typedef struct BST BST;

// Итератор
typedef struct Iterator Iterator;

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
void bstPrint(BST* tree);

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
void bstInorder(BST* tree);

// Прямой обход (корень, левое поддерево, правое поддерево)
void bstPreorder(BST* tree);

// Обратный обход (левое поддерево, правое поддерево, корень)
void bstPostorder(BST* tree);

// Слияние двух деревьев
BST* bstMerge(BST* tree1, BST* tree2);

// Проверка, является ли дерево корректным бинарным деревом поиска (BST)
bool bstIsValid(BST* tree);

// Возвращает k-й элемент дерева
// Если k <= 0, k > bstSize(tree) или дерево пустое, функция возвращает -1
int bstKthMin(BST* tree, int k);
