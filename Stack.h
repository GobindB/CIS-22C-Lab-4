//
//  Stack.h
//  CIS 22C Lab 3B
//
//  Created by Gobind Bakhshi on 11/3/19.
//  Copyright © 2019 Gobind Bakhshi. All rights reserved.
//

#ifndef Stack_h
#define Stack_h
#include "LinkedList.h"

template <class T>
class Stack : protected LinkedList<T>
{
public:
    Stack();
    //~Stack();
    void pop(); // pop ovverride to only allow top of list
    void push(T data); // push override to only allow top of list
    T peek();
    T top();
    
    bool isEmpty(); // override to check if empty
    void emptyList();
    void display();
    
};

template<class T>
Stack<T>::Stack() : LinkedList<T>(0)
{}

// always pops off top of stack
template<class T>
void Stack<T>::pop()
{
    //LinkedList<T>::deleteNode(LinkedList<T>::getCount()-1);
    LinkedList<T>::deleteNode(0);
};

// adds to top of stack
template<class T>
void Stack<T>::push(T data)
{
    //stackPtr->insertOrdered(data, 0);
    LinkedList<T>::insertOrdered(data, 0);
};

//  checks if list is empty
template<class T>
bool Stack<T>::isEmpty()
{
    if (LinkedList<T>::getCount() > 0)
    {
        return false;
    }else
        return true;
};

// prints
template<class T>
void Stack<T>::display()
{
    LinkedList<T>::print();
};

// displays top value of stack
template<class T>
T Stack<T>::peek()
{
    return LinkedList<T>::getFirstData();
};

// empties list contents
template<class T>
void Stack<T>::emptyList()
{
    LinkedList<T>::emptyList();
};

// returns value at top of stack
template<class T>
T Stack<T>::top()
{
   return LinkedList<T>::getLastData();
};
#endif /* Stack_h */

