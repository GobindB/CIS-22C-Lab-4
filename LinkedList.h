#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkNode.h"
#include <iostream>

//******************************************************//
// Template Linked List Class
//******************************************************//

template <typename T>
class LinkedList
{
private:
    int sort = 0; // 0 = unsorted, 1 = ascending, 2 = descending
    int count = 0;
    
protected:
    // list head pointer
    LinkNode<T> *head;
    LinkNode<T> *tail;
    int test = 0;
    
public:
    
    LinkedList();
    LinkedList(int type);
    // deletes the linked list
    virtual ~LinkedList();
    
    bool deleteData(T data);
    bool findData(T data);
    bool deleteNode(int index);
    bool isEmpty(); // DEFINE
    
    void print() const;
    void addData(T data);
    void emptyList();
    void insertOrdered(T data, int index);
    T getData(int index);
    
    // tests if ascending/descending/unsorted
    int getSort();
    int getCount();
    LinkNode<T>* getTail();
    
    T getFirstData();
    T getLastData();
};


//******************************************************//
//        Linked List TEMPLATE Class DEFINITIONS        //
//******************************************************//


//******************************************************
// LinkedList constructors and Destructors
//******************************************************
template <typename T>
LinkedList<T>::LinkedList()
{
    sort = 0;
    count = 0;
    
    // dummy node
    head = new LinkNode<T>();
}
// pre: type - integer
// post: initializes counter to 0
//         assign sort to type to determine sort type
//         creates space for head node (sentinal node)
template <typename T>
LinkedList<T>::LinkedList(int type) : count(0)
{
    // assign type
    if (type < 0 || type > 2)
    {
        sort = type;
    }
    else
    {
        sort = type;
    }
    
    // dummy node
    head = new LinkNode<T>();
}

// Linked List destructor
// post: deletes the linked list
template <typename T>
LinkedList<T>::~LinkedList()
{
    LinkNode<T>* currPtr;
    LinkNode<T>* nextPtr;
    
    currPtr = head->getNext();
    
    
    while (currPtr != nullptr)
    {
        nextPtr = currPtr->getNext();
        delete currPtr;
        currPtr = nextPtr;
    }
    
    delete head;
}

//******************************************************
// Insert/Append functions
//******************************************************

// pre: data - template typename variable
// post: adds new nodes to linked list
//       increments count
template <typename T>
void LinkedList<T>::addData(T data)
{
    //pointer to new node
    LinkNode<T> *newNode;
    // node to traverse the list
    LinkNode<T> *currPtr;
    LinkNode<T>* prePtr = nullptr;
    
    newNode = new LinkNode<T>();
    newNode->setData(data);
    
    
    switch (sort)
    {
        case 0:
            
            currPtr = head;
            while (currPtr->getNext())
                currPtr = currPtr->getNext();
            
            currPtr->setNext(newNode);
            
            count++;
            break;
            
            //ascending
        case 1:
            prePtr = head;
            currPtr = head->getNext();
            // currPtr pointing at data data member from LinkNode class
            while (currPtr != nullptr && currPtr->getData() < data)
            {
                prePtr = currPtr;
                currPtr = currPtr->getNext();
            }
            if (prePtr == nullptr)
            {
                head = newNode;
                newNode->setNext(currPtr);
            }
            else
            {
                prePtr->setNext(newNode);
                newNode->getNext(currPtr);
            }
            
            count++;
            break;
            
            // descending
        case 2:
            
            prePtr = head;
            currPtr = head->getNext();
            
            // currPtr pointing at data data member from LinkNode class
            while (currPtr != nullptr && currPtr->getData() > data)
            {
                prePtr = currPtr;
                currPtr = currPtr->getNext();
            }
            if (prePtr == nullptr)
            {
                head = newNode;
                newNode->setNext(currPtr);
            }
            else
            {
                prePtr->setNext(newNode);
                newNode->getNext(currPtr);
            }
            
            count++;
            break;
            
        default:
            break;
    }
}

// pre: value - template typename variable
//        index - integer type
// post: adds node to specific spot(index) in unsorted linked list
//         increments count
template <typename T>
void LinkedList<T>::insertOrdered(T value, int index)
{
    int indexCount = 0;
    
    LinkNode<T>* newNode = new LinkNode<T>();
    LinkNode<T>* prePtr;
    LinkNode<T>* currPtr;
    
    
    prePtr = head;
    currPtr = head->getNext();
    
    // currPtr pointing at data data member from LinkNode class
    while (currPtr != nullptr && indexCount < index)
    {
        prePtr = currPtr;
        currPtr = currPtr->getNext();
        indexCount++;
    }
    if (prePtr == nullptr)
    {
        head = newNode;
        newNode->setNext(currPtr);
        newNode->setData(value);
    }
    else
    {
        prePtr->setNext(newNode);
        newNode->setNext(currPtr);
        newNode->setData(value);
    }
    
    
    count++;
}

