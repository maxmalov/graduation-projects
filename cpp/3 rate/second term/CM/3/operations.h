#pragma once

#include<fstream>
#include<vector>
#include<list>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
using namespace std;

double** LCouple(int);
double** RCouple(int);
double** Mult(double**,double**, int);	
double** Coupling( double**, double**, double**, int);
void Clear(double**, int);
void Print(ofstream&, double**, int);
double Norm(list<double>&); 

double absD ( double x )
{
	return ( x > 0 ) ? x :( -x );
}

struct MatrixData
{
	double** ptMatrix;
	vector<double> EValues;
	int nSize;

	MatrixData():ptMatrix(0), nSize(0)
	{}
	
	MatrixData(const MatrixData& md)
	{
		EValues = md.EValues;
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
};

MatrixData* ReadFile(const char*, double&);

struct Couple
{
	double **lc, **rc;
	int nSize;
	Couple(int n)
	{
		nSize = n;
		rc = new double* [n];
		lc = new double* [n];
		for(int i = 0; i < n; ++i ) 
		{
			lc[i] = new double [n];
			rc[i] = new double [n];
			for(int j = 0; j < n; ++j)
				lc[i][j] = rc[i][j] = 0;
		}

		for(int i = 0; i < n; ++i )
		{
			for(int j = i; j < n-1; ++j)
				lc[j][i] = rc[i][j] = 1 / sqrt( (double) (j + 1) * (j + 2) ) ;
			lc[n-1][i] = rc[i][n-1] = 1 / sqrt( (double) n );
		}
		for(int i = 0; i < n - 1; ++i)
			lc[i][i+1] = rc[i+1][i] = -sqrt((double)(i + 1) / (i + 2) );
	}
	~Couple()
	{
		Clear(lc,nSize);
		Clear(rc,nSize);
	}
};

double** Mult (double** lm,double** rm, int n)	
{
	double** ptMatr = new double* [n];

	for (int i = 0; i < n; i++)
	{
		ptMatr[i] = new double [n];
		for (int j = 0; j < n; j++)
		{		
			ptMatr[i][j] = 0;
			for (int k = 0; k < n; k++)
				ptMatr[i][j] += lm[i][k] * rm[k][j];
		}
	}
	return ptMatr;
}

double Norm(list<double>& src)
{
	list<double>::iterator tmp = src.begin();
	double res = absD(*tmp);
	for(tmp; tmp != src.end(); tmp++)
		res = (res < absD(*tmp)) ? absD(*tmp) : res;
	return res;
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

MatrixData* ReadFile( const char* path, double& Accuracy )
{
	MatrixData* md = new MatrixData;
	Accuracy = 0;
	
	ifstream ifs(path);
	ifs>>md->nSize;

	double** ptMatr = new double* [md->nSize];

	md->EValues.resize(md->nSize);

	for( int i = 0; i < md->nSize; ++i )
	{
		ifs >> md->EValues[i];
		ptMatr[i] = new double [md->nSize];
	}

	ifs >> Accuracy;

	Couple* couple = new Couple(md->nSize);
	for( int i = 0; i < md->nSize; ++i )
		for( int j = 0; j < md->nSize; ++j )
			ptMatr[i][j] = couple->lc[i][j] * md->EValues[j];

	md->ptMatrix = Mult( ptMatr, couple->rc, md->nSize );
	Clear(ptMatr, md->nSize);
	delete couple;
	return md;
}
