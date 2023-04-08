/*
 * @author  Vincent Johansson
 * @since   2020-04-15
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequency.h"
#include "binarytree.h"
#include "pqueue.h"
#include "bit_buffer.h"


#define MAXBITSIZE 30


// Struct for holding the start arguments.
typedef struct startArgs{
    int mode;
    FILE* freqFile;
    FILE* inFile;
    FILE* outFile;
}startArgs;


// Struct for the data node used in the Huffman tree.
typedef struct freqData{
    int value;
    char character;
} freqData;


/* ---- Private function declaration --- */
bool checkInput(int argc, char *argv[], startArgs *s);
int treeComparison(data firstTree, data secondTree);
binaryTree *buildHuffmanTree(int *freq, int (*compare)(data, data));
void buildCodeTable(binaryTree *tree, treePos pos, bit_buffer *pathArr[],
    int index, int navPath[]);
void encodeFile(FILE *infile, FILE *outfile, bit_buffer *pathArr[]);
void decodeFile(FILE *inFile, FILE *outFile, binaryTree *tree);
void errorInput();


int main(int argc, char *argv[]){

    // Variables.
    int freqArr[256] = {0};
    int navPath[MAXBITSIZE] = {-1};
    int index = 0;


    startArgs *ha = calloc(1, sizeof(startArgs));
    if(!checkInput(argc, argv, ha)){
        free(ha);
        errorInput();
    }


    // Open all files.
    ha->freqFile = fopen(argv[2], "rt");
    if(ha->freqFile == NULL){
        fprintf(stderr, "Couldn't open frequency file %s\n", argv[2]);
        errorInput();
    }

    if(ha->mode == 1){
        ha->inFile = fopen(argv[3], "rt");
    }else{
        ha->inFile = fopen(argv[3], "rb");
    }
    if(ha->inFile == NULL){
        fprintf(stderr, "Couldn't open input file %s\n", argv[3]);
        errorInput();
    }

    ha->outFile = fopen(argv[4], "w");
    if(ha->outFile == NULL){
        fprintf(stderr, "Couldn't open output file %s\n", argv[4]);
        errorInput();
    }


    if(ha->mode == 1){

        // Create frequency array.
        getFrequency(freqArr, ha->freqFile);


        // Build the huffmantree.
        binaryTree *encodeTree = buildHuffmanTree(freqArr, treeComparison);


        // Build the code table for the huffman tree.
        bit_buffer *encodePathArr[256];
        buildCodeTable(encodeTree, binaryTree_root(encodeTree), encodePathArr,
                        index, navPath);

        // Encode the input file.
        encodeFile(ha->inFile, ha->outFile, encodePathArr);


        // Screen output with information on file sizes.
        long readBytes = ftell(ha->inFile);
        long writtenBytes = ftell(ha->outFile);
        printf("%ld bytes read from %s.\n", readBytes, argv[3]);
        printf("%ld bytes used in encoded form.\n", writtenBytes);


        // Free allocated memory.
        for(int i = 0; i < 256; i++){
            bit_buffer_free(encodePathArr[i]);
        }
        binaryTree_destroy(encodeTree);

    }else if(ha->mode == 2){

        // Create frequency array.
        getFrequency(freqArr, ha->freqFile);


        // Build the huffmantree.
        binaryTree *decodeTree = buildHuffmanTree(freqArr, treeComparison);


        // Decode the input file.
        decodeFile(ha->inFile, ha->outFile, decodeTree);


        // Free allocated memory.
        binaryTree_destroy(decodeTree);
    }

    fclose(ha->freqFile);
    fclose(ha->inFile);
    fclose(ha->outFile);

    free(ha);
}


/* PRIVATE FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - */

