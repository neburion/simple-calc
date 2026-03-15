#ifndef IO_H_
#define IO_H_
#include "token.h"

void promptUser        (char *buffer, size_t size, char prompt[]);
void tokenArrayPrinter (Token *tokenArray);

#endif
