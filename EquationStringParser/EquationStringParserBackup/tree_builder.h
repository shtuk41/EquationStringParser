#pragma once

#include <exception>
#include "table_manager.h"

struct node
{

	node *left;
	node *right;
	op nodeOperator;
	std::string val;

	node(op oper):left(NULL), right(NULL), nodeOperator(oper),val("")
	{
	}

	node(std::string v) :left(NULL), right(NULL), val(v), nodeOperator("")
	{

	}

	~node()
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

	bool isOperator() const
	{
		return val.empty();
	}

	bool IsValue() const
	{
		return nodeOperator.name.empty();
	}

	int getOperatorNumber() const
	{
		return nodeOperator.executionNumber;
	}
};

struct binary_tree
{
	std::list<node*> nodes;

	node *getNodeByNumber(int nodeNumber)
	{
		for (node* n : nodes)
		{
			if (n->getOperatorNumber() == nodeNumber)
				return n;
		}

		return NULL;
	}
};


class tree_builder
{
private:
	table_manager *manager;
	binary_tree tree;
	
public:
	tree_builder(table_manager *table)
	{
		manager = table;
	}

	void print_node(node *n)
	{
		if (!n)
		{
			return;
		}

		if (n->nodeOperator.executionNumber != 99999)
		{
			std::cout << n->nodeOperator.name << std::endl;
		}
		else
		{
			std::cout << n->val << std::endl;
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

		if (n->IsValue())
		{
			result = atof(n->val.c_str());
		}
		else
		{
			double left = calcNode(n->left);
			double right = calcNode(n->right);
			result = performOperation(n->nodeOperator, left, right);
		}


		return result;
	}

	double calc()
	{
		node* firstNode = tree.nodes.front();

		double result = calcNode(firstNode);

		return result;
	}
};
