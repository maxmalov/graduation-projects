#include <windows.h>
#include <iostream>

int main()
{
	char* ch = 0;
	int a, b = 3, c = 0;
	
	__try
	{
		ch[0] = '*';
	}
	__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ?
				EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		std::cout<<"Null pointer\n";
	}


	__try
	{
		a = b / c;
	}
	__except ((GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO) ?
				EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		std::cout<<"Zero division\n";
	}
	return 0;
}