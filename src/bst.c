#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

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