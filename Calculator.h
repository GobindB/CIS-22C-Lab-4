#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include <string>

class Calculator
{

private:
	
	std::string infixeq; 
	std::string postfixeq;
	std::string prefixeq;

	Stack<char> operators;
	Stack<char> operand;

public:

	int priority(char oper);
	int findLength(char str[]);

	char reverse(char str[]);
	void in2Postfix();
	void post2Pre();

	// Function to find priority of given 
	// operator. 
	int getPriority(char C);


	bool isOperator(char x);
};

#endif // !CALCULATOR_H

