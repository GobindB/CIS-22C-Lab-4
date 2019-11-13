//
//  Tokenizer.cpp
//  CIS 22C Lab 4
//
//  Created by Gobind Bakhshi on 11/10/19.
//  Copyright © 2019 Gobind Bakhshi. All rights reserved.
//

#include "Tokenizer.h"


///////////////////////////////////////////////////////////////////////////////
// constructor
///////////////////////////////////////////////////////////////////////////////
Tokenizer::Tokenizer() : buffer(""), token(""), delimiter(DEFAULT_DELIMITER)
{
    currPos = buffer.begin();
}

Tokenizer::Tokenizer(const std::string& str, const std::string& delimiter) : buffer(str), token(""), delimiter(delimiter)
{
    currPos = buffer.begin();
}



///////////////////////////////////////////////////////////////////////////////
// destructor
///////////////////////////////////////////////////////////////////////////////
Tokenizer::~Tokenizer()
{
}



///////////////////////////////////////////////////////////////////////////////
// reset string buffer, delimiter and the currsor position
///////////////////////////////////////////////////////////////////////////////
void Tokenizer::set(const std::string& str, const std::string& delimiter)
{
    this->buffer = str;
    this->delimiter = delimiter;
    this->currPos = buffer.begin();
}

void Tokenizer::setString(const std::string& str)
{
    this->buffer = str;
    this->currPos = buffer.begin();
}

void Tokenizer::setDelimiter(const std::string& delimiter)
{
    this->delimiter = delimiter;
    this->currPos = buffer.begin();
}

///////////////////////////////////////////////////////////////////////////////
// return the next token
// If cannot find a token anymore, return "".
///////////////////////////////////////////////////////////////////////////////
std::string Tokenizer::next()
{
    if(buffer.size() <= 0) return "";           // skip if buffer is empty
    
    token.clear();                              // reset token string
    
    this->skipDelimiter();                      // skip leading delimiters
    
    // append each char to token string until it meets delimiter
    while(currPos != buffer.end() && !isDelimiter(*currPos))
    {
        token += *currPos;
        ++currPos;
    }
    return token;
}

///////////////////////////////////////////////////////////////////////////////
// skip any leading delimiters
///////////////////////////////////////////////////////////////////////////////
void Tokenizer::skipDelimiter()
{
    while(currPos != buffer.end() && isDelimiter(*currPos))
        ++currPos;
}



///////////////////////////////////////////////////////////////////////////////
// return true if the current character is delimiter
///////////////////////////////////////////////////////////////////////////////
bool Tokenizer::isDelimiter(char c)
{
    return (delimiter.find(c) != std::string::npos);
}



///////////////////////////////////////////////////////////////////////////////
// split the input string into multiple tokens
// pushes operand tokens to a queue of tokens
///////////////////////////////////////////////////////////////////////////////
Queue<std::string> Tokenizer::split()
{
    Queue<std::string> tokens;
    std::string token;
    
    while((token = this->next()) != "")
    {
        tokens.enqueue(token);
    }
    
    return tokens;
}
