# Optimization algorithms comparison
Authors: Pablo Cabeza García & Paco Criado Gallart

---

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

### Functions

### Testing framework

## Documentation and result structure

The folder [doc][documentation] contains all the documents we have
prepared to build this comparison, before and after testing the
algorithms, plus the [report][pdf_file] we generated.

In [function_study][function_study] we have information from the
functions we where going to use during testing. For each function we
have its expression, its derivative (computed using octave symbolic
computation) and plots from both the function and the derivative when
it was possible. We used this information to prepare the tests and the
report.

The results from the tests are in [result_data][result_data]. There we
hold the raw results output by the tests and the their graphs. The
name contains some of the parameters used in the algorithm. For the
graphs there is a *.R* file that includes the *plot.R* command used to
plot it, since it is very dependent of the specific test and function.

Lastly, we have the *LaTeX* used to generate the [report][pdf_file], with a makefile to generate it, in the folder [report_latex][report_latex].



[//]: # "Links section"

[rosenbrock]: <http://en.wikipedia.org/wiki/Rosenbrock_methods#Search_method>
[simplex]: <http://en.wikipedia.org/wiki/Nelder%E2%80%93Mead_method>
[steepest]: <http://en.wikipedia.org/wiki/Gradient_descent>
[newtorraphson]: <http://en.wikipedia.org/wiki/Newton's_method>
[goldensection]: <http://en.wikipedia.org/wiki/Golden_section_search>

[pdf_file]:</lemniscata/optimization-algorithms-comparison/master/doc/report.pdf> "report of the comparison"
[documentation]:</lemniscata/optimization-algorithms-comparison/master/doc>
[function_study]:</lemniscata/optimization-algorithms-comparison/master/doc/function_study>
[result_data]: </lemniscata/optimization-algorithms-comparison/master/doc/result_data>
[report_latex]: </lemniscata/optimization-algorithms-comparison/master/doc/report_latex>