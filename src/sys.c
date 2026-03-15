#include <stdlib.h>
#include <stdio.h>
#include "sys.h"

void die(char exitMessage[]){
    printf("%s", exitMessage);
    exit(EXIT_FAILURE);
}
