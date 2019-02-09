/*
WORKING

[1] TITLE
GaussSeidel.h

[2] DEPENDENCIES
Root.h

[3] DESCRIPTION
This class will compute for the polynomial
solution of the given polynomial expression
with variable size using iterative techniques


[4] ARGUMENTS

a) Polynomial Expression in the Form

For a square matrix size 3
0 1 0 K 
1 0 1 K 
0 1 0 K 
b) Terminating 

[5] LIMITATIONS
can only evaluate polynomial equations
no transcendentals

~ could not check for input errors yet
*/

#include <string>
#include <vector>
#include <sstream>
#include "Root.h"
using namespace std;

class SeidelIterative : public Precise
{
public:
	SeidelIterative(int,double,double,string);
	void Initialize();
	void GaussSeidel();
	double* Ret_Sol();
	int Ret_Size();
private:
	void Tokenize();
	void Del();

	string Polynomial;
	bool IsValid;
	int size;

	double **A;
	double *K;

	//X current
	double *X;
	//X previous
	double *XP;
};

SeidelIterative::SeidelIterative(int InMaxItr, double InAbsolute, double InRelative, string InPoly)
	:Precise(InMaxItr,InAbsolute,InRelative)
{
	Polynomial = InPoly;
	Tokenize();

	if(IsValid)
		GaussSeidel();
	Del();
}

void SeidelIterative::Tokenize()
{
	string temp;
	vector<string> PolyStr;
	size = 0;
	IsValid = true;

	stringstream split(Polynomial);
	while(split.good())
	{
		getline(split,temp,'|');
		PolyStr.push_back(temp);
	}
	size = PolyStr.size();

	Initialize();

	for (int i = 0; i < size; i++)
	{
		int j=0;
		stringstream splitElem(PolyStr[i]);
		while(splitElem.good())
		{
			getline(splitElem,temp,' ');
			if (istringstream(temp).bad())
			{
				IsValid = false;
				break;
				break;
				break;
			}
			else
			{
				if (j==size)
					istringstream(temp)>>K[i];
				else
					istringstream(temp)>>A[i][j];
			}
			j++;
		}

	}
}

void SeidelIterative::Initialize()
{
	A = new double *[size];
	X = new double [size];
	XP = new double [size];
	K = new double [size];

	for(int row=0;row<size;row++)
	{
		X[row] = 0;
		A[row] = new double[size];
	}
}

void SeidelIterative::Del()
{
	for (int row =0; row < size; row++)
	{
		delete A[row];
	}
	delete[] A;
	delete K;
}

void SeidelIterative::GaussSeidel()
{
	int itr = 0;
	double sum = 0;
	do
	{
		for(int i=0;i<size;i++)
		{
			XP[i] = X[i];
		}
		//Formula for finding X
		for(int i=0;i<size;i++)
		{
			sum = 0;
			for(int j=0;j<size;j++)
			{
				sum += A[i][j]*X[j];
			}
			X[i] = (K[i]-(sum - A[i][i]*X[i]))/A[i][i]; 
		}
		//Setting New Values for X
		itr++;
	}while(ContinuePol(itr,size,XP,X));

	if(MaxxedOut(itr))
	{
		for(int row = 0; row < size; row++)
		{
			X[row] = 0;
		}
	}

}

double* SeidelIterative::Ret_Sol()
{
	return X;
}

int SeidelIterative::Ret_Size()
{
	return size;
}