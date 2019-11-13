//
//  main.cpp
//  CIS 22C Lab 4
//
//  Created by Gobind Bakhshi on 11/7/19.
//  Copyright © 2019 Gobind Bakhshi. All rights reserved.
//

#include <iostream>
#include "Calculator.h"
#include <string>

using namespace std;

void beginCalculator(Calculator *calcPtr);
void inputReset();
void inputInfixValid(char* msg);
string getInput();

int main()
{
	Calculator *abacus1 = new Calculator;
	
	try
	{
		beginCalculator(abacus1);
	}
	catch (...)
	{
		cout << endl;
		cout << "You have made an error. Please begin again." << endl;
		beginCalculator(abacus1);
	}


	system("pause");
	return 0;
}

// prompts user to calculator usage prompt
// pre: calcPtr - Calculator class type
void beginCalculator(Calculator *calcPtr)
{
	std::string infix;

	cout << "**************************************************\n ";
	cout << "           WELCOME TO YOUR CALCULATOR" << endl;
	cout << "**************************************************\n " << endl;


	//*******************************************************
	// do infix to postfix calculation
	//*******************************************************
	int sSize;
	try
	{
		infix = getInput();
		sSize = infix.length();
		if (infix == "end")
		{
			cout << "GoodBye!" << endl;
			exit(0);
		}

		while (sSize > 1 && infix[sSize-1] == ' ') // removes spaces from the end of last character of expression
		{
			--sSize;
		}
		
		Queue<char> obj;
		for (int i = 0; i < sSize; ++i)
		{
			obj.enqueue(infix[i]);
		}

		while (!(obj.isEmpty()) && obj.peek() == ' ')
		{
			obj.dequeue();
		}

		if (infix.length() <= 1) // does not let an empty input through
		{
			inputInfixValid("Please enter an expression");
		}

		Calculator test;
		for (int i = 0; i < infix.length(); ++i) 
		{
			if (isalpha(infix[i])) // checks if expression contains letters
			{
				inputInfixValid("You have inputted an invalid infix expression\nPlease try again");
				break;
			}
		}
	}

	catch (char* msg)
	{
		cout << msg << endl;
		beginCalculator(calcPtr);
	}


	calcPtr->calculatePost(infix);
	cout << "**************************************************" << endl;
	cout << "The postfix expression is: " << calcPtr->getPostfix() << endl;
	cout << "The result of postfix expression is: " << calcPtr->getResultPost() << endl;
	cout << endl;

	calcPtr->calculatePre(infix);
	cout << "**************************************************" << endl;
	cout << "The prefix expression is: " << calcPtr->getPrefix() << endl;
	cout << "The result of prefix expression is: " << calcPtr->getResultPre() << endl;
	cout << endl << endl;

	beginCalculator(calcPtr);
}

// if input is invalid, input stream is cleared,
// next 100 characters and newline will be ignored
// and "Invalid Error will be thrown"
void inputReset()
{
	cin.clear();
	cin.ignore(100, '\n');
	throw "Invalid";
}

// pre: msg - character pointer
// post: if input is invalid, input stream is cleared,
// next 100 characters and newline will be ignored
// and msg
void inputInfixValid(char* msg)
{
	cin.clear();
	cin.clear();
	cin.ignore(100, '\n');
	throw msg;
}

// return: string type for postfix/prefix calculations
string getInput()
{
	string input;
	cout << "Infix Format: \n";
	cout << "a) Operands and Operators seperated by spaces \n";
	cout << "b) Valid Operators: (+,-,/,*,%)\n";
	cout << "c) Valid Operands 0-9\n";
	cout << "d) Input the string 'end' when you want to end the program\n";
	cout << "Example: ( 10 + 3 ) * 6 " << endl;
	cout << "Please do not include a space before inputting your expression" << endl; // code will throw an exeption when done
	cout << "Please enter a infix expression: " << endl;
	cin.clear();
	//    cin.ignore(1000, '\n');
	getline(cin, input); // complete validation
	return input;
}