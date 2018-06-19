#pragma once
#include "input.h"
#include <iostream>
#include <iomanip>
using namespace std;

//returns (t-x0)*...*(t-xN-1)
//stable++
double mult(double* x, double t, int N) {
	double response = 1;
	for(int j = 0; j < N; ++j) {
		response *= (t - x[j] == 0) ? 1 : (t - x[j]);
	}
	return response;
}

double absD(double x) {
	return (x>0)?x:-x;
}

//counts k-th divided difference value
//k should be <= N-1 !!!
//stable
double divDifference (double* x, int k, double (__cdecl *f )(double)) {
	
	if(k == 1) return f(x[0]);

	double response = 0;
	for(int i = 0; i < k + 1; ++i)
		response += f(x[i]) / mult(x,x[i],k+1);

	return response;
}

// input = [t,x0,x1,...,xN-1]
// 0<=seg<=N-2
//stable
//Count segment error
double segErrNewton (double (__cdecl *f )(double), double* x, double* input, 
					 int segidx, int n, int N) {
	
	double errMax = 0, err = 0;
	
	double h = absD((input[segidx+1] - input[segidx])/n);
	for (double i = input[segidx] + h; i <= input[segidx+1] - h; i += h ) {
		x[0] = i;
		err = absD(divDifference(x,N,f)*mult(x,x[0],N+1));
		errMax = (err > errMax) ? err : errMax;
	}
	
	return errMax;
}

//Count result error
double errNewton(double (__cdecl *f )(double), double* input, int n, int N) {
	
	double* x = new double [N+1];
	x[0] = 0;
	for(int i = 1; i < N+1; ++i) {
		x[i] = input[i-1];
	}
	
	double errMax = 0, err = 0;
	for(int i = 0; i < N - 1; ++i) {
		err = segErrNewton(f,x,input,i,n,N);
		errMax = (err > errMax) ? err : errMax; 
	}

	delete x;
	return errMax;
}
