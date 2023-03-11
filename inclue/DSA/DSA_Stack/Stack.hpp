#pragma once
//#include<iostream>
#include"../../../inclue/DSA/DSA_Vector/Vector.hpp"
using namespace std;

template<typename T>
class Stack :public Vector<T>
{
public:
	void push(T const e) { return insert(e); }
	T pop() { return remove(this->size() - 1); }
	T top() { return this[this->size() - 1]; }
};

