#ifndef ENGINE_H
#define ENGINE_H

#include "Stack.h"
#include <string>

class Engine
{
private:
	Stack<char>* brackets; // Stack to store brackets and operands
	Stack<double>* result; // stack to store the final results of computations

public:
	Engine();
	double traverseInputString(string);
	static double calculate(double, double, char);
	static int getPrecedence(char);
	~Engine();
};
#endif

