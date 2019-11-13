//
//  Calculator.cpp
//  CIS 22C Lab 4
//
//  Created by Gobind Bakhshi on 11/7/19.
//  Copyright © 2019 Gobind Bakhshi. All rights reserved.
//

#include "Calculator.h"

//******************************************************//
//                   USER FUNCTIONS                     //
//******************************************************//

/** validates the expression syntax and pushes operators/operands to member stacks
@pre expressionInfix validation
inputExpression - referenced constant string
@post tokenize string and push operators/operands to appropriate stacks
*/
void Calculator::calculatePost(const std::string &inputExpression)
{
	if (validate(inputExpression))
	{
		infixExp = inputExpression;
		infixToPostfix(inputExpression);
	}

}

/** validates the expression syntax and pushes operators/operands to member stacks
pre: input expression - referenced constant string
post: tokenize string and push operators/operands to appropriate stacks for prefix expressions
*/
void Calculator::calculatePre(const std::string &inputExpression)
{
	if (validate(inputExpression))
	{
		infixExp = inputExpression;
		infixToPrefix(inputExpression);
		evaluatePre();
	}

}


//******************************************************//
//                VALIDITY CHECKER                      //
//******************************************************//

/** validates the expression syntax and pushes operators/operands to member stacks
expressionInfix validation
pre: input expression - string type
post: tokenize string and push operators/operands to appropriate stacks
return: false if error message. or true if valid
*/
bool Calculator::validate(std::string inputExpression)
{

	Queue<std::string> *tokenQueue = new Queue<std::string>;
	tokenize(inputExpression, *tokenQueue);

	std::string token;

	int i = 0;
	int operands = 0;
	int operators = 0;
	int openParen = 0;
	int closedParen = 0;

	// checks to make sure first entry in input isnt an operator
	if (isOperator(tokenQueue->peek()))
	{
		throw "Invalid Input: " + inputExpression;
	}

	// loop through each element of the queue and determine if operator or operand while not empty
	while (!tokenQueue->isEmpty())
	{
		operators = 0;
		operands = 0;
		i = 0;

		token = tokenQueue->peek(); // test to ensure correct value is returned after peek!!!!!!!

									// check if token is valid and if so push to appropriate stack
		while (token[i] != '\0')
		{
			// check if token is an operand
			if (token[i] >= '0' && token[i] <= '9')
			{
				operands++;
			}
			// check if token has an operator or parenthesis
			else if (isOperator(token) || isParen(token))
			{
				if (token[i] == '(')
				{
					openParen++;
				}
				if (token[i] == ')')
				{
					closedParen++;
				}

				operators++;
			}
			else
			{
				throw "Invalid Input: " + inputExpression;
			}

			// test to ensure token does not contain operator and operand i.e appropriate spacing has been used
			if (operators > 0 && operands > 0)
			{
				throw "Invalid Input: " + inputExpression;
			}

			i++;
		}

		//token cant have multiple operators
		if (operators > 1)
		{
			throw "Invalid Input: " + inputExpression;
		}

		// deque this token from the queue of tokens
		tokenQueue->dequeue();
	}
	if (openParen != closedParen)
	{
		throw "Invalid Input: " + inputExpression;
	}
	// if no exception has been thrown then input is valid
	infixExp = inputExpression;
	return true;
}

//******************************************************//
//                CONVERSION ENGINES                    //
//******************************************************//


/** converts expressionInfixQ Queue to expressionPostQ Queue
@pre expressionInfixQ checks
infix - string type
@post expressionPostQ is populated
expression Postfix Queue is populated
*/
void Calculator::infixToPostfix(std::string infix)
{

	Stack<int> operandStack;
	Stack<char> operatorStack;
	Queue<std::string> *tokenQueue = new Queue<std::string>;
	std::string token;
	postfixExp = "";

	// tokenize the infix string
	tokenize(infix, *tokenQueue);

	// loop through all tokens
	while (!tokenQueue->isEmpty())
	{
		token = tokenQueue->peek();

		// If character is operator, pop two elements from stack, perform operation and push the result back.
		if (isOperator(token))
		{
			while (!operatorStack.isEmpty() && operatorStack.peek() != '(' && precedence(operatorStack.peek()) > precedence(token[0]))
			{
				// Pop two operands.
				int operand2 = operandStack.peek();
				operandStack.pop();
				int operand1 = operandStack.peek();
				operandStack.pop();
				// Perform operation
				int result = performOperation(operatorStack.peek(), operand1, operand2);

				//Push back result of operation on stack.
				operandStack.push(result);

				postfixExp += operatorStack.peek();
				postfixExp += " ";
				operatorStack.pop();
			}
			operatorStack.push(token[0]);
		}
		// Else if character is an operand
		else if (isOperand(token))
		{
			postfixExp += token + ' ';
			operandStack.push(std::stoi(token));
		}

		else if (token[0] == '(')
		{
			operatorStack.push(token[0]);
		}
		else if (token[0] == ')')
		{
			while (!operatorStack.isEmpty() && operatorStack.peek() != '(')
			{
				postfixExp += operatorStack.peek();
				postfixExp += " ";

				// Pop two operands.
				int operand2 = operandStack.peek();
				operandStack.pop();
				int operand1 = operandStack.peek();
				operandStack.pop();
				// Perform operation
				int result = performOperation(operatorStack.peek(), operand1, operand2);

				//Push back result of operation on stack.
				operandStack.push(result);

				operatorStack.pop();
			}
			operatorStack.pop();
		}
		tokenQueue->dequeue();
	}

	// deal with any remaining operators
	while (!operatorStack.isEmpty())
	{
		// Pop two operands.
		int operand2 = operandStack.peek();
		operandStack.pop();
		int operand1 = operandStack.peek();
		operandStack.pop();
		// Perform operation
		int result = performOperation(operatorStack.peek(), operand1, operand2);

		//Push back result of operation on stack.
		operandStack.push(result);

		postfixExp += operatorStack.peek();
		postfixExp += " ";
		operatorStack.pop();
	}

	resultPost = operandStack.peek();
}

