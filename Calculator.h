//
//  Calculator.h
//  CIS 22C Lab 4
//
//  Created by Gobind Bakhshi on 11/7/19.
//  Copyright © 2019 Gobind Bakhshi. All rights reserved.
//

#ifndef Calculator_h
#define Calculator_h

#include <string>
#include "Stack.h"
#include "Queue.h"

class Calculator
{
    
private:
    
    //stack of operands
    Stack<int> operandStack;
    
    // stack of operatos
    Stack<char> operatorStack;
    
    Queue<std::string> tokenQueue;
    
    // most recent input expression
    std::string infixExp = "";
    
    // most recent expression expressed in post-fix form
    std::string postfixExp = "";
    
    // most recent expression in pre-fix form
    std::string prefixExp = "";
    
    // result of evaluated expression
    int result;

protected:
    bool validate(std::string inputExpression);
    bool isOperator(std::string op);
    bool isParen(std::string op);
    bool isOperand(std::string C);
    int precedence(char op);
    int performOperation(char operation, int operand1, int operand2);
    int higherPrecedence(char op1, char op2);
    int evaluate(std::string evaluate);
    void infixToPostfix();
    void infixToPrefix();
    void reverse(Queue<std::string> aQueue);
    void tokenize(std::string);

public:
    
   
    void calculatePost(const std::string& inputExpression);
    void calculatePre(const std::string &inputExpression);
 
    //getters
    int getResult() const;
    std::string getInfix() const;
    std::string getPostfix() const;
    std::string getPrefix() const;
    
    //setters
    void setInfix(std::string input);
    void setResult(int result);
    void setPrefix(std::string prefix);
    void setPostfix(std::string postfix);
    
};
#endif /* Calculator_h */