bool checkInput(int argc, char *argv[], startArgs *s){

    // Strings to compare to input for selection of mode.
    char encodeStr[8];
    char decodeStr[8];
    strcpy(encodeStr, "-encode");
    strcpy(decodeStr, "-decode");

    // Set mode depending on input in argv[1].
    if(argc != 5){
        return false;
    }else if(argc == 5){
        if(!strcmp(argv[1], encodeStr)){
            s->mode = 1;
            return true;
        }else if(!strcmp(argv[1], decodeStr)){
            s->mode = 2;
            return true;
        }else{
            return false;
        }
    }
    return false;
}


int treeComparison(data treeOne, data treeTwo){
    freqData tempOne;
    freqData tempTwo;

    tempOne = *(freqData*)binaryTree_inspectLabel(treeOne,
                                binaryTree_root(treeOne));
    tempTwo = *(freqData*)binaryTree_inspectLabel(treeTwo,
                                binaryTree_root(treeTwo));

    if(tempOne.value > tempTwo.value){
        return 1;
    }else if(tempOne.value == tempTwo.value){
        return 0;
    }else{
        return -1;
    }
}


binaryTree *buildHuffmanTree(int *freq, int (*compare)(data, data)){
    pqueue *buildingQueue = pqueue_empty(compare);
    binaryTree *firstTree;
    binaryTree *secondTree;
    binaryTree *buildTree;


    // Create tree for all characters and insert to priority queue.
    for(int charCount = 0; charCount < 256; charCount++){
        freqData *nodeLabel = calloc(1, sizeof(freqData));
        nodeLabel->character = charCount;
        nodeLabel->value = freq[charCount];

        buildTree = binaryTree_create();
        binaryTree_setLabel(buildTree, nodeLabel, binaryTree_root(buildTree));
        pqueue_insert(buildingQueue, buildTree);
    }

    // While pqueue isn't empty take out two first trees and combine them.
    while(!pqueue_is_empty(buildingQueue)){
        buildTree = binaryTree_create();

        // Take the first tree in queue and save its label values.
        firstTree = pqueue_inspect_first(buildingQueue);
        freqData *firstTreeLabel = binaryTree_inspectLabel(firstTree,
                                   binaryTree_root(firstTree));
        pqueue_delete_first(buildingQueue);

        if(pqueue_is_empty(buildingQueue)){
            binaryTree_destroy(buildTree);
            pqueue_kill(buildingQueue);

            return firstTree;
        }else{
            secondTree = pqueue_inspect_first(buildingQueue);
            freqData *secondTreeLabel = binaryTree_inspectLabel(secondTree,
                                        binaryTree_root(secondTree));
            pqueue_delete_first(buildingQueue);

            // Initiate combined node label and give values from taken nodes.
            freqData *combinedLabel = calloc(1, sizeof(freqData));
            combinedLabel->value =
                firstTreeLabel->value + secondTreeLabel->value;
            combinedLabel->character = -1;

            // Set the label for the new tree and insert children.
            binaryTree_setLabel(buildTree, combinedLabel,
                binaryTree_root(buildTree));

            buildTree->root->leftChild = secondTree->root;
            buildTree->root->rightChild = firstTree->root;
            secondTree->root->parent = buildTree->root;
            firstTree->root->parent = buildTree->root;

            // Insert the combined tree in the queue.
            pqueue_insert(buildingQueue, buildTree);
            free(firstTree);
            free(secondTree);
        }
    }

    pqueue_kill(buildingQueue);

    return 0;
}


