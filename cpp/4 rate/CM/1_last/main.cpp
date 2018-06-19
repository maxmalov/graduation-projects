#include "count.h"
#include <math.h>
#include <iostream>
#include <windows.h>
using namespace std;

//input functions
double f1(double t) {
	return 1/sqrt(2-t*t);
}
double f2(double t) {
	return absD(t);
}

int main() {
	double a = -1, b = 1;
	double* x = 0;
	int n = 100;
	
	double err1 = 0;
	double* tmp;

	
	int N = 5;
	
	//x = arrEE(a,b,N);
	//	cout<<'\n';
	
	//for(int i = 0; i<3*N-2; ++i) {
	//	cout<<x[i]<<endl;
	//}

	
	for(N = 1000; N < 2000; N += 2) {
		tmp = x;
		x = arrCh(N);
		delete tmp; tmp = 0;
		err1 = errNewton(f2,x,n,N);
		cout<<"Degree: "<<N-1<<" Error: "<<err1<<endl;	
	}
	
}
