#include "bst.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Утилита для создания дерева из массива
BST* createTreeFromArray(int arr[], int n)
{
    BST* tree = createBST();
    for (int i = 0; i < n; i++) {
        bstInsert(tree, arr[i]);
    }
    return tree;
}

// Проверка, что дерево содержит все элементы
bool treeContainsAll(BST* tree, int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        if (!bstContains(tree, arr[i])) {
            return false;
        }
    }
    return true;
}

// Тесты
void testCreateBST()
{
    printf("Testing createBST... ");
    BST* tree = createBST();
    assert(tree != NULL);
    assert(tree->root == NULL);
    bstFree(tree);
    printf("Test createBST passed\n");
}

void testBstInsertAndBstContains()
{
    printf("Testing bstInsert and bstContains: ");
    BST* tree = createBST();

    bstInsert(tree, 52);
    bstInsert(tree, 35);
    bstInsert(tree, 78);
    bstInsert(tree, 12);
    bstInsert(tree, 47);
    bstInsert(tree, 64);
    bstInsert(tree, 89);

    assert(bstContains(tree, 52));
    assert(bstContains(tree, 35));
    assert(bstContains(tree, 78));
    assert(bstContains(tree, 12));
    assert(bstContains(tree, 47));
    assert(bstContains(tree, 64));
    assert(bstContains(tree, 89));
    assert(!bstContains(tree, 0));
    assert(!bstContains(tree, 100));

    // Вставка дубликата
    bstInsert(tree, 52);
    assert(bstSize(tree) == 7);

    bstFree(tree);
    printf("Test bstInsert and bstContains passed\n");
}

void testBstDelete()
{
    printf("Testing bstDelete: ");
    BST* tree = createBST();
    int arr[] = {52, 35, 78, 105, 47, 64, 89};
    for (int i = 0; i < 7; i++) {
        bstInsert(tree, arr[i]);
    }

    // Удаление листа
    bstDelete(tree, 105);
    assert(!bstContains(tree, 105));
    assert(bstSize(tree) == 6);

    // Удаление узла
    bstDelete(tree, 35);
    assert(!bstContains(tree, 35));
    assert(bstSize(tree) == 5);

    bstDelete(tree, 78);
    assert(!bstContains(tree, 78));
    assert(bstSize(tree) == 4);

    // Удаление корня
    bstDelete(tree, 52);
    assert(!bstContains(tree, 52));
    assert(bstSize(tree) == 3);

    // Удаление несуществующего элемента
    bstDelete(tree, 100);
    assert(bstSize(tree) == 3);

    bstFree(tree);
    printf("Test bstDelete passed\n");
}

void testBstHeight()
{
    printf("Testing bstHeight: ");
    BST* tree = createBST();
    assert(bstHeight(tree) == 0);

    bstInsert(tree, 52);
    assert(bstHeight(tree) == 1);

    bstInsert(tree, 35);
    assert(bstHeight(tree) == 2);

    bstInsert(tree, 78);
    assert(bstHeight(tree) == 2);

    bstInsert(tree, 12);
    assert(bstHeight(tree) == 3);

    bstInsert(tree, 5);
    assert(bstHeight(tree) == 4);

    bstFree(tree);
    printf("Test bstHeight passed\n");
}

void testBstSize()
{
    printf("Testing bstSize: ");
    BST* tree = createBST();
    assert(bstSize(tree) == 0);

    bstInsert(tree, 52);
    assert(bstSize(tree) == 1);

    bstInsert(tree, 35);
    bstInsert(tree, 78);
    assert(bstSize(tree) == 3);

    bstInsert(tree, 12);
    bstInsert(tree, 47);
    bstInsert(tree, 64);
    bstInsert(tree, 89);
    assert(bstSize(tree) == 7);

    bstDelete(tree, 52);
    assert(bstSize(tree) == 6);

    bstFree(tree);
    printf("Test bstSize passed\n");
}

void testBstMinAndBstMax()
{
    printf("Testing bstMin and bstMax: ");
    BST* tree = createBST();
    assert(bstMin(tree) == -1);
    assert(bstMax(tree) == -1);

    bstInsert(tree, 52);
    assert(bstMin(tree) == 52);
    assert(bstMax(tree) == 52);

    bstInsert(tree, 35);
    bstInsert(tree, 78);
    bstInsert(tree, 12);
    bstInsert(tree, 89);
    assert(bstMin(tree) == 12);
    assert(bstMax(tree) == 89);

    bstFree(tree);
    printf("Test bstMin and bstMax passed\n");
}

