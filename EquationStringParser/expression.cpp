#include "pch.h"
#include "expression.h"

expression::expression() : nextExecutionScore(0)
{
}

std::vector<op> expression::getOperators()
{
	return operators;
}

std::vector<std::string> expression::getNumbers()
{
	return numbers;
}

void expression::addNumber(std::string token)
{
	numbers.push_back(token);
}

void expression::addOperator(std::string token)
{
	operators.push_back(token);
}

void expression::openBraket()
{
	int sizeops = static_cast<int>(operators.size());
	braket_group bg(sizeops);
	brakets.push_back(bg);
}

void expression::closeBraket()
{
	for (std::vector<braket_group>::reverse_iterator rit = brakets.rbegin(); rit != brakets.rend(); ++rit)
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

void expression::print_numbers() const
{
	std::cout << "\nStored numbers: \n" << std::endl;
	for (std::string s : numbers)
	{
		std::cout << s << std::endl;
	}
}

void expression::print_operators() const
{
	std::cout << "\nStored operators: \n" << std::endl;
	for (op s : operators)
	{
		std::cout << s.name << "," << s.executionNumber << std::endl;
	}
}

void expression::print_brakets() const
{
	std::cout << "\nBrakets: \n" << std::endl;
	for (braket_group b : brakets)
	{
		std::cout << b.getStartIndex() << " " << (b.isClosed() ? "closed" : "open") << std::endl;
	}
}