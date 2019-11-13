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
 @post tokenize string and push operators/operands to appropriate stacks
 */
void Calculator::calculatePost(const std::string &inputExpression)
{
    if(validate(inputExpression))
    {
        infixExp = inputExpression;
        infixToPostfix(inputExpression);
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
        infixExp = inputExpression;
        infixToPrefix(inputExpression);
        evaluatePre();
    }
    
}


//******************************************************//
//                VALIDITY CHECKER                      //
//******************************************************//

/** validates the expression syntax and pushes operators/operands to member stacks
 @pre expressionInfix validation
 @post tokenize string and push operators/operands to appropriate stacks
 @return error message. or true if valid
 */
bool Calculator::validate(std::string inputExpression)
{
    
    Queue<std::string> *tokenQueue = new Queue<std::string>;
    tokenize(inputExpression, *tokenQueue);
    
    std::string token;
    
    int i = 0;
    int operands =0;
    int operators = 0;
    int openParen = 0;
    int closedParen = 0;
    
    // checks to make sure first entry in input isnt an operator
    if(isOperator(tokenQueue->peek()))
    {
        throw "Invalid Input: " + inputExpression;
    }
    
    // loop through each element of the queue and determine if operator or operand while not empty
    while(!tokenQueue->isEmpty())
    {
        operators = 0;
        operands =  0;
        i = 0;
        
        token = tokenQueue->peek(); // test to ensure correct value is returned after peek!!!!!!!
        
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
        tokenQueue->dequeue();
    }
    if(openParen != closedParen)
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
 @post expressionPostQ is populated
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
    while(!tokenQueue->isEmpty())
    {
        token = tokenQueue->peek();
        
        // If character is operator, pop two elements from stack, perform operation and push the result back.
        if(isOperator(token))
        {
            while(!operatorStack.isEmpty() && operatorStack.peek() != '(' && precedence(operatorStack.peek()) > precedence(token[0]))
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
                
                postfixExp +=  operatorStack.peek();
                postfixExp += " ";
                operatorStack.pop();
            }
            operatorStack.push(token[0]);
        }
        // Else if character is an operand
        else if(isOperand(token))
        {
            postfixExp += token + ' ' ;
            operandStack.push(std::stoi(token));
        }
        
        else if (token[0] == '(')
        {
            operatorStack.push(token[0]);
        }
        else if(token[0] == ')')
        {
            while(!operatorStack.isEmpty() && operatorStack.peek() !=  '(')
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
    while(!operatorStack.isEmpty())
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
 @post expressionPostQ is populated
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
    
    while(!tokenQueue->isEmpty())
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
    while(!tokenQueue2->isEmpty())
    {
        finalPreFix += tokenQueue2->peek();
        finalPreFix += " ";
        tokenQueue2->dequeue();
    }
    prefixExp = finalPreFix;
}

void Calculator::evaluatePre()
{
    Stack<int> operandStack;
    Stack<char> operatorStack;
    Queue<std::string> *tokenQueue = new Queue<std::string>;
    std::string token;
    
    // tokenize the prefix string
    tokenize(prefixExp, *tokenQueue);
    
    // loop through all tokens
    while(!tokenQueue->isEmpty())
    {
        token = tokenQueue->peek();
        
        // If character is operator, pop two elements from stack, perform operation and push the result back.
        if(isOperator(token))
        {
            while(!operatorStack.isEmpty() && operatorStack.peek() != '(' && precedence(operatorStack.peek()) > precedence(token[0]))
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
                operatorStack.pop();
            }
            operatorStack.push(token[0]);
        }
        // Else if character is an operand
        else if(isOperand(token))
        {
            operandStack.push(std::stoi(token));
        }
        
        else if (token[0] == '(')
        {
            operatorStack.push(token[0]);
        }
        else if(token[0] == ')')
        {
            while(!operatorStack.isEmpty() && operatorStack.peek() !=  '(')
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
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        tokenQueue->dequeue();
    }
    
    // deal with any remaining operators
    while(!operatorStack.isEmpty())
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
        operatorStack.pop();
    }
    
    resultPre = operandStack.peek();
  
}
//******************************************************//
//                OPERATIONS/PRECEDENCE                 //
//******************************************************//

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
    else if(operation == '%') return operand1 % operand2;
 
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

//******************************************************//
//                STATE CHECKERS                        //
//******************************************************//


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


//******************************************************//
//                TOKENIZER FUNCTIONS                   //
//******************************************************//

void Calculator::reverse(Queue<std::string> &tokenQueue)
{
    Stack<std::string> Stack;
    
    while (!tokenQueue.isEmpty())
    {
        if(tokenQueue.peek() == "(")
        {
            Stack.push(")");
            tokenQueue.dequeue();
        }
        else if(tokenQueue.peek() == ")")
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

/** check if character is an operator
 @pre None.
 @post None.
 */
void Calculator::tokenize(std::string str, Queue<std::string> &tokenQueue)
{
    int i = 0;
    
    if(str[0] == ' ')
    {
        i++;
    }
    std::string temp = "";
    
    char temp2[] = " ";
    
    for(i; i < str.length()+1; i++)
    {
        temp2[0] = str[i];
        
        if(std::strncmp(temp2, " ", 1) == 0)
        {
            tokenQueue.enqueue(temp);
            temp = "";
        }
        else temp += str[i];
        
    }
    
    //remove trailing whitespace
    if(temp[i] == ' ')
    {
        temp.pop_back();
    }
    // pops out null character in the string
    temp.pop_back();
    tokenQueue.enqueue(temp);
}


//******************************************************//
//                SETTERS/GETTERS                       //
//******************************************************//

/** check if character is an operator
 @pre None.
 @post None.
 @return true if is defined operator, false if not defined operator
 */
int Calculator::getResultPost() const
{
    return resultPost;
}

/** check if character is an operator
 @pre None.
 @post None.
 @return true if is defined operator, false if not defined operator
 */
int Calculator::getResultPre() const
{
    return resultPre;
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

/** check if character is an operator
 @pre None.
 @post None.
 @return true if is defined operator, false if not defined operator
 */
std::string Calculator::getPostfix() const
{
    return postfixExp;
}
