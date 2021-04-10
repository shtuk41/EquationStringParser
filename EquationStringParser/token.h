#pragma once

#include <string>

const size_t TOKEN_SIZE = 100;

class token
{
private:
	char *container;
	size_t len = 0;
	char *curr;

public:
	token()
	{
		container = new char[TOKEN_SIZE];
		reset();
	}

	~token()
	{
		delete[] container;
	}

	void add(char c)
	{
		*curr++ = c;
		len++;
	}

	std::string readString() const
	{
		std::string s = std::string(container);
		return s;
	}

	char * readArray() const
	{
		return container;
	}

	size_t length() const
	{
		return len;
	}

	void reset()
	{
		memset(container, '\0', TOKEN_SIZE);
		curr = container;
		len = 0;
	}
};

