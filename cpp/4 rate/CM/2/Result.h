#ifndef _RESULT_H_
#define _RESULT_H_

#include "BaseFunction.h"

class Result {

	double* y;
	BaseFunction* bf;
	int size;

public:

	Result(const double const* x, const SegmentPartition* sp) {
		
		size = sp->getCount();
		
		y = new double [size];
		
		for(int i = 0; i < size; ++i) {
			y[i] = x[i];
		}

		bf = new BaseFunction(sp);
	}

	double operator () (double x) const {
		
		double res = 0;

		for(int i = 0; i < size; ++i) {
			res += y[i] * (*bf)(x,i);
		}

		return res;
	}

	~Result() {
		delete y;
		delete bf;
	}
};

#endif