/** converts expressionInfixQ Queue to expressionPostQ Queue
@pre expressionInfixQ checks
infix - string type
@post expression Prefix Queue is populated
*/
void Calculator::infixToPrefix(std::string infix)
{

	Stack<int> operandStack;
	Stack<char> operatorStack;

	// queues to deal with tokens
	Queue<std::string> *tokenQueue = new Queue<std::string>;
	Queue<std::string> *tokenQueue2 = new Queue<std::string>;

	std::string reversedInfix;

	//reverse the infix equation
	tokenize(infix, *tokenQueue);
	reverse(*tokenQueue);

	while (!tokenQueue->isEmpty())
	{
		reversedInfix += tokenQueue->peek();
		reversedInfix += " ";
		tokenQueue->dequeue();
	}

	//turn the reversed equation to postfix form
	infixToPostfix(reversedInfix);

	//reverse the postfix form
	tokenize(postfixExp, *tokenQueue2);
	reverse(*tokenQueue2);

	std::string finalPreFix;
	while (!tokenQueue2->isEmpty())
	{
		finalPreFix += tokenQueue2->peek();
		finalPreFix += " ";
		tokenQueue2->dequeue();
	}
	prefixExp = finalPreFix;
}

/** evaluates prefix expressions
post: evaluates prefix expression
*/
void Calculator::evaluatePre()
{
	Stack<std::string> tokenStack;
	Stack<int> operandStack;
	Stack<char> operatorStack;
	Queue<std::string> *tokenQueue = new Queue<std::string>;
	std::string token;

	tokenize(prefixExp, *tokenQueue);

	while (!tokenQueue->isEmpty())
	{
		tokenStack.push(tokenQueue->peek());
		tokenQueue->dequeue();
	}

	while (!tokenStack.isEmpty())
	{
		token = tokenStack.peek();

		// Push operand to Stack
		// To convert exprsn[j] to digit subtract
		// '0' from exprsn[j].
		if (isOperand(token))
		{
			operandStack.push(std::stoi(token));
		}
		else {

			// Operator encountered
			// Pop two elements from Stack
			int o1 = operandStack.peek();
			operandStack.pop();
			int o2 = operandStack.peek();
			operandStack.pop();

			// Use switch case to operate on o1
			int result = performOperation(token[0], o1, o2);
			operandStack.push(result);
		}
		tokenStack.pop();
	}
	resultPre = operandStack.peek();
}
//******************************************************//
//                OPERATIONS/PRECEDENCE                 //
//******************************************************//

/** converts expressionInfixQ Queue to expressionPostQ Queue
pre: operation - character type
operand1 - integer type
operand2 - integer type
post: performs arithmetic operation for operands in the converted expression
return: integer type */
int Calculator::performOperation(char operation, int operand1, int operand2)
{
	if (operation == '+') return operand1 + operand2;
	else if (operation == '-') return operand1 - operand2;
	else if (operation == '*') return operand1 * operand2;
	else if (operation == '/') return operand1 / operand2;
	else if (operation == '%') return operand1 % operand2;

	else throw "Invalid operation.";
	return -1;
}

/** returns the precedence "weight" for an operator
pre: op - character type (inputted operator)
return: integer type( to indicate precedence of operators
*/
int Calculator::precedence(char op)
{
	if (op == '^')
		return 3;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '+' || op == '-')
		return 1;
	else
		return -1;
}

//******************************************************//
//                STATE CHECKERS                        //
//******************************************************//


/** checks if character is an operand(number)
pre: C - string (infix expression)
return: true or false */
bool Calculator::isOperand(std::string C)
{
	bool flag = false;

	for (int i = 0; i < C.length(); i++)
	{
		if (C[i] >= '0' && C[0] <= '9')
		{
			flag = true;
		}
		else return false;
	}
	return flag;
}

