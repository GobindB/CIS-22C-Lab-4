#include "Calculator.h"


/* Checks if the argument is a valid operator
Pre: test - char to be tested
Post:
Return: bool - true or false
*/
bool Calculator::isValidOp(char test)
{
	if (test == '+' || test == '-' || test == '*' || test == '/'
		|| test == '%' || test == '(' || test == ')')
		return true;
	else
		return false;
}


/* checks if argument is an integer
Pre: test - char
Post:
Return: bool - true or false
*/
bool Calculator::isInteger(char test)
{
	if (test >= '0' && test <= '9')
		return true;
	else
		return false;
}


/* checks the priority of each operator
Pre: test - char of operator
Post:
Return: int - value of priority for the operator
*/
int Calculator::priority(char test)
{
	if (test == '(' || test == ')')
		return 1;
	else if (test == '+' || test == '-')
		return 2;
	else if (test == '*' || test == '/')
		return 3;
	else
		return 0; //if none of the above
}


/* Reverses a string. Uses a stack to do so.
Pre: str - string of equation to be reversed
Post:
Return: string - the reversed string
*/
std::string Calculator::reverse(std::string str)
{
	Stack<char> reverser;
	std::string temp;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
			reverser.push(')');
		else if (str[i] == ')')
			reverser.push('(');
		else
			reverser.push(str[i]); //put string into the stack
	}

	while (!reverser.isEmpty())
	{
		temp += reverser.peek(); //stack is last in first out, so peeking reverses the original string
		reverser.pop();
	}
	return temp;
}



/* gets the equation from the main. calls the post and prefix conversion funtions
Pre: eqn - string of equation. Has been checked already in the main.
Post: modifies the values of the infix, prefix, and postfix member values
Return:
*/
void Calculator::setEquation(std::string eqn)
{
	infixEquation = eqn;
	postfixEquation = infixToPostfix(infixEquation);
	prefixEquation = infixToPrefix(infixEquation);
}


/* converts infix equation to postfix form
Pre: infix - string of infix equation
Post:
Return: returns string of the postfix form
*/
std::string Calculator::infixToPostfix(std::string infix)
{
	Stack<char> operatorsStack;
	std::string temp; //string to hold the postfix
	Queue<char> eqnQ;

	operatorsStack.push('('); //every equation theoretically can have parenthesis at both ends.
							  // this sets the bounds so that the stack does not underflow nor
							  // attempt to peek an empty stack.

	for (int i = 0; i < infix.length(); i++) //moves the infix equation to the queue
	{
		eqnQ.enqueue(infix[i]);
	}


	while (!eqnQ.isEmpty()) //go through entire equation
	{
		if (eqnQ.front() == '(') //if left parenthesis, add it to stack
		{
			operatorsStack.push(eqnQ.front());
			eqnQ.dequeue();
		}
		else if (isInteger(eqnQ.front())) //if char is a number
		{
			// numbers must be separated by spaces, so read until a space is encountered
			while (!eqnQ.isEmpty() && isInteger(eqnQ.front()))
			{
				temp += eqnQ.front();
				eqnQ.dequeue();
			}
			temp += ' '; //integers followed by a space
		}
		else if (isValidOp(eqnQ.front())) //if char is a valid operator
		{
			if (eqnQ.front() == ')') //if right parenthesis
			{
				while (operatorsStack.peek() != '(') //going to peek and pop until a left parenthesis is found
				{
					temp += operatorsStack.peek();
					temp += ' '; //space
					operatorsStack.pop();
				}

				if (operatorsStack.peek() == '(') //remains at the end of the above
				{
					operatorsStack.pop(); //remove the left parenthesis since the right one is not added to the stack
				}
				eqnQ.dequeue();
			}
			else
			{
				//will keep appending and popping the top of the stack until the top of the stack
				//is not <= the char. The new char should be the smallest operator in the stack
				//within the scope of parenthesis

				while (priority(eqnQ.front()) <= priority(operatorsStack.peek()))
				{
					temp += operatorsStack.peek();
					temp += ' ';
					operatorsStack.pop();
				}

				operatorsStack.push(eqnQ.front()); //pushes to top of stack

				eqnQ.dequeue();
			}
		} //end of else if (char is a valid operator)
		else //skip space
		{
			eqnQ.dequeue();
		}
	} //end of while loop

	while (operatorsStack.peek() != '(') //at the very end, pop until encounter the left parenthesis we added at the beginning.
	{
		temp += operatorsStack.peek();
		temp += ' ';
		operatorsStack.pop();
	}
	return temp;
}



