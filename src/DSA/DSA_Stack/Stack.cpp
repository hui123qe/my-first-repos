#include"..\..\..\inclue\DSA\DSA_Stack\Stack.hpp"

void convert(Stack<char> &S, __int64 n, int base)
{
	static char digit[] = { '1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','H' };
	
	if (n > 0)
	{
		S.push(digit[n%base]);
		convert(S, n / base, base);
	}

}

//void convert(Stack<char> &S, __int64 n, int base)
//{
//	static char digit[] = { '1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','H' };
//
//	while (n > 0)
//	{
//		S.push(digit[n%base]);
//		n = n / base;
//		
//	}
//}

//get the start and end position of '(' and ')'
bool strim(const char expt[], int &lo, int &hi)
{
	while ((expt[lo] != '(') && (lo < hi) && (expt[lo] != ')'))lo++;
	while ((expt[hi] != ')') && (lo < hi) && (expt[hi] != '('))hi--;
	if ((expt[lo] == ')') && (expt[hi] == '('))return false;
	else return true;
}
////devide the string into some parition of(entir '(' and ')')
//int devide(const char expt[], int &lo, int &hi)
//{
//
//}

