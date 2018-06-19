#ifndef _NEWT_POL_
#define _NEWT_POL_

#include "Interpolation.h"

typedef double (*pFUNC)(double);

class NewtonPolynom : public Interpolation {

	pFUNC pf;
	
	NewtonPolynom(void);
	NewtonPolynom(const NewtonPolynom &);

	double divDifference (int k) const {
		
		if(k < 0) return pf((*input)[0]);

		double response = 0;
		for(int i = 0; i <= k; ++i)
			response += pf((*input)[i]) / mult((*input)[i],k+1);

		return response;
	}

public:

	NewtonPolynom(const SegmentPartition& sp, double (__cdecl *f )(double)) 
		: Interpolation(sp) {
		pf = f;
	}
	
	~NewtonPolynom(void) {
	}
};

#endif
