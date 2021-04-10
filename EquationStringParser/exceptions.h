#pragma once

#include <exception>

struct level_below_zero_exception : public std::exception
{
	const char* what() const throw()
	{
		return "level is below 0";
	}
};

struct node_no_constant : public std::exception
{
	const char* what() const throw()
	{
		return "Not a constant node";
	}
};

struct node_no_operator : public std::exception 
{
	const char* what() const throw()
	{
		return "Not an operator node";
	}
};
