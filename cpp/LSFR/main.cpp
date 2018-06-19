#include <iostream>
#include "CustomLfsr.h"

using namespace std;

void main () 
{
	const int length = 7;
	unsigned short polynom[length] = {0,1,0,1,0,1,0};
	unsigned short start[length] = {1,1,1,1,0,0,0};
	Lfsr* lfsr = new CustomLfsr(polynom, start, length);

	const int count = 50;
	const unsigned short* key = lfsr->run(count);

	unsigned short text[count] = {0,1,1,0,0,0,1,0,1,0,1,1,1,0,0,1,1,1,0,1,0,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,1,0,1,1,1,0,0,1,1,1,0,1,0,1};

	for(int i = 0; i < count; ++i)
	{
		cout << (text[i] + key[i]) % 2 << " ";
	}
}