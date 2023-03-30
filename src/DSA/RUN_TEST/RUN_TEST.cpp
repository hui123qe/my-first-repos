//#include<stdlib.h>
#include"../../../inclue/DSA/DSA_List/List.hpp"
#include"../../../inclue/DSA/DSA_Stack/Stack.hpp"
#include"../../../inclue/DSA/DSA_Vector/Vector.hpp"


int main()
{
	
	int A[8];
	for (int i = 0; i < 8; i++)
	{
		A[i] = i;
	}
	Vector<int> vector(A, 8);
	vector.insert(1);
	vector.insert(1, 10);
	vector.insert(9);
	//vector.print();
	//cout << vector.find(0) << endl;
	//cout << vector[1] << endl;
	Vector<int> vector1;
	vector1= vector;
	vector1.print();
	cout << endl;
	cout <<  vector1.remove(2)<<endl;
	cout << endl;
	vector1.print();
	cout << vector1.remove(2, 6) << endl;
	vector1.print();

	system("pause");
	return 0;
}