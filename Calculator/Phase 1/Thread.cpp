#include "Thread.h"

int Thread::num_runs = 0;

Thread::Thread() {}

void Thread::run()
{
	string input;
	cout << "Please enter expression: ";
	getline(cin, input);
	cout << "The answer: " << engine.traverseInputString(input) << endl << endl;
	num_runs++;
}
