#pragma once

#include<fstream>
#include<vector>
#include<iostream>
using namespace std;


double** LCouple(int);
double** RCouple(int);
double** Identity(int);
double** JForm(const char*, int&);
double** Mult (double**,double**, int);	
double** Coupling( double**, double**, double**, int);
void Clear(double**, int);
void Print(ofstream&, double**, int);
double Norm(double**, int);



double** LCouple(int n)
// Creates following matrix:
// 1  0  0 ...  0
// -1 2 -1 ...  0
// .............
// 0  0  0 ... -1
// 0  0  ...-1  2
{
	double** ptMatr = new double* [n];
	for( int i = 0; i < n; ++i ) ptMatr[i] = new double [n];

	ptMatr[0][0] = 1;
	ptMatr[0][1] = -1;
	for(int j = 2; j < n; ++j) ptMatr[0][j] = 0; 

	for(int i = 1; i < n - 1; ++i)
	{
		for(int j = 0; j < i - 1; ++j)
			ptMatr[i][j] = 0;
		
		ptMatr[i][i-1] = ptMatr[i][i+1] = -1;
		ptMatr[i][i] = 2;

		for(int j = i + 2; j < n; ++j)
			ptMatr[i][j] = 0;
	}

	for(int j = 0; j < n - 2; ++j) ptMatr[n-1][j] = 0; 
	ptMatr[n-1][n-2] = -1;
	ptMatr[n-1][n-1] = 2;

	return ptMatr;
}

double** RCouple(int n)
// Creates following matrix:
// n	n-1	n-2 ... 1
// n-1	n-1 n-2 ... 1
// n-2	n-2 n-2 ... 1
// .............
// 1	1	1 ... 1
{
	double** ptMatr = new double* [n];

	for(int i = 0; i < n; ++i)
	{
		ptMatr[i] = new double [n];
		for(int j = 0; j < i + 1; ++j)
			ptMatr[i][j] = n - i;
		for(int j = i + 1; j < n; ++j)
			ptMatr[i][j] = n - j;
	}

	return ptMatr;
}

double** JForm( const char* path, int& size)
//return Jordan matrix form 
{
	size = 0; 
	ifstream ifs(path);
	ifs >> size;	
	
	double** ptMatr = new double* [size];
	for( int i = 0; i < size; ++i ) ptMatr[i] = new double [size];

	int q = 0;
	ifs >> q;

	int ratio, value, k = 0;
	int r = 0;

	for(int n = 0; n < q; ++n)
	{
		ifs >> value;
		ifs >> ratio;
		r = 0;

		for(int i = k; i < k + ratio; ++i)
		{
			for(int j = 0; j < i; ++j) 
				ptMatr[i][j] = 0;
			
			ptMatr[i][i] = value;				
			if( (ratio > 1) && (i!=size-1) ) 
			{
				if(r<ratio-1) ptMatr[i][i+1] = 1;
				else ptMatr[i][i+1] = 0;
				for(int j = i + 2; j < size; ++j)
					ptMatr[i][j] = 0;
				r++;
			}
			if( (ratio == 1) &&  (i!=size-1) ) 
			{
				for(int j = i + 1; j < size; ++j)
					ptMatr[i][j] = 0;
			}												
		}
		k += ratio;
	}

	ifs.close();
	return ptMatr;
}

double** Mult (double** lm,double** rm, int n)	
// returns result of multiplication
{
	double** ptMatr = new double* [n];

	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		ptMatr[i] = new double [n];
		for (int j = 0; j < n; j++)
		{		
			sum = 0;
			for (int k = 0; k < n; k++)
				sum += lm[i][k] * rm[k][j];
			ptMatr[i][j] = sum;
		}
	}
	return ptMatr;
}

double** Coupling( double** lc, double** dst, double** rc, int n)
//couples matrix dst with lc in left way & rc in right way 
{
	return Mult( Mult(lc,dst,n), rc, n);
}

void Clear(double** ptM, int size)
{
	for( int i = 0; i < size; ++i ) delete[] ptM[i];
	delete[] ptM;
}

void Print( ofstream& off, double** ptMatrix, int nSize )
{
	for(int i = 0; i < nSize; ++i)
	{
		for(int j = 0; j < nSize; ++j)
			off << ptMatrix[i][j] <<"\t\t";
		off<<endl;
	}
}

double Norm(double** ptMatrix, int n)
{
	double max = 0;
		
	double sum = 0;
	for(int i = 0; i < n; ++i)
	{
		sum = 0;
		for(int j = 0; j < n; ++j)
		{	
			if( ptMatrix[i][j] < 0 ) sum -= ptMatrix[i][j];
			else sum += ptMatrix[i][j];
		}
		if(sum > max) max = sum;
	}
	return max;
}