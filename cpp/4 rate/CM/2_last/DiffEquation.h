#ifndef _DIFF_EQUATION_
#define _DIFF_EQUATION_

#include "SystemLinearEquations.h"
#include "Integral.h"
#include "BaseFunction.h"

//#include <iostream>
//using namespace std;

typedef double (*aFUNC)(double);
typedef double (*bFUNC)(double);
typedef double (*fFUNC)(double);

class DifferentialEquation {
	
	aFUNC _a;
	bFUNC _b;
	fFUNC _f;

	double _startCondition;

	DifferentialEquation(void);
	DifferentialEquation(const DifferentialEquation&);
	
	double count(const SegmentPartition* sp, int i, int j, const Integral* in) const {
		BaseFunction bf(sp);
		return (in->countD(bf, i, j, _a) + 
			in->count(bf, i, j, _b) );
	}
	
	double count(const SegmentPartition* sp, int i, const Integral* in) const {
		return (in->count(BaseFunction(sp), i, _f));
	}
	
	SystemLinearEquations* FillParts (const SegmentPartition* sp, const Integral* in) const {
		SystemLinearEquations* res = new SystemLinearEquations(sp->getCount());
		for(int i = 0, l = res->getSize(); i < l; ++i) {
			for(int j = 0; j < l; ++j) {
				res->put(count(sp,i,j, in),j,i);
			}
			res->put(count(sp,i, in),i);
		}
		return res;
	}

	double* solution;

public: 

	DifferentialEquation(aFUNC a, bFUNC b, fFUNC f, double sc) {
		_a = a;
		_b = b;
		_f = f;
		_startCondition = sc;
		solution = 0;
	}

	~DifferentialEquation(void) {
	}

	const double* solve (Quadrature* quad, SegmentPartition* sp) {
		if(!solution) {
			Integral* integral = new Integral(quad);

			SystemLinearEquations* sle = FillParts(sp,integral);
			
			//cout<<(*sle)<<endl;
			
			const double* resp = sle->count();
			solution = new double [sp->getCount()];
			for(int i = 0, N = sp->getCount(); i < N; ++i) {
				solution[i] = resp[i];			
			}
			resp = 0;

			//cout<<(*sle)<<endl;

			delete integral;
			delete sle;
		}
		return solution;
	}
};

#endif