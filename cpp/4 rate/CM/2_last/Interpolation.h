#ifndef _INTERPOLATION_
#define _INTERPOLATION_

#include "SegmentPartition.h"

class Interpolation {

	Interpolation(void);
	Interpolation(const Interpolation&);

protected: 

	SegmentPartition* input;

	double mult(double x, int k) const {
		
		if(k < 0) return 1;

		double response = 1;
		for(int j = 0; j <= k; ++j) {
			response *= (x - (*input)[j]);
		}
		return response;
	}
	
	double mult (int idx, int k) const {
		if(k < 0) return 1;

		double response = 1;
		for(int j = 0; j <= k; ++j) {
			response *= (idx == j) ? 1 : ((*input)[idx] - (*input)[j]);
		}
		return response;
	}

	double absD(double x) const {
		return (x>0)?x:-x;
	}

	virtual double divDifference (int k) const = 0;

public:

	Interpolation(const SegmentPartition* sp) {
		input = sp->clone();
	}

	double operator () (double x) {
		double response = 0;
		for(int i = 0, N = input->getCount(); i < N; ++i) {
			response += divDifference(i) * mult(x,i-1);
		}
		return response;
	}

	virtual ~Interpolation(void) {
		delete input;
	}

};


#endif