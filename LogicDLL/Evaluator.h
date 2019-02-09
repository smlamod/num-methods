/*

[1] TITLE
Evaluator.h

[2] DEPENDENCIES
exprtk.hpp - expression solver

[3] DESCRIPTION
This class will intermediate with the expression solver 
and return the value of said expression

[4] REQUIREMENTS

a) Explicit Expression
b) Value of variable

[5] LIMITATIONS
Expression can only evaluate one variable

*/

#ifndef H_Evaluate
#define H_Evaluate
#include<string>
#include"exprtk.hpp"

using namespace std;

class Evaluate
{
public:
	Evaluate(string);
	double Ret_val(double);
private:
	string Function;
};

Evaluate::Evaluate(string InExpress)
{
	Function = InExpress;
};

double Evaluate::Ret_val(double var)
{
	double x = double(var);
	exprtk::symbol_table<double> symbol_table;
	symbol_table.add_variable("x",x);
	symbol_table.add_constants();

	exprtk::expression<double> expression;
	expression.register_symbol_table(symbol_table);

	exprtk::parser<double> parser;
	parser.compile(Function,expression);

	double result = expression.value();
	return result;
};

#endif