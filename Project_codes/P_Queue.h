#pragma once
#include "PQ_Node.h"

template <typename T>
class P_Queue 
{
private:
	PQ_Node<T>* backPtr;
	PQ_Node<T>* frontPtr;
public:
	P_Queue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, int p);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	int getSize() const;
	~P_Queue();

	P_Queue(const P_Queue<T> & PQ);
};


template <typename T>
P_Queue<T>::P_Queue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}

template <typename T>
bool P_Queue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}


template <typename T>
bool P_Queue<T>::enqueue(const T& newEntry, int p)
{
	PQ_Node<T>* newNodePtr = new PQ_Node<T> (newEntry, p);
	
	if (isEmpty())	//special case if this is the first node to insert
	{
		frontPtr = newNodePtr; 
		return true;
	}

	if (frontPtr->getPriority() < p)
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
		return true;
	}
	
	PQ_Node<T>* Temp = frontPtr;
	while (Temp->getNext() &&  Temp->getNext()->getPriority() >= p)
		Temp = Temp->getNext();

	newNodePtr->setNext(Temp->getNext());
	Temp->setNext(newNodePtr);
	return true;
} 



template <typename T>
bool P_Queue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	PQ_Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;

}

template <typename T>
bool P_Queue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T>
P_Queue<T>::~P_Queue()
{
	T temp;

	while (dequeue(temp));
}

template <typename T>
int P_Queue<T>::getSize() const
{
	int count = 0;

	if (isEmpty())
		return count;

	PQ_Node<T>* Ptr = frontPtr;
	while (Ptr)
	{
		count++;
		Ptr = Ptr->getNext();
	}

	return count;
}

template <typename T>
P_Queue<T>::P_Queue(const P_Queue<T> & PQ)
{
	PQ_Node<T>* NodePtr = PQ.frontPtr;
	if (!NodePtr) 
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	PQ_Node<T>* ptr = new PQ_Node<T>(NodePtr->getItem(), NodePtr->getPriority());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		PQ_Node<T>* ptr = new PQ_Node<T>(NodePtr->getItem(), NodePtr->getPriority());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}
