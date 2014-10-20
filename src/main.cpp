#include <iostream>
#include <functional>

#include "function.hpp"
#include "solution.hpp"
#include "analysis.hpp"
#include "analysisData.hpp"

#include "algorithms/secaur.hpp"
#include "algorithms/rosenbrock.hpp"
#include "algorithms/simplex.hpp"
#include "algorithms/steepest_descent.hpp"
#include "algorithms/newraphsmod.hpp"

#include "examples/rosenbrock.hpp"
#include "examples/sumsquare.hpp"
#include "examples/valley.hpp"
#include "examples/patata.hpp"
#include "examples/rastrigin.hpp"
#include "examples/gregory_karney.hpp"

/*

  Guía para tontos (o no tan tontos) de cómo hacer test y sacar
  resultados.

  Lo primero es como crear una instancia de la clase analysis, como
  usa templates para el tipo algoritmo, he creado una función
  make_analysis() que devuelve ya la instancia creada, lo mejor es
  usarla con auto:

  auto instance=make_analysis(algorithm);

  Este "algorithm" debe de tener la pinta siguiente:

  solution algorithm(const function& f, mat p, ...);

  Los puntos suspensivos son otros parámetros que pueda necesitar el
  algoritmo, como el épsilon,maxit,....

  Si el algoritmo ya tiene esta pinto, hemos acabado, se lo pasamos y
  punto. Si no es el caso, lo mejor es usar std::bind(). La pinta de
  esta función es:

  std::function std::bind( F, P1,P2,P3,P4,...)

  Es decir, devuelve un objeto de tipo función (tiene el operator()) y
  al llamarlo lo llama con los parámetros P1,P2,P3: F(P1,P2,P3,...)

  Para que el objeto std::function que devuelve pueda recibir
  parámetros, se usan los "placeholders" _1,_2,_3,... que representan
  los parámetros de entrada 1,2,3,... Así por ejemplo:

  string foo(int,double,vector<int>);
  auto fun=std::bind(foo, _2 , 0.5 , _1);
  fun(vector<int>() , 5);

  Es equivalente a la llamada:

  foo( 5 , 0.5 , vector<int>() );

  De esta forma se puede modificar el orden de los parámetros o pasar
  parámetros por defecto a la clase analysis

  *Nota1: si quieres que algún parámetro sea una referencia tienes
  que usar std::ref() o std::cref() para encapsular el
  parámetro


  El método analize() es más sencillo, su prototipo es:

  void analyze( ostream o , 
  function f ,
  container c ,
  analysisData<...> d ,
  bool header );

  El parámetro más extraño es analysisData<...>, este parámetro está
  aquí para pasar parámetros extra al algoritmo, como épsilon,
  maxit... para generarlo hay un método auxliar que lo genera de
  forma sencilla:

  analysisData<...> make_adata(par1,string name1, par2, string name2,...);

  El orden de los parámetro es en el que se le pasaran al
  algoritmo. Los parámetros nameN están para que aparezca en el csv
  los valores de parN, en una columna llamada nameN (ver ejemplos).

  El resto de parámetros son normales: 

  header es un booleano que indica si se imprime una cabecera con los
  nombre de las columnas, está para encadenar más de una prueba en un
  mismo csv.

  container c es un contenedor con iteradores, es decir, un vector de
  puntos o algo similar

  Con esta "breve" guía de como hacer ejemplos "cualquiera" que se
  moleste en leerla debería poder hacer sus propia pruebas.

  Para cualquier duda contactar con lemniscata<lemniscata.lmn@gmail.com>

*/


using namespace std;

const double PI=acos(-1);