void testBstIsValid()
{
    printf("Testing bstIsValid: ");
    BST* tree = createBST();
    assert(bstIsValid(tree) == true);

    bstInsert(tree, 52);
    bstInsert(tree, 35);
    bstInsert(tree, 78);
    assert(bstIsValid(tree) == true);

    // Создание некорректного дерева
    tree->root->right->left = (Node*)malloc(sizeof(Node));
    tree->root->right->left->data = 47;
    tree->root->right->left->left = NULL;
    tree->root->right->left->right = NULL;
    assert(bstIsValid(tree) == false);

    bstFree(tree);
    printf("Test bstIsValid passed\n");
}

void testBstKthMin()
{
    printf("Testing bstKthMin: ");
    BST* tree = createBST();
    int arr[] = {52, 35, 78, 12, 47, 64, 89};
    for (int i = 0; i < 7; i++) {
        bstInsert(tree, arr[i]);
    }

    assert(bstKthMin(tree, 1) == 12);
    assert(bstKthMin(tree, 2) == 35);
    assert(bstKthMin(tree, 3) == 47);
    assert(bstKthMin(tree, 4) == 52);
    assert(bstKthMin(tree, 5) == 64);
    assert(bstKthMin(tree, 6) == 78);
    assert(bstKthMin(tree, 7) == 89);

    // Некорректные входные данные
    assert(bstKthMin(tree, 0) == -1);
    assert(bstKthMin(tree, 8) == -1);
    assert(bstKthMin(tree, -1) == -1);

    bstFree(tree);
    printf("Test bstKthMin passed\n");
}

void testBstMerge()
{
    printf("Testing bstMerge: ");
    BST* tree1 = createBST();
    BST* tree2 = createBST();

    int arr1[] = {52, 35, 78};
    int arr2[] = {47, 64, 89};
    for (int i = 0; i < 3; i++) {
        bstInsert(tree1, arr1[i]);
        bstInsert(tree2, arr2[i]);
    }

    BST* merged = bstMerge(tree1, tree2);
    assert(merged != NULL);
    assert(bstSize(merged) == 6);
    assert(bstContains(merged, 35));
    assert(bstContains(merged, 47));
    assert(bstContains(merged, 52));
    assert(bstContains(merged, 64));
    assert(bstContains(merged, 78));
    assert(bstContains(merged, 89));

    bstFree(tree1);
    bstFree(tree2);
    bstFree(merged);
    printf("Test bstMerge passed\n");
}

void testIterator()
{
    printf("Testing iterator: ");
    BST* tree = createBST();
    int arr[] = {52, 35, 78, 12, 47, 64, 89};
    for (int i = 0; i < 7; i++) {
        bstInsert(tree, arr[i]);
    }

    Iterator* it = makeIterator(tree);
    assert(it != NULL);

    int expected[] = {12, 35, 47, 52, 64, 78, 89};
    for (int i = 0; i < 7; i++) {
        assert(iteratorHasNext(it));
        assert(iteratorNextElem(it) == expected[i]);
    }
    assert(!iteratorHasNext(it));

    // Попытка получить элемент из пустого итератора
    assert(iteratorNextElem(it) == -1);
    iteratorFree(it);

    // Итератор для пустого дерева
    BST* emptyTree = createBST();
    Iterator* emptyIt = makeIterator(emptyTree);
    assert(emptyIt != NULL);
    assert(!iteratorHasNext(emptyIt));
    iteratorFree(emptyIt);

    bstFree(tree);
    bstFree(emptyTree);
    printf("Test iterator passed\n");
}

int main()
{
    printf("\nRUNNING TESTS\n\n");

    testCreateBST();
    testBstInsertAndBstContains();
    testBstDelete();
    testBstHeight();
    testBstSize();
    testBstMinAndBstMax();
    testBstIsValid();
    testBstKthMin();
    testBstMerge();
    testIterator();

    printf("\nALL TESTS PASSED\n");

    return 0;
}
}
