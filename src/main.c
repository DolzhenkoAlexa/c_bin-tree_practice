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

    bstPrint(tree);
    printf("\n\n");

    printf("Inorder traversal (left-root-right): ");
    bstInorder(tree);
    printf("\n");

    printf("Preorder traversal (root-left-right): ");
    bstPreorder(tree);
    printf("\n");

    printf("Postorder traversal (left-right-root): ");
    bstPostorder(tree);

    printf("\n");
    printf("Does the tree contain 7? %s\n", bstContains(tree, 7) ? "yes" : "no");
    printf("Does the tree contain 20? %s\n", bstContains(tree, 20) ? "yes" : "no");

    printf("\n");
    printf("Attempt to delete '7'\n");
    bstDelete(tree, 7);
    printf("Does the tree contain 7? %s\n", bstContains(tree, 7) ? "yes" : "no");

    printf("\n");
    printf("What is the height of the tree? %d\n", bstHeight(tree));
    printf("What is the size of the tree? %d\n", bstSize(tree));
    printf("What is the minimal value of the tree? %d\n", bstMin(tree));
    printf("What is the maximal value of the tree? %d\n", bstMax(tree));

    printf("Is the tree a valid BST? %s\n", bstIsValid(tree) ? "yes" : "no");

    printf("1st minimum: %d\n", bstKthMin(tree, 1));
    printf("2nd minimum: %d\n", bstKthMin(tree, 2));
    printf("3rd minimum: %d\n", bstKthMin(tree, 3));
    printf("4th minimum: %d\n", bstKthMin(tree, 4));
    printf("5th minimum: %d\n", bstKthMin(tree, 5));

    printf("0th minimum (error expected): %d\n", bstKthMin(tree, 0));
    printf("10th minimum (error expected): %d\n", bstKthMin(tree, 10));

    bstFree(tree);

    BST* tree1 = createBST();
    bstInsert(tree1, 10);
    bstInsert(tree1, 5);
    bstInsert(tree1, 15);
    bstInsert(tree1, 3);
    bstInsert(tree1, 7);

    printf("Tree 1: ");
    bstInorder(tree1);
    printf("\n");

    BST* tree2 = createBST();
    bstInsert(tree2, 12);
    bstInsert(tree2, 8);
    bstInsert(tree2, 20);
    bstInsert(tree2, 1);

    printf("Tree 2: ");
    bstInorder(tree2);
    printf("\n\n");

    BST* merged = bstMerge(tree1, tree2);

    printf("Merged tree: ");
    bstInorder(merged);
    printf("\n");

    printf("Is the merged tree a valid BST? %s\n", bstIsValid(merged) ? "yes" : "no");

    printf("1st minimum: %d\n", bstKthMin(merged, 1));
    printf("5th minimum: %d\n", bstKthMin(merged, 5));
    printf("9th minimum: %d\n", bstKthMin(merged, 9));

    printf("\nOriginal Tree 1: ");
    bstInorder(tree1);
    printf("\n");

    printf("Original Tree 2: ");
    bstInorder(tree2);
    printf("\n");

    bstFree(tree1);
    bstFree(tree2);
    bstFree(merged);

    BST* emptyTree = createBST();
    printf("Is empty tree a valid BST? %s\n", bstIsValid(emptyTree) ? "yes" : "no");
    bstFree(emptyTree);

    return 0;
}
