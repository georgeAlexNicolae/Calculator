#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;


template <typename T>
class Stack
{
private:
	int t;
	int size;
	T* stack;

public:
	Stack()
	{
		this->size = 0;
		this->t = -1;
		this->stack = new T;
	}

	void pop()
	{
		if (!empty())
		{
			this->stack = (T*) realloc (this->stack, (this->size - 1) * sizeof(T));
			this->t--;
			this->size--;
		}
	}

	void push(T value)
	{
		this->stack = (T*)realloc(this->stack, (this->size + 1) * sizeof(T));
		this->stack[this->size] = value;
		this->size++;
		this->t++;
	}

	bool empty()
	{
		if (this->size == 0)
			return true;
		else
			return false;
	}

	T top()
	{
		if (!empty())
			return this->stack[this->t];
	}

	~Stack()
	{
		delete this->stack;
	}
};
#endif