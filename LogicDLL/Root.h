/*

[1] TITLE
Root.h

[2] DEPENDENCIES
N/A

[3] DESCRIPTION
A parent class inherited by other classes
for the termination of iterations

[4] REQUIREMENTS

a) Max Itr
b) ErAbsolute
c) ErRelative

[5] LIMITATIONS
N/A

*/

#ifndef H_Precise
#define H_Precise
#include<math.h>
using namespace std;

class Precise
{
public:
	Precise(int,double,double);
	bool Continue(int, double, double);
	bool ContinuePol(int,int,double*,double*);
	bool MaxxedOut(int);
private:
	//Terminating Condition Variables
	double ErAbsolute;
	double ErRelative;
	int MaxItr;
};

Precise::Precise(int InMaxItr, double InAbsolute, double InRelative)
{
	MaxItr = InMaxItr;
	ErAbsolute = InAbsolute;
	ErRelative= InRelative;
}

bool Precise::Continue(int InItr, double InPrev, double InCurr)
{
	if(MaxxedOut(InItr))
	{
		// Iteration Maxxed Out
		return false;
	}
	else if(InPrev == NULL)
	{
		// Initial Iteration
		// Used for Mullers
		return true;
	}
	else
	{
		if (ErRelative == 0)
		{
			if (ErAbsolute >= abs(InCurr-InPrev))
				// Met Condition of Error less than 0.00--1
					return false;
			else 
				return true;
		}
		else
		{
			if (ErRelative >= (abs((InCurr-InPrev)/InCurr)*100))
				// Met Condition of Precision more than 99.99--9%
					return false;
			else 
				return true;
		}
	}

}

bool Precise::ContinuePol(int InItr,int InSize, double* InPrev , double *InCurr )
{
	if(MaxxedOut(InItr))
	{
		// Iteration Maxxed Out
		return false;
	}
	else
	{
		if (ErRelative == 0)
		{
			for(int i=0;i<InSize;i++)
			{
				if(ErAbsolute >= abs(InCurr[i]-InPrev[i]))
					// Met Condition of Error less than 0.00--1
						return false;
			}
			return true;
		}
		else
		{
			for(int i=0;i<InSize;i++)
			{
				if(ErRelative >= abs(((InCurr[i]-InPrev[i])/InCurr[i])*100))
					// Met Condition of Error less than 0.00--1
						return false;
			}
			return true;
		}
	}

}

bool Precise::MaxxedOut(int InItr)
{
	if(InItr > MaxItr)
		return true;
	else 
		return false;
}

#endif