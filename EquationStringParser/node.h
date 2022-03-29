#pragma once

#include <string>
#include "expression.h"

class node
{
private:
	op nodeOperator;
	std::string constant;
	std::string variable;

public:
	node *left;
	node *right;

	node(op oper);
	node(std::string v);
	~node();
	bool isOperator() const;
	bool IsConstant() const;
	int getOperatorNumber() const;
	op getOperator() const;
	std::string getConstant() const;
	void setConstant(std::string);
};