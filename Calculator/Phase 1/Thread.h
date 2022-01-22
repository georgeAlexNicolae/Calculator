#ifndef THREAD_H
#define THREAD_H

#include "Engine.h"

class Thread
{
	static int num_runs;
private:
	Engine engine;
public:
	Thread();
	void run();
};
#endif

