#include "Engine.h"

Engine::Engine()
{
	this->brackets = new Stack<char>();
	this->result = new Stack<double>();
}

double Engine::calculate(double v1, double v2, char operand)
{
    try
    {
        if (operand == '+')
            return v1 + v2;
        else if (operand == '-')
            return v1 - v2;
        else if (operand == '*')
            return v1 * v2;
        else if (operand == '/')
        {
            if (v2 == 0)
                throw 505;
            else
                return v1 / v2;
        }
        else if (operand == '^')
            return pow(v1, v2);
        else if (operand == '#')
            return pow(v1, 1/v2);
    }
    catch (int e) {
        cout << "Division by 0 is not possible" << endl;
        exit(-1);
    }
}

int Engine::getPrecedence(char operand)
{
    if (operand == '+' || operand == '-')
        return 1;
    else if (operand == '*' || operand == '/')
        return 2;
    else if (operand == '^' || operand == '#')
        return 3;
    else
        return 0;
}

double Engine::traverseInputString(string input)
{
    for (int i = 0; i < input.length(); i++) {

        if (input[i] == ' ')
            continue;

        else if (input[i] == '(' || input[i] == '[' || input[i] == '{')
        {
            this->brackets->push(input[i]);
        }

        else if (isdigit(input[i]))
        {
            string val;

            while (i < input.length() && (isdigit(input[i]) || input[i] == '.'))
            {
                val.push_back(input[i]);
                i++;
            }

            this->result->push(atof(val.c_str()));
            i--;
        }

        else if (input[i] == ')' || input[i] == ']' || input[i] == '}')
        {
            char temp;
            if (input[i] == ')')
                temp = '(';
            else if (input[i] == ']')
                temp = '[';
            else if (input[i] == '}')
                temp = '{';

            while (!this->brackets->empty() && this->brackets->top() != temp)
            {
                double val2 = this->result->top();
                this->result->pop();

                double val1 = this->result->top();
                this->result->pop();

                char op = brackets->top();
                brackets->pop();

                this->result->push(calculate(val1, val2, op));
            }

            if (!this->brackets->empty())
                this->brackets->pop();
        }

        else
        {
            while (!this->brackets->empty() && getPrecedence(this->brackets->top()) >= getPrecedence(input[i])) {
                double val2 = this->result->top();
                this->result->pop();

                double val1 = this->result->top();
                this->result->pop();

                char op = this->brackets->top();
                this->brackets->pop();

                this->result->push(calculate(val1, val2, op));
            }

            this->brackets->push(input[i]);
        }
    }

    while (!this->brackets->empty())
    {
        double val2 = this->result->top();
        this->result->pop();

        double val1 = this->result->top();
        this->result->pop();

        char op = this->brackets->top();
        this->brackets->pop();

        this->result->push(calculate(val1, val2, op));
    }

    return this->result->top();
}

Engine::~Engine()
{
	delete this->brackets;
	delete this->result;
}