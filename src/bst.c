#include "bst.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_STACK_SIZE 32

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
            it->buffer *= 2;
            Node** newStack = (Node**)realloc(it->stack, sizeof(Node*) * it->buffer);
            if (newStack == NULL) {
                return result;
            }
            it->stack = newStack;
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
