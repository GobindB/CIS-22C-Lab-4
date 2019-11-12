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
        result = evaluatePostfix(postfixExp);
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
        result = evaluatePrefix(postfixExp);
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
    
    // checks to make sure first entry in input isnt an operator
    if(isOperator(token))
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
            
            i++;
        }
      
        // test to ensure token does not contain operator and operand i.e appropriate spacing has been used
        if(operators > 0 && operands > 0)
        {
            throw "Invalid Input: " + inputExpression;
        }
        //token cant have multiple operators
        else if(operators > 1)
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
            while(!operatorStack.isEmpty() && operatorStack.top() != '(' && higherPrecedence(operatorStack.top(),infixExp[i]))
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
    Tokenizer input(infixExp);
    Queue<std::string> tokenQueue = input.split();
   
    std::string token;
    std::string operands = "";
    std::string operators = "";
    prefixExp = "";
    operandStack.emptyList();
    operatorStack.emptyList();
    
        while(!tokenQueue.isEmpty())
        {
            token = tokenQueue.peek();
            
            if (token[0] == '(')
            {
                operatorStack.push(token[0]);
            }
            
            // If current character is closing bracket, then pop from both stacks and push result in operands stack until
            // matching opening bracket is not found.
            else if (token[0] == ')')
            {
                
                while (!operatorStack.isEmpty() && operatorStack.top() != '(')
                {
                    
                    // operand 1
                    int op1 = operandStack.top();
                    operandStack.pop();
                    
                    // operand 2
                    int op2 = operandStack.top();
                    operandStack.pop();
                    
                    // operator
                    char op = operatorStack.top();
                    operatorStack.pop();
                    
                    // Add operands and operator in form operator + operand1 + operand2.
                    //prefixExp += op + std::to_string(op1) + std::to_string(op2);
                    operators += op;
                    operands += std::to_string(op2);
                    
                    int evaluated1 = performOperation(op, op1, op2);
                    operandStack.push(evaluated1);
                }
                
                // Pop opening bracket from stack.
                operatorStack.pop();
            }
            
            // If current character is an operand then push it into operands stack.
            else if (isOperand(token))
            {
                operandStack.push(std::stoi(token));
            }
            
            // If current character is an operator, then push it into operators stack after popping
            // high priority operators from operators stack and pushing result in operands stack.
            else
            {
                while (!operatorStack.isEmpty() && precedence(token[0]) <= precedence(operatorStack.top()))
                {
                    
                    int op1 = operandStack.top();
                    operandStack.pop();
                    
                    int op2 = operandStack.top();
                    operandStack.pop();
                    
                    char op = operatorStack.top();
                    operatorStack.pop();
                    
                    operators += op;
                    operands += std::to_string(op2);
                    
                    int evaluated = performOperation(op, op1, op2);
                    operandStack.push(evaluated);
                }
                
                operatorStack.push(token[0]);
            }
            tokenQueue.dequeue();
        }
        
        // Pop operators from operators stack until it is empty and add result of each pop operation in
        // operands stack.
        while (!operatorStack.isEmpty())
        {
            int op1 = operandStack.top();
            operandStack.pop();

            int op2 = operandStack.top();
            operandStack.pop();

            char op = operatorStack.top();
            operatorStack.pop();


            operators += op;
            operands += std::to_string(op2);

            int evaluated = performOperation(op, op1, op2);
            operandStack.push(evaluated);
        }
    
    prefixExp += operators + operands;
    
    return prefixExp;
}



/** check if character is a parenthesis
 @pre None.
 @post None.
 @param postfix the character to test
 @return true if is parenthesis, false otherwise
 */
int Calculator::evaluatePostfix(std::string postfix)
{
    for(int i = 0;i< postfix.length();i++)
    {
        
        std::string temp;
        temp[0] = postfix[i]; // BUG what if double digit
        
        // If character is operator, pop two elements from stack, perform operation and push the result back.
        if(isOperator(temp))
        {
            // Pop two operands.
            int operand2 = operandStack.top();
            operandStack.pop();
            int operand1 = operandStack.top();
            operandStack.pop();
            // Perform operation
            int result = performOperation(postfix[i], operand1, operand2);
            //Push back result of operation on stack.
            operandStack.push(result);
        }

    }
    // If expression is in correct format, Stack will finally have one element. This will be the output.
    return operandStack.top();
}

/** check if character is a parenthesis
 @pre None.
 @post None.
 @param prefix the character to test
 @return true if is parenthesis, false otherwise
 */
int Calculator::evaluatePrefix(std::string prefix)
{
    int num1;
    int num2;
    std::string temp;
    for (int i = 0; i < prefix.length(); i++)
    {
        temp = prefix[i];
        if(isOperator(temp))
        {
            num1 = operandStack.top();
            operandStack.pop();
            num2 = operandStack.top();
            operandStack.pop();
            
            operandStack.push(performOperation(prefix[i], num1, num2));
        }
    }
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

/** converts expressionInfixQ Queue to expressionPostQ Queue
 @pre expressionInfixQ checks
 @post expressionPostQ is populated
 @return expressionPostQ as a string */
int Calculator::higherPrecedence(char op1, char op2)
{
    int op1Weight = precedence(op1);
    int op2Weight = precedence(op2);
    
    // If operators have equal precedence, return true if they are left associative.
    // return false, if right associative.
    // if operator is left-associative, left one should be given priority.
    if(op1Weight == op2Weight)
        return true;
    
    return op1Weight > op2Weight ?  true: false;
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

