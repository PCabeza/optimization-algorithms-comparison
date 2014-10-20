#include"../function.hpp"
#include<cmath>

class Gregory_Karney :public ::function {
	unsigned n;
	mat ev, gr;
public:
	unsigned dim() const{return n;}

	Gregory_Karney(unsigned n1){
		n=n1;
		ev=mat(n,n,fill::zeros);
		gr=mat(n,n,fill::zeros);
	
		ev(0,0)=1; gr(0,0)=2;
		for(unsigned i=1; i<n; i++)
		{
			ev(i,i)=2;
			ev(i-1,i)=ev(i,i-1)=-1;
			gr(i,i)=4;
			gr(i,i-1)=gr(i-1,i)=-2;
		}
	}
	mat _eval (mat point) const{
		if(point.n_rows!=n||point.n_cols!=1) throw F_EXCEPTION;
		mat res=point.t()*ev*point;
		res(0,0)-=2*point(0,0);

		return res;
	}
	mat _gradient (mat point) const{
		if(point.n_rows!=n||point.n_cols!=1) throw F_EXCEPTION;
		mat res=gr*point;
		res(0,0)-=2;
	
		return res;
	}
	mat _hessian (mat point) const{
		if(point.n_rows!=n||point.n_cols!=1) throw F_EXCEPTION;
		return gr;
	}
};

