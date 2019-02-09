// LogicDLL.h
#pragma once

#include"RegulaFalsi.h"
#include"Secant.h"
#include"Mullers.h"
#include"CroutsCholesky.h"
#include "GaussJacobi.h"
#include "GaussSeidel.h"

#include "Regression.h"
#include "NewtonsDDifference.h"
#include "Integration.h"
#include "Differentiation.h"

using namespace std;
using namespace System;

namespace CashewLogicDLL 
{
	public ref class CashewLogic
	{
	public:
		property int ItrProp
		{
			int get(){return MaxItr;}
			void set(int setdata) { MaxItr = setdata;}
		}
		property double AbsProp
		{
			double get(){return Absolute;}
			void set(double setdata) { Absolute = setdata;}
		}
		property double RelProp
		{
			double get(){return Relative;}
			void set(double setdata) { Relative = setdata;}
		}
		double  ImpRegula(String^,double,double);
		double  ImpSecant(String^,double,double);
		double  ImpMuller(String^,double,double,double);
		String^ ImpCClsky(String^);
		String^ ImpGJcobi(String^);
		String^ ImpGSeidl(String^);

		String^ ImpLReggression(String^,String^);
		String^ ImpNewtonsDDiff(String^,String^);
		
		double ImpIntegTrapezd(String^, double, double, int);
		double ImpIntegOneThrd(String^, double, double, int);
		double ImpIntegThreEht(String^, double, double, int);

		double ImpForwardDDiff(String^,double, double);
		double ImpBackwrdDDiff(String^,double, double);
		double ImpCentereDDiff(String^,double, double);

		string  StrConvert(String^);
	private:
		double Absolute;
		double Relative;
		int	   MaxItr;
	};
}
