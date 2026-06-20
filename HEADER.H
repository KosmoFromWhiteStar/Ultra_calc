#ifndef __HEADER_H__
#define __HEADER_H__

#define NAME XX
#define size_t long long int

typedef struct DIA{
    double start_par;
    double end_par;
    double step;
}RANGE;

typedef struct HEADER
{
    int(**foo)(double, double, double);
    size_t count_f;
    double** par;
    size_t len;
} NAME;


double from_str_to_double(const char* str);
int range_function(const char* str, RANGE* par);
int init_function(const char* str);
int polk_notation(const char* str, NAME* calc);






#endif // __HEADER_H__