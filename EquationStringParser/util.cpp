#include "pch.h"
#include "util.h"

int score(std::string op)
{
	char o = op[0];

	switch (o)
	{
	case '+':
		return 1;
	case '-':
		return 1;
	case '/':
		return 2;
	case '*':
		return 2;
	case '^':
		return 3;
	default:
		return 0;
	}
}