#ifndef _COMBO_H_
#define _COMBO_H_

#include "Quadrature.h"

#include <iostream>
using namespace std;

class ComboSimpson : public Quadrature {
	static const int TREATMENT = 8; 
public: 
	ComboSimpson(const SegmentPartition* sp) {

		_m = (sp->getCount()-1)*TREATMENT + 1;
		_coefs = new double [_m];
		_pattern = new double [_m];

		double h = (double)(sp->getR() - sp->getL()) / (_m-1);
		double x = 0;

		for(int i = 0; i < _m; ++i, x += h) {
			_coefs[i] = (i == 0 || i == _m-1) ? h/3 : ( (i%2 == 0) ? (double)2*h/3 : (double)4*h/3 );
			_pattern[i] = x;
		}
	}
};

class ComboTrapeze : public Quadrature {
	static const int TREATMENT = 8; 
public: 
	ComboTrapeze(const SegmentPartition* sp) {

		_m = (sp->getCount()-1)*TREATMENT + 1;
		_coefs = new double [_m];
		_pattern = new double [_m];

		double h = (double)(sp->getR() - sp->getL()) / (_m-1);
		double x = 0;

		for(int i = 0; i < _m; ++i, x += h) {
			_coefs[i] = (i == 0 || i == _m-1) ? h/2 : h;
			_pattern[i] = x;
		}
	}
};

#endif