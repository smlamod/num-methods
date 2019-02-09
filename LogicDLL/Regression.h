#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Regression
{
public:
	Regression(string,string);
	string Ret_Func();
	void Parse(string,string);
	void LinearRegression();
private:
	bool isGoodInput;
	int Size;
	double a1, a0;
	double Ex, Ey, Exy, Ex2;
	double *Inx;
	double *Iny;
};

Regression::Regression(string InStr_x,string InStr_y)
{
	Ex = Ey = Exy = Ex2 = 0;
	Parse(InStr_x,InStr_y);

	if(isGoodInput)
	{
		for(int i =0; i <Size; i++)
		{
			Ex += Inx[i];
			Ey += Iny[i];
			Exy += Inx[i]*Iny[i];
			Ex2 += Inx[i]*Inx[i];
		}
		LinearRegression();
	}
}

void Regression::Parse(string X, string Y)
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
		isGoodInput = true;
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
		isGoodInput = false;
}

void Regression::LinearRegression()
{
	double xm = Ex/Size;
	double ym = Ey/Size;

	a1 = (Size*Exy - Ex*Ey)/(Size*Ex2 - Ex*Ex);
	a0 = ym - a1*xm;
}

string Regression::Ret_Func()
{
	if(isGoodInput)
	return to_string(a1) + "x + " + to_string(a0); 
	else
	return "Sizes does not match";
}

