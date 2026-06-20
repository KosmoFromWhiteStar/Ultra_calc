#include "Ultra_calc.h"
#include <stdlib.h>
#include <stdio.h>

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

int priorety (char _operator){
    int res = 0;
    switch (_operator)
    {
    case '+':
    case '-': res = 0; break;
    case '*':
    case '/': res = 1; break;
    case 's': //sin
    case 'a': //argsin
    case 't': //tan
    case 'g': //ctan
    case 'l': //LOG10
    case 'c': res = 2; break; //cos
    case '^': res = 3; break; 
    case '(':
    case ')': res = 4; break; 
    default:
        res = -1;
        break;
    }
    return res;
}

char find_foo(const char* str){
   char res = 0;
   
   return res;
}

///
//Determinate rang of one parametr
///
int range_function(const char* str, RANGE* par){
    char flag = 0;
    char str_line[1024]; 
    int c = 0;
    double* ptr = &(par->start_par);

    for(int i = 0; ; ++i){
        if(str[i] == ' ') continue;
        if((str[i] >= '0' && str[i] <= '9') || str[i] == '.'){
            str_line[c] = str[i];
            c++;
        }else {
            flag >>= 1;
            flag++;
            if(flag && c > 1){
                //save point;
                *ptr = from_str_to_double(str_line);
                for(int i = 0; i < c+1; ++i) str_line[i] = 0;
                c = 0;
                ptr = &(par->end_par);
            }
        }
        if(str[i] == ','){
            ptr = &(par->step);
        }
        if(str[i] == '\0') break;
    }
    return 0;
}

int init_function(const char* str){
    if(str[0] != 'f') return -1;
    if(str[1] != '(') return -1;
    RANGE rang;
    char* str_parametrs = (char*) (char*)calloc(1024, sizeof(char));
    int c = 0;
    for(int i = 2; str[i] != '\0'; ++i){
        if(str[i] != ';' || str[i] != ')') str_parametrs[c] = str[i];
        else {
           range_function(str_parametrs, &rang);
           for(int i = 0; i < c+1; ++i)str_parametrs[i] = 0;
           c = 0;
        }
        if(str[i] == '='){
            ++i;
            to_polk_notation(&(str[i]), NULL);
            break;
        }
        
    }
    free(str_parametrs);
    return 0;
}

int to_polk_notation(const char* str, char** _output){
    char* output = (char*)calloc(1024, 1);
    int c_out = 0;
    char* stack = (char*)calloc(1024, 1);
    int s_out = 0;
    char* math_foo = (char*)calloc(20, 1);
    int math_c = 0;
    for(int i = 0; str[i] != '\0'; ++i){
        if((str[i] >= '0' && str[i] <= '9') || (str[i]  == 'x')){
            output[c_out] = str[i];
            c_out++;
        }else if((str[i] >= 'a' && str[i] <= 'z')){
            math_foo[math_c] = str[i];
            math_c++;
        }else{
            char temp = str[i];
            if(math_c != 0){
                temp = find_foo(math_foo);
            }

            for(; priorety(temp) <= priorety(stack[s_out - 1]); --s_out){
                output[c_out] = stack[s_out - 1];
                stack[s_out - 1] = 0;
                (c_out)++;
            }
            output[c_out] = ' ';
            c_out++;

            stack[s_out] = temp;
            s_out++;
        }
    }

    for(int i = s_out-1; i >= 0; --i){
        output[c_out] = stack[i];
        c_out++;
    }
    
    *(_output) = output;
    free(stack);
    free(math_foo);
    return 0;
}