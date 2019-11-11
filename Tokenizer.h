//
//  Tokenizer.hpp
//  CIS 22C Lab 4
//
//  Created by Gobind Bakhshi on 11/10/19.
//  Copyright © 2019 Gobind Bakhshi. All rights reserved.
//



#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include "Queue.h"

// default delimiter string (space, tab, newline, carriage return, form feed)
const std::string DEFAULT_DELIMITER = " \t\v\n\r\f";

class Tokenizer
{
public:
    // ctor/dtor
    Tokenizer();
    Tokenizer(const std::string& str, const std::string& delimiter=DEFAULT_DELIMITER);
    ~Tokenizer();
    
    // set string and delimiter
    void set(const std::string& str, const std::string& delimiter=DEFAULT_DELIMITER);
    void setString(const std::string& str);             // set source string only
    void setDelimiter(const std::string& delimiter);    // set delimiter string only
    
    std::string next();                                 // return the next token, return "" if it ends
    
    Queue<std::string> split();                   // return array of tokens from current cursor
    
protected:
    
    
private:
    void skipDelimiter();                               // ignore leading delimiters
    bool isDelimiter(char c);                           // check if the current char is delimiter
    
    std::string buffer;                                 // input string
    std::string token;                                  // output string
    std::string delimiter;                              // delimiter string
    std::string::const_iterator currPos;                // string iterator pointing the current position
    
};

#endif // TOKENIZER_H
