/*

[1] TITLE
NewtonsDDifference

[2] DEPENDENCIES
None

[3] DESCRIPTION
This class will return a function said to be derived
from a given set of points using newtons divided difference

[4] ARGUMENTS

An array of the form

|	x|	F(x)|
|	0|	   1|
|	n|	   n|

where size of x and fx must be equal

[5] LIMITATIONS

*/

#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Interpolate
{
public:
	Interpolate(string,string);
	void Initialize();
	string Ret_Func();
	double Diff(double,double,double,double);
	void Parse(string,string);
	void NewtonsDDiff();
private:
	double **N;
	double *Inx;
	double *Iny;
	bool IsGoodInput;
	string Ans;
	string ToString(double);
	string Simplify(double**,int,int) ;
	void Del();
	int Size;
};

string Interpolate::Simplify(double** T, int row, int col)
{
	if (row > Size-1 || col > Size )
		return to_string(T[0][col+1]);
	else
		return "("+ to_string(T[0][col+1]) + "+" + 
		"(x" + ToString(T[row][0]) + ")"  
		+ Simplify(T,row+1,col+1)+")";
}

string Interpolate::ToString(double num)
{
	if (num > 0)
	{
		return " - " + to_string(num);
	}
	else
		return " + " + to_string((-1)*num);
}

Interpolate::Interpolate(string InStr_x,string InStr_y)
{
	Parse(InStr_x,InStr_y);

	if(IsGoodInput == true)
	{
		Initialize();
		for (int row=0; row < Size; row++)
		{
			N[row][0] = Inx[row];
			N[row][1] = Iny[row];
		}

		NewtonsDDiff();
		Ans = Simplify(N,0,0);
		Del();
	}
}

void Interpolate::Parse(string X,string Y)
{
	string tempX;
	string tempY;
	vector<string> vx;
	vector<string> vy;

	stringstream splitX(X);
	while(splitX.good())
	{
		getline(splitX,tempX,',');
		vx.push_back(tempX);
	}

	stringstream splitY(Y);
	while (splitY.good())
	{
		getline(splitY,tempY,',');
		vy.push_back(tempY);
	}

	if (vx.size() == vy.size())
	{
		IsGoodInput = true;
		Size = vx.size();
		Inx = new double[Size];
		Iny = new double[Size];

		for (int i = 0; i < Size; i++)
		{
			istringstream(vx[i])>>Inx[i];
			istringstream(vy[i])>>Iny[i];
		}
	}
	else 
		IsGoodInput = false;
}

//	Allocate the Table
void Interpolate::Initialize()
{
	int Tsize = Size;
	N = new double *[Size];
	for (int row = 0; row < Size; row++)
	{
		N[row] = new double[Tsize +1];
		Tsize--;
	}
}

//	Clear Memory
void Interpolate::Del()
{
	for(int row=0; row < Size; row++)
	{
		delete N[row];
	}
	delete[] Inx;
	delete[] Iny;
	delete[] N;
}

double Interpolate::Diff(double x0, double fx0, double x1, double fx1)
{
	return ((fx1-fx0)/(x1-x0));
}

void Interpolate::NewtonsDDiff()
{
	int Tsize = Size-1;
	int h = 1;

	for (int col = 2; col <= Size; col++)
	{
		for(int row = 0; row < Tsize ; row++)
		{
			N[row][col] = Diff(N[row][0],N[row][col-1],N[row+h][0],N[row+1][col-1]);
		}
		h++;
		Tsize--;
	}
}

string Interpolate::Ret_Func()
{
	if (IsGoodInput)
		return Ans;
	else
		return "Sizes does not match";
}
