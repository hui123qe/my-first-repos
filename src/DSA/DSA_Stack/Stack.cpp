#include"..\..\..\inclue\DSA\DSA_Stack\Stack.h"

void convert(Vector<char> &S, __int64 n, int base)
{
	static char digit[] = { '1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','H' };
	
	if (n > 0)
	{
		S.push(digit[n%base]);
		convert(S, n / base, base);
	}

}

void convert(Vector<char> &S, __int64 n, int base)
{
	static char digit[] = { '1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','H' };

	while (n > 0)
	{
		S.push(digit[n%base])
		n = n / base;
		
	}
}