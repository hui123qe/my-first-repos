#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Stack ::public Vector<T>
{
public:
	void push(T const e) { return insert(e); }
	T pop() { return remove(_size-1); }
	T top() { return (this[_size - 1]; }
};

