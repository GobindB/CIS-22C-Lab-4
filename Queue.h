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
class Queue : protected LinkedList<T>
{

public:

	Queue();
	void enqueue(T data);
	void dequeue();
	void clear();

	// data at front of queue
	T peek();

	bool isEmpty();
	bool isFull();

};

// Queue constructor
// post: initializes sort type in linked list constructor to 0
template <class T>
Queue<T>::Queue() : LinkedList<T>(0)
{}

// dequeues node at the front of queue
// post: deletes node at index 0 of queue
template <class T>
void Queue<T>::dequeue()
{
	LinkedList<T>::deleteNode(0);
}

// enqueues node at the rear of queue
// post: inserts node at rear of queue
template <class T>
void Queue<T>::enqueue(T data)
{
	LinkedList<T>::insertOrdered(data, LinkedList<T>::getCount());
}

// clears queue
// post: deletes all nodes of queue
template <class T>
void Queue<T>::clear()
{
	LinkedList<T>::emptyList();
}

// checks if queue is empty
// return: true or false
template<class T>
bool Queue<T>::isEmpty()
{
	if (LinkedList<T>::getCount() > 0)
	{
		return false;
	}
	else
		return true;
};

// displays front value of queue
// return template T type
template<class T>
T Queue<T>::peek()
{
	return LinkedList<T>::getFirstData();
};
#endif /* Queue_h */