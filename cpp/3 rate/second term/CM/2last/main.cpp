#include<iostream>
#include<time.h>
using namespace std;

#include "richardson_elimination .h"
//#define TEST

void main()
{
	double nIterQuan;
	vector<double> AccRoot(0);

#ifdef TEST
	//TestingIteration("input.txt");
	MatrixData* md = ReadFile ( "input.txt", AccRoot, nIterQuan );
	ofstream off("test.txt",ios_base::app);
	Print(off, md->ptMatrix, md->nSize);
	off.close();
#endif


#ifndef TEST
	clock_t start, finish;
	start = clock();

	MatrixData* md = ReadFile ( "input.txt", AccRoot, nIterQuan );
	
	
	ofstream off("output.txt",ios_base::app);

	RichElimSolve ( md, AccRoot, off, nIterQuan );

	finish = clock();

	off << "Elapsed time: " << (double) (finish - start)/CLOCKS_PER_SEC << " seconds";

	off.close();
#endif
}