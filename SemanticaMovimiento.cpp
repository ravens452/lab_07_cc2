//****************  Semantica de movimiento **************************************************
#include <cstdio>
#include <iostream>
#include <memory>
using namespace std;

void message(const char*s){
    puts(s);
    fflush(stdout);
}

class Rational {
    int _n = 0;
    int _d = 1;

    static const int _bufsize = 128;
    mutable char * _buf = nullptr;

public:
    Rational (){
        reset();
        message("constructor normal");
    }
    Rational (const int &numerador): _n(numerador),_d(1){
        message("Contructor con 1 Int de entrada");
    }
    Rational (const int &numerador, const int &denominador): _n(numerador),_d(denominador){
        message("Contructor con 2 Int de entrada");
    }
    Rational ( const Rational & rhs ) : _n(rhs._n), _d(rhs._d) {
    message("Constructor copia");}

    Rational(Rational &&); //ESTO HACE QUE EL CONSTRUCTOR SEA DE MOVIMIENTO

    ~Rational ();
    inline int numerator() const { return _n; };
    inline int denominator() const { return _d; };

    Rational & operator = ( const Rational & );

    void reset();
};

Rational & Rational::operator = ( const Rational & rhs ) {
    if( this != &rhs ) {
        _n = rhs.numerator();
        _d = rhs.denominator();
    }
    return *this;
}


Rational::~Rational() {
    _n = 0; _d = 1;
}
//Esta funcion coloca los datos en un estado conocido sino te pondria cualquier numero.
void Rational::reset() {
    _n=0;
    _d=1;
    delete  [] _buf;
    _buf = nullptr;
}

Rational::Rational(Rational && rhs) {
    _n = move(rhs._n);
    _d = move(rhs._d);
    rhs.reset();
    message("Constructor de movimiento");
}

// useful for std::cout
std::ostream & operator << (std::ostream & o, const Rational & r) {
    return o << r.numerator() << '/' << r.denominator();
}

int main( int argc, char ** argv ) {

    Rational a = 7;        // 7/1
    cout << "a is: " << a << endl;
    Rational b(5, 3);    // 5/3
    cout << "b is: " << b << endl;
    Rational c = b;        // constructor copia
    cout << "c is: " << c << endl;
    Rational d = move(c);            // Constructor de movimiento
    cout << "d is: " << d << endl;
    cout <<"c is now:" <<c << endl;
    d = c;                // assignment operator
    cout << "d is: " << d << endl;
    Rational &e = d;    // reference
    d = e;                // assignment to self!
    cout << "e is: " << e << endl;

    return 0;

}
