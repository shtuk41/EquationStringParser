#pragma once

#include <ctime>
#include <exception>
#include <string>
#include "node.h"
#include "expression.h"

struct binary_tree
{
	std::vector<node*> nodes;

	node *getNodeByNumber(int nodeNumber)
	{
		for (node* n : nodes)
		{
			if (n->getOperatorNumber() == nodeNumber)
				return n;
		}

		return NULL;
	}

	~binary_tree()
	{
		for (auto n : nodes)
		{
			delete n;
		}

		nodes.clear();
	}
};


class tree_builder
{
private:
	expression *manager;
	binary_tree tree;
	double x, y, z;
	
public:
	tree_builder(expression *table = nullptr) : manager(table)
	{
		srand((unsigned)time(0));
	}

	void generate_random_tree(int numberOfLevels, std::string mathOperators, std::string supportedVariables = std::string(""))
	{
		//select operator random from mathOperators
		int idx = rand() % mathOperators.length();

		op oper(std::string(1, mathOperators.at(idx)));
		node *n = new node(oper);

		tree.nodes.push_back(n);

		createLeftRightNodes(numberOfLevels - 1, mathOperators, n, supportedVariables);
	}

	double randomDouble(double fMin, double fMax)
	{
		double f = (double)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
	}

	int getrand(size_t max)
	{
		return rand() % max;

	}

	void createLeftRightNodes(int numberOfLevels, std::string operators, node *n, std::string supportedVariables)
	{
		if (numberOfLevels == 0)
		{
			bool useVar = getrand(2) == 0;

			if (useVar && supportedVariables.size() > 0)
			{
				int idx = getrand(supportedVariables.size());
				n->left = new node(supportedVariables.substr(idx,1));
				tree.nodes.push_back(n->left);

			}
			else
			{
				double l = randomDouble(-100.0, 100.0);
				n->left = new node(std::to_string(l));
				tree.nodes.push_back(n->left);
			}

			useVar = useVar ? false : getrand(2) == 0;

			if (useVar && supportedVariables.size() > 0)
			{
				int idx = getrand(supportedVariables.size());
				n->right = new node(supportedVariables.substr(idx, 1));
				tree.nodes.push_back(n->right);

			}
			else
			{
				double r = randomDouble(-100.0, 100.0);
				n->right = new node(std::to_string(r));
				tree.nodes.push_back(n->right);
			}

			
			
		}
		else
		{
			int idx = rand() % operators.length();

			op operL(std::string(1, operators.at(idx)));
			n->left = new node(operL);
			tree.nodes.push_back(n->left);

			idx = rand() % operators.length();

			op operR(std::string(1, operators.at(idx)));
			n->right = new node(operR);
			tree.nodes.push_back(n->right);

			createLeftRightNodes(numberOfLevels - 1, operators, n->left, supportedVariables);
			createLeftRightNodes(numberOfLevels - 1, operators, n->right, supportedVariables);
		}
	}

	void print_node(node *n)
	{
		if (!n)
		{
			return;
		}

		if (n->isOperator() && n->getOperator().executionNumber != 99999)
		{
			std::cout << n->getOperator().name << std::endl;
		}
		else
		{
			std::cout << n->getConstant() << std::endl;
		}

		print_node(n->left);
		print_node(n->right);
	}

	void print_tree()
	{
		std::vector<op> operators = manager->getOperators();

		int numberOfOperators = (int)operators.size() - 1;

		node *n = tree.getNodeByNumber(numberOfOperators);

		print_node(n);
	}

	std::string to_string()
	{
		std::vector<op> operators = manager->getOperators();

		int numberOfOperators = (int)operators.size() - 1;

		node *n = tree.getNodeByNumber(numberOfOperators);

		std::string eq = "";

		get_string(n, eq);

		return eq;
	}

	std::string random_to_string()
	{
		node *n = tree.nodes.front();

		std::string eq = "";

		get_string(n, eq);

		return eq;
	}

	void get_string(node *n, std::string &eq)
	{
		if (n->IsConstant())
		{
			eq = n->getConstant();
		}
		else
		{
			std::string left_str;
			std::string right_str;

			get_string(n->left, left_str);
			get_string(n->right, right_str);
			eq = "(" + left_str + " " + n->getOperator().name + " " + right_str + ")";
		}
	}

