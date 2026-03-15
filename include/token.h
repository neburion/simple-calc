#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdlib.h>

#define OPERATION_SIZE_LIMIT 1000

static const char VALID_CHARS[]     = "1234567890.+-*/";
static const char VALID_OPERANDS[]  = "1234567890.";
static const char VALID_OPERATORS[] = "+-*/";

#define VALID_CHARS_SIZE     (sizeof(VALID_CHARS) - 1)
#define VALID_OPERANDS_SIZE  (sizeof(VALID_OPERANDS) - 1)
#define VALID_OPERATORS_SIZE (sizeof(VALID_OPERATORS) - 1)

typedef enum{
    OPERAND,
    OPERATOR,
    END
}TokenType;

typedef enum{
    ADD,
    SUB,
    MUL,
    DIV
}OperatorType;

typedef struct{
    TokenType type;
    union{
        OperatorType operator;
        double       operand;
    };
}Token;

typedef struct{
    size_t size;
    Token  *array;
}TokenList;

void      addToken                 (TokenList *tokenArray, Token *newToken);
TokenList stringToTokenList        (char *string);
double    calculateBinaryOperation (Token leftOperand, Token operator, Token rightOperand);
double    calculateOperation       (TokenList tokenArray);

#endif
