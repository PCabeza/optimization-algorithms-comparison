#ifndef _NEWTON_RAPHSON_MOD_
#define _NEWTON_RAPHSON_MOD_

#include "function.hpp"
#include "solution.hpp"
#include <cmath>

using namespace std;
using namespace arma;

template <class LINALG>
solution newton_raphson_mod(const ::function &f, double eps,
	mat x_0, const LINALG& lin) {
	assert(eps>0 && x_0.n_rows==f.dim() && x_0.n_cols==1);
	mat c;
	mat x_k=x_0;
	mat g_k=f.gradient(x_k), G_k=f.hessian(x_k), p;
	double f_k=f.eval(x_k)(0,0), lambda_k;
	solution sol; sol.add(x_k, f_k);

	for(int k=0; norm(colvec(g_k), 2)>=eps && k<1000; k++) {
		if(det(G_k)==0) break;
		//c=chol(G_k);//triup
		p=solve(G_k,-g_k); //solve(trimatu(c),solve(trimatl(c.t()),-g_k));
		lambda_k=lin({-1000.0},{1000.0}, *f.restrict(x_k, p), eps).point(0,0);
		x_k+=lambda_k*p;
		f_k=f.eval(x_k)(0,0);
		g_k=f.gradient(x_k);
		G_k=f.hessian(x_k);
		sol.add(x_k, f_k);
	}
	sol.value=f_k;
	sol.point=sol.path.back();
	return sol;
}

#endif