/* changes an infix equation to its prefix form
Pre: infix - string of infix form
Post:
Return: string - the infix form of the equation
*/
std::string Calculator::infixToPrefix(std::string infix)
{
	std::string temp;
	temp = reverse(infix); //reverse the infix equation

	temp = infixToPostfix(temp); //turn the reversed equation to postfix form

	temp = reverse(temp); //reverse the postfix form

	return temp; //not in prefix form
}



/* checks if the equation is valid.
Pre: eqn - string to be checked
Post:
Return: bool - true or false. true if valid, false otherwise
*/
bool Calculator::checkValidEqn(std::string eqn)
{
	bool valid = true; //holds the validity
	int dupeType = 0; //1: operand, 2:operator
					  // used to make sure characters of the same type don't follow each other

	Stack<char> parenthesisCheck; //stack to make sure each left parenthesis has a right one
	Queue<char> eqnQ; //queue for the equation as we parse through it

	long size = eqn.length(); //size will be modified to cut off tailing spaces from equation
							  //back to front, removing rear spaces which only cause problems
	while (eqn.length() >= 1 && eqn[size - 1] == ' ')
	{
		--size;
	}

	//equeueing the equation into the queue
	for (int i = 0; i < size; i++)
	{
		eqnQ.enqueue(eqn[i]);
	}

	//dequeueing useless spaces from the front.
	while (!eqnQ.isEmpty() && eqnQ.front() == ' ')
	{
		eqnQ.dequeue();
	}

	//if equation has no characters in it, return false immediately
	if (eqnQ.isEmpty())
	{
		return false;
	}

	//if equation leads with anything other than an integer or a left parenthesis, return false
	if (!eqnQ.isEmpty() && !isInteger(eqnQ.front()) && eqnQ.front() != '(')
	{
		return false;
	}

	while (valid && !eqnQ.isEmpty()) //parses through until queue is empty
	{
		if (eqnQ.front() == '(') //adds '(' to a stack. Used to make sure each '(' has a ')'
		{
			if (dupeType == 1) //makes sure previous type was not an operand
				valid = false;
			else //left parenthesis must be followed by an operand
				dupeType = 2; //informs program the type is now treated as an operator

			parenthesisCheck.push(eqnQ.front()); //pushes the '(' to the stack.
			eqnQ.dequeue(); //removes front of queue
		}
		else if (eqnQ.front() == ')')
		{
			if (dupeType == 2) //can not be preceded by an operator
				valid = false;
			else
				dupeType = 1; // must be followed by an operator, not an operand

							  //remove a '(' from the stack due to encountering a ')'
			eqnQ.dequeue();


			//If unable to pop, it means the stack is already empty.
			//It means that there are not enough '('s to match the ')'s
			if (!parenthesisCheck.pop())
			{
				valid = false;
			}
		}
		else if (isValidOp(eqnQ.front())) //if a valid operator
		{
			if (dupeType == 2) //can not be preceded by an operator
				valid = false;
			else
				dupeType = 2;


			eqnQ.dequeue(); //check next char

			if (eqnQ.isEmpty()) //if operator is last char, equation is invalid
			{
				valid = false;
			}

			// if followed by anything other than a space or '(', equation is invalid
			if (!eqnQ.isEmpty() && eqnQ.front() != ' ' && eqnQ.front() != '(')
				valid = false;

		}
		else if (isInteger(eqnQ.front())) //if front of queue is an integer
		{
			if (dupeType == 1) //can not be preceded by another integer
				valid = false;
			else
				dupeType = 1;

			//Will move through queue until hitting a space. Make sure integers are isolated
			while (valid && !eqnQ.isEmpty() && (eqnQ.front() != ' ' && eqnQ.front() != ')'))
			{
				if (!isInteger(eqnQ.front()))
				{
					valid = false;
				}
				eqnQ.dequeue();
			}
		}
		else if (eqnQ.front() == ' ') //if front is a space, move on
		{
			eqnQ.dequeue();
		}
		else //if none of the above, the character must be invalid
		{
			valid = false;
		}
	}

	//should be empty by the end because each '(' needs a ')'
	if (!parenthesisCheck.isEmpty()) //if not empty, it means there were not enough ')'s
	{
		valid = false;
	}

	return valid;
}


/* gets the infix equation
Pre:
Post:
Return: string - infix equation
*/
std::string Calculator::getInfixEquation()
{
	return infixEquation;
}


/* gets the prefix equation
Pre:
Post:
Return: string - prefix equation
*/
std::string Calculator::getPrefixEquation()
{
	return prefixEquation;
}


/* gets the postfix equation
Pre:
Post:
Return: string - postfix equation
*/
std::string Calculator::getPostfixEquation()
{
	return postfixEquation;
}
