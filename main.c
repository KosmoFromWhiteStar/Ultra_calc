#include "HEADER.C"
#include "stdio.h"

int main(){
    char str[] = "Log(x*2)";
    NAME calc;
    polk_notation(str, &calc);
    return 0;
}