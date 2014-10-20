#ifndef _ANALYSISDATA_HPP_
#define _ANALYSISDATA_HPP_

#include <string> // for attributes names
#include <sstream> // for analysisData::values() call

class solution; // forward declaration of class solution


/**
   analysisData is a special class to pass extra parameters to the Analysis
   algorithm and make them available in the output of the Analysis

   Always use make_adata to build an analysisData as follows:
      auto data=make_adata(1000,"maxit",0.005,"epsilon");
      data.call(algo,par1,par2,...);

   This will call algo(par1,par2,...,1000,0.005);

 */
template <typename... Arg>
class analysisData{
public:
    template<class F,typename... Param>
    solution call(F&&f,Param... params){
	return f(params...);
    }

    template <class T> void values(const T&t){}
    template <class T> void headers(const T& t){}
};


/**
   Specialization of analysisData, the actual class
 */
template <typename T1, typename STR,typename... Arg>
class analysisData<T1,STR,Arg...>{
public:
    template<typename... Params>
    analysisData(const T1& t1,const STR& n1,Params... args)
	:value(t1),name(n1),tail(args...){
    }

    template<class F,typename...Param>
    solution call(F && f,Param... params){
	return tail.call(f,params...,value);
    }

    template <typename Cont>
    Cont& headers(Cont& v){
	v.push_back(name);
	tail.headers(v);
	return v;
    }

    template <typename Cont>
    Cont& values(Cont& v){
	std::stringstream ss; ss << value;
	v.push_back(ss.str());
	tail.values(v);
	return v;
    }


    enum {size=sizeof...(Arg)/2+1};
    typedef T1 type;
    typedef analysisData<Arg...> dtail;
    T1 value;
    std::string name;
    analysisData<Arg...> tail;
};



namespace AData{

    /**
       Helper class type_getter, that gets the type of the ith data element
     */
    template <unsigned i, class T> struct type_getter;

    template <unsigned i,typename HeadType, typename HeadName,typename... T> 
    struct type_getter<i,analysisData<HeadType,HeadName,T...> >{
	typedef typename type_getter<i-1,analysisData<T...> >::type type;
    };

    template <typename HeadType, typename HeadName,typename... T> 
    struct type_getter<0,analysisData<HeadType,HeadName,T...> >{
	typedef HeadType type;
    };




    /**
       Helper class that retrieves the value of the ith data element<br>
       it shall be used as follows:<br>
       	    value_getter<i>::get(t);
       where t is an analysisData instance.
     */
    template <unsigned i>
    struct value_getter{
	template<typename... Arg>
	static typename type_getter<i,analysisData<Arg...> >::type
	get(const analysisData<Arg...>& t){
	    return value_getter<i-1>::get(t.tail);
	}
    };

    template <>
    struct value_getter<0>{
	template<typename... Arg>
	static typename type_getter<0,analysisData<Arg...> >::type
	get(const analysisData<Arg...>& t){
	    return t.value;
	}
    };


    /**
       Retrieves the ith value of an analysisData instance<br>
       	Use: get<i>(t);

       \param t the data from where to get the value
       \return the value with its corresponding type
     */
    template <unsigned i,typename... Arg>
    typename type_getter<i,analysisData<Arg...> >::type 
    get(const analysisData<Arg...>& t){
	return value_getter<i>::get(t);
    }
}



/**
   Method to generate an analysisData instance in an easy way.<br>
   	Call as: make_adata(value1,name1,value2,name2,...);
   \param args the package of arguments forwarded to analisysData
   	constructor
   \return the analysisData instance
 */
template <typename...Args>
analysisData<Args...> make_adata(Args... args){
    return std::forward<analysisData<Args...> >(analysisData<Args...>(args...));
}



#endif // _ANALYSISDATA_HPP_
