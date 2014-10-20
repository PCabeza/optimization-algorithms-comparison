#ifndef _ROSENBROCK_HPP_
#define _ROSENBROCK_HPP_

#include "function.hpp"
#include "solution.hpp"

#include <iostream>
using namespace std;

/**
   The algorithm to find the minimum of rosebrock

   \param x0 the initial point of the search
   \param eps the epsilon for the stop criteria
   \param maxit the maximum num of iterations to forbid cycles
   \param f the function to minimize
   \param lin the algorithm to minimize in a segment, the format must be 
   	solution lin(double A,double B,const function& f, double eps);
	it searches the minimum in [A,B] of f
*/
template <class LINALG>
inline solution rosenbrock(mat x0, double eps, int maxit,const ::function& f, const LINALG& lin){
    solution solu; int k=0; double val=numeric_limits<double>::quiet_NaN();
    vector<mat> y(f.dim()+1,x0);
    vector<mat> dirs(f.dim(), mat(f.dim(),1,fill::zeros));
    vector<mat> a(f.dim());
    vector<double> lambda(f.dim());

    // cout << "initial point: " << x0 << endl<<endl;
    for(unsigned i=0;i<f.dim();++i) dirs[i](i,0)=1; //initialize directions
    for(;k<maxit;++k){
	for(unsigned i=0;i<f.dim();++i){
	    auto ret=lin({-1000.0},{1000.0},*f.restrict(y[i],dirs[i]),eps); //TODO what limits to lin?
	    y[i+1]=y[i]+(lambda[i]=ret.point(0,0))*dirs[i];
	    if(i==f.dim()) val=ret.value;
	}
	solu.add(y[f.dim()],val);
	// cout << "solution " << solu.path.size() << ": " << y[f.dim()]<<endl<<endl;
	if(k!=0) if(norm(colvec(solu.path.back()-solu.path[solu.path.size()-2]),2)<eps) break; //TODO check also if f->0
	
	for(unsigned i=0;i<f.dim();++i){
	    a[i]=(lambda[i]==0) ? dirs[i]: [&](){ //lambda to calc sum of dirs
		mat res(f.dim(),1,fill::zeros);
		for(unsigned j=i;j<f.dim();++j) res+=lambda[j]*dirs[j];
		return res;
	    }();

	    mat aux=(i==0) ? a[i] : a[i]-[&](){ //lambda to calc sum for bj
		mat ret(f.dim(),1,fill::zeros);
		for(unsigned j=0;j<i;j++) ret+= mat(a[i].t()*dirs[j])(0,0)*dirs[j];
		return ret;
	    }();
	    dirs[i]=aux/norm(colvec(aux),2);
	}
    }
    // cout << "path is " << solu.path.size() << endl;
    return solu.setsol(f);
}

#endif //_ROSENBROCK_HPP_
