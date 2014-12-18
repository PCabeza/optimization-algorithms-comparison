# Optimization algorithms comparison
Authors: Pablo Cabeza García & Paco Criado Gallart

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

Each file holds much documentation from how it is implemented or how
it should work. We used duck typing techniques (with meta-programming
magic) in our testing framework to easy implementing the algorithms
and tests.

### Algorithms

[Algorthms][algorithms] are implemented as inline functions in header
files. Each algorithm returns a [solution][solution] object that holds
the information from the optimization process that we can use to
evaluate the algorithm. Algorithms don't have a common interface,
since we use
[std::bind()](http://en.cppreference.com/w/cpp/utility/functional/bind)
to rewrite the signature of the algorithms in the testing framework.

### Functions

For the [functions][functions] we used a common interface
[function.hpp][function] that all surfaces must inherit from to be
used in our testing framework.

We have implemented some known functions:

- [Rosenbrock][frosenbrock]
- [Gregory-Karney][fgregory]
- [Rastrigin][frastrigin]

And we designed other two functions in order to test some aspects of
the algorithms:

- [Patata][fpatata]: Similar to Rastrigin in the aspect that it has many local
  minimums, but just one global minimum.
  
- [Meseta][fmeseta]: It has local minimums as layers, but no global minimum. With
  it we wanted to how far the algorithms would go.

### Testing framework

The testing framework consists of two files:

- [analysis.hpp][analysis]: holds the logic of testing the algorithms
  against a function and a set of initial points.

- [analysisData.hpp][analysisData]: auxiliary class and functions to help `analysis()`

#### How to use ####

A simple guide to create a test would be:

1. Create an instance of the class `analysis`, it makes use of
   tamplates for types, so an utility function `make_analysis()` can
   be used. The best way to use it is:

		auto instance = make_analysis(algorithm);
2. If the algorithms needs extra parameters like epsilon,
   maxit,... you need to create en instance of `analysisData`. To
   create it you use the function:
   
		analysisData<...> make_adata(par1,string name1, par2, string name2,...);

	The order of parameters in `make_adata` is the same as in the
	algorthm. Parameter `nameN` is there to name columns in the csv
	output.

3. Finally, use `analize()` to test the algorithm. Its prototype is: 

		void analyze( ostream o , 
			function f ,
			container c ,
			analysisData<...> d ,
			bool header
		);


	- `header` indicates whether to print or not a first row with the
      name of columns. It is used to chain different tests in the same
      csv.

	- `container c` is an iterable container of points, for example, a
      vector.

#### Note about algorithm

The `algorithm` in the first points must be of the form `solution
algorithm(const function& f, mat p, ...)`.

- Extra parameters can be any that the algorithm needs, for example
  epsilon, maxit...

- If algorithm doesn't look like this you can use `std::bind()` to
  reorder parameters. For example:

		string foo(int,double,vector<int>);
		auto fun=std::bind(foo, _2 , 0.5 , _1);
		fun(vector<int>() , 5);

	Is equivalent to the call `foo( 5 , 0.5 , vector<int>() )`




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

The results from the tests are stored inn
[result_data][result_data]. There we hold the raw results outputted by
the tests and the their graphs. The name of the data files contains
some of the parameters used in the algorithm in order to trace the
tests. For the graphs, there is a *.R* file that includes the
[plot.R][plotR] command used to plot it, since it is very dependent of
the specific test and function.

Lastly, we have the *LaTeX* used to generate the [report][pdf_file], with a makefile to generate it, in the folder [report_latex][report_latex].



[//]: # "Links section"

[rosenbrock]: <http://en.wikipedia.org/wiki/Rosenbrock_methods#Search_method>
[simplex]: <http://en.wikipedia.org/wiki/Nelder%E2%80%93Mead_method>
[steepest]: <http://en.wikipedia.org/wiki/Gradient_descent>
[newtorraphson]: <http://en.wikipedia.org/wiki/Newton's_method>
[goldensection]: <http://en.wikipedia.org/wiki/Golden_section_search>

[frosenbrock]: </src/examples/rosenbrock.hpp>
[fgregory]: </src/examples/gregory_karney.hpp>
[frastrigin]: </src/examples/rastrigin.hpp>
[fpatata]: </src/examples/patata.hpp>
[fmeseta]: </src/examples/valley.hpp>

[pdf_file]:</doc/report.pdf> "report of the comparison"
[documentation]:</doc>
[function_study]:</doc/function_study>
[result_data]: </doc/result_data>
[report_latex]: </doc/report_latex>

[plotR]: </utilities/plot.R> "plot utility for surfaces for out tests"

[function]: </src/function.hpp>

[algorithms]: </src/algorithms>
[solution]: </src/solution.hpp>
[functions]: </src/examples>

[analysis]: </src/analysis.hpp>
[analysisData]: </src/analysisData.hpp>
