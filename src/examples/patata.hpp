#ifndef  _PATATA_HPP_
#define  _PATATA_HPP_

#include"function.hpp"
#include<cmath>

class patata: public ::function {
public:
    unsigned dim() const{ return 2; }

    mat _eval (mat point) const{	
	double x=point(0,0),y=point(1,0);
	return {(pow(y,2))/10 + cos((pow(x,2) + pow(y,2))/2)/4 -1/(pow(x,2) + pow(y,2) + 1)};

    }

    mat _gradient (mat point) const{
	double x=point(0,0),y=point(1,0);
	return mat({-(0.25)*x*sin((0.5)*pow(y,2.0)+(0.5)*pow(x,2.0))+(2.0)*x*pow((1.0+pow(y,2.0)+pow(x,2.0)),(-2)) ,
		    (0.2)*y-(0.25)*sin((0.5)*pow(y,2.0)+(0.5)*pow(x,2.0))*y+(2.0)*pow((1.0+pow(y,2.0)+pow(x,2.0)),(-2))*y}).t();
    }

    mat _hessian (mat point) const{
	double x=point(0,0),y=point(1,0);
	mat r({
		-(8.0)*pow(x,2)*pow((1.0+pow(y,2.0)+pow(x,2.0)),(-3))+(2.0)*pow((1.0+pow(y,2.0)+pow(x,2.0)),(-2))-(0.25)*sin((0.5)*pow(y,2.0)+(0.5)*pow(x,2.0))-(0.25)*pow(x,2)*cos((0.5)*pow(y,2.0)+(0.5)*pow(x,2.0)),
		    -(8.0)*x*pow((1.0+pow(y,2.0)+pow(x,2.0)),(-3))*y-(0.25)*x*y*cos((0.5)*pow(y,2.0)+(0.5)*pow(x,2.0)),
		    -(8.0)*x*pow((1.0+pow(y,2.0)+pow(x,2.0)),(-3))*y-(0.25)*x*y*cos((0.5)*pow(y,2.0)+(0.5)*pow(x,2.0)),
		    0.2+(2.0)*pow((1.0+pow(y,2.0)+pow(x,2.0)),(-2))-(0.25)*sin((0.5)*pow(y,2.0)+(0.5)*pow(x,2.0))-(0.25)*pow(y,2)*cos((0.5)*pow(y,2.0)+(0.5)*pow(x,2.0))-(8.0)*pow((1.0+pow(y,2.0)+pow(x,2.0)),(-3))*pow(y,2)});
	r.reshape(2,2);
	return r;
    }
};

#endif // _PATATA_HPP_
