#pragma once

template < typename T>
class PQ_Node
{
private :
	T item;
	int Priority;
	PQ_Node<T>* next;
public :
	PQ_Node();
	PQ_Node( const T & r_Item);
	PQ_Node( const T & r_Item, int p);
	PQ_Node( const T & r_Item, PQ_Node<T>* nextNodePtr, int p);
	void setItem( const T & r_Item);
	void setPriority(int p);
	void setNext(PQ_Node<T>* nextNodePtr);
	T getItem() const ;
	PQ_Node<T>* getNext() const ;
	int getPriority() const;
};

template < typename T>
PQ_Node<T>::PQ_Node()
{
	next = nullptr;
	Priority = 0;
}

template < typename T>
PQ_Node<T>::PQ_Node( const T& r_Item)
{
	item = r_Item;
	next = nullptr;
	Priority = 0;
}

template < typename T>
PQ_Node<T>::PQ_Node( const T& r_Item, int p)
{
	item = r_Item;
	next = nullptr;
	Priority = p;
}

template < typename T>
PQ_Node<T>::PQ_Node( const T& r_Item, PQ_Node<T>* nextNodePtr, int p)
{
	item = r_Item;
	next = nextNodePtr;
	Priority = p;
}

template < typename T>
void PQ_Node<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void PQ_Node<T>::setPriority(int p)
{
	Priority = p;
}

template < typename T>
void PQ_Node<T>::setNext(PQ_Node<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
T PQ_Node<T>::getItem() const
{
	return item;
} 

template < typename T>
int PQ_Node<T>::getPriority() const
{
	return Priority;
} 

template < typename T>
PQ_Node<T>* PQ_Node<T>::getNext() const
{
	return next;
} 

