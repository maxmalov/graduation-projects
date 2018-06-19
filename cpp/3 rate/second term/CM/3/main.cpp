#include "Jacobi.h"
#include <time.h>
#include "vld.h"

#define SIZE	500

void main()
{
	double accuracy = 1.e-9;
	ofstream ofs("input.txt");
	ofs<<SIZE<<endl;

	for(int i = 0; i < SIZE / 2; ++i)
		ofs<< (rand()%9 + 1) * 1000000 << " ";
	for(int i = SIZE / 2; i < SIZE; ++i )
		ofs<< (rand()%9 + 1) << " ";

	ofs<<endl<<accuracy;
	ofs.close();
		
	MatrixData* md = ReadFile( "input.txt", accuracy );

	ofstream off ("output.txt", ios_base::app );
	clock_t start = clock();
	JacobiElim(md, accuracy, off);
	clock_t finish = clock();
	off << "Elapsed time: " << (double) (finish - start) / CLOCKS_PER_SEC << endl;
	off.close();

	delete md;
}