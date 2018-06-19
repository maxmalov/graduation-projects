#include "lu_method.h"
#include<iostream>
#include<time.h>
using namespace std;
void main()
{
	clock_t start, finish;

	start = clock();

	int nSize = 0;
	double** jf = JForm("input.txt", nSize);
	double** ptMatrix = Coupling( LCouple(nSize), jf, RCouple(nSize), nSize);
	Clear(jf,nSize);

	//ofstream offt("test.txt");
	//Print(offt,ptMatrix,nSize);
	//offt << Norm(ptMatrix,nSize) <<endl;
	//offt << '\n';
	//
	//Print(off,LUView(ptMatrix,nSize), nSize);
	//off.close();
	
	
	
	double** ptInvMatrix = InvMatr(ptMatrix,nSize);
	//Print(offt,ptInvMatrix,nSize);
	//offt << Norm(ptInvMatrix,nSize) <<endl;
	//offt << '\n';

	//Print(offt,Mult(ptMatrix,ptInvMatrix,nSize),nSize);
	//offt.close();

	double** deviant = Mult(ptMatrix, ptInvMatrix, nSize);
	for(int i = 0; i < nSize; ++i) deviant[i][i] -= 1;
	//Print(offt,deviant,nSize);
	//offt << Norm(deviant,nSize) <<endl;
	//offt.close();

	
	ofstream off("output.txt");

	off << "Conditionality: " << Norm(ptMatrix,nSize) * Norm(ptInvMatrix,nSize) << endl; 
	off << "Residual norm: " << Norm(deviant,nSize) << endl; 

	finish = clock();

	off << "Elapsed time: " << (double) (finish - start)/CLOCKS_PER_SEC << " seconds";

	off.close();

	Clear(ptMatrix,nSize);
	Clear(ptInvMatrix,nSize);
	Clear(deviant,nSize);
}