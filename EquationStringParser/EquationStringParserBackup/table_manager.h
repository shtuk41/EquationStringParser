#pragma once

#include <list>
#include <vector>
#include <exception>
#include <iostream>
#include <string>

struct LevelBelowZeroException : public std::exception
{
	const char* what() const throw()
	{
		return "level is below 0";
	}
};

struct braketGroup
{
private:
	int startIndex;
	bool closed;
public:

	braketGroup(int si) : startIndex(si), closed(false)
	{

	}

	int getStartIndex() const
	{
		return startIndex;
	}

	bool isClosed() const
	{
		return closed;
	}

	void close()
	{
		closed = true;
	}
};

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

class table_manager
{
private:

	std::vector<std::string> numbers;
	std::vector<op> operators;
	std::vector<braketGroup> brakets;
	int nextExecutionScore;

public:
	table_manager() : nextExecutionScore(0)
	{
		
	}

	std::vector<op>  getOperators()
	{
		return operators;
	}

	std::vector<std::string> getNumbers()
	{
		return numbers;
	}

	void addNumber(std::string token)
	{
		numbers.push_back(token);
	}

	void addOperator(std::string token)
	{
		operators.push_back(token);
	}

	void openBraket()
	{
		int sizeops = static_cast<int>(operators.size());
		braketGroup bg(sizeops);
		brakets.push_back(bg);
	}

	void closeBraket()
	{
		for (std::vector<braketGroup>::reverse_iterator rit = brakets.rbegin(); rit != brakets.rend(); ++rit)
		{
			if (!(*rit).isClosed())
			{
				int startIndex = (*rit).getStartIndex();
				int endIndex = (int)operators.size();

				bool found = false;

				do
				{
					found = false;
					int index;
					int maxScore = -1;
					for (int ii = startIndex; ii < endIndex; ii++)
					{
						if (operators[ii].executionNumber == MaxExecutionNumber)
						{
							found = true;
							int localScore = score(operators[ii].name);

							if (localScore > maxScore)
							{
								maxScore = localScore;
								index = ii;
							}

						}
					}

					if (found)
					{
						operators[index].executionNumber = nextExecutionScore;
						nextExecutionScore++;
					}

				} while (found);



				(*rit).close();
				return;
			}
		}
	}
	
	void print_numbers() const
	{
		std::cout << "\nStored numbers: \n" << std::endl;
		for (std::string s : numbers)
		{
			std::cout << s << std::endl;
		}
	}

	void print_operators() const
	{
		std::cout << "\nStored operators: \n" << std::endl;
		for (op s : operators)
		{
			std::cout << s.name << "," << s.executionNumber << std::endl;
		}
	}

	void print_brakets() const
	{
		std::cout << "\nBrakets: \n" << std::endl;
		for (braketGroup b : brakets)
		{
			std::cout << b.getStartIndex() << " " << (b.isClosed() ? "closed" : "open") << std::endl;
		}
	}
};
