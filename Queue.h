//
//  Queue.h
//  CIS 22C Lab 3B
//
//  Created by Gobind Bakhshi on 11/3/19.
//  Copyright © 2019 Gobind Bakhshi. All rights reserved.
//

#ifndef Queue_h
#define Queue_h
#include "LinkedList.h"

template <class T>
class Queue : public LinkedList<T>
{
private:
    
public:
    Queue();
    void enqueue(T data);
    void dequeue();
    void clear();
    
    T peek();
    
    bool isEmpty();
    bool isFull();
    
};

template <class T>
Queue<T>::Queue() : LinkedList<T>(0)
{}

template <class T>
void Queue<T>::dequeue()
{
    LinkedList<T>::deleteNode(0);
}

template <class T>
void Queue<T>::enqueue(T data)
{
    LinkedList<T>::insertOrdered(data, LinkedList<T>::getCount());
}

template <class T>
void Queue<T>::clear()
{
    LinkedList<T>::emptyList();
}

//  checks if list is empty
template<class T>
bool Queue<T>::isEmpty()
{
    if (LinkedList<T>::getCount() > 0)
    {
        return false;
    }else
        return true;
};

// displays top value of stack
template<class T>
T Queue<T>::peek()
{
    return LinkedList<T>::getFirstData();
};
#endif /* Queue_h */
