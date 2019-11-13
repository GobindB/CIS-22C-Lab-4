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
    
    std::string infixExp = "";
    std::string postfixExp = "";
    std::string prefixExp = "";
    int resultPost;
    int resultPre;

protected:
    
    bool validate(std::string inputExpression);
   
    bool isOperator(std::string op);
    bool isParen(std::string op);
    bool isOperand(std::string C);
    
    int precedence(char op);
    int performOperation(char operation, int operand1, int operand2);
    int higherPrecedence(char op1, char op2);
    
    void infixToPostfix(std::string infix);
    void infixToPrefix(std::string infix);
    void evaluatePre();
    
    void reverse(Queue<std::string> &aQueue);
    void tokenize(std::string, Queue<std::string> &aQ);

public:
    
   
    void calculatePost(const std::string& inputExpression);
    void calculatePre(const std::string &inputExpression);
 
    //getters
    int getResultPost() const;
    int getResultPre() const;
    std::string getInfix() const;
    std::string getPostfix() const;
    std::string getPrefix() const;
    
};
#endif /* Calculator_h */
