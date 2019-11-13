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

// TO DO FIX INPUT VALIDATION
using namespace std;

void beginCalculator(Calculator *calcPtr);
void mainMenu();
void inputReset();
string getInput();

int main()
{
    Calculator *abacus1 = new Calculator;
    beginCalculator(abacus1);
    
    try
    {
        beginCalculator(abacus1);
    }
    catch (char * msg)
    {
        cout << "You have made an error. Please begin again." << endl;
        beginCalculator(abacus1);
    }
}

void beginCalculator(Calculator *calcPtr)
{
        std::string infix;
    
        cout << "**************************************************\n ";
        cout << "           WELCOME TO YOUR CALCULATOR" << endl;
        cout << "**************************************************\n " << endl;
        
 
                //*******************************************************
                // do infix to postfix calculation
                //*******************************************************
                infix = getInput();
                
                calcPtr->calculatePost(infix);
                cout << "**************************************************" << endl;
                cout << "The postfix expression is: " << calcPtr->getPostfix() << endl;
                cout << "The result of postfix expression is: " << calcPtr->getResult() << endl;
                
                calcPtr->calculatePre(infix);
                cout << "**************************************************" << endl;
                cout << "The prefix expression is: " << calcPtr->getPrefix() << endl;
                cout << "The result of prefix expression is: " << calcPtr->getResult() << endl;
                cout << endl << endl;
 
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

string getInput()
{
    string input;
    cout << "Infix Format: \n";
    cout << "a) Operands and Operators seperated by spaces \n";
    cout << "b) Valid Operators: (+,-,/,*,%)\n";
    cout << "c) Valid Operands 0-9\n";
    cout << "Example: ( 10 + 3 ) * 6 " << endl;
    cout << "Please enter a infix expression: " << endl;
    cin.clear();
//    cin.ignore(1000, '\n');
    getline(cin, input); // complete validation
    return input;
}
