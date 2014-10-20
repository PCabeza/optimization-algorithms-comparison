#ifndef FUNCTION_H
#define FUNCTION_H 
#define F_EXCEPTION 42 

#include <armadillo>

#include <iostream>
#include <memory>
#include <string>

// function class: it represent the function to be optimizated
// It should check that the point is a (nx1) matrix, throw 
// an exception else

using namespace arma;

class function{
 public:
    virtual ~function(){}
    virtual unsigned dim() const=0;
    
    mat eval(mat point) const;
    virtual mat _eval(mat point) const=0;


    /** Default empty implementation */
    mat gradient(mat point) const;
    virtual mat _gradient(mat point) const{ return mat(); }; 		

    /** Default empty implementation */
    mat hessian(mat point) const;
    virtual mat _hessian(mat point) const{ return mat(); };

    /** Restrict the function to a line */
    std::shared_ptr<function> restrict(mat p, mat v) const;

    bool restrcheck(const mat&p) const;
    static void reset();
    const std::string& name() const{ return _name; }

    enum { EVAL=0,GRAD=1,HESS=2 };
    static unsigned calls[3];
    std::string _name;
};
#endif
