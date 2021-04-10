// EquationStringParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <list>

#include "table_manager.h"
#include "token.h"
#include "tree_builder.h"

int level = 0;

int main()
{
	//const char* eq = "(((55 + 3) ^ 4) * x + ((5 + y) * x))";
	//const char *eq = "15 - (6 + 5 / 3) / (1 * (4 + 2) + 7)";
	//const char *eq = "3.756 + (6.4563 / 2.23 /3.0 * (4.1 + 2.8))";
	const char *eq = "(45.45 - 45 ^ 2) * 4563.45 - 485 * (4.4586 - (2.7562 * 756 / 3)) / (4585 * 45.45)";
	
	std::cout << eq << std::endl;

	const char *eqptr = eq;
	
	token tok;
	table_manager manager;

	manager.openBraket();

	   
	while (*eqptr != '\0')
	{
		if (isdigit(*eqptr) || *eqptr == '.')
		{
			tok.add(*eqptr);
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

		eqptr++;
	}

	manager.closeBraket();

	manager.print_numbers();
	manager.print_operators();
	manager.print_brakets();

	tree_builder builder(&manager);
	builder.build();

	builder.print_tree();
	double result = builder.calc();

	std::cout << result << std::endl;

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
