#ifndef _UNIF_PART_
#define _UNIF_PART_

#include "SegmentPartition.h"

class UniformPartition : public SegmentPartition {

public:

	UniformPartition(double l, double r, int N) 
		: SegmentPartition(l,r,N) {
		int i = 0;
		for(double x = l, h = (r - l) / (ptCount - 1); i < ptCount - 1; x += h, ++i) {
			pts[i] = x;
		} 
		pts[ptCount-1] = r;
	}

	UniformPartition(const UniformPartition& up) 
		: SegmentPartition((const SegmentPartition&)up) {
	}

	~UniformPartition(void) {
	}

	SegmentPartition* clone() const {
		return new UniformPartition(*this);
	}
};

#endif
