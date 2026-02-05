#ifndef TOKEN_H_
#define TOKEN_H_
#include <stdlib.h>

typedef enum TokType_T {
    OPED, OPET, LAST
} TokType;

typedef enum OptType_T {
    NOT, ADD, SUB, MULT, DIV
} OptType;

typedef struct Token_T{
    TokType type;
    OptType opt;
    double opd;
} Token;

Token *inputToTok(char *input);
void addTok(Token **tokArr, size_t newSize, Token *tok);
double calcTok(Token *tokArr);

#define OPERATION_MAX_SIZE 1000

extern const char VALID_CHARS_LIST[];
extern const size_t VALID_CHARS_LIST_SIZE;

extern const char OPERANDS_LIST[];
extern const size_t OPERANDS_LIST_SIZE;

extern const char OPERATORS_LIST[];
extern const size_t OPERATORS_LIST_SIZE;

#endif
