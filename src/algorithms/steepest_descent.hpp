#ifndef _STEEPEST_DESCENT_HPP_
#define _STEEPEST_DESCENT_HPP_

#include "function.hpp"
#include "solution.hpp"

using namespace std;
using namespace arma;

template <class LINALG>
solution steepest_descent(const ::function &f, double eps, mat x_0,
	const LINALG& lin) {
	assert(eps>0 && x_0.n_cols==1 && x_0.n_rows==f.dim());
	mat x_k=x_0;
	mat g_k=f.gradient(x_k), p;
	double f_k=f.eval(x_k)(0,0), lambda_k;
	solution sol; sol.add(x_k, f_k);

	for(int k=0; norm(colvec(g_k), 2)>=eps && k<1000; k++) {
		p=-g_k;
		lambda_k=lin({0}, {1000.0}, *f.restrict(x_k, p), eps).point(0,0);
		x_k+=lambda_k*p;
		f_k=f.eval(x_k)(0,0);
		g_k=f.gradient(x_k);
		sol.add(x_k, f_k);
	}
	sol.point=sol.path.back();
	sol.value=f_k;
	return sol;
}
#endif 
