#include"function.hpp"
#include<cmath>

class Rosenbrock: public ::function {
	double a; unsigned n;
public:
	Rosenbrock(double a1){
		char buffer[100]; sprintf(buffer,"%f",a1);
		n=2;a=a1; ((_name+="rosenbrock(")+=buffer)+=")";
	}	
	
	unsigned dim() const{ return n; }

	mat _eval (mat point)const{	
		if(point.n_rows!=n||point.n_cols!=1) throw F_EXCEPTION;	
		mat result({a*pow(point(1,0)-pow(point(0,0),2),2)+
			pow(1-point(0,0),2)});
		return result;
	}

	mat _gradient (mat point) const{
		mat result={4*a*point(0,0)*(pow(point(0,0),2)-point(1,0))+2*(point(0,0)-1),
					2*a*(point(0,0)-pow(point(0,0),2))};
		result.reshape(2,1);
		return result; 
	}

	mat _hessian (mat point) const{
		mat result={12*a*pow(point(0,0),2)-4*a*point(1,0)+2,
					-4*a*point(0,0),
					-4*a*point(0,0),
					2*a};
		result.reshape(2,2);
		return result; 
	}
};
