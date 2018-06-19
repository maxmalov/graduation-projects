#ifndef _QUADRATURE_
#define _QUADRATURE_

class Quadrature {
	
protected: 

	int _m;
	double* _coefs;
	double* _pattern;

	Quadrature(void) { }

	Quadrature(const Quadrature& quad) {
		_m = quad._m;
		_coefs = new double [_m];
		_pattern = new double [_m];
		for(int i = 0; i < _m; ++i) {
			_coefs[i] = quad._coefs[i];
			_pattern[i] = quad._pattern[i];
		}
	}

public:

	Quadrature(int m, double* coefs, double* pattern) {
		_m = m;
		_coefs = new double [_m];
		_pattern = new double [_m];
		for(int i = 0; i < _m; ++i) {
			_coefs[i] = coefs[i];
			_pattern[i] = pattern[i];
		}
	}

	~Quadrature(void) {
		delete _coefs;
		delete _pattern;
	}

	double m () const { 
		return _m;
	} 
	
	virtual void log () {};

	const double const* coefs () const {
		return _coefs;
	}
	const double const* pattern () const {
		return _pattern;
	}

	virtual Quadrature* clone() const {
		return new Quadrature(*this);
	}
};

#endif