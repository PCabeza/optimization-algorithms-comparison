#include"../function.hpp"
#include<cmath>

class Rastrigin :public ::function {
	unsigned n;
public:
	unsigned dim() const{ return n;}
	
	Rastrigin(){n=2;}
	
	mat _eval (mat point) const{
		if(point.n_rows!=n||point.n_cols!=1) throw F_EXCEPTION;
		mat result({point(0,0)*point(0,0)+
					point(1,0)*point(1,0)-
					cos(18*point(0,0))-
					cos(18*point(1,0))});
		return result;
	}
	mat _gradient (mat point) const{
		if(point.n_rows!=n||point.n_cols!=1) throw F_EXCEPTION;
		mat result({2*point(0,0)+ 18*sin(18*point(0,0)),
					2*point(1,0)+ 18*sin(18*point(1,0))});
		result.reshape(2,1);
		return result;
	}
	mat _hessian (mat point) const{
		if(point.n_rows!=n||point.n_cols!=1) throw F_EXCEPTION;
		mat result({2+324*cos(18*point(0,0)),0,
			0,2+324*cos(18*point(1,0))});
		result.reshape(2,2);
		return result;
	}
};