int main(int argc, char **argv){
    using namespace std::placeholders;

    vector<mat> rosenp({
	    mat({0,0}).t(),
		mat({10,-10}).t(),
		mat({0,10}).t(),
		mat({-1,1}).t()
		});

    vector<mat> rastriginp({
	    mat({2,2}).t(),
		mat({PI/9,PI/9}).t(),
		mat({PI/3,2*PI/9}).t(),
		mat({6,6}).t()
		});

    vector<mat> gregory2p({
	    mat({4,4}).t(),
		mat({-4,-4}).t(),
		mat({4,-4}).t()});

    vector<mat> gregory3p({
	    mat({0,0,0}).t(),
		mat({3,3,3}).t()});

    vector<mat> gregory5p({
		mat({0,0,0,0,0}).t(),
		mat({5,5,5,5,5}).t()
		});

    vector<mat> patatap({
	    mat({0.001,10}).t(),
		mat({10,10}).t(),
		mat({10,0}).t()});


    Rosenbrock rosen(100);
    Rastrigin rastri;
    Gregory_Karney gre2(2), gre3(3),gre5(5);
    patata pat;

    // create analysis clases for different algorithms
    auto arosen=make_analysis(std::bind(rosenbrock<decltype(secaur)>,
    					std::placeholders::_2 , // point
    					_3, // eps
    					_4, //maxit
    					std::placeholders::_1, // function
    					std::ref(secaur)));

    auto asimplex=make_analysis(std::bind(simplex,
    					  std::placeholders::_1 , // function
    					  _3, // eps
    					  std::placeholders::_2, // point
    					  _4, // alpha
    					  _5, // beta
    					  _6, // gamma
    					  _7, // delta
    					  _8)); // a


    auto anewt=make_analysis(std::bind(newton_raphson_mod<decltype(secaur)>,
    					  std::placeholders::_1 , // function
    					  _3, // eps
    					  std::placeholders::_2, // point
    					  std::ref(secaur)));


    auto asteep=make_analysis(std::bind(steepest_descent<decltype(secaur)>,
					  std::placeholders::_1 , // function
					  _3, // eps
					  std::placeholders::_2, // point
					  std::ref(secaur)));


    cout << "testing rosenbrock algorithm with patata function" << endl;
    arosen.analyze(cout,
    		   pat,
    		   patatap,
    		   make_adata(0.0005,"eps",10000,"maxit"),
    		   {"","","",""});


    cout << "\n\ntesting steepest descent algorithm with patata function" << endl;
    asteep.analyze(cout,
    		  pat,
    		  patatap,
    		  make_adata(0.0005,"eps"),
    		  {"","","",""});



    cout << "\n\ntesting newton-raphson algorithm with gregory-karney function" << endl;
    anewt.analyze(cout,
    		  gre2,
    		  gregory2p,
    		  make_adata(0.0005,"eps"),
    		  {"","","",""});
    anewt.analyze(cout,
    		  gre3,
    		  gregory3p,
    		  make_adata(0.0005,"eps"),
    		  {"","","",""},false);
    anewt.analyze(cout,
    		  gre5,
    		  gregory5p,
    		  make_adata(0.0005,"eps"),
    		  {"","","",""},false);
        

    cout << "\n\ntesting steepest descent algorithm with gregory-karney function" << endl;
    asteep.analyze(cout,
    		  gre2,
    		  gregory2p,
    		  make_adata(0.0005,"eps"),
    		  {"","","",""});
    asteep.analyze(cout,
    		  gre3,
    		  gregory3p,
    		  make_adata(0.0005,"eps"),
    		  {"","","",""},false);
    asteep.analyze(cout,
    		  gre5,
    		  gregory5p,
    		  make_adata(0.0005,"eps"),
    		  {"","","",""},false);
    


    cout << "\n\ntesting rosenbrock algorithm with rosenbrock function" << endl;
    arosen.analyze(cout,
    		   rosen,
    		   rosenp,
    		   make_adata(0.0005,"eps",10000,"maxit"),
    		   {"","","",""});



    cout << "\n\ntesting simplex algorithm with rosenbrock function" << endl;
    asimplex.analyze(cout,
    		     rosen,
    		     rosenp,
    		     make_adata(0.0005,"eps",
    				1, "alpha",
    				0.5,"beta",
    				2,"gamma",
    				0.5,"delta",
    				1,"s"),
    		     {"","","",""}
    		     );




    cout << "\n\ntesting simplex algorithm with rastrigin function" << endl;
    asimplex.analyze(cout,
    		     rastri,
    		     rastriginp,
    		     make_adata(0.0005,"eps",
    				1, "alpha",
    				0.5,"beta",
    				2,"gamma",
    				0.5,"delta",
    				1,"s"),
    		     {"","","",""}
    		     );

    cout << "\n\ntesting newton-raphson algorithm with ratrigin function" << endl;
    anewt.analyze(cout,
    		   rastri,
    		   rastriginp,
    		   make_adata(0.0005,"eps"),
    		   {"","","",""});



    return 0;
}


/// Local Variables:
/// compile-command: "cd ..; make"
/// End:
