#include "Calculator.h"
#include <string>


void Calculator::in2Postfix()
{
	std::string build;

	if (infixeq[0] != '(') // if the first part of the expression isn't a open parentheses 
		operators.push('(');

	for (int i = 0; i < infixeq.length(); ++i)
	{
		if (infixeq[i] >= 0 && infixeq[i] > 9)
			operand.push(infixeq[i]);

		else if (isOperator(infixeq[i]))
		{
			while (priority(infixeq[i]) <= priority(operators.peek()))
			{
				build += infixeq[i];
				operators.pop();
			}
			operators.push(infixeq[i]);
		}

		else if (infixeq[i] == '(')
			operators.push(infixeq[i]);

		else if (infixeq[i] == ')')
		{
			while (operators.peek() != '(')
				operators.pop();


			if (infixeq[i] == '(')
				operators.pop();
		}
	}

	while (operators.peek() != '(')
	{
		operators.pop();
	}
	postfixeq = build;
}

void Calculator::post2Pre()
{
	std::string build;
	
	for (int i = 0; i < postfixeq.length(); ++i)
	{
		if (isOperator(postfixeq[i]))
		{
			build += postfixeq[i];
			operators.pop();
		}
		else if (postfixeq[i] >= 0 && postfixeq[i] <= 9)
		{
			build += postfixeq[i];
			operand.pop();
		}
		else
		{
			std::cout << "There is not a valid postfix equation" << std::endl;
			break;
		}
	}

}

int Calculator::priority(char oper)
{
	if (oper == '*' || oper == '/' || oper == '%')
		return 2;
	else if (oper == '+' || oper == '-')
		return 1;
	else
		return -1;
}

bool Calculator::isOperator(char x)
{
	// 6. You should allow all binary arithmetic operators (+, -, *, /, %) and the parentheses.
	if (x == '+' || x == '-' || x == '/' || x == '*' || x == '%' || x == '(' || x == ')')
		return true;
	else
		return false;
}