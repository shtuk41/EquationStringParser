// EquationStringParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <list>

#include "expression.h"
#include "token.h"
#include "tree_builder.h"

int level = 0;

static const char supportedOps[] = {'+','-','*','/','^'};
static const char supportedVariableNames[] = { 'x','y','z' };

bool isTokenizable(char in)
{
	return isdigit(in) || in == '.';
}

bool IsSupportedVariableName(char in)
{
	for (auto a : supportedVariableNames)
	{
		if (in == a)
			return true;
	}

	return false;
}

bool setPrev(char in, char *prev)
{
	if (in != ' ')
	{
		*prev = in;
		return true;
	}
	else
	{
		return false;
	}
}

bool IsOperator(char in)
{
	for (auto a : supportedOps)
	{
		if (in == a)
			return true;
	}

	return false;
}

int main()
{
	char supportedOps[] = {'+','-','*','/','^'};

	//const char* eq = "(((55 + 3) ^ 4) * x + ((5 + y) * x))";
	//const char *eq = "15 - (6 + 5 / 3) / (1 * (4 + 2) + 7)";
	//const char *eq = "3.756 + (6.4563 / 2.23 /3.0 * (4.1 + 2.8))";
	//const char *eq = "(45.45 - 45 ^ -2) * -4563.45 - 485 * (4.4586 - (2.7562 * 756 / 3)) / (4585 * 45.45)";
	//const char* eq = "44 * x";
	const char* eq = "(45.45 - x ^ -2) * -4563.45 - y * (4.4586 - (2.7562 * z / 3)) / (4585 * 45.45)";


	for (int ii = 0; ii < 1; ii++)
	{
		std::cout << eq << std::endl;

		const char *eqptr = eq;
	
		token tok;
		expression manager;

		char prevChar = ' ';

		manager.openBraket();
	   
		while (*eqptr != '\0')
		{
			if (IsSupportedVariableName(*eqptr))
			{
				if (tok.length() > 0)
					throw new std::exception("unexpected variable name");

				setPrev(*eqptr, &prevChar);
				std::string toklocal(1, *eqptr);
				manager.addNumber(toklocal);
				eqptr++;
				continue;
			}
			else if (isTokenizable(*eqptr))
			{
				tok.add(*eqptr);
				setPrev(*eqptr, &prevChar);
				eqptr++;
				continue;
			}
			else if ((IsOperator(prevChar) || prevChar == '(') && *eqptr == '-')
			{
				tok.add(*eqptr);
				prevChar = ' ';
				eqptr++;
				continue;
			}
			else if (tok.length() > 0)
			{
				manager.addNumber(tok.readString());
				tok.reset();
			}

			switch (*eqptr)
			{
				case ' ':
					eqptr++;
					continue;
				case '(':
					manager.openBraket();
					break;	
				case ')':
					manager.closeBraket();
					break;			
				case '*':
					manager.addOperator(std::string(1, *eqptr));
					break;
				case '/':
					manager.addOperator(std::string(1, *eqptr));
					break;
				case '+':
					manager.addOperator(std::string(1, *eqptr));
					break;
				case '-':
					manager.addOperator(std::string(1, *eqptr));
					break;
				case '^':
					manager.addOperator(std::string(1, *eqptr));
					break;
			}

			std::cout << *eqptr;

			setPrev(*eqptr, &prevChar);
			eqptr++;
		}

		manager.closeBraket();

		std::cout << "\nNumbers:\n";
		manager.print_numbers();
		std::cout << "\nOperators:\n";
		manager.print_operators();
		std::cout << "\nBrackets\n";
		manager.print_brakets();

		tree_builder builder(&manager);
		builder.build();

		std::cout << "\nTree:\n";
		builder.print_tree();
		double result = builder.calc(5, 4);

		std::cout << "\nTree to string\n" << std::endl;
		std::cout << builder.to_string() << std::endl;
		std::cout << "\nResults:\n";
		std::cout << std::fixed << result << std::endl;
	}

	std::cout << "########################################################\n";

	std::cout << "Generating random tree\n";

	tree_builder builder2;
	builder2.generate_random_tree(3, "*/+-");
	//std::cout << "Print tree\n";
	//builder2.print_tree();
	std::cout << "Random to string\n";
	std::cout << builder2.random_to_string() << std::endl;

	builder2.mutate();

	std::cout << "Random to string after mutate\n";
	std::cout << builder2.random_to_string() << std::endl;

	double r_result = builder2.calc(2);

	std::cout << "\nrandom result: " << r_result << std::endl;

	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
