// This is the main DLL file.
#include "stdafx.h"
#include "LogicDLL.h"
#include <msclr/marshal_cppstd.h>
using namespace msclr::interop;
using namespace CashewLogicDLL;

double CashewLogic::ImpRegula(String^ InExpress, double InUp, double InLw)
{
	Bracket Solve(MaxItr,Absolute,Relative,StrConvert(InExpress),InUp,InLw);
	return Solve.Ret_Root();
}

double CashewLogic::ImpSecant(String^ InExpress,double Init0, double Init1)
{
	Open Solve(MaxItr,Absolute,Relative,StrConvert(InExpress),Init0,Init1);
	return Solve.Ret_Root();
}

double CashewLogic::ImpMuller(String^ InExpress, double Init0, double Init1, double Init2)
{
	CurveFit Solve(MaxItr,Absolute,Relative,StrConvert(InExpress),Init0,Init1,Init2);
	return Solve.Ret_Root();
}

String^ CashewLogic::ImpCClsky(String^ InExpress)
{
	string Outstr;
	Direct Solve(StrConvert(InExpress));
	for(int i=0; i < Solve.Ret_Size();i++)
	{
		Outstr += to_string(Solve.Ret_Sol()[i]);
		Outstr += " ";
	}
	return marshal_as<String^>(Outstr);
}

String^ CashewLogic::ImpGJcobi(String^ InExpress)
{
	string Outstr;
	JacobiIterative Solve(MaxItr,Absolute,Relative,StrConvert(InExpress));
	for(int i=0; i < Solve.Ret_Size();i++)
	{
		Outstr += to_string(Solve.Ret_Sol()[i]);
		Outstr += " ";
	}
	return marshal_as<String^>(Outstr);
}

String^ CashewLogic::ImpGSeidl(String^ InExpress)
{
	string Outstr;
	SeidelIterative Solve(MaxItr,Absolute,Relative,StrConvert(InExpress));
	for(int i=0; i < Solve.Ret_Size();i++)
	{
		Outstr += to_string(Solve.Ret_Sol()[i]);
		Outstr += " ";
	}
	return marshal_as<String^>(Outstr);
}

String^ CashewLogic::ImpLReggression(String^ Inx, String^ Iny)
{
	Regression Solve(StrConvert(Inx),StrConvert(Iny));
	return marshal_as<String ^>(Solve.Ret_Func());
}

String^ CashewLogic::ImpNewtonsDDiff(String^ Inx, String^ Iny)
{
	Interpolate Solve(StrConvert(Inx),StrConvert(Iny));
	return marshal_as<String ^>(Solve.Ret_Func());
}

double CashewLogic::ImpIntegTrapezd(String^ InExpress, double Init0, double Init1, int InSeg)
{
	Integrate Solve(StrConvert(InExpress),Init0,Init1,InSeg);
	return Solve.Ret_TrapArea();
}

double CashewLogic::ImpIntegOneThrd(String^ InExpress, double Init0, double Init1, int InSeg)
{
	Integrate Solve(StrConvert(InExpress),Init0,Init1,InSeg);
	return Solve.Ret_OTrdArea();
}

double CashewLogic::ImpIntegThreEht(String^ InExpress, double Init0, double Init1, int InSeg)
{
	Integrate Solve(StrConvert(InExpress),Init0,Init1,InSeg);
	return Solve.Ret_TEhtArea();
}

double CashewLogic::ImpForwardDDiff(String^ InExpress,double Init0, double InStep)
{
	Differentiate Solve(StrConvert(InExpress),Init0,InStep);
	return Solve.CenterFDD();
}

double CashewLogic::ImpBackwrdDDiff(String^ InExpress,double Init0, double InStep)
{
	Differentiate Solve(StrConvert(InExpress),Init0,InStep);
	return Solve.BackwardFDD();
}

double CashewLogic::ImpCentereDDiff(String^ InExpress,double Init0, double InStep)
{
	Differentiate Solve(StrConvert(InExpress),Init0,InStep);
	return Solve.CenterFDD();
}

string CashewLogic::StrConvert(String^ InString)
{
	return msclr::interop::marshal_as< std::string >(InString);
}
