#include "Evaluator.h"

using namespace std;

class Integrate
{
public:
	Integrate(string,double,double,int);
	void Trapzoidal();
	void OneThird();
	void ThreeEight();
	void Initialize(int);
	double Summation();
	double Ret_TrapArea();
	double Ret_OTrdArea();
	double Ret_TEhtArea();
	double StepSize(double,double,int);
private:
	string Expression;
	double a,b,h;
	double Area;
	int size;
	double *Rule;
	
};

Integrate::Integrate(string InExpress, double llimit, double ulimit, int Step)
{
	Expression = InExpress;
	a = llimit;
	b = ulimit;
	h = StepSize(llimit,ulimit,Step);
	size = Step;
	Initialize(Step);
}

double Integrate::StepSize(double a, double b, int n)
{
	return (b-a)/n;
}

void Integrate::Initialize(int size)
{
	Rule = new double[size+1];
}

void Integrate::Trapzoidal()
{
	Evaluate val(Expression);
	double itr = a;
	for (int i = 0 ;i < size+1 ;i++)
	{

		if (i == 0 || i == size)
			Rule[i] = val.Ret_val(itr);
		else 
			Rule[i] = 2*val.Ret_val(itr);	

		itr += h;
	}
}

void Integrate::OneThird()
{
	Evaluate val(Expression);
	double itr = a;
	for (int i = 0 ;i < size+1 ;i++)
	{

		if (i == 0 || i == size)
			Rule[i] = val.Ret_val(itr);
		else if (i % 2 == 0)
			Rule[i] = 2*val.Ret_val(itr);
		else
			Rule[i] = 4*val.Ret_val(itr);

		itr += h;
	}
}

void Integrate::ThreeEight()
{
	Evaluate val(Expression);
	double itr = a;
	for (int i = 0 ;i < size+1 ;i++)
	{

		if (i == 0 || i == size)
			Rule[i] = val.Ret_val(itr);
		else if (i % 3 == 0)
			Rule[i] = 2*val.Ret_val(itr);
		else
			Rule[i] = 3*val.Ret_val(itr);

		itr += h;
	}
}

double Integrate::Summation()
{
	double sum =0;
	for(int i=0; i < size +1; i++)
	{
		sum += Rule[i];
	}
	return sum;
}

double Integrate::Ret_TrapArea()
{
	Trapzoidal();
	return Summation()*(h/2);
}

double Integrate::Ret_OTrdArea()
{
	OneThird();
	return Summation()*(h/3);
}

double Integrate::Ret_TEhtArea()
{
	ThreeEight();
	return Summation()*(3*h/8);
}

