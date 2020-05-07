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
    double solve(const RealVariable &x) // Returns the max number of the answers
    { 
        double ans1;
        double ans2;
        if(x.a == 0 && x.b == 0)
            throw NoAnswer();
        if(x.a>0 && x.b == 0 && x.c > 0)
            throw NoAnswer();
        else if(x.a == 0)
        {
            if(abs(x.c) <= EPSILON) // handle negative 0
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

        return max(ans1,ans2);
    }
    complex<double> solve(const ComplexVariable &x) 
    { 
        complex<double> zero (0.0,0.0);
        if(x.a!=zero) 
            return (-x.b + sqrt(x.b*x.b-(x.a.real()*4 + x.a.imag()*4) * x.c))/((2*x.a.real() + 2*x.a.imag()));
        if(x.b==zero && x.c!=zero)
            throw NoAnswer();
        else 
            return x.c/-x.b;
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
    RealVariable operator/(const RealVariable &x, const RealVariable &y) 
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
        if(power == 1)
            return x;
        if(power == 2)
            return x*x;
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
    ComplexVariable operator/(const ComplexVariable &x, const ComplexVariable &y) //
    { 
        complex<double> zero (0.0,0.0);
        ComplexVariable toreturn;
        if (y.a == zero && y.b == zero && y.c == zero) 
            throw InvalidEquation();
        if(y.a != zero) toreturn.a = x.a/y.a;
        else toreturn.a = 0;

        if(y.b != zero) toreturn.b = x.b/y.b;
        else toreturn.b = 0;

        if(y.c != zero) toreturn.c = x.c/y.c;
        else toreturn.c = 0;

        return toreturn;
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
    ComplexVariable operator^(const ComplexVariable &x, const complex<double> power)
    { 
        complex<double> zero (0.0,0.0);
        if(power.imag() == 0)
        {
            if(power.real() == 2)
                return x*x;
            if(power==complex<double>(0.0,1.0)) 
                return x;
            if(power==zero) 
                return ComplexVariable(0,0,1);
        } 
        throw InvalidEquation();
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