/*
WORKING
[1] TITLE
Secant.h

[2] DEPENDENCIES
Evaluator.h - returns value of expression
Root.h (parent) - checks if current iteration is good

[3] DESCRIPTION
This class will find the root of the indicated
expression using open method specifically 
the secant method

[4] ARGUMENTS

a) Explicit Expression
b) Initial Value
c) Root.h arguments

[5] LIMITATIONS
~ can currently evaluate one root only

*/

#include "Evaluator.h"
#include "Root.h"
using namespace std;

class Open : public Precise
{
public:
	Open(int, double, double, string, double, double);
	void Secant(Evaluate);
	double Ret_Root();
private:
	double x, x0, x1, fx, fx0, fx1;
	double root;
	int itr;
};

Open::Open(int InMaxItr, double InAbsolute, double InRelative, string InExpress, double Init0, double Init1)
	:Precise(InMaxItr,InAbsolute,InRelative)
{
    Evaluate val(InExpress);
	x = NULL;
	x0 = Init0;
	x1 = Init1;
	itr = 0;
	Secant(val);
};

void Open::Secant(Evaluate val)
{
	do
	{
		fx0 = val.Ret_val(x0);
		fx1 = val.Ret_val(x1);

		if (fx0 == fx1)
		{
			root = NULL;
			break;
		}

		x = x0 - ((x1 - x0) / (fx1 - fx0))*fx0;
		fx = val.Ret_val(x);
		itr++;

		x0 = x1;
		x1 = x;
	}
	while(Continue(itr,x0,x1));

	if(MaxxedOut(itr))
		root = NULL;
	else
		root = x;

}

double Open::Ret_Root()
{
	return root;
}