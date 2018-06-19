#include<iostream>
#include<time.h>
using namespace std;

#include "richardson_elimination .h"
//#define TEST

void main()
{
#ifdef TEST
	TestingIteration("input.txt");
#endif


#ifndef TEST
	clock_t start, finish;
	start = clock();

	double nIterQuan;
	vector<double> AccRoot(0);

	MatrixData* md = ReadFile ( "input.txt", AccRoot, nIterQuan );
	
	
	ofstream off("output.txt");

	RichElimSolve ( md, AccRoot, off, nIterQuan );

	finish = clock();

	off << "Elapsed time: " << (double) (finish - start)/CLOCKS_PER_SEC << " seconds";

	off.close();
#endif
}