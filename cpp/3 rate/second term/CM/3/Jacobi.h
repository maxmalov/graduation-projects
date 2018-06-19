#pragma once
#include<list>
#include "operations.h"

struct Index
{
	int i, j;
};

struct exNullMax {};

Index FindAbsMax ( double** ptMatrix, int nSize )
{
	Index ind;
	
	double max = absD( ptMatrix[0][1] );
	ind.i = 0; ind.j = 1;

	for( int i = 0; i < nSize; ++i )
	{
		for( int j = i + 1; j < nSize; ++j)
		{
			if( max < absD( ptMatrix[i][j] ) )
			{
				max = absD( ptMatrix[i][j] );
				ind.i = i; ind.j = j;
			}
		}
	}

	return ind;
}

double** JIteration ( double** ptMatrix, int nSize, const Index ind )
{
	double** B = new double* [nSize];
	for(int i = 0; i < nSize; ++i)
		B[i] = new double [nSize];

	double p = 2 * ptMatrix[ind.i][ind.j], q = ptMatrix[ind.i][ind.i] - ptMatrix[ind.j][ind.j],
		d = sqrt ( p*p + q*q );

	double r,c,s;

	if( q == 0)
		c = s = sqrt( (double)2 ) / 2;
	else
	{
		r = absD( q ) / ( 2 * d );
		c = sqrt ( 0.5 + r );
		if( absD(p)* 1.0e3 < absD(q) )
			s = absD( p ) * ( ( p*q > 0)? 1:(-1) ) / ( 2*c*d );
		else 
			s = sqrt ( 0.5 - r ) * ( ( p*q > 0)? 1:(-1) );
	}

	for(int i = 0; i < nSize; ++i)
	{
		B[i][i] = ptMatrix[i][i];
		for(int j = i + 1; j < nSize; ++j)
			B[i][j] = B[j][i] = ptMatrix[i][j];
	}

	B[ind.i][ind.i] = c*c*ptMatrix[ind.i][ind.i] + s*s*ptMatrix[ind.j][ind.j] + 2*c*s*ptMatrix[ind.i][ind.j];
	B[ind.j][ind.j] = s*s*ptMatrix[ind.i][ind.i] + c*c*ptMatrix[ind.j][ind.j] - 2*c*s*ptMatrix[ind.i][ind.j];
	B[ind.i][ind.j] = B[ind.j][ind.i] = 0;
	
	for( int m = 0; m < nSize; ++m )
		if(m != ind.i && m != ind.j) B[ind.i][m] = B[m][ind.i] = c*ptMatrix[m][ind.i] + s*ptMatrix[m][ind.j]; 	

	for(int m = 0; m < nSize; ++m )
		if(m != ind.i && m != ind.j) B[ind.j][m] = B[m][ind.j] = -s*ptMatrix[m][ind.i] + c*ptMatrix[m][ind.j]; 	
	
	return B;
}

void JacobiElim ( const MatrixData* md, double Accuracy, ofstream& off )
{
	double** A = md->ptMatrix;
	double** tmp;
	long int q;
	Index ind;
	double absMax = 1;

	for( q = 0;  absMax > Accuracy; ++q)
	{
		ind = FindAbsMax(A, md->nSize);
		absMax = absD(A[ind.i][ind.j]);
		if( q > 0 ) tmp = A;
		A = JIteration( A, md->nSize, ind );
		if( q > 0 ) Clear( tmp, md->nSize );

		cout<<q<<" "<<absMax<<endl;
	}

	list<double> EValues, rEValues;
	list<double>::iterator ita, ite;
	double eNorm, aNorm;
	
	for(int i = 0; i < md->nSize; ++i)
	{
		rEValues.push_front(A[i][i]);
		EValues.push_front(md->EValues[i]);
	}
	EValues.sort();
	rEValues.sort();

	ite = rEValues.begin();
	ita = EValues.begin();

	eNorm = absD(*ite - *ita);
	ite++;
	ita++;
	for(ite,ita; ite != rEValues.end() && ita != EValues.end(); ite++, ita++ )
		eNorm = (eNorm < absD(*ite - *ita )) ? absD(*ite - *ita) : eNorm;
	aNorm = Norm(EValues);

	off<< "_______________________________________________________________________________________________________"<<endl;

	off << "Conditionality: " << EValues.back() / EValues.front() << endl;
	off << "Size: " << md->nSize << endl;
	off << "Accuracy: " << Accuracy << endl;
	off << "\nAbsolute residual: " << eNorm <<endl;
	off << "Relative residual: " << eNorm / aNorm <<endl;
	off << "Iterations: " << q << endl; 

	Clear(A,md->nSize);
}