/** check if character is a parenthesis
pre: op - string type
op is the character to check
return: true if operator is parenthesis, false otherwise
*/
bool Calculator::isParen(std::string op)
{


	if (op[0] == '(' || op[0] == ')')
	{
		return true;
	}
	else return false;
}

/** check if character is an operator
pre: op - string type
op is the operator to test
return: true if is defined operator, false if not defined operator
*/
bool Calculator::isOperator(std::string op)
{
	if (op[0] == '-' || op[0] == '+' || op[0] == '/' || op[0] == '%' || op[0] == '/' || op[0] == '*')
	{
		return true;
	}
	return false;
}


//******************************************************//
//                TOKENIZER FUNCTIONS                   //
//******************************************************//

// pre: tokenQueue - referenced string type queue object
// post: reverses the token order in queue to convert entire expression into prefix
void Calculator::reverse(Queue<std::string> &tokenQueue)
{
	Stack<std::string> Stack;

	while (!tokenQueue.isEmpty())
	{
		if (tokenQueue.peek() == "(")
		{
			Stack.push(")");
			tokenQueue.dequeue();
		}
		else if (tokenQueue.peek() == ")")
		{
			Stack.push("(");
			tokenQueue.dequeue();
		}
		else
		{
			Stack.push(tokenQueue.peek());
			tokenQueue.dequeue();
		}
	}
	while (!Stack.isEmpty())
	{
		tokenQueue.enqueue(Stack.peek());
		Stack.pop();

	}

}

// seperates the string into individual tokens to convert entire expression into postfix or prefix
// pre: str - string type
// post: seperates the string into individual tokens to convert entire expression into postfix or prefix
void Calculator::tokenize(std::string str, Queue<std::string> &tokenQueue)
{
	int i = 0;

	std::string input = trim(str);

	std::string temp = "";
	char temp2[] = " ";

	for (; i < static_cast<int>(input.length() + 1); i++)
	{
		temp2[0] = input[i];

		if (std::strncmp(temp2, " ", 1) == 0)
		{
			tokenQueue.enqueue(temp);
			temp = "";
		}
		else temp += str[i];

	}

	// pops out null character in the string
	temp.pop_back();
	tokenQueue.enqueue(temp);
}

//pre: s - referenced constant string type
//post: trims extra spaces off expression 
//return: string typr
std::string Calculator::trim(const std::string &s)
{
	auto start = s.begin();
	while (start != s.end() && isspace(*start)) {
		start++;
	}

	auto end = s.end();
	do {
		end--;
	} while (std::distance(start, end) > 0 && isspace(*end));

	return std::string(start, end + 1);
}

//******************************************************//
//                SETTERS/GETTERS                       //
//******************************************************//

/** gets result of calculated postfix expression
@pre None.
@post None.
@return: integer type (result of postfix calculation)
*/
int Calculator::getResultPost() const
{
	return resultPost;
}

/** gets result of calculated prefix expression
@pre None.
@post None.
@return: integer type (result of prefix calculation)
*/
int Calculator::getResultPre() const
{
	return resultPre;
}

/** gets prefix expression
@pre None.
@post None.
@return: string type (prefix expression)
*/
std::string Calculator::getPrefix() const
{
	return prefixExp;
}

/** gets postfix expression
@pre None.
@post None.
@return: string type (postfix expression)
*/
std::string Calculator::getPostfix() const
{
	return postfixExp;
}


//Queue<std::string> *tokenQueue = new Queue<std::string>;
//std::string token;
//
//// tokenize the prefix string
//tokenize(prefixExp, *tokenQueue);
//
//// loop through all tokens
//while(!tokenQueue->isEmpty())
//{
//    token = tokenQueue->peek();
//
//
//    if(isOperand(token))
//    {
//        operandStack.push(std::stoi(token));
//    }
//    // Else if character is an operator
//    else if(isOperator(token))
//    {
//        int op1 = 0, op2 = 0;
//
//        if(!operandStack.isEmpty())
//        {
//            // Operator encountered
//            // Pop two elements from Stack
//            op1 = operandStack.peek();
//            operandStack.pop();
//            op2 = operandStack.peek();
//            operandStack.pop();
//
//            int result = performOperation(token[0], op1, op2);
//            operandStack.push(result);
//        }else operatorStack.push(token[0]);
//            }
//    tokenQueue->dequeue();
//}
//// deal with any remaining operators
//while(!operatorStack.isEmpty())
//{
//    // Pop two operands.
//    int operand2 = operandStack.peek();
//    operandStack.pop();
//    int operand1 = operandStack.peek();
//    operandStack.pop();
//    // Perform operation
//    int result = performOperation(operatorStack.peek(), operand1, operand2);
//
//    //Push back result of operation on stack.
//    operandStack.push(result);
//    operatorStack.pop();
//}