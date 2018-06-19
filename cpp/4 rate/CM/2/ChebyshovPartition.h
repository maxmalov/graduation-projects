#ifndef _CHEB_PART_
#define _CHEB_PART_

#include "SegmentPartition.h"
#include <math.h>

#define PI 3.1415926

class ChebyshovPartition : public SegmentPartition
{
	static int dCompare( const void* a1, const void* a2) {
		if(* (double *)a1 > * (double*)a2) return 1;
		if(* (double *)a1 < * (double*)a2) return -1;
		return 0;
	}

public:

	ChebyshovPartition(int N) 
		: SegmentPartition (-1,1,N) {
		pts[0] = -1;
		for(int i = 1; i < ptCount - 1; ++i) {
			pts[i] = cos((2*i+1)*PI/(2*ptCount));
		}
		pts[ptCount - 1] = 1;
		qsort((void* )pts,ptCount,sizeof(double), ChebyshovPartition::dCompare);
	}

	ChebyshovPartition(const ChebyshovPartition& cp) 
		: SegmentPartition((const SegmentPartition&)cp) {
	}

	~ChebyshovPartition(void) {
	}

	virtual SegmentPartition* clone() const {
		return new ChebyshovPartition(*this);
	}
};

#endif
