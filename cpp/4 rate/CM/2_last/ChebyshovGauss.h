#ifndef _GAUSS_H_
#define _GAUSS_H_

#include "Quadrature.h"
#include <iostream>
using namespace std;

class ChebyshovQuadrature: public Quadrature {

public:

	ChebyshovQuadrature () {
		_m = 7;
		_coefs = new double [_m];
		_pattern = new double [_m];
		for(int i = 0; i < _m; ++i) {
			_coefs[i] = (double) 2/_m;
		}

		_pattern[0] = -0.883862;
		_pattern[1] = -0.529657;
		_pattern[2] = -0.323912;
		_pattern[3] = 0;
		for(int i = 4; i < _m; ++i) {
			_pattern[i] = -_pattern[_m-i-1];
		}
		/*
		for(int i = 0; i < _m; ++i) {
			cout<<_coefs[i]<<" "<<_pattern[i]<<endl;
		}
		*/	
	}
};

class GaussQuadrature: public Quadrature {

public:

	GaussQuadrature () {
		_m = 7;
		_coefs = new double [_m];
		_pattern = new double [_m];
		
		_pattern[0] = -0.0491079123427596;
		_pattern[1] = -0.7415311855993944;
		_pattern[2] = - 0.4058451513773970;
		_pattern[3] = 0;
		_pattern[4] = - _pattern[2];
		_pattern[5] = - _pattern[1];
		_pattern[6] = - _pattern[0];
		
		_coefs[0] = _coefs[6] = 2 * 0.0647424830844348;
		_coefs[1] = _coefs[5] = 2 * 0.1398526957446384;
		_coefs[2] = _coefs[4] = 2 * 0.1909150252525595;
		_coefs[3] = 0.2089795918367347;
		/*
		for(int i = 0; i < _m; ++i) {
			cout<<_coefs[i]<<" "<<_pattern[i]<<endl;
		}
		*/	
	}
};

#endif