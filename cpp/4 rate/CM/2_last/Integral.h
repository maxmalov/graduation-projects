#ifndef _INTEGRAL_
#define _INTEGRAL_

#include "Quadrature.h"
#include "BaseFunction.h"

typedef double (*FUNC)(double);

struct exNullQuadrature {};

class Integral {

	Quadrature* quad;

public:

	Integral(const Quadrature* q) {
		quad = q->clone();
	}

	~Integral() {
		delete quad;
	}
	
	double count(BaseFunction& B, int index, FUNC weight) const {
		if(quad) {
			double response = 0;
			for(int i = 0, N = quad->m(); i < N; ++i) {
				response += (double)(quad->coefs())[i]*weight((quad->pattern())[i])*B((quad->pattern())[i],index);
			}
			return response;
		}
		throw exNullQuadrature();
	}

	double count(BaseFunction& B, int index1, int index2, FUNC weight) const {
		if(quad) {
			double response = 0;
			for(int i = 0, N = quad->m(); i < N; ++i) {
				response += (quad->coefs())[i] * B((quad->pattern())[i], index1) * B((quad->pattern())[i], index2) * weight((quad->pattern())[i]);
			}
			return response;
		}
		throw exNullQuadrature();
	}

	double countD(BaseFunction& B, int index1, int index2, FUNC weight) const {
		if(quad) {
			double response = 0;
			for(int i = 0, N = quad->m(); i < N; ++i) {
				response += (quad->coefs())[i] * B.derivative((quad->pattern())[i], index1) * B((quad->pattern())[i], index2) * weight((quad->pattern())[i]);
			}
			return response;
		}
		throw exNullQuadrature();
	}
};

#endif