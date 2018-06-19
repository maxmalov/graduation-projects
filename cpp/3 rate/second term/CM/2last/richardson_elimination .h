#pragma once

#include "operations.h"
#include<stdlib.h>
#include<complex>
#include<vector>
#include<time.h>

#define PI	3.14159265358979323846

vector<double>* Iteration ( const MatrixData* md, const vector<double>& b, 
						   const vector<double>* Xk, int nIterNumber, double nIterQuan );

void TestingIteration ( const char* path )
{
	vector<double> AccRoot(0);
	double nIterQuan;

	MatrixData* md = ReadFile( path, AccRoot, nIterQuan );

	vector<double> b = MultV( md->ptMatrix, AccRoot, md->nSize );

	vector<double> Xk(md->nSize);
	srand(time(0));
	for(int i = 0; i < md->nSize; ++i )
		Xk[i] = rand()%20 - 10;
	
	ofstream off("test.txt");

	off<<"-------------- Matrix -----------------"<<endl;
	Print(off,md->ptMatrix,md->nSize);
	off<<"\n";
	
	off<<"--------------- b ----------------------"<<endl;
	for(int i = 0; i < md->nSize; ++i)
		off<<" "<<b[i];
	off<<"\n";

	off<<"--------------- X1 ----------------------"<<endl;
	for(int i = 0; i < md->nSize; ++i)
		off<<" "<<Xk[i];
	off<<"\n";


	vector<double>* Xkk = Iteration ( md, b, &Xk, 2, 4 );
	
	off<<"\n---------------------X2----------------------"<<endl;
	for(int i = 0; i < md->nSize; ++i)
		off<<" "<<(*Xkk)[i];
	
	Xkk = Iteration ( md, b, Xkk, 3, 4 ); 

	off<<"\n---------------------X3----------------------"<<endl;
	for(int i = 0; i < md->nSize; ++i)
		off<<" "<<(*Xkk)[i];

	off.close();
}

vector<double>* Iteration ( const MatrixData* md, const vector<double>& b, 
						   const vector<double>* Xk, int nIterNumber, double nIterQuan )
{
	vector<double>* Xkk = new vector<double>(md->nSize);

	double res, Tk;

	double a = 2 * nIterNumber + 1, c = 2 * nIterQuan;

	Tk = 2 / ( ( md->dEnMax + md->dEnMin ) + ( md->dEnMax - md->dEnMin ) * cos ( a/c * (double)PI ) );

	//Tk = 1;

	for(int i = 0; i < md->nSize; ++i )
	{
		res = 0;
		for(int j = 0; j < md->nSize; ++j)
		{
			if(i == j)
				res += ( 1 - md->ptMatrix[i][j] * Tk ) * (*Xk)[j];
			else
				res += -Tk * md->ptMatrix[i][j] * (*Xk)[j];
		}
		
		res += Tk * b[i];
		(*Xkk)[i] = res;
	}

	return Xkk;
}					    

void RichElimSolve ( const MatrixData* md, const vector<double>& AccRoot, 
					ofstream& off, double nIterQuan )
{
	vector<double> b = MultV( md->ptMatrix, AccRoot, md->nSize );

	vector <double>* Xres = new vector<double> ( md->nSize );
	srand(time(0));
	for(int i = 0; i < md->nSize; ++i )
		(*Xres)[i] = rand()%20-10;

	vector<double>* tmp = 0;

	double absRes = 1, relRes, absErr, relErr;
	long int iter = 0;

	for(;absRes > nIterQuan;)
	{
		//off << "\n------------------- X" << i << " ----------------------"<<endl;
		//for(int i = 0; i < md->nSize; ++i)
		//	off<<" "<<(*Xres)[i];
		//off<<"\n";
		//for(int i = 0; i < md->nSize; ++i)
		//	off<<" "<<AccRoot[i];

		tmp = Xres;
		Xres = Iteration ( md, b, Xres, 0, nIterQuan );
		delete tmp;

		absRes = NormV( DiffV( b, MultV( md->ptMatrix, *Xres, md->nSize ), md->nSize ), md->nSize );
		iter++;
	}
	
	relRes = absRes / NormV( b, md->nSize );

	absErr = NormV( DiffV( AccRoot, *Xres, md->nSize ), md->nSize );
	relErr = absErr / NormV( AccRoot, md->nSize );

	off << " \nAbsolute residual = " << absRes << endl;
	off << " Relative residual = " << relRes << endl;

	off << " Absolute error = " << absErr << endl;
	off << " Relative error = " << relErr << endl;

	off<< "Iterations : " << iter << endl;


}