void buildCodeTable(binaryTree *tree, treePos pos, bit_buffer *pathArr[],
    int index, int navPath[]){

    // Add '0' to the bit sequence in case we move left in the tree.
    if(binaryTree_hasLeftChild(tree, pos)){
        navPath[index] = 0;
        buildCodeTable(tree, binaryTree_leftChild(tree, pos), pathArr,
            index+1, navPath);
    }

    // Add '1' to the bit sequence in case we move right in the tree.
    if(binaryTree_hasRightChild(tree, pos)){
        navPath[index] = 1;
        buildCodeTable(tree, binaryTree_rightChild(tree, pos), pathArr,
            index+1, navPath);
    }

    // When the node doesn't have any children, save the bit sequence.
    if(!binaryTree_hasLeftChild(tree, pos) &&
        !binaryTree_hasRightChild(tree, pos)){
            freqData *tempLabel = binaryTree_inspectLabel(tree, pos);
            bit_buffer *charSequence = bit_buffer_empty();

            for(int i = 0; i < index; i++){
                bit_buffer_insert_bit(charSequence, navPath[i]);
            }

            pathArr[(unsigned char)tempLabel->character] = charSequence;
    }
}


void encodeFile(FILE *inFile, FILE *outFile, bit_buffer *pathArr[]){
    char temp;
    int lengthCharBits;
    bit_buffer *combinedBitBuffer = bit_buffer_empty();
    char *printToFile;

    while((temp = fgetc(inFile))){
        if(feof(inFile)){
            lengthCharBits = bit_buffer_size(pathArr[4]);

            for(int i = 0; i < lengthCharBits; i++){
                bit_buffer_insert_bit(combinedBitBuffer,
                    bit_buffer_inspect_bit(pathArr[4], i));
            }
            break;
        }

        lengthCharBits = bit_buffer_size(pathArr[(unsigned char)temp]);

        for(int i = 0; i < lengthCharBits; i++){
            bit_buffer_insert_bit(combinedBitBuffer,
                bit_buffer_inspect_bit(pathArr[(unsigned char)temp], i));
        }
    }

    // Write the bit buffer to the output file.
    printToFile = bit_buffer_to_byte_array(combinedBitBuffer);

    for(int i = 0; i < bit_buffer_size(combinedBitBuffer)/8; i++){
        fputc(printToFile[i], outFile);
    }


    // Free used memory.
    free(printToFile);
    bit_buffer_free(combinedBitBuffer);
}


void decodeFile(FILE *inFile, FILE *outFile, binaryTree *tree){
    int decodePos = 0;
    int fileSize;
    int tempBit;
    freqData *currentLabel;
    treePos pos = binaryTree_root(tree);


    // Length of input file.
    fseek(inFile, 0, SEEK_END);
    fileSize = ftell(inFile);
    fseek(inFile, 0, SEEK_SET);


    // Read input file and copy to decodeBuffer.
    char decodeArray[fileSize];

    for(int i = 0; i < fileSize; i++){
        decodeArray[i] = fgetc(inFile);
    }

    bit_buffer *decodeBuffer = bit_buffer_create(decodeArray, 8 * fileSize);


    // Use decodeBuffer and move accordingly in Huffmantree.
    // Print char at leaf in output file.
    while(decodePos < fileSize * 8){
        if(binaryTree_hasLeftChild(tree, pos) ||
                binaryTree_hasRightChild(tree, pos)){
            tempBit = bit_buffer_remove_bit(decodeBuffer);
            if(tempBit == 0){
                pos = binaryTree_leftChild(tree, pos);
                decodePos++;
            }else if(tempBit == 1){
                pos = binaryTree_rightChild(tree, pos);
                decodePos++;
            }
        }else{
            currentLabel = (freqData*)binaryTree_inspectLabel(tree, pos);
            fputc(currentLabel->character, outFile);
            pos = binaryTree_root(tree);
        }
    }
    bit_buffer_free(decodeBuffer);
    printf("File decoded successfully!\n");
}


void errorInput(){
    printf("USAGE:\nhuffman [OPTION] [FILE0] [FILE1] [FILE2]\n");
    printf("Options:\n-encode encodes FILE1 according to frequence ");
    printf("analysis done on FILE0. Stores the result in FILE2\n");
    printf("-decode decodes FILE1 according to frequence analysis done");
    printf("on FILE0. Stores the result in FILE2\n");

    exit(EXIT_FAILURE);
}
