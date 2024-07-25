my_which_max <- function(x)
{
    # prepare input data:
    if (!is.double(x))
        x <- as.double(x)
    
    .Call("my_which_max_wrapper", x, PACKAGE="cpackagedemo")
}