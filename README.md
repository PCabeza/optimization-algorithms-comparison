[rosenbrock]: <http://en.wikipedia.org/wiki/Rosenbrock_methods#Search_method>
[simplex]: <http://en.wikipedia.org/wiki/Nelder%E2%80%93Mead_method>
[steepest]: <http://en.wikipedia.org/wiki/Gradient_descent>
[newtorraphson]: <http://en.wikipedia.org/wiki/Newton's_method>
[goldensection]: <http://en.wikipedia.org/wiki/Golden_section_search>

[pdf_file]: </memoria.pdf> "report of the comparison"


# Optimization algorithms comparison
Authors: Pablo Cabeza & Paco Criado

This project is from the subject *optimization*. The aim of it is to
implement and compare multivariate optimization algorithms and see how
they react against some surfaces.

We have implemented:

* [Rosenbrock algorithm][rosenbrock]
* [Simplex method][simplex]
* [Steepest descent][steepest]
* [Newton-Raphson algorithm][newtorraphson]

Since some of them needed a univariate algorithm, we implemented the
[golden section][goldensection] algorithm.

We have a (very large) [pdf][pdf_file] file with the results of the
comparison. The pdf size is due to high quality vector images used
when plotting the algorithms.

## Compiling it

It makes use of [armadillo](http://arma.sourceforge.net/), a
header-only linear algebra library for c++. You also need an
implementation of [LAPACK](http://www.netlib.org/lapack/) and
[BLAS](http://www.netlib.org/blas/) libraries for it to compile.

When meeting all dependencies, just use `make` to compile it and
generate a *bin* folder with the tester. Use `make help` to find
different options when compiling.

## Source Structure

### Algorithms

### Surfaces

### Testing framework

## Documentation and result structure
