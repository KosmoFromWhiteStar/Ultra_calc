#include "HEADER.C"
#include <stdio.h>
#include <stdlib.h>

int main(){
    char str[] = "2+3^LOG(x)*1";
    char* str_1 = (char*)calloc(1024, 1);;
    to_polk_notation(str, &str_1);
    printf("%s", str_1);
    free(str_1);
    return 0;
}