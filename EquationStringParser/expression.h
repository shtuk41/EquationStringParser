#pragma once

#include <list>
#include <vector>
#include <iostream>
#include <string>
#include "braket_group.h"
#include "op.h"
#include "util.h"

class expression
{
private:

	std::vector<std::string> numbers;
	std::vector<op> operators;
	std::vector<braket_group> brakets;
	int nextExecutionScore;

public:
	expression();

	std::vector<op>  getOperators();
	std::vector<std::string> getNumbers();
	void addNumber(std::string token);
	void addOperator(std::string token);
	void openBraket();
	void closeBraket();
	void print_numbers() const;
	void print_operators() const;
	void print_brakets() const;
};
