// Author - Dvir sadon

#include "solver.hpp"
#include <iostream>
#include <string>
#include "doctest.h"
#include <complex>

using std::string;
using namespace std;
using solver::solve, solver::RealVariable, solver::ComplexVariable;

TEST_CASE("Test Realvarible solve ") 
{
    RealVariable x;

    /*Normal checks - 40*/

    // Linear check - 20
    
    CHECK((solve(2*x-4 == 10)) == 7);
    CHECK((solve(2*x-3 == 10)) == 6.5);
    CHECK((solve(2*x-2 == 10)) == 6);
    CHECK((solve(2*x-1 == 10)) == 5.5);
    CHECK((solve(2*x == 10)) == 5);
    CHECK((solve(2*x == 4)) == 2);
    CHECK((solve(2*x == 1)) == 1);
    CHECK((solve(5*x-7 == 3)) == 2);
    CHECK((solve(10*x-5 == 45)) == 5);
    CHECK((solve(5*x+10 == 40)) == 6);
    CHECK((solve(4*x+1 == 8)) == 1.75);
    CHECK((solve(5*x-5 == 10)) == 3);
    CHECK((solve(1*x+2 == 2)) == 0);
    CHECK((solve(8*x+17 == 31)) == 1.75);
    CHECK((solve(2*x-10 == 60)) == 35);
    CHECK((solve(3*x == 60)) == 20);
    CHECK((solve(6*x == 60)) == 10);
    CHECK((solve(4*x+20 == 60)) == 10);
    CHECK((solve(10*x-8 == 18)) == 2.6);
    CHECK((solve(1*x+2 == 4)) == 2);

    // Non linear check - 20 

    CHECK((solve((x^2) == 16)) == 4);
    CHECK((solve((x^2) == 9)) == 3);
    CHECK((solve((x^2) == 4)) == 2);
    CHECK((solve((x^2) == 1)) == 1);
    CHECK(solve((2/3)*x + 9 == x) == 27);
    CHECK(solve((x^2) - 2*x + 9 == x^2) == 4.5);
    CHECK(solve(2*((x)^2) + 2 == 10) == 2);
    CHECK(solve((x^2) + 2*x == 2*x + 9) == 3);
    CHECK(solve(x + 9 == x) == -9);
    CHECK((solve((x^2) == 0)) == 0);
    CHECK((solve((2*(x^2)) == 18)) == 3);
    CHECK((solve((2*(x^2)) == 64)) == 6);
    CHECK((solve((2*(x^2)) == 50)) == 5);
    CHECK((solve((2*(x^2)) == 32)) == 4);
    CHECK((solve((2*(x^2)) == 98)) == 7);
    CHECK((solve((2*(x^2)) == 128)) == 8);
    CHECK((solve((2*(x^2)) == 162)) == 9);
    CHECK((solve((2*(x^2)) == 200)) == 10);
    CHECK((solve((3*(x^2)) == 300)) == 10);
    CHECK((solve((4*(x^2)) == 400)) == 10);
    
    /*Error throwing checks - 10*/
    
    CHECK_THROWS(solve((x^2) +3*x + 5 == 0));
    CHECK_THROWS(solve((x^2) == -9));
    CHECK_THROWS(solve((x^2) + x + 1 == 0));
    CHECK_THROWS(solve((x^2) + 5 == 0));
    CHECK_THROWS(solve(2*(x^2) +3*x + 5 == 0));
    CHECK_THROWS(solve(x == x));
    CHECK_THROWS(solve((x^2) + 5 == 0));
    CHECK_THROWS(solve((x^2) == -1));
    CHECK_THROWS(solve((x^2) + 5 == -9));
    CHECK_THROWS(solve((x^2) +3*x == -78));
}


