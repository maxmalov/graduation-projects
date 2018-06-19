//#include "UniformPartition.h"
#include "ChebyshovPartition.h"
#include "DiffEquation.h"
#include "Rectangles.h"
#include "Combo.h"
#include "ChebyshovGauss.h"
#include "Result.h"
#include <math.h>
#include <iostream>
using namespace std;

double F(double x) {
	return cos(x);
}

double a (double x) {
	return 1;
}
double b (double x) {
	return 1;
}
double f (double x) {
	return cos(x) - sin(x);
}

double absD (double x) {
	return (x > 0) ? x : -x;
}

void main (void) {

	int N = 5;
	
	SegmentPartition* sp = new ChebyshovPartition(N);
	
	Quadrature* quad1 = new Rectangles(sp);
	Quadrature* quad2 = new ComboSimpson(sp);
	Quadrature* quad3 = new ComboTrapeze(sp);

	Quadrature* qCh = new ChebyshovQuadrature();
	Quadrature* qGs = new GaussQuadrature();

	DifferentialEquation* de = new DifferentialEquation(a,b,f,1);
	Result r(de->solve(quad1,sp), sp);

	double err = absD(F((*sp)[0]) - r((*sp)[0]));
	for(int i = 1; i < sp->getCount(); ++i) {
		err = (err < absD(F((*sp)[i]) - r((*sp)[i]))) ? absD(F((*sp)[i]) - r((*sp)[i])) : err; 
	}

	cout<<err*(1.e-3)<<endl;
	
	delete de;
	delete sp;
	delete quad1;
	delete quad2;
	delete quad3;
	delete qCh;
	delete qGs;
} 