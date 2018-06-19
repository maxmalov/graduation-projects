#ifndef _BASE_FUNC_
#define _BASE_FUNC_

#include "Interpolation.h"
	
class BaseFunction : public Interpolation {
	
	int index;

	double idx (double x) const {
		 return (x == (*input)[index]) ? 1:0;
	}

	double Mult(double x, int end, int without) const {
		double res = 1;
		for(int i = 0; i < end; ++i) {
			res *= (i == without) ? 1 : (x-(*input)[i]);
		}
		return res;
	}

	double SumMult (double x, int end) const {
		if(end == 1) return 1;
		double res = 0;
		for(int i  = 0; i < end; ++i) {
			res += Mult(x, end, i);
		}
		return res;
	}

	double divDifference (int k) const {
		
		if(k < index) return 0;
		if(k == 0) return idx((*input)[0]); 
		
		return 1 / mult(index,k);
	}

public: 

	BaseFunction(const SegmentPartition* sp) 
		: Interpolation(sp) {
	}

	~BaseFunction() {
	}

	double operator () (double x, int _index) {
		index = _index;
		return (*(Interpolation*)this)(x);
	}

	double derivative (double x, int _index) {
		index = _index;
		double res = divDifference(1);
		for(int i = 2, N = input->getCount(); i < N; ++i) {
			res += divDifference(i) * SumMult(x,i);
		}
		return res;
	}

};


#endif