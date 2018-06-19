#pragma once

#include "operations.h"
struct exZero {};
double** LUView(double**,int);
vector<double> LSolve(double**, int, int);
vector<double> USolve(double**, vector<double>, int);
double** InvMatr(double** , int);

double** LUView(double** ptDst,int nSize)
{
	double** ptMatrix = new double* [nSize];
	for( int i = 0; i < nSize; ++i ) ptMatrix[i] = new double [nSize];

	double sum = 0;
	for (int i = 0; i < nSize; i++)
	{
		for (int j = 0; j < nSize; j++)
		{
			ptMatrix[0][j] = ptDst[0][j];
			//if( ptMatrix[0][0] == 0 )
			//{ 
			//	Clear(ptMatrix, nSize );
			//	return 0;
			//}

			ptMatrix[i][0] = ptDst[i][0]/ptMatrix[0][0];
            
			if(i<=j)
			{
				sum = 0;
				for(int k = 0; k < i; ++k)
					sum += ptMatrix[i][k] * ptMatrix[k][j];
				ptMatrix[i][j] = ptDst[i][j] - sum;
				//if(ptMatrix[i][j] == 0) 
				//	return 0;
			}
			else
			{
				sum = 0;
				for(int k = 0; k < j; ++k)
					sum += ptMatrix[i][k] * ptMatrix[k][j];
				//if( ptMatrix[j][j] == 0 )
				//{
				//	Clear(ptMatrix, nSize);
				//	return 0;
				//}
				ptMatrix[i][j] = (ptDst[i][j] - sum)/ptMatrix[j][j];
			}
		}
	}

	return ptMatrix;
}

vector<double> LSolve(double** ptMatrix, int n, int id)
// ptMatrix should be LU-view
{
	vector<double> x(n);

	double sum = 0;

	if(id == 0) x[0] = 1;
	else x[0] = 0;
	
	for(int i = 1; i < n; ++i)
	{
		sum = 0;
		for(int j = 0; j < i; ++j)
			sum += ptMatrix[i][j] * x[j];
		if( i == id ) x[i] = 1 - sum;
		else x[i] = -sum;
	}

	return x;
}

vector<double> USolve(double** ptMatrix, vector<double> b, int nSize)
// ptMatrix should be LU-view
{
	vector<double> x(nSize);
	
	double sum = 0;
	x[nSize -1] = b[nSize -1]/ptMatrix[nSize -1][nSize-1];
	for(int i = nSize-2; i >= 0; --i)
	{
		sum = 0;
		for(int j = nSize - 1; j >= i; --j)
			sum += ptMatrix[i][j] * x[j];
		x[i] = (b[i] - sum)/ptMatrix[i][i];
	}

	return x;
}

double** InvMatr(double** ptMatrix, int n)
{
	vector<double> column;
	double** ptLU = LUView(ptMatrix,n);
	if(ptLU == 0) return 0;

	double** ptRes = new double* [n];
	for( int i = 0; i < n; ++i ) ptRes[i] = new double [n];

	for( int j = 0; j < n; ++j )
	{
		column = USolve(ptLU, LSolve(ptLU,n,j), n);
		for(int i = 0; i < n; ++i) ptRes[i][j] = column[i];
	}
	return ptRes;
}
