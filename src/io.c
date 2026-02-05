#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "io.h"
#include "token.h"

// prompts the user for an input with a custom prompt
char *promptUser(char prompt[]){
    // prints the message that asks the user for input
    printf("%s", prompt);

    // initializing the input buffer
    char buffer[2000] = {0};
    // getting user inpuet and writing it to a buffer
    if(fgets(buffer, sizeof(buffer), stdin) == NULL){
        printf("Error! NULL input received!");
        return NULL; //return NULL if fgets is null
    }
    
    // getting buffer size
    size_t strSize = strlen(buffer);
    // null terminting the buffer
    buffer[strSize - 1] = '\0';

    // allocating memory for input
    char *input = malloc(strSize + 1);
    // transefer string from buffer to input
    strcpy(input, buffer);

    return input;
}

// Prints the token array to the terminal
void tokArrPrinter(Token *tokArr){
    // loops through the entire array
    for(size_t i = 0; tokArr[i].type != LAST; i++){
        // if the current token is an operand print it with a .2 decimal point precision
        if(tokArr[i].type == OPED){
    	    printf("[%.2f]", tokArr[i].opd);
        }
        // if the token is an operator print it's corresponding character
        else if(tokArr[i].type == OPET){
            switch(tokArr[i].opt){
                case  ADD:
                    printf("[+]");
                    break;
                case  SUB:
    	            printf("[-]");
                    break;
                case  MULT:
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
