#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include <iostream>
using namespace std;

#define PI 3.1415

//compare function for double
int dCompare( const void* a1, const void* a2) {
	if(* (double *)a1 > * (double*)a2) return 1;
	if(* (double *)a1 < * (double*)a2) return -1;
	return 0;
}

double* arrE (double a, double b, int N) {
	double* response = new double [N];
	double h = (b-a)/N;
	
	response[0] = a;
	int i;
	double x;
	for(x = a + h, i = 0; x < b - h, i < N - 1; x += h, ++i) {
		response[i] = x;
	}
	response[N-1] = b;
	qsort((void* )response,N,sizeof(double),dCompare);
	return response;
}

double* arrCh (int N) {
	double* response = new double [N];
	for(int i = 0; i < N; ++i) {
		response[i] = cos((2*i+1)*PI/(2*N));
	}
	qsort((void* )response,N,sizeof(double),dCompare);
	return response;
}

double* arrEE (double a, double b, int N) {
	double* tmp = arrCh(N);
	
	double e0 = tmp[(N-1)/2-1],
		e1 = tmp[(N-1)/2],
		e2 = tmp[(N-1)/2+1];
	double* response = new double[3*N-2];
	int i = 0;
	for(; i < (N-1)/2-1; ++i) {
		response[i] = tmp[i];
	}
	double h = (e1-e0)/N, x;
	for(x = e0; i < 3*(N-1)/2; ++i, x += h) {
		response[i] = x;
	}
	for(x=e1; i < 3*(N-1)/2 + N; ++i, x+=h) {
		response[i] = x; 
	}
	for(int j = (N-1)/2+1; i<3*N-2 && j < N; ++i, ++j) {
		response[i] = tmp[j];
	}
	return response;

} 
