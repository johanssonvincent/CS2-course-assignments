#include <stdlib.h>
#include "binarytree.h"


binaryTree *binaryTree_create(){
    binaryTree *tree = calloc(1, sizeof(binaryTree));
    tree->root = calloc(1, sizeof(node));
    return tree;
}


treePos binaryTree_insertLeft(binaryTree *tree, treePos pos){
    treePos newNode = calloc(1, sizeof(node));
    newNode->parent = pos;

    if(pos->leftChild != NULL){
        binaryTree_deleteNode(tree, pos->leftChild);
    }

    pos->leftChild = newNode;
    return newNode;
}


treePos binaryTree_insertRight(binaryTree *tree, treePos pos){
    treePos newNode = calloc(1, sizeof(node));
    newNode->parent = pos;

    if(pos->rightChild != NULL){
        binaryTree_deleteNode(tree, pos->rightChild);
    }

    pos->rightChild = newNode;
    return newNode;
}


void binaryTree_setLabel(binaryTree *tree, data label, treePos pos){
    pos->label=label;
}


bool binaryTree_isEmpty(binaryTree *tree){
    treePos pos = binaryTree_root(tree);

    if(binaryTree_hasLeftChild(tree, pos) ||
        binaryTree_hasRightChild(tree, pos)){
        return false;
    }

    if(tree->root->label != NULL){
        return false;
    }else{
        return true;
    }
}


bool binaryTree_hasLeftChild(binaryTree *tree, treePos pos){
    return pos->leftChild != NULL;
}


bool binaryTree_hasRightChild(binaryTree *tree, treePos pos){
    return pos->rightChild != NULL;
}


bool binaryTree_hasLabel(binaryTree *tree, treePos pos){
    return pos->label != NULL;
}


data binaryTree_inspectLabel(binaryTree *tree, treePos pos){
    return pos->label;
}


treePos binaryTree_root(binaryTree *tree){
    return tree->root;
}


treePos binaryTree_leftChild(binaryTree *tree, treePos pos){
    return pos->leftChild;
}


treePos binaryTree_rightChild(binaryTree *tree, treePos pos){
    return pos->rightChild;
}


treePos binaryTree_parent(binaryTree *tree, treePos pos){
    return pos->parent;
}


treePos binaryTree_deleteNode(binaryTree *tree, treePos pos){
    treePos parent = pos->parent;

    if(pos->leftChild != NULL){
        binaryTree_deleteNode(tree, pos->leftChild);
    }

    if(pos->rightChild != NULL){
        binaryTree_deleteNode(tree, pos->rightChild);
    }

    if(parent->leftChild == pos){
        parent->leftChild = NULL;
    }else{
        parent->rightChild = NULL;
    }

    free(pos->label);
    free(pos);

    return parent;
}


void binaryTree_destroy(binaryTree *tree){
    if(binaryTree_hasLeftChild(tree, tree->root)){
        binaryTree_deleteNode(tree, tree->root->leftChild);
    }

    if(binaryTree_hasRightChild(tree, tree->root)){
        binaryTree_deleteNode(tree, tree->root->rightChild);
    }

    free(tree->root->label);
    free(tree->root);
    free(tree);
}
