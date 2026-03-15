#include <stdio.h>
#include "io.h"
#include "check.h"
#include "token.h"
#include "sys.h"

double run(double lastResult){
    double result = 0;

    char input[OPERATION_SIZE_LIMIT+1] = {0};
    promptUser(input, sizeof(input), "Write an operation... ");
    if (isValidOperation(input, lastResult)){
        TokenList tokenList = stringToTokenList(input);
        if(tokenList.array == NULL)
            die("Error! strToTokArr() failed and returned NULL!\n");
        tokenArrayPrinter(tokenList.array);

        result = calculateOperation(tokenList);
        printf("Your resutlt is: %.2f\n", result);

        free(tokenList.array);
    }
    return result;
}

int main(void){
    double lastResult = run(0);
    while(1){
        char input[10] = {0};
        promptUser(input, sizeof(input), "Would you like to continue? ([y]es/[n]o) ");
        if(input[0] == 'y')
            lastResult = run(lastResult);
        else if(input[0] == 'n')
            break;
        else
            printf("Please respond with 'y' or 'n'.");
    }
    return 0;
}
