#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;


template <typename T>
class Stack
{
private:
	int t; //top index of stack
	int size; // size of stack
	T* stack; //array to act as a stack

public:
	Stack()
	{
		this->size = 0;
		this->t = -1;
		this->stack = new T;
	}

	void pop()
	{
		if (!empty()) // if stack is not empty
		{
			this->stack = (T*) realloc (this->stack, (this->size - 1) * sizeof(T)); // decrease the stack size by 1
			this->t--;
			this->size--;
		}
	}

	void push(T value)
	{
		this->stack = (T*)realloc(this->stack, (this->size + 1) * sizeof(T)); // increase the stack size by 1
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
			return this->stack[this->t]; // return the top index
	}

	~Stack()
	{
		delete this->stack;
	}
};
#endif