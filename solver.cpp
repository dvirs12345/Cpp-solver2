// Author - Dvir Sadon
#include "solver.hpp"
#include <iostream>
#include <string>
#include <complex>
#include <math.h>
#define EPSILON 0.0001
using namespace std;
using namespace solver;

namespace solver
{
    double solve(const RealVariable &x) 
    { 
        double ans1;
        double ans2;
        if(x.a == 0 && x.b == 0)
            throw NoAnswer();
        if(x.a>0 && x.b == 0 && x.c > 0)
            throw NoAnswer();
        else if(x.a == 0)
        {
            if(abs(x.c) <= 0.0001) // handle negative 0
                return 0;
            return (-1)*(x.c/x.b);
        }
        else // Quadriatic equation 
        {
            double below = ((x.b*x.b)-(4*x.a*x.c));
            if(below < 0)
                throw NoAnswer();
            else
            {
                ans1 = ((-1)*x.b+sqrt(below))/(2*x.a);
                ans2 = ((-1)*x.b-sqrt(below))/(2*x.a);
            }
        }

        double toreturn = max(ans1,ans2);
        return toreturn;
    }
    complex<double> solve(const ComplexVariable &x) 
    { 
        complex<double> a = x.a;
        complex<double> b = x.b;
        complex<double> c = x.c;
        complex<double> zero (0.0,0.0);
        if(a==zero) 
        {
            if(b==zero && c!=zero)
                throw NoAnswer();
            else return c/-b;
        }
        return (-b + sqrt(b * b - (a.real()*4+a.imag()*4) * c)) / ((2 * a.real() + 2 * a.imag()));
    }
    
    /* RealVariable */
    // +
    RealVariable operator+(const RealVariable &x, const RealVariable &y)
    {
        RealVariable toreturn;
        toreturn.a = x.a+y.a;
        toreturn.b = x.b+y.b;
        toreturn.c = x.c+y.c;
        return toreturn;
    }
    RealVariable operator+(const RealVariable &x, const double y)
    {
        RealVariable toreturn;
        toreturn.a = x.a;
        toreturn.b = x.b;
        toreturn.c = x.c+y;
        return toreturn;
    }
    RealVariable operator+(const double y, const RealVariable &x)
    {
        return x+y;
    }

    // -
    RealVariable operator-(const RealVariable &x, const RealVariable &y) 
    {
        RealVariable toreturn;
        toreturn.a = x.a-y.a;
        toreturn.b = x.b-y.b;
        toreturn.c = x.c-y.c;
        return toreturn;
    }
    RealVariable operator-(const RealVariable &x, const double y) 
    {
        RealVariable toreturn;
        toreturn.a = x.a;
        toreturn.b = x.b;
        toreturn.c = x.c-y;
        return toreturn;
    }
    RealVariable operator-(const double y, const RealVariable &x) 
    { 
        RealVariable toreturn;
        toreturn.a = x.a;
        toreturn.b = x.b;
        toreturn.c = y-x.c;
        return toreturn; 
    }

    //*
    RealVariable operator*(const RealVariable &x, const RealVariable &y)
    {
        RealVariable toreturn;
        if(x.a>0 && y.a>0) // x^4
            throw InvalidEquation();
        else if(x.a>0 && y.b>0) // x^3
            throw InvalidEquation();
        else if(y.a>0 && x.b>0) // x^3
            throw InvalidEquation();
        else // x^2
        {
            toreturn.a = (x.a*y.c)+(x.b*y.b)+(x.c*y.a);
            toreturn.b = (x.b*y.c)+(y.b*x.c);
            toreturn.c = (x.c*y.c);   
        }
        return toreturn;
    }
    RealVariable operator*(const RealVariable &x, const double y) 
    {
        RealVariable toreturn;
        toreturn.a = x.a*y;
        toreturn.b = x.b*y;
        toreturn.c = x.c*y;
        return toreturn;
    }
    RealVariable operator*(const double y, const RealVariable &x) 
    {
        return x*y; 
    }

