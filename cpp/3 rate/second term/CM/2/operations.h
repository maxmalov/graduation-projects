#pragma once

#include<fstream>
#include<vector>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
using namespace std;

//////////////////////////////////////Implementation/////////////////////////////////

double** LCouple(int);
double** RCouple(int);
double** Identity(int);
vector<double> MultV(double**, const vector<double>&, int);
double** Mult(double**,double**, int);	
double** Coupling( double**, double**, double**, int);
void Clear(double**, int);
void Print(ofstream&, double**, int);
double Norm(double**, int);
double NormV(const vector<double>&, int);


struct MatrixData
{
	double** ptMatrix;
	double dEnMax, dEnMin;
	int nSize;

	MatrixData():ptMatrix(0), dEnMax(0), dEnMin(0), nSize(0)
	{}
	
	MatrixData(const MatrixData& md)
	{
		dEnMax = md.dEnMax;
		dEnMin = md.dEnMin;
		nSize = md.nSize;

		ptMatrix = new double* [nSize];

		for(int i = 0; i < nSize; ++i)
		{
			ptMatrix[i] = new double[nSize];
			for(int j = 0; j < nSize; ++j)
				ptMatrix[i][j] = md.ptMatrix[i][j];
		}
	}
	
	~MatrixData()
	{
		Clear(ptMatrix,nSize);
	}

	MatrixData& operator = (const MatrixData& md)
	{
		if(this != &md)
		{
			Clear(ptMatrix, nSize);

			dEnMax = md.dEnMax;
			dEnMin = md.dEnMin;
			nSize = md.nSize;

			ptMatrix = new double* [nSize];

			for(int i = 0; i < nSize; ++i)
			{
				ptMatrix[i] = new double[nSize];
				for(int j = 0; j < nSize; ++j)
					ptMatrix[i][j] = md.ptMatrix[i][j];
			}
		}
		return *this;
	}
};

MatrixData* ReadFile(const char*, vector<double>&, double&);

/////////////////////////////Realisation////////////////////////////////////////

double** RCouple(int n)
{
	double** ptMatr = new double* [n];

	for(int i = 0; i < n; ++i )
    {
		ptMatr[i] = new double [n];
		for(int j = i; j < n-1; ++j)
			ptMatr[i][j] = 1 / sqrt( (double) (j + 1) * (j + 2) ) ;
		ptMatr[i][n-1] = 1 / sqrt( (double) n );
    }
    for(int i = 0; i < n - 1; ++i)
		ptMatr[i+1][i] = -sqrt((double)(i + 1) / (i + 2) );

	ptMatr[n-1][0] = 0;
	
	return ptMatr;
}

double** LCouple(int n)
{
	double** ptMatr = new double* [n];
	
	for( int i = 0; i < n; ++i )
	{
		ptMatr[i] = new double [n];
		for( int j = 0; j < i + 1; ++j )
			ptMatr[i][j] = 1 / sqrt( (double) (i+1) / (i+2) );
	}
	for( int j = 0; j < n; ++j )
		ptMatr[n-1][j] = 1 / sqrt( (double) n);
	for( int j = 0; j < n - 1; ++j )
		ptMatr[j][j+1] = - sqrt( (double) (j+1) / (j+2) );

	ptMatr[0][n-1] = 0;

	return ptMatr;
}

vector<double> MultV(double** A, const vector<double>& b, int nSize)
{
	vector<double> res(nSize);
	double sum = 0;

	for(int i = 0; i < nSize; ++i )
	{
		sum = 0;
		for(int j = 0; j < nSize; ++j )
			sum += A[i][j] * b[j];
		res[i] = sum;
	}

	return res;
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

double NormV(const vector<double>& x, int n)
{
	double max = x[0];
	for(int i = 0; i < n; ++i)
	{
		if(x[i] > max) max = x[i];
		if(-x[i] > max) max = -x[i];
	}

	return max;
}

vector<double> DiffV(const vector<double>& l,const vector<double>& r,int n)
{
	vector<double> res(l);
	for(int i = 0; i < n; ++i)
		res[i] -= r[i];
	return res;	
}

MatrixData* ReadFile( const char* path, vector<double>& AccRoot, double& nIter )
{
	MatrixData* md = new MatrixData();
	
	ifstream ifs(path);
	ifs >> md->nSize;	
	
	double** ptMatr = new double* [md->nSize];
	for( int i = 0; i < md->nSize; ++i ) ptMatr[i] = new double [md->nSize];

	int q = 0;
	ifs >> q;

	double value, EnMax = 0, EnMin = 0; 
	int ratio, k = 0;
	int r = 0;

	ifs >> value;
	EnMax = EnMin = value;
	
	for(int n = 0; n < q; ++n)
	{
		if(value > EnMax) EnMax = value;
		if(value <= EnMin) EnMin = value;
		
		ifs >> ratio;
		r = 0;

		for(int i = k; i < k + ratio; ++i)
		{
			for(int j = 0; j < i; ++j) 
				ptMatr[i][j] = 0;
			
			ptMatr[i][i] = value;				
			if( (ratio > 1) && (i!=md->nSize-1) ) 
			{
				if(r<ratio-1) ptMatr[i][i+1] = 1;
				else ptMatr[i][i+1] = 0;
				for(int j = i + 2; j < md->nSize; ++j)
					ptMatr[i][j] = 0;
				r++;
			}
			if( (ratio == 1) &&  (i!=md->nSize-1) ) 
			{
				for(int j = i + 1; j < md->nSize; ++j)
					ptMatr[i][j] = 0;
			}												
		}
		k += ratio;
		if(n<q-1) ifs >> value;

	}

	AccRoot.resize(md->nSize);
	for(int i = 0; i < md->nSize; ++i) 
		ifs >> AccRoot[i];

	nIter = 0;
	ifs >> nIter;
	
	ifs.close();

	md->ptMatrix = Coupling( LCouple(md->nSize), ptMatr, RCouple(md->nSize), md->nSize );
	
	md->dEnMax = EnMax;
	md->dEnMin = EnMin;

	Clear(ptMatr,md->nSize);

	return md;
}


