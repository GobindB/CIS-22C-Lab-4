#ifndef Calculator_h
#define Calculator_h

#include "StacksAndQueue.h"


class Calculator
{
private:
	std::string infixEquation;
	std::string prefixEquation;
	std::string postfixEquation;

protected:
	bool isValidOp(char);
	bool isInteger(char);
	int priority(char);
	std::string reverse(std::string);

	std::string infixToPostfix(std::string);
	std::string infixToPrefix(std::string);
public:

	void setEquation(std::string);

	bool checkValidEqn(std::string);

	std::string getInfixEquation();
	std::string getPrefixEquation();
	std::string getPostfixEquation();
};

#endif /* Calculator_h */
