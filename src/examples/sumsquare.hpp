#include"function.hpp"
#include<cmath>

class sumsquare :public ::function{
	public:
		unsigned n;
	explicit sumsquare(int N=2):n(N){_name="sum(x^2)";}
	unsigned dim() const{ return n; }

	mat _eval (mat point) const{
		double r=0;
		for(unsigned i=0;i<n;++i) r+=(point(i,0)-1)*(point(i,0)-1); 
		return {r};
	}

	mat _gradient (mat point) const{
		mat r(n,1,fill::zeros);
		for(unsigned i=0;i<n;++i) r(i,0)=2*(point(i,0)-1);
		return r;
	}

	mat _hessian (mat point) const{
		mat r(n,n,fill::zeros);
		for(unsigned i=0;i<n;++i) r(i,i)=2;
		return r;
	}
};
