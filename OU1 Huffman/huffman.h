/**
 * @defgroup huffman Huffman
 *
 * @brief The main application for the Huffman program.
 *
 * The main program, handles encoding and decoding of the input text files.
 *
 * @author: Vincent Johansson <dv14vjn>
 * @since:  2019-04-15
 *
 * @{
 */

 /*! \mainpage Huffman
  *
  * \section intro_sec Introduction
  *
  * Program used to decode and encode text files using Huffman coding.
  *
  * \section usage_sec Usage
  *
  * USAGE: huffman [OPTION] [FILE0] [FILE1] [FILE2] \n
  * Options: \n
  * -encode encodes FILE1 according to frequence analysis done on FILE0.
  * Stores the result in FILE2. \n
  * -decode decodes FILE1 according to frequence analysis done on FILE0.
  * Stores the result in FILE2.
  *
  */


 /**
  * @brief               Validate input commands.
  *
  * @param argc          Argument count.
  * @param argv          Argument vector.
  * @param *s            Pointer to struct where input commands are stored.
  * @return              true if correct input, otherwise false.
  */
 bool checkInput(int argc, char *argv[], startArgs *s);


 /**
  * @brief               Comparison of trees.
  *
  * @param treeOne       First tree used for comparison.
  * @param treeTwo       Second tree used for comparison.
  *
  * @return              1 if the value of the first tree is larger,
  *                      2 if the second trees value is larger, otherwise 0.
  */
 int treeComparison(data treeOne, data treeTwo);


 /**
  * @brief               Construction of the Huffman tree.
  *
  * @param freq          Frequency array used in making the Huffmantree.
  * @param (*compare)    Funciton used for comparison of binary trees.
  *
  * @return              The completed Huffmantree.
  */
 binaryTree *buildHuffmanTree(int *freq, int (*compare)(data, data));


 /**
  * @brief               Used to build a code table using bit buffer.
  *
  * @param *tree         Pointer to the Huffmantree used for building code table.
  * @param pos           Position in the tree at initiation of function.
  * @param *pathArr[]    Pointer to an array of bit bufferts where the bit
  *                      sequences are stored.
  * @param index         index number used to navigate in navPath array.
  * @param navPath[]     Array used to store path used in the tree.
  *                      This is converted to a bitsequence.
  *
  * @return              -
  */
 void buildCodeTable(binaryTree *tree, treePos pos, bit_buffer *pathArr[],
     int index, int navPath[]);


 /**
  * @brief               Encodes the file using bitsequences.
  *
  * @param *inFile       Pointer to input file.
  * @param *outFile      Pointer to output file.
  * @param *pathArr[]    Pointer to array of bitsequences used to encode file.
  *
  * @return              -
  */
 void encodeFile(FILE *inFile, FILE *outFile, bit_buffer *pathArr[]);


 /**
  * @brief               Decode the input file.
  *
  * @param *inFile       Pointer to input file.
  * @param *outFile      Pointer to output file.
  * @param *tree         Pointer to the Huffmantree used in decoding.
  *
  * @return              -
  */
 void decodeFile(FILE *inFile, FILE *outFile, binaryTree *tree);


 /**
  * @brief               Prints usage instruction if input commands are wrong.
  *
  * @return              -
  */
  void errorInput();