	int findMaxIndex(std::vector<op> operators, int minIndex, int maxIndex, int currentExecutionNumber)
	{
		int counter = 0;
		int selectedIndex = -1;
		int maxExecution = -1;

		for (op oper : operators)
		{
			if (counter >= minIndex &&
				counter < maxIndex &&
				oper.executionNumber > maxExecution && 
				oper.executionNumber < currentExecutionNumber)
			{
				bool matchFound = false;

				for (node * n : tree.nodes)
				{
					if (oper.executionNumber == n->getOperatorNumber())
					{
						matchFound = true;
						break;
					}
				}

				if (matchFound)
				{
					counter++;
					continue;
				}

				maxExecution = oper.executionNumber;
				selectedIndex = counter;
			}

			counter++;
		}

		return selectedIndex;
	}

	void addLeft(node* n, int index)
	{
		if (index == 0)
		{
			n->left = new node(manager->getNumbers()[index]);
			tree.nodes.push_back(n->left);
		}
		else
		{

			int currentExecNumber = manager->getOperators()[index].executionNumber;

			int nextMaximumLeft = findMaxIndex(manager->getOperators(), 0, index, currentExecNumber);

			if (nextMaximumLeft != -1)
			{
				op nextMaximumNode = (manager->getOperators()[nextMaximumLeft]);
				n->left = new node(nextMaximumNode);
				tree.nodes.push_back(n->left);

				addLeft(n->left, nextMaximumLeft);
				addRight(n->left, nextMaximumLeft, index);
			}
			else
			{
				n->left = new node(manager->getNumbers()[index]);
				tree.nodes.push_back(n->left);
			}
		}
	}

	void addRight(node* n, int index, int parentIndex)
	{
		std::vector<op> operators = manager->getOperators();

		int currentExecNumber = manager->getOperators()[index].executionNumber;

		int nextMaximumRight = findMaxIndex(manager->getOperators(), index, parentIndex, currentExecNumber);

		if (nextMaximumRight != -1)
		{
			op nextMaximumNode = (manager->getOperators()[nextMaximumRight]);
			n->right = new node(nextMaximumNode);
			tree.nodes.push_back(n->right);

			addLeft(n->right, nextMaximumRight);
			addRight(n->right, nextMaximumRight, parentIndex);
		}
		else
		{
			n->right = new node(manager->getNumbers()[index + 1]);
			tree.nodes.push_back(n->right);
		}
	}

	void build()
	{
		std::vector<op> operators = manager->getOperators();
		std::vector<std::string> numbers = manager->getNumbers();

		int numberOfOperators = (int)operators.size();

		int indexMaximum = findMaxIndex(operators, 0, numberOfOperators, numberOfOperators);

		op maxNode = operators[indexMaximum];
		node* newNode = new node(maxNode);
		tree.nodes.push_back(newNode);

		addLeft(newNode, indexMaximum);
		addRight(newNode, indexMaximum, numberOfOperators);
	}

	double performOperation(op o, double l, double r)
	{
		double result;

		switch (o.name[0])
		{
			case '+':
				result = l + r;
				break;
			case '-':
				result = l - r;
				break;
			case '/':
				result = l / r;
				break;
			case '*':
				result = l * r;
				break;
			case '^':
				result = pow(l,r);
				break;
			default:
				throw new std::exception("undefined operator in performOperation()");
		}

		return result;
	}

	double calcNode(node *n)
	{
		double result;

		if (n->IsConstant())
		{
			std::string c = n->getConstant();

			if (c.compare("x") == 0)
			{
				result = x;
			}
			else if (c.compare("y") == 0)
			{
				result = y;
			}
			else if (c.compare("z") == 0)
			{
				result = z;
			}
			else
			{
				result = atof(c.c_str());
			}
		}
		else
		{
			double left = calcNode(n->left);
			double right = calcNode(n->right);
			result = performOperation(n->getOperator(), left, right);
		}


		return result;
	}

	double calc(double x = 0, double y = 0, double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;


		node* firstNode = tree.nodes.front();

		double result = calcNode(firstNode);

		return result;
	}
};
