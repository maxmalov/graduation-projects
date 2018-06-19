#pragma once

class Lfsr
{
public:

	virtual const unsigned short* run (int length) const = 0;

	virtual ~Lfsr(void)
	{
	}
};

