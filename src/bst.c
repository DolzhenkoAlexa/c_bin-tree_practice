#include "bst.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_STACK_SIZE 32

typedef enum {
    GoLeft,
    GoRight
} Direction;

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

// Рекурсивная функция нахождения высоты узла
static int nodeHeight(Node* node)
{
    if (node == NULL)
        return 0;

    int leftHeight = nodeHeight(node->left);
    int rightHeight = nodeHeight(node->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Рекурсивная функция нахождения размера узла
static int nodeSize(Node* node)
{
    if (node == NULL)
        return 0;

    return 1 + nodeSize(node->left) + nodeSize(node->right);
}

// Нахождение минимального узла в поддереве
static Node* findMinNode(Node* node)
{
    while (node && node->left)
        node = node->left;
    return node;
}

// Удаление узла
static Node* deleteNode(Node* node, int value)
{
    if (node == NULL)
        return NULL;

    if (value < node->data) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->data) {
        node->right = deleteNode(node->right, value);
    } else {
        // Узел найден
        if (node->left == NULL) {
            Node* rightChild = node->right;
            free(node);
            return rightChild;
        }
        if (node->right == NULL) {
            Node* leftChild = node->left;
            free(node);
            return leftChild;
        }
        // Узел с двумя детьми
        Node* minNode = findMinNode(node->right);
        node->data = minNode->data;
        node->right = deleteNode(node->right, minNode->data);
    }

    return node;
}

// Рекурсивная функция для поиска k-го минимального элемента
static bool kthMin(Node* node, int k, int* counter, int* result)
{
    if (node == NULL)
        return false;

    // Обходим левое поддерево
    if (kthMin(node->left, k, counter, result))
        return true;

    // Текущий узел
    (*counter)++;
    if (*counter == k) {
        *result = node->data;
        return true;
    }

    // Обходим правое поддерево
    return kthMin(node->right, k, counter, result);
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
    Direction goLeft = GoRight;

    while (current != NULL) {
        if (data == current->data)
            return;
        parent = current;
        if (data < current->data) {
            current = current->left;
            goLeft = GoLeft;
        } else {
            current = current->right;
            goLeft = GoRight;
        }
    }

    Node* newNode = createNode(data);
    if (parent == NULL) {
        tree->root = newNode;
    } else {
        if (goLeft == GoLeft)
            parent->left = newNode;
        else
            parent->right = newNode;
    }
}

// Удаление узла с заданным значением
void bstDelete(BST* tree, int value)
{
    if (tree != NULL)
        tree->root = deleteNode(tree->root, value);
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

// Высота дерева
int bstHeight(BST* tree)
{
    if (tree == NULL || tree->root == NULL)
        return 0;

    return nodeHeight(tree->root);
}

// Количество узлов
int bstSize(BST* tree)
{
    if (tree == NULL || tree->root == NULL)
        return 0;

    return nodeSize(tree->root);
}

// Минимальное значение
// Если дерево пусто, возвращает -1
int bstMin(BST* tree)
{
    if (tree == NULL || tree->root == NULL)
        return -1;

    Node* current = tree->root;
    while (current->left != NULL)
        current = current->left;

    return current->data;
}

// Максимальное значение
// Если дерево пусто, возвращает -1
int bstMax(BST* tree)
{
    if (tree == NULL || tree->root == NULL)
        return -1;

    Node* current = tree->root;
    while (current->right != NULL)
        current = current->right;

    return current->data;
}

// Симметричный обход
void bstInorder(Node* root)
{
    if (root == NULL)
        return;

    bstInorder(root->left);
    printf("%d ", root->data);
    bstInorder(root->right);
}

// Прямой обход
void bstPreorder(Node* root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    bstPreorder(root->left);
    bstPreorder(root->right);
}

// Обратный обход
void bstPostorder(Node* root)
{
    if (root == NULL)
        return;

    bstPostorder(root->left);
    bstPostorder(root->right);
    printf("%d ", root->data);
}

// Функция для добавления всех элементов из одного дерева в другое
static void addAllNodes(Node* sourceRoot, BST* targetTree)
{
    if (sourceRoot == NULL)
        return;

    // Рекурсивно обходим все узлы и вставляем
    addAllNodes(sourceRoot->left, targetTree);
    bstInsert(targetTree, sourceRoot->data);
    addAllNodes(sourceRoot->right, targetTree);
}

// Слияние двух деревьев
BST* bstMerge(BST* tree1, BST* tree2)
{
    if (tree1 == NULL && tree2 == NULL)
        return NULL;

    // Создаем новое дерево
    BST* mergedTree = createBST();
    if (mergedTree == NULL)
        return NULL;

    // Добавляем все элементы из первого дерева
    if (tree1 != NULL && tree1->root != NULL) {
        addAllNodes(tree1->root, mergedTree);
    }

    // Добавляем все элементы из второго дерева
    if (tree2 != NULL && tree2->root != NULL) {
        addAllNodes(tree2->root, mergedTree);
    }

    return mergedTree;
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

    // Динамическое расширение стека
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
            Node** newStack = (Node**)realloc(it->stack, sizeof(Node*) * it->buffer);
            if (newStack == NULL) {
                free(it->stack);
                free(it);
                return NULL;
            }
            it->stack = newStack;
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
            int newBuffer = it->buffer * 2;
            Node** newStack = (Node**)realloc(it->stack, sizeof(Node*) * newBuffer);
            if (newStack == NULL) {
                fprintf(stderr, "Error: not enough memory for iterator realloc\n");
                return result;
            }
            it->stack = newStack;
            it->buffer = newBuffer;
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

// Вспомогательная рекурсивная функция с диапазонами допустимых значений
static bool isValidBSTHelper(Node* node, int min, int max)
{
    // Пустой узел - корректный
    if (node == NULL)
        return true;

    // Проверяем, что значение узла в допустимом  диапазоне
    if (node->data <= min || node->data >= max)
        return false;

    // Рекурсивно проверяем левое и правое поддеревья
    return isValidBSTHelper(node->left, min, node->data) && isValidBSTHelper(node->right, node->data, max);
}

// Проверка, является ли дерево корректным бинарным деревом поиска (BST)
bool bstIsValid(BST* tree)
{
    // Пустое дерево считается корректным BST
    if (tree == NULL || tree->root == NULL)
        return true;

    return isValidBSTHelper(tree->root, INT_MIN, INT_MAX);
}

// Поиск k-го минимального элемента
int bstKthMin(BST* tree, int k)
{
    // Проверка корректности входных данных
    if (tree == NULL || tree->root == NULL) {
        printf("Error: Tree is empty\n");
        return -1;
    }

    if (k <= 0) {
        printf("Error: k must be positive\n");
        return -1;
    }

    int size = bstSize(tree);
    if (k > size) {
        printf("Error: k (%d) exceeds tree size (%d)\n", k, size);
        return -1;
    }

    int counter = 0;
    int result = -1;

    kthMin(tree->root, k, &counter, &result);

    return result;
}
