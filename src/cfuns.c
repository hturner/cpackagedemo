#include "cfuns.h"

/* computes the sum of all elements in an array x of size n */
double my_c_sum(const double* x, size_t n)
{
    double s = 0.0;
    for (size_t i = 0; i < n; ++i) {
        /* this code does not treat potential missing values specially
           (they are kinds of NaNs); to fix this, add:
        if (ISNA(x[i])) return NA_REAL;  // #include <R.h>  */
        s += x[i];
    }
    return s;
}

/* computes the index of the greatest element in a numeric vector. */
int my_which_max(const double* x, size_t n)
{
    int w = 0;
    double v = x[0];
    
    for (size_t i = 1; i < n; i++) {
        /* this code does not handle NAs */
        if (x[i] > v) {
            v = x[i];
            w = i;
        }
    }
    return w + 1; /* add 1 for 1-based indexing */
}
