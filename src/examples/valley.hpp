#ifndef  _VALLEY_HPP_
#define  _VALLEY_HPP_

#include"function.hpp"
#include<cmath>

class valley: public ::function {
public:
    unsigned dim() const{ return 2; }

    mat _eval (mat point) const{	
	double x=point(0,0),y=point(1,0);
	return {pow(x,4)*cos(x) + pow(y,4)};

    }

    mat _gradient (mat point) const{
	double x=point(0,0),y=point(1,0);
	return mat({4*pow(x,3)*cos(x)-pow(x,4)*sin(x) , (4.0)*pow(y,3.)}).t();

    }

    mat _hessian (mat point) const{
	double x=point(0,0),y=point(1,0);
	mat r({-(8.0)*pow(x,3.0)*sin(x)-pow(x,4.0)*cos(x)+(12.0)*pow(x,2.0)*cos(x),0,
		    0,	(12.0)*pow(y,2.0)});
	r.reshape(2,2);
	return r;
    }
};

#endif // _VALLEY_HPP_
