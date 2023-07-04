#pragma once
//#include<iostream>
#include"../../../inclue/DSA/DSA_Vector/Vector.hpp"
#include"../../../inclue/DSA/DSA_List/List.hpp"
using namespace std;

template<typename T>
class Stack :public Vector<T>
{
public:
	void push(T const e) { return insert(e); }
	T pop() { return remove(this->size() - 1); }
	T top() { return this[this->size() - 1]; }
};

template<typename T>
class Stack :public List<T>
{
public:
	void push(T const e) { InsertAsFirst(e) };
	T pop() 
	{ 
		if (this->head == NULL)return;
		T temp=head->succ->data;
		remove(first());
		return temp;
	};
	T top() 
	{
		return (first())->data;
	};
};