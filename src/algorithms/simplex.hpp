#ifndef _SIMPLEX_HPP_
#define _SIMPLEX_HPP_

#include "function.hpp"
#include "solution.hpp"
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace arma;

typedef vector<mat> vm;
typedef vector<double> vd;

bool stop(vd &fval, double eps)
{
	double med=0, var=0;

	for(unsigned int i=0; i<fval.size(); i++)
		med+=fval[i];
	med/=(fval.size());

	for(unsigned int i=0; i<fval.size(); i++)
		var+=(fval[i]-med)*(fval[i]-med);
	var/=(fval.size());

	return sqrt(var)<eps; //eps al cuadrado porque evaluar con la varianza no es justo para otros algoritmos	
}

solution simplex(const ::function &f, double eps, mat x_0, 
	double alpha=1, double beta=0.5, double gamma=2, double delta=0.5, double s=1)
{	
	assert(alpha>0 && beta>0 && beta<1 && gamma>1 
			&& delta<1 && delta>0&& s>0);
	assert(x_0.n_rows==f.dim() && x_0.n_cols==1);

	solution sol;
	int n=f.dim(), h, l;
	mat A;
	vm simplex;
	vd fval;

	double p=s*(sqrt(n+1)+n-1)/(n*sqrt(2));
	double q=s*(sqrt(n+1)-1)/(n*sqrt(2));

	mat v_med;
	mat v_r, v_e, v_c;
	double f_r, f_e, f_c;

	//Hasta que se diga lo contrario, empezamos en 0
	simplex.push_back(x_0);
	fval.push_back(f.eval(simplex[0])(0,0));
	sol.add(simplex[0], fval[0]);

	for(int i=1; i<=n; i++)
	{
		A.ones(n,1); A=A*q;
		A(i-1,0)=p;
		A=A+simplex[0];
		simplex.push_back(A);
		fval.push_back(f.eval(simplex[i])(0,0)),
		sol.add(simplex[i], fval[i]);
	}

	//for(int i=0; i<=n; i++) cout<<simplex[i]<<endl;
	//cout<<"|||||||||||||||||||||||||||||||||||"<<endl;
	
	while(!stop(fval, eps))
	{
		l=distance(fval.begin(), min_element(fval.begin(),fval.end()));
		h=distance(fval.begin(), max_element(fval.begin(),fval.end()));
		
		v_med.zeros(n,1);
		for(int i=0; i<=n; i++) if(i!=h) v_med+=simplex[i];
		v_med/=n;

		v_r=v_med+alpha*(v_med-simplex[h]); f_r=f.eval(v_r)(0,0); sol.add(v_r, f_r);
		if(fval[l]<=f_r && f_r<fval[h]) //Reflexión
			simplex[h]=v_r, fval[h]=f_r;
		else if(f_r<fval[l]) //Expansión
		{
			v_e=v_med+gamma*(v_r-v_med); f_e=f.eval(v_e)(0,0); sol.add(v_e,f_e);
			if(f_e<fval[l]) simplex[h]=v_e, fval[h]=f_e;
			else simplex[h]=v_r, fval[h]=f_r; 
		}
		else //Contracción
		{
			v_c=v_med+beta*(simplex[h]-v_med), f_c=f.eval(v_c)(0,0), sol.add(v_c, f_c);
			if(f_c<fval[h]) simplex[h]=v_c, fval[h]=f_c;
			else 
				for(int i=0; i<=n; i++) simplex[i]=simplex[l]+(simplex[i]-simplex[l])*delta,
					fval[i]=f.eval(simplex[i])(0,0), sol.add(simplex[i],fval[i]);
		}
		
	//	for(int i=0; i<=n; i++) cout<<simplex[i]<<endl;
	//	cout<<"|||||||||||||||||||||||||||||||||||"<<endl;
	}

	l=distance(fval.begin(),min_element(fval.begin(),fval.end()));
	sol.point=simplex[l];sol.value=fval[l];

	return sol;
}

#endif
