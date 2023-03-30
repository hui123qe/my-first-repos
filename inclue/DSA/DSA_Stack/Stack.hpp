#pragma once
//#include<iostream>
#include"../../../inclue/DSA/DSA_Vector/Vector.hpp"
using namespace std;

template<typename T>
class Stack :public Vector<T>
{
public:
	T push(T const e) { return this->insert(e); }
	T pop() { return remove(this->size() - 1); }
	T top() { return this[this->size() - 1]; }
};

