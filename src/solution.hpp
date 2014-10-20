#ifndef SOLUTION_H
#define SOLUTION_H
#include "function.hpp"

#include<armadillo>
#include<vector>

using namespace std;
using namespace arma;

struct solution{
    mat point;
    double value;
	
    vector<mat> path;
    vector<double> pvalues;


    solution& add(mat p,double v=numeric_limits<double>::quiet_NaN()){ 
	path.push_back(p); 
	pvalues.push_back(v);
	return *this; 
    }
    solution& setsol(mat p,double v){ point=p; value=v; return *this; }
    solution& setsol(const ::function& f){ point=path.back(); value=f.eval(point)(0,0); return *this; }
};
#endif