TEST_CASE("Test ComplexVariable solve ") 
{
    ComplexVariable x;

    /*Normal checks - 40*/
    
    CHECK(solve(3*x-12 == 0) == complex<double>(4.0,0.0));
    CHECK(solve(3*x == 12) == complex<double>(4.0,0.0));
    CHECK(solve(4*x-16==0) == complex<double>(4.0,0.0));
    CHECK(solve(5*x-20==0) == complex<double>(4.0,0.0));
    CHECK(solve(6*x-24==0) == complex<double>(4.0,0.0));
    CHECK(solve(7*x==28) == complex<double>(4.0,0.0));
    CHECK(solve(8*x-32==0) == complex<double>(4.0,0.0));
    CHECK(solve(9*x-36==0) == complex<double>(4.0,0.0));
    CHECK(solve(10*x==40) == complex<double>(4.0,0.0));
    CHECK(solve(11*x-44==0) == complex<double>(4.0,0.0));

    CHECK(solve((x^2)==-1) == complex<double>(0.0,1.0));
    CHECK(solve((x^2) -1==-1) == complex<double>(0.0,0.0));
    CHECK(solve((x^2) -2==-1) == complex<double>(1.0,0.0));
    CHECK(solve((x^2) -3==-1) == complex<double>(2.0,0.0));
    CHECK(solve((x^2) -4==-1) == complex<double>(3.0,0.0));
    CHECK(solve((x^2) -5==-1) == complex<double>(4.0,0.0));
    CHECK(solve(2*x==0) == complex<double>(0.0,0.0));
    CHECK(solve((x^2)==-4) == complex<double>(0.0,2.0));
    CHECK(solve((x^2)==0) == complex<double>(0.0,0.0));
    CHECK(solve(2*(x^2)==0) == complex<double>(0.0,0.0));

    CHECK(solve(2*(x^2)==x^2) == complex<double>(0.0,0.0));
    CHECK(solve(2*x==x) == complex<double>(0.0,0.0));
    CHECK(solve((x^2) + 3==-1) == complex<double>(0.0,2.0));
    CHECK(solve((x^2) + 1==0) == complex<double>(0.0,1.0));
    CHECK(solve((x^2)==-1) == complex<double>(0.0,1.0));
    CHECK(solve((x^2) +3-3==-1) == complex<double>(0.0,1.0));
    CHECK(solve((x*x)==-1) == complex<double>(0.0,1.0));
    CHECK(solve((x^2)+1-2+1==-1) == complex<double>(0.0,1.0));
    CHECK(solve((x^2)==-9) == complex<double>(0.0,3.0));
    CHECK(solve((x^2)+9==0) == complex<double>(0.0,3.0));

    CHECK(solve((x^2)+10==1) == complex<double>(0.0,3.0));
    CHECK(solve((x^2)+8==-1) == complex<double>(0.0,3.0));
    CHECK(solve((x^2)==3-3+1-1) == complex<double>(0.0,0.0));
    CHECK(solve((x^2)==-16) == complex<double>(0.0,4.0));
    CHECK(solve((x^2)+16==0) == complex<double>(0.0,4.0));
    CHECK(solve((x^2)+15==-1) == complex<double>(0.0,4.0));
    CHECK(solve((x^2)+17==1) == complex<double>(0.0,4.0));
    CHECK(solve((x^2)+15==-1+1-1) == complex<double>(0.0,4.0));
    CHECK(solve((x^2)+4==0) == complex<double>(0.0,2.0));
    CHECK(solve((x^2)==-3-1) == complex<double>(0.0,2.0));

    /*Error throwing checks - 10*/

    CHECK_THROWS(solve(5 == 0*x));
    CHECK_THROWS(solve(0 == 0*x));
    CHECK_THROWS(solve(0*x == 0*x));
    CHECK_THROWS(solve(x == x));
    CHECK_THROWS(solve(2*x == 2*x));
    CHECK_THROWS(solve(8 == 0*x));
    CHECK_THROWS(solve(5+x == 5+x));
    CHECK_THROWS(solve((x^2) == (x^2)));
    CHECK_THROWS(solve(5 == 5+0*x));
    CHECK_THROWS(solve(17 == 0*x));

}
