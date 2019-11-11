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
    int j = 0;
    int operands =0;
    int operators = 0;
    int openParen = 0;
    int closedParen = 0;
    char x;
    
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
        i = 0;
        j = 0;
        
        token = tokenQueue.peek(); // test to ensure correct value is returned after peek!!!!!!!
        
        // check if token is valid and if so push to appropriate stack
        while(token[i] != '\0') //null terminator?!!!!!!
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
        //token cant have multiple operators
        else if(operators > 1)
        {
            throw "Invalid Input: " + inputExpression;
        }
        if (operands > 0)
        {
            operandStack.push(stoi(token));
        }
        else
        {
            if(token[0] == '(')
            {
                operatorStack.push(token[0]);
            }
            else if( isdigit(token[0]) || isalpha(token[0]))
            {
                postfixExp[j] = token[0];              /* add operand symbol to postfix expr */
                j++;
            }
            else if(token[0] == '*' || token[0] == '/' ||token[0] == '+'
                    || token[0] =='-' || token[0] =='%')        /* means symbol is operator */
            {
                x = operatorStack.peek();
                operatorStack.pop();
                
                while(isOperator(x) == 1 && precedence(x)>= precedence(token[0]))
                {
                    postfixExp[j] = x;                  /* so pop all higher precendence operator and */
                    j++;
                    x = operatorStack.peek();
                    operatorStack.pop();                    /* add them to postfix expresion */
                }
                operatorStack.push(x);
                /* because just above while loop will terminate we have
                 oppped one extra item
                 for which condition fails and loop terminates, so that one*/
                
                operatorStack.push(token[0]);                 /* push current oprerator symbol onto stack */
            }
            else if(token[0] == ')')         /* if current symbol is ')' then */
            {
                x = operatorStack.peek();
                operatorStack.pop();                  /* pop and keep popping until */
               
                while(x != '(')                /* '(' encounterd */
                {
                    postfixExp[j] = x;
                    j++;
                    x = operatorStack.peek();
                    operatorStack.pop();
                }
            }
           
            i++;
            
         /* while loop ends here */
    
            postfixExp[j] = '\0'; /* add sentinel else puts() fucntion */
            /* will print entire postfix[] array upto SIZE */
            
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
int Calculator::precedence(char op)
{
    if(op == '^')
        return 3;
    else if(op == '*' || op == '/')
        return 2;
    else if(op == '+' || op == '-')
        return 1;
    else
        return -1;
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

/** converts expressionInfixQ Queue to expressionPostQ Queue
 @pre expressionInfixQ checks
 @post expressionPostQ is populated
 @param None
 @return expressionPostQ as a string */
std::string Calculator::infixToPostfix()
{
    return "";
}

/*
 // if valid operand then there will only be one member of the character token array.
 // If the precedence of the scanned operator is greater than the precedence of the operator
 // in the stack(or the stack is empty or the stack contains a ‘(‘ ), push it.
 if(operatorStack.isEmpty())
 {
 operatorStack.push(token[0]);
 }
 else if(operatorStack.peek() == '(')
 {
 operatorStack.push(token[0]);
 }
 else if(precedence(token[0]) > precedence(operatorStack.peek()))
 {
 operatorStack.push(token[0]);
 }
 else
 {
 while(!operatorStack.isEmpty())
 {
 if(precedence(operatorStack.peek()) >= precedence(token[0])
 && (operatorStack.peek() != '(' ||operatorStack.peek() != ')' ))
 {
 operatorStack.pop();
 }
 }
 operatorStack.push(token[0]);
 }
 */
