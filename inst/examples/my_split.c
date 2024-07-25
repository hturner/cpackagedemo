// the necessary header files are automatically included by `csource`

SEXP C_my_split(SEXP x, SEXP f, SEXP n)
{
    if (!Rf_isReal(x)) Rf_error("`x` should be of the type 'double'");
    if (!Rf_isReal(f)) Rf_error("`f` should be of the type 'double'"); //convert fac to numeric in R
    if (!Rf_isInteger(n)) Rf_error("`n` should be of the type 'integer'"); //compute n groups in R
    
    size_t x_len = XLENGTH(x), i, j, k;
    const double *xp = REAL(x), *fp = REAL(f);
    const int *np = INTEGER(n);
    
    // create a list to return
    SEXP split_result = PROTECT(Rf_allocVector(VECSXP, np[0]));
    
    // allocate memory for vector to index each group
    size_t* grp_id = (size_t*)malloc(x_len*sizeof(size_t));  // conservative: as large as x
    if (!grp_id) Rf_error("memory allocation error");
    
    // for each group: 
    for (i = 0; i < np[0]; i++){
        // walk along grouping vector f, save index of values in group
        for (j = 0, k = 0; j < x_len; j++){
            if (!ISNA(fp[j]) && fp[j] == i + 1) // group index starts from 1
                grp_id[k++] = j; 
        }
        
        // create a vector from the indexed elements
        SEXP y = PROTECT(Rf_allocVector(REALSXP, k));
        double* yp = REAL(y);
        for (j = 0; j < k; j++){
            yp[j] = xp[grp_id[j]];  
        }
        
        // allocate to the result list
        SET_VECTOR_ELT(split_result, i, y);
    }
    
    free(grp_id);
    UNPROTECT(np[0] + 1); //each vector plus the list?
    return split_result;
}

/* R
# this chunk will be extracted and executed by `csource`.
my_split <- function(x, f) {
    if (!is.double(x)) x <- as.double(x)
    f <- as.double(as.factor(f))
    n <- as.integer(max(f))
 
    .Call("C_my_split", x, f, n, PACKAGE="my_split")
}
R */
