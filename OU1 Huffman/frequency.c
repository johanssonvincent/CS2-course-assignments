/*
 * @author  Vincent Johansson
 * @since   2020-04-15
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void getFrequency(int freqArr[], FILE* file){
    int ch;
    bool finish = false;

    // Increase the frequency of EOT char by 1.
    freqArr[4]++;

    while(!finish){
        ch = fgetc(file);
        if(ch == EOF){
            finish = true;
        }else{
            freqArr[ch]++;
        }
    }
}

/* ---- External functions used for debugging - Not part of API --- */
void printFrequency(int freqArr[]){
    int count = 0;

    for(int i = 0; i < 256; i++){
            if(count == 3){
                printf("fqArr[%d] = %d\n", i, freqArr[i]);
                count = 0;
            }else{
                printf("fqArr[%d] = %d, ", i, freqArr[i]);
                count++;
            }
    }
}
