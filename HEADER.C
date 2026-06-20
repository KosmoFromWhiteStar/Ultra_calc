#include "HEADER.H"
#include "stdlib.h"


double from_str_to_double(const char* str){
    int dec = 0;
    int manitsa = 0;
    double result = 0;
    int* ptr = &dec;

    for(int i = 0; str[i] != '\0'; ++i){
        if(str[i] == '.'){
            ptr = &manitsa;
            continue;
        }
        *ptr *= 10;
        int temp = str[i] - '0';
        *ptr += temp;
    }
    
    result += dec;
    double _mantisa = manitsa;
    while(_mantisa > 1){
        _mantisa /= 10;
    }
    result += _mantisa;
    return result;
}

///
//Deteminat rang of one parametr
///
int range_function(const char* str, RANGE* par){
    char flag = 0;
    char str_line[1024]; 
    int c = 0;
    double first = 0;
    double second = 0;
    double* ptr = &first;

    for(int i = 0; ; ++i){
        if(str[i] == ' ') continue;
        if((str[i] >= '0' && str[i] <= '9') || str[i] == '.'){
            str_line[c] = str[i];
            c++;
        }else {
            flag >> 1;
            flag++;
            if(flag && c > 1){
                //save point;
                *ptr = from_str_to_double(str_line);
                for(int i = 0; i < c+1; ++i) str_line[i] = 0;
                c = 0;
                ptr = &second;
            }
        }
        if(str[i] == ','){
            ptr = &(par->step);
        }
        if(str[i] == '\0') break;
    }
    par->start_par = first;
    par->end_par = second;
    return 0;
}

int init_function(const char* str){
    if(str[0] != 'f') return -1;
    if(str[1] != '(') return -1;
    RANGE rang;
    char* str_parametrs = calloc(1024, sizeof(char));
    size_t c = 0;
    for(int i = 2; str[i] != '\0'; ++i){
        if(str[i] != ';' || str[i] != ')') str_parametrs[c] = str[i];
        else {
           range_function(str_parametrs, &rang);
           for(int i = 0; i < c+1; ++i)str_parametrs[i] = 0;
           c = 0;
        }
        if(str[i] == '='){
            ++i;
            polk_notation(&(str[i]), NULL);
            break;
        }
        
    }
    free(str_parametrs);
    return 0;
}

int polk_notation(const char* str, NAME* calc){
    char* output = calloc(1024, 1);
    int c_out = 0;
    char* stack = calloc(1024, 1);
    int s_out = 0;
    for(int i = 0; str[i] != '\0'; ++i){
        if(str[i] >= '0' && str[i] <= '9'){
            output[c_out] = str[i];
            c_out++;
        }else{
            
            stack[s_out] = str[i];
            s_out++;
        }
    }
    free(output);
    return 0;
}