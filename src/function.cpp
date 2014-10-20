#include "function.hpp"
#include <memory>

std::shared_ptr<function> function::restrict(mat p, mat v) const{
    class frestr : public function{
    public:
	unsigned dim() const{ return n; }

	frestr(const function &f2, mat point, mat vector) 
	    : fun(f2),origin(point),dir(vector),n(1){
	    if(f2.dim()!=point.n_rows || f2.dim()!=vector.n_rows||
	       point.n_cols!=1        || vector.n_cols!=1       ) 
		throw F_EXCEPTION;
	}
		
	mat _eval (mat point) const{
	    if(point.n_rows!=n || point.n_cols!=1) throw F_EXCEPTION;
	    return fun.eval(origin+point(0,0)*dir);
	}
		
	mat _gradient(mat point) const{
	    if(point.n_rows!=n||point.n_cols!=1) throw F_EXCEPTION;
	    return dir.t()*fun.gradient(origin+point(0,0)*dir);
	}
		
	mat _hessian(mat point) const{
	    if(point.n_rows!=n||point.n_cols!=1) throw F_EXCEPTION;
	    return dir.t()*fun.hessian(origin+point(0,0)*dir)*dir;
	}

    private:
	const function &fun;
	mat origin,dir;
	unsigned n;
    };

    return std::shared_ptr<function>(new frestr(*this,p,v));
}


mat function::eval(mat point) const{
    if(!restrcheck(point)) throw std::exception();
    ++calls[EVAL];
    return _eval(point);
}

mat function::gradient(mat point) const{
    if(!restrcheck(point)) throw std::exception();
    ++calls[GRAD];
    return _gradient(point);
}


mat function::hessian(mat point) const{
    if(!restrcheck(point)) throw std::exception();
    ++calls[HESS];
    return _hessian(point);
}

bool function::restrcheck(const mat&point) const{
    return (point.n_rows==dim() && point.n_cols==1);
}

void function::reset(){
    memset(calls,0,sizeof(calls));
}


unsigned function::calls[3]={0};
