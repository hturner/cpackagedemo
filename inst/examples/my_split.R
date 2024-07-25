source("inst/examples/csource.R")  # defines csource
csource("inst/examples/my_split.c")

x <- 1:10
f <- rep(1:3, c(3, 3, 4))

my_split(x, f)

my_split(c(1, 3, 7, 9, 8), c(1, 2, 1, 1, 2))

my_split(c(1, 3, NA, 9, 8), c(1, 2, 1, 1, 2))

## This doesn't work
my_split(c(1, 3, NA, 9, 8), c(1, 2, 1, NA, 2))

x <- sample(1:1e6, 1e4, replace = TRUE)
f <- sample(1:5, 1e4, replace = TRUE)
bench::mark(unname(split(x, f)), my_split(x, f))


## base::split is nearly twice as fast
bench::mark(unname(split(x, f)), my_split(x, f))