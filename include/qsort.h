#ifndef QSORT_H
#  define QSORT_H
#  ifndef STDLIB_H
#    include "stdlib.h"
#  endif

typedef unsigned char (*qsort_callback)(int, int) ;

int *my_qsort(int*, size_t, qsort_callback);
#endif 
