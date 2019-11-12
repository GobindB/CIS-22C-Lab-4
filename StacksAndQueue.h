
#ifndef StacksAndQueue_h
#define StacksAndQueue_h
#include "LinkedList.h"

//=====================================================================================
// Stack
//=====================================================================================
template <typename T>
class Stack : private LinkedList<T>
{
public:
	void push(T data); //adds data to top
	bool pop(); //removes data from top
	T& peek(); //shows top of stack without popping it

	void emptyStack(); // empties out the stack
	bool isEmpty(); //checks if stack is empty
	int getSize(); //returns size of stack
	void print(); //outputs stack
};


/* adds data to the top of the stack
Pre: data - type T of data to be added to stack
Post:
Return:
*/
template <typename T>
void Stack<T>::push(T data)
{
	LinkedList<T>::addData(data, 0); //calls LinkedList function to add data to beginning of list
}


/* pops data from the top of the stack
Pre:
Post:
Return: bool - true if the operation completed. false otherwise
*/
template <typename T>
bool Stack<T>::pop()
{
	if (LinkedList<T>::isEmpty()) //if stack is empty, can't pop anything, so return false
		return false;
	else
		LinkedList<T>::deleteData(LinkedList<T>::getDataList(0)); //calls LinkedList function to delete the node at front of list
	return true;

}


/*
Pre: shows data on top of stack without popping it
Post:
Return: T - data on top of the stack
*/
template <typename T>
T& Stack<T>::peek()
{
	if (!LinkedList<T>::isEmpty())
		return LinkedList<T>::getDataList(0); //returns data from LinkedList function at index 0
	else
		throw "ERROR: Can't peek an empty stack.";
}


/* empties out the stack
Pre:
Post: stack is now empty except head node in list
Return:
*/
template <typename T>
void Stack<T>::emptyStack()
{
	LinkedList<T>::emptyList(); //only calls LinkedList function one time instead of popping and calling LinkedList function numerous times
}


/* checks of stack is empty
Pre:
Post:
Return: bool - true or false. true is stack is empty, false otherwise
*/
template <typename T>
bool Stack<T>::isEmpty()
{
	return LinkedList<T>::isEmpty(); //calls LinkedList isEmpty function
}


/* gets the size of the stack
Pre:
Post:
Return: int - number of nodes in the stack
*/
template <typename T>
int Stack<T>::getSize()
{
	return LinkedList<T>::getCount(); //calls LinkedList isEmpty function
}


/* outputs the contents of the stack. (left is the top, right is the bottom)
Pre:
Post:
Return:
*/
template <typename T>
void Stack<T>::print()
{
	if (LinkedList<T>::isEmpty())
	{
		std::cout << "(Empty)" << std::endl; //if list is empty, output (Empty)
	}
	else
		LinkedList<T>::print(); //outputs contents of list if it is not empty
}



//=====================================================================================
// Queue
//=====================================================================================
template <typename T>
class Queue : private LinkedList<T>
{
public:
	void enqueue(T data); //enters data into the queue
	bool dequeue(); //removes data from the front of the queue

	T& front(); //returns the data at the front of the queue
	T& rear(); //returns the data at the end of the queue

	void emptyQueue(); //empties out the queue
	bool isEmpty(); //checks if queue is empty
	int getSize(); //gets the size of the queue
	void print(); //outputs the contents of the queue
};


/* enters data into the queue
Pre: data - T type data to be entered into the end of the queue
Post: adds node to the end of the list
Return:
*/
template <typename T>
void Queue<T>::enqueue(T data)
{
	LinkedList<T>::addData(data, LinkedList<T>::getCount()); //sets new data as last element of list. Count is the new index of last enement
}


/* deletes the data at the front of the queue
Pre:
Post: deletes node from front of list
Return: bool - true if operation succeeds, false otherwise
*/
template <typename T>
bool Queue<T>::dequeue()
{
	if (LinkedList<T>::isEmpty()) //if queue is empty, can't dequeue anything, so return
		return false;
	else
		LinkedList<T>::deleteData(LinkedList<T>::getDataList(0)); //deletes the data at front of list
	return true;
}


/* returns the data at the front of the list
Pre:
Post:
Return: T - data from the front of the queue
*/
template <typename T>
T& Queue<T>::front()
{
	if (!LinkedList<T>::isEmpty()) //if not empty
		return LinkedList<T>::getDataList(0); //LinkedList function gets data from index 0
	else
		throw "ERROR: Queue is empty!";
}


/* returns the data at the end of the list
Pre:
Post:
Return: T - data from the rear of the queue
*/
template <typename T>
T& Queue<T>::rear()
{
	if (!LinkedList<T>::isEmpty())
		return LinkedList<T>::getTail(); //LinkedList function to get the last node in the list
	else
		throw "ERROR: Queue is empty!";
}


/* empies out the queue
Pre:
Post: list is now empty besides the head
Return:
*/
template <typename T>
void Queue<T>::emptyQueue()
{
	LinkedList<T>::emptyList(); //calls one LinkedList function instead of numerous dequeues which would call a LinkedList function numerous times
}


/*checks if queue is empty
Pre:
Post:
Return: bool - true if empty, false otherwise
*/
template <typename T>
bool Queue<T>::isEmpty()
{
	return LinkedList<T>::isEmpty(); //calls LinkedList isEmpty function
}


/* gets the size of the queue
Pre:
Post:
Return: int - number of nodes in the queue
*/
template <typename T>
int Queue<T>::getSize()
{
	return LinkedList<T>::getCount(); //calls LinkedList getSize function
}


/* outputs the contents of the queue (left is front, right is rear)
Pre:
Post:
Return:
*/
template <typename T>
void Queue<T>::print()
{
	if (LinkedList<T>::isEmpty())
	{
		std::cout << "(Empty)" << std::endl; //if list is empty, output (Empty)
	}
	else
		LinkedList<T>::print(); //calls LinkedList print. outputs contents of the list
}


#endif /* StacksAndQueue_h */
