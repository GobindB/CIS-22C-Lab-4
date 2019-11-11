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
    std::string infixExp = "";
    
    // most recent expression expressed in post-fix form
    std::string postfixExp = "";
    
    // most recent expression in pre-fix form
    std::string prefixExp = "";
    
    // result of evaluated expression
    int result;
    
    
    
    bool validate(const std::string& inputExpression);
    bool isOperator(std::string op);
    bool isParen(std::string op);
    bool isOperand(std::string C);
   
    int precedence(char op);
    int performOperation(char operation, int operand1, int operand2);
    int higherPrecedence(char op1, char op2);
    int evaluatePostfix(std::string postfix);
    int evaluatePrefix(std::string postfix);
    
    
    
    std::string infixToPostfix();
    std::string infixToPrefix();

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
