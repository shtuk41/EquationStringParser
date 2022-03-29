#include "pch.h"
#include "exceptions.h"
#include "node.h"


node::node(op oper):left(NULL), right(NULL), nodeOperator(oper), constant("")
{
}

node::node(std::string constant):left(NULL), right(NULL), constant(constant), nodeOperator("")
{
}

node::~node()
{
	if (left != NULL)
	{
		left->~node();
	}

	if (right != NULL)
	{
		right->~node();
	}
}

bool node::isOperator() const
{
	return !nodeOperator.name.empty();
}

bool node::IsConstant() const
{
	return !constant.empty();
}

int node::getOperatorNumber() const
{
	return nodeOperator.executionNumber;
}

op node::getOperator() const
{
	if (nodeOperator.name.empty())
	{
		throw new node_no_operator();
	}

	return nodeOperator;
}

std::string node::getConstant() const
{
	if (constant.empty())
	{
		throw new node_no_constant();
	}

	return constant;
}

void node::setConstant(std::string val)
{
	constant = val;
}