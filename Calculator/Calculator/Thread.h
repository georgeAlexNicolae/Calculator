#ifndef THREAD_H
#define THREAD_H

#include <fstream>
#include <vector>
#include "Engine.h"
#include "ExpressionMenu.h"

class Thread
{
	static int num_runs;
private:
	vector <double>* results; // vector that saves the results of expressions
public:
	Thread();
	void perfromAction(int);
	static vector<double>* readFromFile();
	static void solveExpression();
	static void printOrFile(vector<double>*);
	static bool saveResults();
	void run();
	~Thread();
};
#endif

