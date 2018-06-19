#ifndef _SEGMENT_PART_
#define _SEGMENT_PART_

#include <iostream>
using namespace std;

class SegmentPartition {

protected: 

	double l,r;
	double* pts;
	int ptCount;

public:

	SegmentPartition (double _l, double _r, int N) {
		l = _l;
		r = _r;
		pts = new double[N];
		ptCount = N;		
	}

	SegmentPartition (const SegmentPartition& sp) {
		l = sp.l;
		r = sp.r;
		ptCount = sp.ptCount;

		pts = new double [ptCount];
		for (int i = 0; i < ptCount; ++i) {
			pts[i] = sp.pts[i];
		}
	}

	double operator [] (int idx) const {
		if (-1 < idx && idx < ptCount) {
			return pts[idx];
		}
	}

	virtual ~SegmentPartition () {
		delete pts;
	}

	int getCount() const {
		return ptCount;
	}

	int getL() const {
		return l;
	}
	int getR () const {
		return r;
	}

	virtual SegmentPartition* clone () const {
		return new SegmentPartition(*this);
	}
};

#endif