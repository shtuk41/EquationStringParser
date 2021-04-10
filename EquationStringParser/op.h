#pragma once

const int MaxExecutionNumber = 99999;

struct op
{
	std::string name;
	int executionNumber;

	op(std::string n) : executionNumber(MaxExecutionNumber)
	{
		name = n;
	}
};
