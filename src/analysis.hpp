#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "function.hpp"
#include "analysisData.hpp"


/**
   Class to analyze algorithms in an easy and standard way
 */
template <typename Algorithm>
class analysis{
public:
    analysis(const  Algorithm& alg) :_alg(alg){}


    /**
       Analyzes the a functions optimals using the analysis algorithm
       in the given points, and prints results in csv format

       \param ostr output stream to output the csv
       \param _f function to optimize
       \param ps an iterable container of points
       \param d extra data to pass to the algorithm
       \param pathfiles files to print the path of that certain point
              if, "" nothing will be printed
       \param headers whether a header for the csv should be
              printed or not
     */
    template <class Cont,class NamesCont=vector<string>,typename... Arg>
    void analyze(std::ostream& ostr,const ::function& _f, 
		 const Cont& ps,analysisData<Arg...> d,
		 const NamesCont& pathfiles,
		 bool headers=true){
	
	vector<string> names,values;
	d.headers(names); d.values(values);

	// prepare headers in csv format
	if(headers){
	    ostr << "point;";
	    for(auto str:names) ostr << str << ';';
	    ostr << "path;"
		"eval;"
		"grad;"
		"hess;"
		"diff;"
		"final;"
		"value\n";
	}

	unsigned i=0;
	for(auto p:ps){
	    _f.reset(); // reset counters for algorithm
	    auto sol=d.call(_alg,std::cref(_f),p); // call algorithm
						   // and find solution
	    
	    // print results for this point
	    ostr << print(p) << ';'; 
	    for(auto str:values) ostr << str << ';';
	    ostr << sol.path.size() << ';'
		 << _f.calls[_f.EVAL] << ';'
		 << _f.calls[_f.GRAD] << ';'
		 << _f.calls[_f.HESS] << ';'
		 << _f.eval(p)(0,0)-sol.value << ';'
		 << print(sol.point) << ';'
		 << sol.value << '\n';
	    //maybe add some information about point found


	    if(pathfiles[i]!=""){ //print this path in csv format
		std::ofstream fs(pathfiles[i],std::ofstream::out);

		for(unsigned j=1;j<=p.n_rows;++j){ // csv header
		    if(j!=1) fs << ';'; fs << 'p' << j; }
		fs << '\n';

		for(unsigned j=0;j<p.n_rows;++j){ // initial point
		    if(j!=0) fs << ';'; fs << p(j,0); }
		fs << '\n';

		for( auto pathp: sol.path){ // path
		    for(unsigned j=0;j<pathp.n_rows;++j){
			if(j!=0) fs << ';'; fs << pathp(j,0); }
		    fs << '\n';
		}

		fs.close();
	    } ++i;
	}
    }


    /**
       Analyze method that forwards to the complete version with an
       empty filenames list
     */
    template <class Cont,typename... Arg>
    void analyze(std::ostream& ostr,const ::function& _f, 
		 const Cont& ps,analysisData<Arg...> d,
		 bool headers=true){
	analyze(ostr,_f,ps,d,std::vector<string>(ps.size(),""),headers);
    }


    
private:
    string print(const mat& p){
	std::stringstream ss; ss << '(';
	
	for(unsigned i=0;i<p.n_rows;++i){
	    if(i!=0) ss << ',';
	    ss << p(i,0);
	} ss << ')';
	return ss.str();
    }

    Algorithm _alg;
};



/**
   Helper method to easy the creation of analysis<...> class 

   \param alg the algorithm that will be forwarded to analysis
   constructor
 */
template <typename Algorithm>
analysis<Algorithm> make_analysis(const Algorithm& alg){
    return analysis<Algorithm>(alg);
}
