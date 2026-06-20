#ifndef __Ultra_calc_H__
#define __Ultra_calc_H__

#define NAME calc

typedef struct{
    double start_par;
    double end_par;
    double step;
}RANGE;

typedef struct
{
    int(**foo)(double, double, double);
    int count_f;
    double** par;
    int len;
} NAME;

double from_str_to_double(const char* str);
int range_function(const char* str, RANGE* par);
int init_function(const char* str);
int to_polk_notation(const char* str, char** _output);


#endif // __HEADER_H__