#include <stdio.h>
#include "io.h"
#include "check.h"
#include "token.h"

int main(void){
    // get input from user
    char *input = promptUser("Write an operation... ");

    // check
    if (isValidOpe(input)){
        // tokenize the operation
        Token *tokArr = inputToTok(input);
        // abort the program ig tokenization fails
        if(tokArr == NULL){
            printf("Error! strToTokArr() failed and returned NULL!\n");
            abort();
        }
        // print the tokenized operation
        tokArrPrinter(tokArr);

        // calculate and print the resutlt
        printf("Your resutlt is: %.2f\n", calcTok(tokArr));

        // free token array
        free(tokArr);
        tokArr = NULL;
    }

    // free input
    free(input);
    input = NULL;

    return 0;
}
