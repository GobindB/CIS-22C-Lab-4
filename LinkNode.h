#ifndef LINKNODE_H
#define LINKNODE_H

#include <iostream>
//******************************************************//
// Template Link Node Class
//******************************************************//
template <typename T>
class LinkNode
{
private:

	LinkNode<T> *next;
	T data;

public:
	LinkNode();
	LinkNode<T>* getNext();
	T getData();
	void setNext(LinkNode<T> * next);
	void setData(T value);
};

//******************************************************//
// Template Link Node Class Definition
//******************************************************//

// LinkNode default constructor
// assigns  data member to constructor data value
// post: initializes next pointer to nullptr
template <typename T>
LinkNode<T>::LinkNode()
{
	next = nullptr;
}

// return: next pointer
template <typename T>
LinkNode<T>* LinkNode<T>::getNext()
{
	return next;
}

// return: data pointer
template <typename T>
T LinkNode<T>::getData()
{
	return data;
}

// pre: value - class pointer
// post: sets next pointer equal to value pointer
template <typename T>
void LinkNode<T>::setNext(LinkNode<T> *value)
{
	next = value;
}

// pre: value - class pointer
// post: sets data pointer to value pointer
template <typename T>
void LinkNode<T>::setData(T value)
{
	data = value;
}

#endif // !LINKNODE_H