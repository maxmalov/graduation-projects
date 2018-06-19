#ifndef _JMATRIX_H_
#define _JMATRIX_H_

#include "AMatrix.h"

class JMATRIX: public AMATRIX
{
	struct EIGENNUMBER
	{
		double dENumber;
		int nRatio;
	};

	EIGENNUMBER* ptJMatrix;
	int nSize;
};

#endif
