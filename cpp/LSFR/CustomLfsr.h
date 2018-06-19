#pragma once

#include "Lfsr.h"

struct Exception {};

class CustomLfsr : public Lfsr
{
	unsigned  short* _polynom;
	unsigned  short* _start;
	int _length;

public:

	CustomLfsr(unsigned short* polynom, unsigned short* start, int length)
	{
		_length = length;
		_polynom = new unsigned short[length];
		_start = new unsigned short[length];
		for(int i = 0; i < length; ++i) 
		{
			if(polynom[i] > 1 || start[i] > 1) 
			{
				throw Exception();
			}
			_polynom[i] = polynom[i];
			_start[i] = start[i];
		}
	}

	const unsigned short* run (int length) const
	{
		unsigned  short* result = new unsigned  short[length];
		int i = 0;
		for(i; i < _length; ++i)
		{
			result[i] = _start[i];
		}

		for(i; i < length; ++i) 
		{
			result[i] = 0;
			for(int j = 1; j < _length + 1; ++j) 
			{
				result[i] += _polynom[j-1] * result[i - j];
			}

			result[i] %= 2;
		}

		return result;
	} 

	~CustomLfsr(void)
	{
		delete _polynom;
		delete _start;
		_start = 0;
		_polynom = 0;
	}
};