    // Divide
    RealVariable operator/(const RealVariable &x, const RealVariable &y) // Not sure about this
    { 
        if(y.a == 0 && y.b == 0 && y.c == 0)
            throw InvalidEquation();
        return x*(1/y);
    }
    RealVariable operator/(const RealVariable &x, const double y) 
    {
        if(y == 0)
            throw InvalidEquation();
        RealVariable toreturn;
        toreturn.a = x.a/y;
        toreturn.b = x.b/y;
        toreturn.c = x.c/y; 
        return toreturn; 
    }
    RealVariable operator/(const double y, const RealVariable &x) 
    { 
        if(x.a == 0 && x.b == 0 && x.c == 0)
            throw InvalidEquation();
        RealVariable toreturn;
        toreturn.a = y/x.a;
        toreturn.b = y/x.b;
        toreturn.c = y/x.c; 
        return toreturn;  
    }

    // ^
    RealVariable operator^(const RealVariable &x, const double power) 
    {   
        RealVariable toreturn;
        if(power == 1)
            return x;
        if(power == 2)
            return x*x;
        if(power>2 && (x.b>0 || x.a>0))
            throw InvalidEquation();
        else if(power == 2 && x.a>0)
            throw InvalidEquation();
        else if(power<0)
            throw InvalidEquation();
        if(x.a == 0 && x.c == 0)
        {
            toreturn.a = x.b*x.b;
            toreturn.b = 0;
            toreturn.c = 0;
        }
        else
        {
            toreturn.a = pow(x.a, power);
            toreturn.b = 2*x.b*x.c;
            toreturn.c = pow(x.c, power);
        }
        return toreturn;
        
    }

    // ==
    RealVariable operator==(const RealVariable &x, const RealVariable &y) 
    {
        return x-y; 
    }
    RealVariable operator==(const RealVariable &x, const double y) 
    {
        return x-y; 
    }
    RealVariable operator==(const double y, const RealVariable &x) 
    { 
        return y-x; 
    }


    /*ComplexVariable*/


    // +
    ComplexVariable operator+(const ComplexVariable &x, const ComplexVariable &y) 
    { 
        ComplexVariable toreturn;
        toreturn.a = x.a+y.a;
        toreturn.b = x.b+y.b;
        toreturn.c = x.c+y.c;
        return toreturn;
    }
    ComplexVariable operator+(const ComplexVariable &x, const complex<double> y) 
    { 
        ComplexVariable toreturn;
        toreturn.a = x.a;
        toreturn.b = x.b;
        toreturn.c = x.c+y;
        return toreturn;
    }
    ComplexVariable operator+(const complex<double> y, const ComplexVariable &x) 
    { 
        return x+y;
    }

    // -
    ComplexVariable operator-(const ComplexVariable &x, const ComplexVariable &y) 
    { 
        ComplexVariable toreturn;
        toreturn.a = x.a-y.a;
        toreturn.b = x.b-y.b;
        toreturn.c = x.c-y.c;
        return toreturn;
    }
    ComplexVariable operator-(const ComplexVariable &x, const complex<double> y) 
    { 
        ComplexVariable toreturn;
        toreturn.a = x.a;
        toreturn.b = x.b;
        toreturn.c = x.c-y;
        return toreturn; 
    }
    ComplexVariable operator-(const complex<double> y, const ComplexVariable &x) 
    {
        ComplexVariable toreturn;
        toreturn.a = x.a;
        toreturn.b = x.b;
        toreturn.c = y-x.c;
        return toreturn; 
    }

    // *
    ComplexVariable operator*(const ComplexVariable &x, const ComplexVariable &y) 
    { 
        ComplexVariable toreturn;
        toreturn.a = (x.a*y.c)+(x.b*y.b)+(x.c*y.a);
        toreturn.b = (x.b*y.c)+(y.b*x.c);
        toreturn.c = (x.c*y.c);   
        return toreturn;
    }
    ComplexVariable operator*(const ComplexVariable &x, const complex<double> y) 
    { 
        ComplexVariable toreturn;
        toreturn.a = x.a*y;
        toreturn.b = x.b*y;
        toreturn.c = x.c*y;
        return toreturn;
    }
    ComplexVariable operator*(const complex<double> y, const ComplexVariable &x) 
    { 
        ComplexVariable toreturn;
        toreturn.a = y*x.a;
        toreturn.b = y*x.b;
        toreturn.c = y*x.c;
        return toreturn;
    }

