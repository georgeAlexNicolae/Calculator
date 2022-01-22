#include "Engine.h"

Engine::Engine()
{
	this->brackets = new Stack<char>();
	this->result = new Stack<double>();
}

// funcție statică care returnează rezultatul pe baza a 2 valori în funcție de operandul transmis (plus, minus, inmultit, etc)
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
                throw 505; //exeptie pentru impartirea la 0
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

// aici identificam ordinea operatilor pentru ca 2*3 de ex facem inainte de 2+3 trebuie sa fie ordinea mai mica la adunare/scadere
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
    // traversam expresia de input char cu char
    for (int i = 0; i < input.length(); i++) {

        if (input[i] == ' ') // daca caracterul (char-ul) este un spatiu, continuam si nu facem nimic
            continue;

        else if (input[i] == '(' || input[i] == '[' || input[i] == '{') // daca spatiul e o paranteza de deschidere o vom pune(paranteza respectiva) in stack ul de paranteze, e ca un array unde vei stoca totul inclusiv operanzii. EXEMPLU:  2*3+1. Stack ul rezultatului va avea intai 2 si 3 apoi va rezolva 2*3 si va sterge 2 si 3 si va pune 6 in locul lor iar la final dupa +1, avem 7 rezultat final
        {
            this->brackets->push(input[i]);
        }

        else if (isdigit(input[i])) // daca e cifra
        {
            string val;

            while (i < input.length() && (isdigit(input[i]) || input[i] == '.')) // verificam dacă numărul este compus din mai mult de 1 cifră sau este un număr zecimal
            {
                val.push_back(input[i]);
                i++;
            }

            this->result->push(atof(val.c_str())); // in stack ul rezultatului punem ultimul numar
            i--;
        }

        else if (input[i] == ')' || input[i] == ']' || input[i] == '}') // acum, avem parantezele de la final
        {
            char temp;
            if (input[i] == ')')
                temp = '(';
            else if (input[i] == ']')
                temp = '[';
            else if (input[i] == '}')
                temp = '{';

            while (!this->brackets->empty() && this->brackets->top() != temp) // obtinerea tuturor valorilor si a operanzilor intre paranteze
            {
                double val2 = this->result->top();
                this->result->pop();

                double val1 = this->result->top();
                this->result->pop();

                char op = brackets->top();
                brackets->pop();

                this->result->push(calculate(val1, val2, op));
            }

            if (!this->brackets->empty()) // eliminam paranteza de inceput
                this->brackets->pop();
        }

        else // daca spatiul este un operand
        {
            while (!this->brackets->empty() && getPrecedence(this->brackets->top()) >= getPrecedence(input[i])) // cat timp precedentul operatorului ( cum am vazut inainte, 1 pt adunare/scadere 2 pt inmultire/impartire s.a.m.d.) din varful stackului parantezelor e mai mare sau egal decat operatorul curent, facem calculele
            {
                double val2 = this->result->top();
                this->result->pop();

                double val1 = this->result->top();
                this->result->pop();

                char op = this->brackets->top();
                this->brackets->pop();

                this->result->push(calculate(val1, val2, op));
            }

            this->brackets->push(input[i]); // impingem operandul catre brackets stack (stack ul parantezelor)
        }
    }

    // Toata expresia este analizata pana in acest punct, calculam valorile care au mai ramas
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