#include "bst.h"
#include <stdio.h>

int main()
{
    BST* tree = createBST();

    bstInsert(tree, 10);
    bstInsert(tree, 5);
    bstInsert(tree, 15);
    bstInsert(tree, 7);
    bstInsert(tree, 12);

    bstPrint(tree->root);

    printf("\n");
    printf("Does the tree contain 7? %s\n", bstContains(tree, 7) ? "yes" : "no");
    printf("Does the tree contain 20? %s\n", bstContains(tree, 20) ? "yes" : "no");
    printf("What is the height of the tree? %d\n", bstHeight(tree));
    printf("What is the size of the tree? %d\n", bstSize(tree));
    printf("What is the minimal value of the tree? %d\n", bstMin(tree));
    printf("What is the maximal value of the tree? %d\n", bstMax(tree));

    bstFree(tree);

    return 0;
}
