#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "check.h"
#include "token.h"

// checks if a character is in a character array
bool inArr(char *arr, size_t size, char c){
    for(size_t i = 0; i < size; i++){
        if(c == arr[i]){
            return true;
        }
    }
    return false;
}

// checks if the string is a valid operation
bool isValidOpe(char *ope){
    size_t opeSize = strlen(ope);

    //remove all spaces
    for(size_t i = 0; i < opeSize; i++){
        if(ope[i] == ' '){
            for(size_t j = i; j < opeSize; j++){
                ope[j] = ope[j+1];
            }

            opeSize = strlen(ope);
            i--; // goes back to check the new charcter at the current index
        }
    }

    //check if the operation excedes the max size
    if(opeSize > OPERATION_MAX_SIZE){
        printf("Error! Your ope excedes the limit of 1000 characters!\n");
        return false;
    }

    //check if the operation uses non-valid characters
    for(size_t i = 0; i < opeSize; i++){
        if(!inArr(VALID_CHARS_LIST, VALID_CHARS_LIST_SIZE, ope[i])){
            return false;
        }
    }

    //check that the first and last char are not operators
    if(inArr(OPERATORS_LIST, OPERATORS_LIST_SIZE, ope[0]) && ope[0] != '-'){
        printf("Error! First character can't be an operator!\n");
        return false;
    }
    if(inArr(OPERATORS_LIST, OPERATORS_LIST_SIZE, ope[opeSize-1])){
        printf("Error! Last character can't be an operator!\n");
        return false;
    }

    //check for consecutive operators
    for(size_t i = 0; i < opeSize; i++){
        if(inArr(OPERATORS_LIST, OPERATORS_LIST_SIZE, ope[i]) && inArr(OPERATORS_LIST, OPERATORS_LIST_SIZE, ope[i+1])){
            if(ope[i+1] != '-'){
                printf("Error! Cannot use consecutive operators!\n");
                return false;
            }
        }
    }

    //check for at least one operator
    for(size_t i = 1; i < opeSize; i++){
        if(inArr(OPERATORS_LIST, OPERATORS_LIST_SIZE, ope[0])){
            break;
        }
        else if(i == opeSize){
            return true;
        }
    }

    return true;
}
