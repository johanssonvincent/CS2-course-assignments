#include <stdlib.h>
#include <stdio.h>
#include "binarytree.h"


typedef struct freqChar{
    int value;
    char character;
} freqChar;


int main(void){

    freqChar *nodeLabel = calloc(1, sizeof(freqChar));
    nodeLabel->value = 1;
    nodeLabel->character = 'C';

    binaryTree *bst = binaryTree_create();


    treePos pos = binaryTree_root(bst);

    binaryTree_insertLeft(bst, pos);

    binaryTree_setLabel(bst, nodeLabel, binaryTree_leftChild(bst, pos));

    pos = binaryTree_leftChild(bst, binaryTree_root(bst));

    if(binaryTree_hasLabel(bst, pos)){
        printf("WORKS\n");
    }

    binaryTree_destroy(bst);
}
