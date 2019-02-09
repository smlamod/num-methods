#include "Evaluator.h"

using namespace std;

class Differentiate
{
public:
	Differentiate(string,double,double);
	double ForwardFDD();
	double BackwardFDD();
	double CenterFDD();
	double XStep(int);
	
private:
	string Expression;
	double x;
	double Step;
};

Differentiate::Differentiate(string InExpress, double InX, double InStep)
{
	Expression = InExpress;
	x = InX;
	Step = InStep;
}

double Differentiate::XStep(int i)
{
	return x + i*Step;
}

double Differentiate::ForwardFDD()
{
	Evaluate val(Expression);
	return (-val.Ret_val(XStep(2)) + 4*val.Ret_val(XStep(1)) -3*val.Ret_val(XStep(0)))/(2*Step);
}

double Differentiate::BackwardFDD()
{
	Evaluate val(Expression);
	return (3*val.Ret_val(XStep(0))-4*val.Ret_val(XStep(-1)) + val.Ret_val(XStep(-2)))/(2*Step);
}

double Differentiate::CenterFDD()
{
	Evaluate val(Expression);
	return (-val.Ret_val(XStep(2)) + 8*val.Ret_val(XStep(1)) -8*val.Ret_val(XStep(-1)) + val.Ret_val(XStep(-2)))/(12*Step);
}