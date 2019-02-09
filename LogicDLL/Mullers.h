/*
ITS ALIVE!!

[1] TITLE
Mullers.h

[2] DEPENDENCIES
Evaluator.h - returns value of expression
Root.h (parent) - checks if current iteration is good
math.h - for evaluation of determinants

[3] DESCRIPTION
This class will find the roots of the indicated 
expression using curve fitiing techniques

[4] ARGUMENTS

a) Explicit Expression
b) 3 initial values
C) Root.h arguments

[5] LIMITATIONS
~ can currently evaluate one root only


*/

#include<math.h>
#include"Evaluator.h"
#include"Root.h"

using namespace std;

class CurveFit : public Precise
{
public:
	CurveFit(int, double, double, string, double, double,double);
	void Mullers(Evaluate);
	void Coefficient(Evaluate);
	double H(double,double);
	double D(double,double,double,double);
	void Determinant();
	bool isPos();
	double Ret_Root();
private:
	//Initial Values
	double xr0, xr1, x0, x1, x2, fx0, fx1, fx2;
	//Coefficient
	double a, b ,c, d;
	double root;
	int itr;
	int limit;
};

CurveFit::CurveFit(int InMaxItr, double InAbsolute, double InRelative, string InExpress, double Init0, double Init1, double Init2)
	:Precise(InMaxItr,InAbsolute,InRelative)
{
	Evaluate val(InExpress);
	x0 = Init0;
	x1 = Init1;
	x2 = Init2;

	xr0 = xr1 = NULL;
    a = b = c = d = NULL;
	itr = 0;
	Mullers(val);
}

void CurveFit::Mullers(Evaluate val)
{
	do
	{
		xr0 = xr1;

		Coefficient(val);
		Determinant();

		if(isPos())
			xr1 = x2 + (-2*c)/(b + d);
		else
			xr1 = x2 + (-2*c)/(b - d);
		itr++;

		x0 = x1;
		x1 = x2;
		x2 = xr1;

	}while(Continue(itr,xr0,xr1));

	if(MaxxedOut(itr))
		root = NULL;
	else
		root = xr1;
}

void CurveFit::Coefficient (Evaluate val)
{
	fx0 = val.Ret_val(x0);
	fx1 = val.Ret_val(x1);
	fx2 = val.Ret_val(x2);

	a = (D(x1,fx1,x2,fx2)-D(x0,fx0,x1,fx1))/(H(x1,x2)+H(x1,x2));
	b = a*H(x1,x2) + D(x1,fx1,x2,fx2);
	c = fx2;
}

double CurveFit::H(double num0 , double num1)
{
	return num1 - num0;
}

double CurveFit::D(double num0 , double fnum0, double num1, double fnum1)
{
	return (fnum1-fnum0)/(num1 - num0);
}

void CurveFit::Determinant()
{
	d = sqrt(pow(b,2)-4*a*c);
}

bool CurveFit::isPos()
{
	return abs(b + d) > abs(b -d);
}

double CurveFit::Ret_Root()
{
	return root;
}

