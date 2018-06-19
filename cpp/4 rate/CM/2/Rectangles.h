#ifndef _RECTANGLES_H_
#define _RECTANGLES_H_

#include "Quadrature.h"

class Rectangles : public Quadrature {
	
	const static int TREATMENT = 100;

public:
	
	Rectangles(const SegmentPartition* sp) {
		_m = (sp->getCount()-1) * TREATMENT;

		_coefs = new double [_m];
		_pattern = new double [_m];
		
		double h = (double)(sp->getR() - sp->getL()) / _m;
		for (int i = 0; i < _m; ++i) {
			_coefs[i] = h;
			_pattern[i] = (i + 0.5) * h;
		}
	}

	~Rectangles(void) {}
};

#endif

