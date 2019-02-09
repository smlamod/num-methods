/*
WORKING
[1] TITLE
RegulaFalsi.h

[2] DEPENDENCIES
Evaluator.h - returns value of expression
Root.h (parent) - checks if current iteration is good

[3] DESCRIPTION
This class will find the roots of the indicated 
expression using  bracketing techniques specfically
regula falsi

[4] ARGUMENTS

a) Explicit Expression
b) Boundaries (Up and Low)
C) Root.h arguments

[5] LIMITATIONS
~ can currently evaluate one root only

*/
#include "Evaluator.h"
#include "Root.h"
using namespace std;

class Bracket : public Precise
{
public:
	Bracket(int, double, double, string,double,double);
	void RegulaFalsi(Evaluate);
	double Ret_Root();
private:
	double x, x0, x1, fx, fx0, fx1;
	double root;
	int itr;
	int limit;
};

Bracket::Bracket(int InMaxItr, double InAbsolute, double InRelative, string InExpress, double InUp, double InLw)
	:Precise(InMaxItr,InAbsolute,InRelative)
{
	Evaluate val(InExpress);
	x = NULL;
	x0 = InLw;
	x1 = InUp;
	RegulaFalsi(val);
};


void Bracket::RegulaFalsi(Evaluate val)
{
	itr = 0;
	do
	{
		fx0 = val.Ret_val(x0);
		fx1 = val.Ret_val(x1);
		x = x0 - ((x1 - x0) / (fx1 - fx0))*fx0;
		fx = val.Ret_val(x);
		itr++;

		if(fx>0)
			x1 = x;
		else
			x0 = x;
	}
	while(Continue(itr,x0,x1));

	if(MaxxedOut(itr))
	{
		root = NULL;
	}else
	{
		root = x;
	}

}

double Bracket::Ret_Root()
{
	return root;
}