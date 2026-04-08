#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "token.h"

void printToken(Token token, char *name){
    printf("%s\n", name);
    switch(token.type){
        case OPERAND:
          printf("  type=Operand\n  value=%.2f\n", token.operand);
          break;
        case OPERATOR:{
          char operator;
          switch(token.operator){
            case ADD:
              operator = '+';
              break;
            case SUB:
              operator = '-';
              break;
            case MUL:
              operator = '*';
              break;
            case DIV:
              operator = '/';
              break;
          }
          printf("  type=Operator\n  value=%c\n", operator);
          break;
        }
        case END:
          printf("  type=End\n");
          break;
    }
}

bool tokensAreEqual (Token a, Token b){
    if(a.type     != b.type ||
       a.operand  != b.operand ||
       a.operator != b.operator)
        return false;

    return true;
}

void test_addToken(void){
    printf("================================================================================\n");
    printf("= Testing addToken()\n");
    printf("================================================================================\n");

    Token t0 = {.type = OPERAND,  .operand  = 1};
    Token t1 = {.type = OPERATOR, .operator = ADD};
    Token t2 = {.type = OPERAND,  .operand  = 1};
    Token te = {.type = END};
    Token *tokenArray = NULL;
    TokenList list = {.size = 0, .array = tokenArray};

    printf("List Size (initial)=%zu\n", list.size);
    
    addToken(&list, &t0);
    printf("List Size (after 1 add)=%zu\n", list.size);
    printToken(list.array[0], "token n1");
    assert(list.size == 1);
    assert(tokensAreEqual(t0, list.array[0]));

    addToken(&list, &t1);
    printf("List Size (after 2 adds)=%zu\n", list.size);
    printToken(list.array[1], "token n2");
    assert(list.size == 2);
    assert(tokensAreEqual(t1, list.array[1]));
    
    addToken(&list, &t2);
    printf("List Size (after 3 adds)=%zu\n", list.size);
    printToken(list.array[2], "token n3");
    assert(list.size == 3);
    assert(tokensAreEqual(t2, list.array[2]));

    addToken(&list, &te);
    printf("List Size (after 4 adds)=%zu\n", list.size);
    printToken(list.array[3], "last token");
    assert(list.size == 4);
    assert(tokensAreEqual(te, list.array[3]));

    free(list.array);
    printf("================================================================================\n");
    printf("= Test Passed!\n");
    printf("================================================================================\n");
}

void test_stringToTokenList(void){
    printf("================================================================================\n");
    printf("= Testing stringToTokenList()\n");
    printf("================================================================================\n");

    TokenList list = stringToTokenList("1+1");

    printf("List Size=%zu\n", list.size);
    printToken(list.array[0], "token n1");
    printToken(list.array[1], "token n2");
    printToken(list.array[2], "token n3");
    printToken(list.array[3], "last token");

    assert(list.size == 4);
    assert(list.array[0].type == OPERAND);
    assert(list.array[1].type == OPERATOR);
    assert(list.array[2].type == OPERAND);
    assert(list.array[3].type == END);

    free(list.array);
    printf("================================================================================\n");
    printf("= Test Passed!\n");
    printf("================================================================================\n");
}

void test_calculateBinaryOperation(void){
    printf("================================================================================\n");
    printf("= Testing calculateBinaryOperation()\n");
    printf("================================================================================\n");

    Token t0 = {.type = OPERAND,  .operand  = 1};
    Token t1 = {.type = OPERATOR, .operator = ADD};
    Token t2 = {.type = OPERAND,  .operand  = 1};

    double result = calculateBinaryOperation(t0, t1, t2);
    printf("Result = %.2f\n", result);
    assert(result == 2);

    printf("================================================================================\n");
    printf("= Test Passed!\n");
    printf("================================================================================\n");
}

void test_calculateOperation(void){
    printf("================================================================================\n");
    printf("= Testing calculateOperation()\n");
    printf("================================================================================\n");

    Token t0 = {.type = OPERAND,  .operand  = 1};
    Token t1 = {.type = OPERATOR, .operator = ADD};
    Token t2 = {.type = OPERAND,  .operand  = 1};
    Token te = {.type = END};
    Token tokenArray[] = {t0, t1, t2, te};
    TokenList list = {.size = 0, .array = tokenArray};

    double result = calculateOperation(list);
    printf("Result = %.2f\n", result);
    assert(result == 2);
    
    printf("================================================================================\n");
    printf("= Test Passed!\n");
    printf("================================================================================\n");
}

int main(void) {
    test_addToken();
    printf(".\n.\n.\n");
    test_stringToTokenList();
    printf(".\n.\n.\n");
    test_calculateBinaryOperation();
    printf(".\n.\n.\n");
    test_calculateOperation();
    return 0;
}
