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
    int choice;
    std::string infix;
    do
    {
        mainMenu();
        try
        {
            cin >> choice;
            if(choice < 1 || choice > 3 )
            {
                cout << "Please enter a value between 1 and 3 " << endl;
                cin.clear();
                cin.ignore(100, '\n');
                cin >> choice;
            }
            if(!cin)
            {
                inputReset();
            }
        }
        catch (...)
        {
            cout << "Invalid input. Please begin again" << endl;
            beginCalculator(calcPtr);
        }
      
        
        
        
        switch (choice)
        {
                //*******************************************************
                // do infix to postfix calculation
                //*******************************************************
            case 1:
                infix = getInput();
                calcPtr->calculatePost(infix);
                cout << "**************************************************" << endl;
                cout << "The postfix expression is: " << calcPtr->getPostfix() << endl;
                cout << "The result of postfix expression is: " << calcPtr->getResult() << endl;
                cout << endl << endl;
                break;
            case 2:
                infix = getInput();
                calcPtr->calculatePre(infix);
                cout << "**************************************************" << endl;
                cout << "The prefix expression is: " << calcPtr->getPrefix() << endl;
                cout << "The result of prefix expression is: " << calcPtr->getResult() << endl;
                cout << endl << endl;
                break;
        }

    }while(choice != 3);
    
        if (choice == 3)
        {
            exit(0);
        }
}

void mainMenu()
{
  
    cout << "**************************************************\n ";
    cout << "           WELCOME TO YOUR CALCULATOR" << endl;
    cout << "**************************************************\n " << endl;
    cout << "Please select an option from the following (1-3)" << endl;
    cout << "Select an option \n";
    cout << "1. Infix to Postfix \n";
    cout << "2. Infix to Prefix\n";
    cout << "3. Exit Calculator\n";
    cout << "**************************************************" << endl;
    cout << "Please select an option from 1-3: " << endl;
  
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
    cout << endl << endl;
    cout << "**************************************************" << endl;
    cout << "Infix Format: \n";
    cout << "a) Operands and Operators seperated by spaces \n";
    cout << "b) Valid Operators: (+,-,/,*,%)\n";
    cout << "c) Valid Operands 0-9\n";
    cout << "Example: ( 10 + 3 ) * 6 " << endl;
    cout << "Please enter a infix expression: " << endl;
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, input); // complete validation
    return input;
}
