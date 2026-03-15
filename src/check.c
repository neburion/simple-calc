#include <float.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "check.h"
#include "sys.h"
#include "token.h"

void strReplace(char *string, char *toReplace, size_t toReplaceLen, char *replaceWith){

    if(toReplace < string || toReplace >= string + strlen(string))
        die("Error! strReplace() tried to replace a string that was not inside it!\n");

    char stringBuffer[OPERATION_SIZE_LIMIT+1];

    size_t prefixLen    = toReplace - string;
    char   *suffixPtr   = toReplace + toReplaceLen;
    
    if(!string || !replaceWith || !suffixPtr)
        die("Error! NULL pointer passed to strReplace()!\n");

    snprintf(stringBuffer, sizeof(stringBuffer), "%.*s%s%s", 
        (int)prefixLen, string, replaceWith, suffixPtr);

    strcpy(string, stringBuffer);
}

bool isValidOperation(char *operation, double lastResult){
    if(!operation) die("Error! NULL operation passed!\n");

    size_t operationSize = strlen(operation);

    //remove all spaces
    for(size_t i = 0; i < operationSize; i++){
        if(operation[i] == ' '){
            for(size_t j = i; j < operationSize; j++){
                operation[j] = operation[j+1];
            }
            operationSize = strlen(operation);
            i--; // goes back to check the new charcter at the current index
        }
    }
    
    // replace abs with its value
    char *lastResultPtr = strstr(operation, "abs");
    if(lastResultPtr){
        char lastResultStr[64];
        snprintf(lastResultStr, sizeof(lastResultStr), "%.2f", lastResult);
        size_t absLen = strlen("abs");
        strReplace(operation, lastResultPtr, absLen, lastResultStr);
        operationSize = strlen(operation);
    }

    //check if the operation excedes the max size
    if(operationSize > OPERATION_SIZE_LIMIT){
        printf("Error! Your operation excedes the limit of 1000 characters!\n");
        return false;
    }

    //check if the operation uses non-valid characters
    for(size_t i = 0; i < operationSize; i++){
        if(!strchr(VALID_CHARS, operation[i])){
            printf("Error! You are using non valid characters!\n");
            return false;
        }
    }

    //check that the first and last char are not operators
    if(strchr(VALID_OPERATORS, operation[0]) && operation[0] != '-'){
        printf("Error! First character can't be an operator!\n");
        return false;
    }
    if(strchr(VALID_OPERATORS, operation[operationSize-1])){
        printf("Error! Last character can't be an operator!\n");
        return false;
    }

    //check for consecutive operators
    for(size_t i = 0; i < operationSize; i++){
        if(strchr(VALID_OPERATORS, operation[i]) && strchr(VALID_OPERATORS, operation[i+1])){
            if(operation[i+1] != '-'){
                printf("Error! Cannot use consecutive operators!\n");
                return false;
            }
        }
    }

    //check for at least one operator
    for(size_t i = 1; i < operationSize; i++){
        if(strchr(VALID_OPERATORS, operation[0])){
            break;
        }
        else if(i == operationSize){
            return true;
        }
    }

    return true;
}
