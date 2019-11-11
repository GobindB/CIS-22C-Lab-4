//
//  Calculator.cpp
//  CIS 22C Lab 4
//
//  Created by Gobind Bakhshi on 11/7/19.
//  Copyright © 2019 Gobind Bakhshi. All rights reserved.
//

#include "Calculator.h"


int Calculator::calculate(const std::string &inputExpression)
{
    if(validate(inputExpression))
    {
        //set infix expression to input after validation checking
        infixExp = inputExpression;
        
        // clear previous result of postfix expression
        postfixExp = "";
        
        
        return result;
    }
    else
    {
        throw "Invalid syntax.";
    }
    
    
}

/** validates the expression syntax and pushes operators/operands to member stacks
 @pre expressionInfix validation
 @post tokenize string and push operators/operands to appropriate stacks
 @return error message. or true if valid
 */
bool Calculator::validate(const std::string &inputExpression)
{
    Tokenizer input(inputExpression);
    Queue<std::string> tokenQueue;
    
    std::string token;
    int i = 0;
    int operands =0;
    int operators = 0;
    int openParen = 0;
    int closedParen = 0;
    
    // returns a queue of tokenized string
    tokenQueue = input.split();
    
    // must test
    // 1. series cant end with operator
    
    token = tokenQueue.peek();
    
    // checks to make sure first entry in input isnt an operator
    if(isOperator(token[0]))
    {
        throw "Invalid Input: " + inputExpression;
    }
    
    // loop through each element of the queue and determine if operator or operand while not empty
    while( !tokenQueue.isEmpty() )
    {
        operators = 0;
        operands =  0;
        
        token = tokenQueue.peek(); // test to ensure correct value is returned after peek!!!!!!!
        
        // check if token is valid and if so push to appropriate stack
        while(token[i])
        {
            // check if token is an operand
            if(token[i] >= '0' && token[i] <= '9')
            {
                operands++;
            }
            // check if token has an operator
            else if (isOperator(token[i]))
            {
                if(token[i] == '(')
                {
                    openParen++;
                }
                if(token[i] == ')')
                {
                    closedParen++;
                }
                
                operators++;
            }
            else
            {
                throw "Invalid Input: " + inputExpression;
            }
            
            i++;
        }
        // test to ensure token does not contain operator and operand i.e appropriate spacing has been used
        if(operators > 0 && operands > 0)
        {
            throw "Invalid Input: " + inputExpression;
        }
        else if(openParen != closedParen)
        {
            throw "Invalid Input: " + inputExpression;
        }
        else if (operands > 0)
        {
            operandStack.push(stoi(token));
        }
        //token cant have multiple operators
        else if(operators > 1)
        {
            throw "Invalid Input: " + inputExpression;
        }
        else
        {
            // if valid operand then there will only be one member of the character token array
            operatorStack.push(token[0]);
        }
        
        // deque this token from the queue of tokens
        tokenQueue.dequeue();
    }
    
    // if no exception has been thrown then input is valid
    return true;
}

/** returns the precedence "weight" for an operator
 @pre None.
 @post None.
 @param op the operator
 @return Weight of the operator and -1 if not found
 */
int Calculator::precedence(std::string op)
{
    int weight = -1;
    if (op == "+") weight = 1;
    else if (op == "-") weight = 1;
    else if (op == "*") weight = 2;
    else if (op == "/") weight = 2;
    else if (op == "%") weight = 2;
    else if (op == "$") weight = 3;
    else if (op == "^") weight = 3;
    return weight;
}

/** check if character is an operator
 @pre None.
 @post None.
 @param op the operator to test
 @return true if is defined operator, false if not defined operator
 */
bool Calculator::isOperator(char op)
{
    if (op == '-' || op == '+' || op == '/' || op == '%' || op == '/' || op == '(' || op == ')')
    {
        return true;
    }
    return false;
}
