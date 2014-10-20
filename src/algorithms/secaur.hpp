#ifndef _SECAUR_HPP_
#define _SECAUR_HPP_

#include "function.hpp"
#include <cmath>
#include <vector>

const double alpha=0.5*(sqrt(5)-1);
typedef pair<double,double> dd;
typedef std::vector<double> v;

solution secaur(mat A, mat B, const ::function& f,double eps){
    solution sol;
    mat a=A,
	b=B,
	r=a+(1-alpha)*(b-a),
	s=a+alpha*(b-a),
	fr=f.eval(r),
	fs=f.eval(s);

    while(norm(b-a,2) >= eps){
	if(norm(fr,2) <= norm(fs,2)){
	    b=s;
	    s=r;
	    fs=fr;
	    r=a+(1-alpha)*(b-a);
	    fr=f.eval(r);
	    sol.add(r);
	}
	else{
	    a=r;
	    r=s;
	    fr=fs;
	    s=a+alpha*(b-a);
	    fs=f.eval(s);
	    sol.add(s);
	}
    }
    if(norm(fr,2)<=norm(fs,2)) return sol.setsol(r,fr(0,0));
    else return sol.setsol(s,fs(0,0));
}

double testsecaur(double A,double B,double eps){
    class cc:public ::function{
		      unsigned dim() const{ return 1; }
		      mat _eval(mat point) const{ return mat(std::vector<double>(1,point(0,0)*point(0,0))); }
    };
	
    return secaur({A},{B}, cc(), eps).point(0,0);
}

#endif //_SECAUR_HPP_
