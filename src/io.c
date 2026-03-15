#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "io.h"
#include "token.h"

void promptUser(char *buffer, size_t size, char prompt[]){
    printf("%s", prompt);
    if(fgets(buffer, size, stdin) == NULL)
        buffer[0] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';
}

void tokenArrayPrinter(Token *tokenArray){
    for(size_t i = 0; tokenArray[i].type != END; i++){
        if(tokenArray[i].type == OPERAND)
    	    printf("[%.2f]", tokenArray[i].operand);

        else if(tokenArray[i].type == OPERATOR){
            switch(tokenArray[i].operator){
                case  ADD:
                    printf("[+]");
                    break;
                case  SUB:
    	            printf("[-]");
                    break;
                case  MUL:
    	            printf("[*]");
                    break;
                case  DIV:
    	            printf("[/]");
                    break;
                default:
    	            printf("[BUG]");
                    break;
            }
        }
    }
    printf("\n");
}
