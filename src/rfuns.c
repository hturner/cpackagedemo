#include "rfuns.h"
#include "cfuns.h"

/* a wrapper around my_c_sum callable from R */
SEXP my_c_sum_wrapper(SEXP x)
{
    double s;

    if (!Rf_isReal(x)) {
        /* the caller is expected to prepare the arguments
           (doing it at the C level is tedious work) */
        Rf_error("`x` should be a vector of the type 'double'");
    }

    s = my_c_sum(REAL(x), (size_t)XLENGTH(x));

    return Rf_ScalarReal(s);
}


/* a wrapper around my_which_max callable from R */
SEXP my_which_max_wrapper(SEXP x)
{
    int w;
    
    if (!Rf_isReal(x)) {
        /* the caller is expected to prepare the arguments
         (doing it at the C level is tedious work) */
        Rf_error("`x` should be a vector of the type 'double'");
    }
    
    w = my_which_max(REAL(x), (size_t)XLENGTH(x));
    
    return Rf_ScalarInteger(w);
}