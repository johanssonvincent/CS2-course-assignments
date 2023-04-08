/**
 * @defgroup binarytree Binarytree
 *
 * @brief A data type representing a binary tree.
 *
 * The data type represents a binary tree. Built with a 3 cell system,
 * two for pointers to the two children and one for a pointer to the
 * parent node.
 *
 * @author: Vincent Johansson <dv14vjn>
 * @since:  2019-04-15
 *
 * @{
 */


#include <stdbool.h>


/**
 * @brief               typedef for 'void *' as 'data'.
 *
 *                      Defines 'void *' as data, to make it possible to have
 *                      self defined data structs put into the labels
 *                      of the tree.
 *
 */
typedef void * data;


/**
 * @brief               Struct for the nodes
 *
 *                      Definition of the struct for the nodes used
 *                      in the binary tree.
 *
 */
typedef struct node{
    data label;
    struct node *parent;
    struct node *leftChild;
    struct node *rightChild;
} node;


/**
 * @brief               typedef for 'node *' as treePos.
 *
 *                      Defines 'node *' as treePos in the code.
 *
 */
typedef node * treePos;


/**
 * @brief               Struct for the binary tree.
 *
 *                      Definition of the binary tree struct
 *                      containing the root node.
 *
 */
typedef struct binaryTree{
    treePos root;
} binaryTree;


/**
 * @brief Creates an empty binary tree.
 *
 * Creates an empty binary tree with root node.
 *
 * @return Pointer to the tree.
 */
binaryTree *binaryTree_create();


/**
 * @brief Inserts a new left child to given node.
 *
 * @param *tree Pointer to tree where node is to be inserted.
 * @param pos Position of the parent node for the new left child.
 *
 * @return Pointer to the new node.
 */
treePos binaryTree_insertLeft(binaryTree *tree, treePos pos);


/**
 * @brief Inserts a new right child to given node.
 *
 * @param *tree Pointer to tree where node is to be inserted.
 * @param pos Position of the parent node for the new right child.
 *
 * @return Pointer to the new node.
 */
treePos binaryTree_insertRight(binaryTree *tree, treePos pos);


/**
 * @brief Sets label for specified node.
 *
 * Takes a given data struct and sets it as the label at the specified
 * node position in the tree.
 *
 * @param *tree Pointer to the tree.
 * @param label The label to be added to the node.
 * @param pos Position of the node where label is to be added.
 *
 * @return Pointer to the new node.
 */
void binaryTree_setLabel(binaryTree *tree, data label, treePos pos);

/**
 * @brief Checks if given tree is empty.
 *
 * @param *tree Pointer to the tree.

 * @return True if the tree is empty, otherwise false.
 */
bool binaryTree_isEmpty(binaryTree *tree);


/**
 * @brief Checks if given node has a left child.
 *
 * @param *tree Pointer to the tree.
 * @param pos Position of the node to be checked if it has a left child.
 *
 * @return True if the node has a left child, otherwise false.
 */
bool binaryTree_hasLeftChild(binaryTree *tree, treePos pos);


/**
 * @brief Checks if given node has a right child.
 *
 * @param *tree Pointer to the tree.
 * @param pos Position of the node to be checked if it has a right child.
 *
 * @return True if the node has a right child, otherwise false.
 */
bool binaryTree_hasRightChild(binaryTree *tree, treePos pos);


/**
 * @brief Checks if node has a label.
 *
 * @param *tree Pointer to the tree.
 * @param pos Position of the node that is to be checked for a label.
 *
 * @return True if node has a label, otherwise false.
 */
bool binaryTree_hasLabel(binaryTree *tree, treePos pos);


/**
 * @brief See the value of a nodes label.
 *
 * Finds the specified node and returns the data struct within
 * the label of the node.
 *
 * @param *tree Pointer to the tree.
 * @param pos Position of the node that label info is to be inspected.
 *
 * @return The labels value.
 */
data binaryTree_inspectLabel(binaryTree *tree, treePos pos);


/**
 * @brief Gets the position for the root node.
 *
 * Takes given binary tree and sends back the position for the root node.
 *
 * @param *tree Pointer to the tree where you want to find the root node.
 */
treePos binaryTree_root(binaryTree *tree);


/**
 * @brief Gets the position of the left child of specified node.
 *
 * @param *tree Pointer to the tree.
 * @param pos Position of the parent node to which we want to find out
 *            the left childs position.
 */
treePos binaryTree_leftChild(binaryTree *tree, treePos pos);


/**
 * @briefGets the position of the right child of specified node.
 *
 * @param *tree Pointer to the tree.
 * @param pos Position of the parent node to which we want to find out
 *            the right childs position.
 */
treePos binaryTree_rightChild(binaryTree *tree, treePos pos);


/**
 * @brief Gets the position to the parent of the given node position.
 *
 * @param *tree Pointer to the tree where you want to find the root node.
 * @param pos Position of the node which we want to find the parent of.
 */
treePos binaryTree_parent(binaryTree *tree, treePos pos);


/**
 * @brief Deletes a node.
 *
 * Takes given binary tree and the position of the node to be removed.
 * Frees the allocated memory for that node.
 *
 * @param *tree Pointer to the tree.
 * @param pos Position of the node to be removed.
 */
treePos binaryTree_deleteNode(binaryTree *tree, treePos pos);


/**
 * @brief Destroys the binary tree.
 *
 * Takes given binary tree and frees all used memory.
 *
 * @param *tree Pointer to the tree to be destroyed.
 */
void binaryTree_destroy(binaryTree *tree);
