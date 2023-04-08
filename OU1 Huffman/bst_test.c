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

    bst->root->label = nodeLabel;

    if(binaryTree_isEmpty(bst)){
        printf("TOMT TRÄD\n");
    }else{
        printf("ROOT FYLLD.\n");
    }

    treePos pos = binaryTree_root(bst);

    binaryTree_insertLeft(bst, pos);

    binaryTree_setLabel(bst, nodeLabel, binaryTree_root(bst));

    if(binaryTree_hasLabel(bst, binaryTree_root(bst))){
        printf("works.\n");
    }

    if(!binaryTree_isEmpty(bst)){
        printf("FYLLT TRÄD\n");
    }

    binaryTree_destroy(bst);
}
