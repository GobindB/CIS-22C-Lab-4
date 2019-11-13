//
//  Calculator.cpp
//  CIS 22C Lab 4
//
//  Created by Gobind Bakhshi on 11/7/19.
//  Copyright © 2019 Gobind Bakhshi. All rights reserved.
//

#include "Calculator.h"


/** validates the expression syntax and pushes operators/operands to member stacks
 @pre expressionInfix validation
 @post tokenize string and push operators/operands to appropriate stacks
 */
void Calculator::calculatePost(const std::string &inputExpression)
{
    if(validate(inputExpression))
    {
        //set infix expression to input after validation checking
        infixExp = inputExpression;
        infixToPostfix();
        result = evaluate(postfixExp);
    }
    
}

/** validates the expression syntax and pushes operators/operands to member stacks
 @pre expressionInfix validation
 @post tokenize string and push operators/operands to appropriate stacks
 */
void Calculator::calculatePre(const std::string &inputExpression)
{
    if(validate(inputExpression))
    {
        //set infix expression to input after validation checking
        infixExp = inputExpression;
        infixToPrefix();
        result = evaluate(prefixExp);
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
    Queue<std::string> tokenQueue = input.split();
    
    std::string token;
    int i = 0;
    int operands =0;
    int operators = 0;
    int openParen = 0;
    int closedParen = 0;
    
    // must test
    // 1. series cant end with operator
    
    token = tokenQueue.peek();
    
    std::string temp1 = std::to_string(token[0]);
    // checks to make sure first entry in input isnt an operator
    if(isOperator(temp1))
    {
        throw "Invalid Input: " + inputExpression;
    }
    
    // loop through each element of the queue and determine if operator or operand while not empty
    while( !tokenQueue.isEmpty() )
    {
        operators = 0;
        operands =  0;
        i = 0;
        
        token = tokenQueue.peek(); // test to ensure correct value is returned after peek!!!!!!!
        
        // check if token is valid and if so push to appropriate stack
        while(token[i] != '\0')
        {
            // check if token is an operand
            if(token[i] >= '0' && token[i] <= '9')
            {
                operands++;
            }
            // check if token has an operator or parenthesis
            else if (isOperator(token) || isParen(token))
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
            
            // test to ensure token does not contain operator and operand i.e appropriate spacing has been used
            if(operators > 0 && operands > 0)
            {
                throw "Invalid Input: " + inputExpression;
            }
            
            i++;
        }
      
        //token cant have multiple operators
        if(operators > 1)
        {
            throw "Invalid Input: " + inputExpression;
        }
        
        // deque this token from the queue of tokens
        tokenQueue.dequeue();
    }
    if(openParen != closedParen)
    {
        throw "Invalid Input: " + inputExpression;
    }
    // if no exception has been thrown then input is valid
    infixExp = inputExpression;
    return true;
}

/** converts expressionInfixQ Queue to expressionPostQ Queue
 @pre expressionInfixQ checks
 @post expressionPostQ is populated
 @return expressionPostQ as a string */
std::string Calculator::infixToPostfix()
{
    Tokenizer input(infixExp);
    Queue<std::string> tokenQueue = input.split();
    
    std::string token;
    postfixExp = "";
    
    operandStack.emptyList();
    operatorStack.emptyList();
    int i = 0;
    
    while(!tokenQueue.isEmpty())
    {
        token = tokenQueue.peek();
        // If character is operator, pop two elements from stack, perform operation and push the result back.
        if(isOperator(token))
        {
            while(!operatorStack.isEmpty() && operatorStack.top() != '(' && precedence(operatorStack.top()) > precedence(infixExp[i]))
            {
                postfixExp += operatorStack.peek();
                operatorStack.pop();
            }
            operatorStack.push(token[0]);
        }
        // Else if character is an operand
        else if(isOperand(token))
        {
            postfixExp += token;
            operandStack.push(std::stoi(token));
        }
        
        else if (token[0] == '(')
        {
            operatorStack.push(token[0]);
        }
        
        else if(token[0] == ')')
        {
            while(!operatorStack.isEmpty() && operatorStack.top() !=  '(') {
                postfixExp += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        tokenQueue.dequeue();
    }
    
    while(!operatorStack.isEmpty()) {
        postfixExp += operatorStack.top();
        operatorStack.pop();
    }
    
    return postfixExp;
}

/** converts expressionInfixQ Queue to expressionPostQ Queue
 @pre expressionInfixQ checks
 @post expressionPostQ is populated
 @return expressionPostQ as a string */
std::string Calculator::infixToPrefix()
{
    prefixExp = "";
    Tokenizer input(infixExp);
    Queue<std::string> tokenQueue = input.split();
    
    std::string token;
    postfixExp = "";
    
    operandStack.emptyList();
    operatorStack.emptyList();
    int i = 0;
    
    while(!tokenQueue.isEmpty())
    {
        token = tokenQueue.peek();
        // If character is operator, pop two elements from stack, perform operation and push the result back.
        if(isOperator(token))
        {
            while(!operatorStack.isEmpty() && operatorStack.top() != '(' && precedence(operatorStack.top()) > precedence(infixExp[i]))
            {
                postfixExp += operatorStack.peek();
                operatorStack.pop();
            }
            operatorStack.push(token[0]);
        }
    
    }
     return prefixExp;
}



/** check if character is a parenthesis
 @pre None.
 @post None.
 @param expression the string to evaluate
 @return true if is parenthesis, false otherwise
 */
int Calculator::evaluate(std::string expression)
{
    std::string temp;
    
    for(int i = 0;i< expression.length();i++)
    {
        
       
       temp[0] = expression[i]; // BUG what if double digit
        
        // If character is operator, pop two elements from stack, perform operation and push the result back.
        if(isOperator(temp))
        {
            // Pop two operands.
            int operand2 = operandStack.top();
            operandStack.pop();
            int operand1 = operandStack.top();
            operandStack.pop();
            // Perform operation
            int result = performOperation(expression[i], operand1, operand2);
            //Push back result of operation on stack.
            operandStack.push(result);
        }

    }
    // If expression is in correct format, Stack will finally have one element. This will be the output.
    return operandStack.top();
}

/** converts expressionInfixQ Queue to expressionPostQ Queue
 @pre expressionInfixQ checks
 @post expressionPostQ is populated
 @return expressionPostQ as a string */
bool Calculator::isOperand(std::string C)
{
    bool flag = false;
    
    for(int i = 0; i < C.length(); i++)
    {
        if(C[i] >= '0' && C[0] <= '9')
        {
            flag = true;
        }
        else return false;
    }
    return flag;
}

/** converts expressionInfixQ Queue to expressionPostQ Queue
 @pre expressionInfixQ checks
 @post expressionPostQ is populated
 @return expressionPostQ as a string */
int Calculator::performOperation(char operation, int operand1, int operand2)
{
    if(operation == '+') return operand1 +operand2;
    else if(operation == '-') return operand1 - operand2;
    else if(operation == '*') return operand1 * operand2;
    else if(operation == '/') return operand1 / operand2;
    
    else throw "Invalid operation.";
    return -1;
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

/** check if character is a parenthesis
 @pre None.
 @post None.
 @param op the character to test
 @return true if is parenthesis, false otherwise
 */
bool Calculator::isParen(std::string op)
{
   
    
    if(op[0] == '(' || op[0] == ')')
    {
        return true;
    }else return false;
}

/** check if character is an operator
 @pre None.
 @post None.
 @param op the operator to test
 @return true if is defined operator, false if not defined operator
 */
bool Calculator::isOperator(std::string op)
{
    if (op[0] == '-' || op[0] == '+' || op[0] == '/' || op[0] == '%' || op[0] == '/' || op[0] =='*' )
    {
        return true;
    }
    return false;
}

/** check if character is an operator
 @pre None.
 @post None.
 @return true if is defined operator, false if not defined operator
 */
int Calculator::getResult() const
{
    return result;
}

/** check if character is an operator
 @pre None.
 @post None.
 @return true if is defined operator, false if not defined operator
 */
std::string Calculator::getPostfix() const
{
    return postfixExp;
}

/** check if character is an operator
 @pre None.
 @post None.
 @return true if is defined operator, false if not defined operator
 */
std::string Calculator::getPrefix() const
{
    return prefixExp;
}


