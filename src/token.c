#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "io.h"
#include "sys.h"

void addToken(TokenList *tokenArray, Token *newToken){
    size_t newSize = tokenArray->size + 1;

    Token *tmp = realloc(tokenArray->array, newSize * sizeof(Token));
    if(!tmp) 
        die("Error! Failed to realloc the token array in addToken() when trying to add a new token!");

    tokenArray->array            = tmp;
    tokenArray->array[newSize-1] = *newToken;
    tokenArray->size             = newSize;
}

Token bufferToOperand(char *tokenBuffer){
    Token token = {
        .type = OPERAND,
        .operand = atof(tokenBuffer)
    };
    return token;
}

Token charToOperator(char operator){
    Token token = {
        .type = OPERATOR,
    };
    switch(operator){
        case '+':
            token.operator = ADD;
            break;
        case '-':
            token.operator = SUB;
            break;
        case '*':
            token.operator = MUL;
            break;
        case '/':
            token.operator = DIV;
            break;
    }
    return token;
}

TokenList stringToTokenList(char *string){
    TokenList tokenArray = {
        .size = 0,
        .array = NULL
    };
    size_t    stringSize                        = strlen(string);
    char      tokenBuffer[OPERATION_SIZE_LIMIT] = {0};
    size_t    bufferPosition                    = 0;

    for(size_t i = 0; i < stringSize; i++){
        tokenBuffer[bufferPosition] = string[i];
        bufferPosition++;

        if(string[i+1] == '\0'){
            tokenBuffer[bufferPosition] = '\0';
            Token operandToken = bufferToOperand(tokenBuffer);
            addToken(&tokenArray, &operandToken);

            Token endToken = {.type = END};
            addToken(&tokenArray, &endToken);
            break;
        }
        else if(strchr(VALID_OPERATORS, string[i+1]) != NULL){
            tokenBuffer[bufferPosition] = '\0';
            Token operandToken = bufferToOperand(tokenBuffer);
            addToken(&tokenArray, &operandToken);

            char operator = string[i+1];
            Token operatorToken = charToOperator(operator);
            addToken(&tokenArray, &operatorToken);

            memset(tokenBuffer, 0, bufferPosition);
            bufferPosition = 0;
            i++; // skip the operator since we processed two tokens
        }
    }
    return tokenArray;
}

double calculateBinaryOperation(Token leftOperand, Token operator, Token rightOperand){
    switch(operator.operator){
        case  ADD:
            return leftOperand.operand + rightOperand.operand;
        case  SUB:
            return leftOperand.operand - rightOperand.operand;
        case  MUL:
            return leftOperand.operand * rightOperand.operand;
        case  DIV:
            if(rightOperand.operand != 0)
                return leftOperand.operand / rightOperand.operand;
            else
                die("Error! calculateTwoTokenArray() to divide by zero!");
            return 0;
        default:
            die("Error! Invalid operator in calculateBinaryOperation()!");
            return 0;
    }
}

double calculateOperation(TokenList tokenArray){
    size_t originalSize = tokenArray.size * sizeof(Token);
    TokenList copy = {
        .size = tokenArray.size,
        .array = malloc(originalSize)
    };
    memcpy(copy.array, tokenArray.array, originalSize);

    for(int i = 0; copy.array[1].type != END; i++){
        OperatorType turnA, turnB;
        if(i % 2 == 0)
            turnA = MUL, turnB = DIV;
        else
            turnA = ADD, turnB = SUB;
        for(int j = 1; (size_t)(j+1) < copy.size && copy.array[j+1].type != END; j++){
            if(copy.array[j].operator == turnA || copy.array[j].operator == turnB){
                copy.array[j-1].operand = calculateBinaryOperation(copy.array[j-1], copy.array[j], copy.array[j+1]);
                for(int k = j; (size_t)k + 2 < copy.size && copy.array[k].type != END; k++)
                    copy.array[k] = copy.array[k+2];
                copy.size -= 2;
                j--; // recheck the posision after the shift
                tokenArrayPrinter(copy.array);
            }
        }
    }

    double result = copy.array[0].operand;
    free(copy.array);
    return result;
}