//******************************************************
// Deletion function
//******************************************************

// pre: index - integer type
// post: Deletes node at a particular index point in unsorted linked list
//         decrements count
// return: value of node
template<typename T>
bool LinkedList<T>::deleteNode(int index)
{
    if (count == 0)
    {
        return false;
    }
    
    int indexCount = 0;
    
    LinkNode<T>* prePtr;
    LinkNode<T>* currPtr;
    
    prePtr = head;
    currPtr = head->getNext();
    
    // currPtr pointing at data data member from LinkNode class
    while (currPtr != nullptr && indexCount < index)
    {
        prePtr = currPtr;
        currPtr = currPtr->getNext();
        indexCount++;
    }
    
    
    if (currPtr != nullptr)
    {
        prePtr->setNext(currPtr->getNext());
        delete currPtr;
    }
    
    count--;
    return true;
}


//******************************************************
// pre: value - template class type
// post: Delete all instances of a particular value from the LinkedList
// return: true or false
//******************************************************
template <typename T>
bool LinkedList<T>::deleteData(T value)
{
    bool deleted = false;
    if (count == 0)
    {
        return false;
    }
    
    LinkNode<T>* prePtr;
    LinkNode<T>* currPtr;
    LinkNode<T>* nextPtr;
    
    prePtr = head;
    currPtr = head->getNext();
    
    while (currPtr->getNext())
    {
        nextPtr = currPtr->getNext();
        
        if (currPtr->getData() == value)
        {
            prePtr->getNext() = nextPtr;
            delete currPtr;
            --count;
            deleted = true;
        }
        else
        {
            prePtr = prePtr->getNext();
        }
        currPtr = nextPtr;
        
    }
    return deleted;
}

//******************************************************
// pre: value - template class type
// post: See if data value exists in linked list
// return: true or false
//******************************************************
template <typename T>
bool LinkedList<T>::findData(T value)
{
    LinkNode<T>* prePtr;
    LinkNode<T>* currPtr;
    
    prePtr = head;
    currPtr = head->getNext();
    
    // currPtr pointing at data data member from LinkNode class
    while (currPtr != nullptr)
    {
        if (currPtr->getData() == value)
        {
            return true;
        }
        else
        {
            prePtr = currPtr;
            currPtr = currPtr->getNext();
        }
    }
    //    if (currPtr != nullptr)
    //        return false;
    //    else
    return false;
}


//******************************************************
// post: Return member variable count
//******************************************************
template <typename T>
int LinkedList<T>::getCount()
{
    return count;
}

//******************************************************
// post: Return member variable count
//******************************************************
template <typename T>
int LinkedList<T>::getSort()
{
    return sort;
}

//******************************************************
// post: Return tail pointer
//******************************************************
template <class T>
LinkNode<T>* LinkedList<T>::getTail ()
{
    return tail;
}

//******************************************************
// post: Empty all linked list contents and deallocates memory
//******************************************************
template <typename T>
void LinkedList<T>::emptyList()
{
    LinkNode<T>* currPtr;
    LinkNode<T>* nextPtr;
    
    currPtr = head->getNext();
    
    while (currPtr != nullptr)
    {
        nextPtr = currPtr->getNext();
        delete currPtr;
        currPtr = nextPtr;
    }
    
    head->setNext(nullptr);
    
    if (currPtr == nullptr)
    {
        return;
    }
}

//******************************************************
// post: displays linked list contents to console
//******************************************************
template <typename T>
void LinkedList<T>::print() const
{
    LinkNode<T> *currPtr;
    
    currPtr = head->getNext();
    
    while (currPtr)
    {
        T data = currPtr->getData();
        // dereference the currPtr to access the node to access the data
        std::cout << data;
        std::cout << std::endl;
        
        // make currPtr access next node of the list
        currPtr = currPtr->getNext();
    }
}

// get head data
template <typename T>
T LinkedList<T>::getFirstData()
{
    return head->getNext()->getData();
}


// get head data
template <typename T>
T LinkedList<T>::getLastData()
{
    return getData(count-1);
}

// get data at index
template <typename T>
T LinkedList<T>::getData(int index)
{
    
    int indexCount = 0;
    
    LinkNode<T>* prePtr;
    LinkNode<T>* currPtr;
    
    prePtr = head;
    currPtr = head->getNext();
    
    // currPtr pointing at data data member from LinkNode class
    while (currPtr != nullptr && indexCount < index)
    {
        prePtr = currPtr;
        currPtr = currPtr->getNext();
        indexCount++;
    }

    return currPtr->getData();
}
#endif
