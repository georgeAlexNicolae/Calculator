#include "Thread.h"

int Thread::num_runs = 0;

Thread::Thread() {
	this->results = new vector<double>();
}

vector<double>* Thread::readFromFile() // functie care citeste fisierul de expresii (input.txt-ul) linie cu linie
{
	Engine engine;
	vector<double>* results = new vector<double>();
	string filename;
	cin.ignore();
	cout << "Please enter file Path" << endl;
	getline(cin, filename);
	ifstream file;
	file.open(filename);
	string line;

	if (!file.is_open())
	{
		cout << "Invalid Path" << endl;
		exit(-1);
	}
	while (getline(file, line))
	{
		results->push_back(engine.traverseInputString(line)); // adaugam in vector rezultatul fiecarei expresii
	}

	file.close();
	return results;
}

void Thread::solveExpression() // similar cu faza 1 luam input ul din consola
{
	Engine engine;
	string input;
	cin.ignore();
	cout << "Please enter expression: ";
	getline(cin, input);
	cout << fixed << "The answer: " << engine.traverseInputString(input) << endl << endl;
	num_runs++;
}

void Thread::printOrFile(vector<double>* results)
{
	char input;
	while (1)
	{
		cout << "Press 1 to save results in file" << endl;
		cout << "Press 2 to print results on console" << endl;
		cin >> input;
		
		if (input == '1')
		{
			ofstream file;
			file.open("output.txt");

			for (int i = 0; i < results->size(); i++) // parcurgem valorile din vector si le savam in output.txt
			{
				file << fixed << results->at(i) << endl;
			}

			file.close();
			cout << "Save to File successful" << endl;
			break;
		}

		else if (input == '2')
		{
			cout << endl << endl;
			for (int i = 0; i < results->size(); i++) // parcurgem valorile din vector si le afisam pe consola
			{
				cout << fixed << results->at(i) << endl;
			}

			break;
		}

		else
		{
			cout << "Invalid Input" << endl;
		}
	}
}

bool Thread::saveResults()
{
	char inp;
	cout << "Do you want to save previous results (y/n)" << endl;
	cin >> inp;
	if (inp == 'y' || inp == 'Y')
		return true;
	else
		return false;

}

void Thread::perfromAction(int input)
{
	switch (input)
	{
	case 1:
		this->results = readFromFile();
		printOrFile(this->results);
		break;
	case 2:
		if (!saveResults())
			this->results->empty(); // daca rezultatele nu sunt salvate vectorul e gol
		break;
	case 3:
		solveExpression();
		break;
	default:
		cout << "Invalid Input" << endl;
		break;
	}
}

void Thread::run()
{
	ExpressionMenu menu;
	int input;
	menu.display();
	cin >> input;
	perfromAction(input);
}

Thread::~Thread()
{
	delete this->results;
}