    // Divide
    ComplexVariable operator/(const ComplexVariable &x, const ComplexVariable &y) // Implement better please
    { 
        if (y.a == complex<double >(0.0,0.0) && y.b == complex<double >(0.0,0.0) && y.c == complex<double>(0.0,0.0)) 
            throw InvalidEquation();
        else 
        {
            if (y.a == complex<double>(0.0,0.0) && y.b == complex<double>(0.0,0.0) && y.c != complex<double>(0.0,0.0))
                return ComplexVariable(x.a / y.c, x.b / y.c, x.c / y.c);
            if (y.a == complex<double>(0.0,0.0) && y.b == complex<double>(0.0,0.0) && y.c != complex<double>(0.0,0.0))
                return ComplexVariable(x.a / y.c, x.b / y.c, x.c / y.c);
            if (y.a != complex<double>(0.0,0.0) && y.b != complex<double>(0.0,0.0) && y.c == complex<double>(0.0,0.0)) 
                return ComplexVariable(x.a / y.a, x.b / y.b, 0);
            if (y.a == complex<double>(0.0,0.0) && y.b != complex<double>(0.0,0.0) && y.c == complex<double>(0.0,0.0)) 
                return ComplexVariable(0, x.b / y.b, 0);
        }
    }
    ComplexVariable operator/(const ComplexVariable &x, const complex<double> y) 
    { 
        ComplexVariable toreturn;
        if(y == complex<double>(0.0,0.0))
            throw InvalidEquation();
        else
        {
            toreturn.a = x.a/y;
            toreturn.b = x.b/y;
            toreturn.c = x.c/y;
        }
        return toreturn;
    }
    ComplexVariable operator/(const complex<double> y, const ComplexVariable &x) 
    { 
        ComplexVariable toreturn;
        if(y != complex<double>(0.0,0.0))
            throw InvalidEquation();
        else
        {
            toreturn.a = y/x.a;
            toreturn.b = y/x.b;
            toreturn.c = y/x.c;
        }
        return toreturn;
    }

    // ^
    ComplexVariable operator^(const ComplexVariable &x, const complex<double> power) // Implement better
    { 
        if(power.imag() != 0) 
            throw InvalidEquation();
        if(power.real() == 2)
            return x*x;
        if((power.real()>2 && x.a==complex<double>(0.0,0.0) && x.b==complex<double>(0.0,0.0))) 
            return ComplexVariable(0,0,pow(x.c,power));
        if ((x.a!=complex<double>(0.0,0.0)) || (power.real()>2) || (power.real()<0) ) 
            throw InvalidEquation();
        if(x.b!=complex<double>(0.0,0.0) && x.c!=complex<double>(0.0,0.0) && power.real()==2)
            return ComplexVariable(pow(x.b,power),x.b*x.c*power,pow(x.c,power));
        if(x.b!=complex<double>(0.0,0.0) && x.c==complex<double>(0.0,0.0) && power.real()==2) 
            return ComplexVariable(pow(x.b,power),0,0);
        if(power==complex<double>(0.0,1.0)) 
            return x;
        if(power==complex<double>(0.0,0.0)) 
            return ComplexVariable(0,0,1);
    }

    // ==
    ComplexVariable operator==(const ComplexVariable &x, const ComplexVariable &y) 
    { 
        return x-y; 
    }
    ComplexVariable operator==(const ComplexVariable &x, const complex<double> y) 
    { 
        return x-y; 
    }
    ComplexVariable operator==(const complex<double> y, const ComplexVariable &x) 
    { 
        return y-x; 
    }
}