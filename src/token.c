#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "token.h"
#include "check.h"
#include "io.h"

// initializing the constants
const char VALID_CHARS_LIST[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', '+', '-', '*', '/', '\0'};
const size_t VALID_CHARS_LIST_SIZE = sizeof(VALID_CHARS_LIST) / sizeof(VALID_CHARS_LIST[0]);
const char OPERANDS_LIST[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.'};
const size_t OPERANDS_LIST_SIZE = sizeof(OPERANDS_LIST) / sizeof(OPERANDS_LIST[0]);
const char OPERATORS_LIST[] = {'+', '-', '*', '/'};
const size_t OPERATORS_LIST_SIZE = sizeof(OPERATORS_LIST) / sizeof(OPERATORS_LIST[0]);

// add a token and resize the token array to fit it
void addTok(Token **tokArr, size_t newSize, Token *tok){
    Token *tmp = realloc(*tokArr, newSize * sizeof(Token));
    if(!tmp){
        printf("Error! Failed to realloc the token array in addTok() when trying to add a new token at: %zu", newSize);
        abort();
    }
    *tokArr = tmp;

    (*tokArr)[newSize-1] = *tok;
    
    tmp = NULL;
}

// parse and tokenize an input string
Token *inputToTok(char *input){
    Token *tokArr = NULL;
    size_t inputSize = strlen(input);
    char buf[OPERATION_MAX_SIZE] = {0};
    size_t bufPos = 0;
    size_t tokCount = 0;

    for(size_t i = 0; i < inputSize; i++){
        buf[bufPos] = input[i];
        bufPos++;

        if(inArr(OPERATORS_LIST, OPERATORS_LIST_SIZE, input[i+1])){
            // Operand
            tokCount++;
            buf[bufPos] = '\0';
            double opd = atof(buf);
            Token opdTok = {OPED, NOT, opd};
            addTok(&tokArr, tokCount, &opdTok);

            // Operator
            tokCount++;
            char opt = input[i+1];
            if(opt == '+'){
                Token optTok = {OPET, ADD, opt};
                addTok(&tokArr, tokCount, &optTok);
            }
            else if(opt == '-'){
                Token optTok = {OPET, SUB, opt};
                addTok(&tokArr, tokCount, &optTok);
            }
            else if(opt == '*'){
                Token optTok = {OPET, MULT, opt};
                addTok(&tokArr, tokCount, &optTok);
            }
            else if(opt == '/'){
                Token optTok = {OPET, DIV, opt};
                addTok(&tokArr, tokCount, &optTok);
            }

            memset(buf, 0, strlen(buf));
            bufPos = 0;
            i++; // skip the operator
        }

        else if(input[i+1] == '\0'){
            // Operand
            tokCount++;
            buf[bufPos] = '\0';
            double opd = atof(buf);
            Token opdTok = {OPED, NOT, opd};
            addTok(&tokArr, tokCount, &opdTok);

            tokCount++;
            Token lastTok = {LAST, NOT, -1};
            addTok(&tokArr, tokCount, &lastTok);

            memset(buf, 0, strlen(buf));
            bufPos = 0;

            break;
        }
    }

    return tokArr;
}

// calculate a 2 operand operation
double calcTwoTok(Token opdL, Token opt, Token opdR){
    switch(opt.opt){
        case  ADD:
            return opdL.opd + opdR.opd;
        case  SUB:
            return opdL.opd - opdR.opd;
        case  MULT:
            return opdL.opd * opdR.opd;
        case  DIV:
            return opdL.opd / opdR.opd;
        default:
            printf("Error! Passed a non operator as an operator in calcTok()");
            return 0;
    }
}

// calculates the whole token array
double calcTok(Token *tokArr){
    // first loop for high priority operations (multiplication and division)
    while(tokArr[1].type != LAST){
        for(size_t i = 0; tokArr[i].type != LAST; i++){
            if(tokArr[i].opt == MULT || tokArr[i].opt == DIV){
                tokArr[i-1].opd = calcTwoTok(tokArr[i-1], tokArr[i], tokArr[i+1]);
                for(size_t j = i; tokArr[j-1].type != LAST; j++){
                    tokArr[j].type = tokArr[j+2].type;
                    tokArr[j].opt = tokArr[j+2].opt;
                    tokArr[j].opd = tokArr[j+2].opd;
                }
            }
        }

        // second loop for low priority operations (addition and substraction)
        for(size_t i = 0; tokArr[i].type != LAST; i++){
            if(tokArr[i].opt == ADD || tokArr[i].opt == SUB){
                tokArr[i-1].opd = calcTwoTok(tokArr[i-1], tokArr[i], tokArr[i+1]);
                for(size_t j = i; tokArr[j-1].type != LAST; j++){
                    tokArr[j].type = tokArr[j+2].type;
                    tokArr[j].opt = tokArr[j+2].opt;
                    tokArr[j].opd = tokArr[j+2].opd;
                }
            }
        }
        tokArrPrinter(tokArr);
    }
    // handles the case where there is still more then the result token
    if(tokArr[1].type != LAST){
        printf("Error! calcTok failed!\n");
        return 0;
    }
    return tokArr[0].opd;
}
