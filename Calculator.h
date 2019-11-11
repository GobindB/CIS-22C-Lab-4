//
//  Calculator.h
//  CIS 22C Lab 4
//
//  Created by Gobind Bakhshi on 11/7/19.
//  Copyright © 2019 Gobind Bakhshi. All rights reserved.
//

#ifndef Calculator_h
#define Calculator_h

#include <stdio.h>
#include "Stack.h"
#include "Queue.h"
#include "Tokenizer.h"

// use the two stack method as shown in class

// 1. change the infix expression to post-fix expression.
// 2. output the post fix expression as well as its result
// 3. verify result by repeating process with converting to pre-fix expression
// 4. output pre-fix expression and result
//
// 5. assume operands in input will be any size integer operands but succesive operands/operators are
//    seperated by spaces (perform appropriate validation) infrom user if malformed
//    unary operators are illegal
//
// 6. all binary arithmetic operators (+,-,*,/,%) and parentheses



class Calculator
{
    
private:
    
    //stack of operands
    Stack<int> operandStack;
    
    // stack of operatos
    Stack<char> operatorStack;
    
    // most recent input expression
    std::string infixExp;
    
    // most recent expression expressed in post-fix form
    std::string postfixExp;
    
    // most recent expression in pre-fix form
    std::string prefixExp;
    
    // result of evaluated expression
    int result;
    
    void evaluate();
    
    
    
public:
    
   
    int calculate(const std::string& inputExpression);
    int precedence(std:: string operators);
    bool validate(const std::string& inputExpression);
    bool isOperator(char op);
    
    //setters
    void setInfix(std::string input);
    
    //getters
    int getResult() const;
    std::string getInfix() const;
    std::string getPostfix() const;
    std::string getPrefix() const;
    
    
    std::string infixToPostfix();
    
};
#endif /* Calculator_h */
