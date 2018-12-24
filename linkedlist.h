#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <cstdlib>
#include <iostream>


template <class T>
class Node
{
public:
	Node(T data, Node<T>* ptr) { m_next = ptr; m_data = data; }
	Node<T>* getNext() { return m_next; }
	T getData() { return m_data; }
	void setNext(Node<T>* ptr) { m_next = ptr; }
	void setData(T data) { m_data = data; }
private:
	T m_data;
	Node<T>* m_next;
};

template <class T>
class LinkedList
{
public:
	LinkedList();

	int getSize() { return m_size; }
	void setSize(int val) { m_size = val; }

	bool empty();
	void push_front(T data);
	void push_back(T data);
	void pop_front();
	T front() { return m_head->getData(); }

	void print();

	/// functions used in class to demonstrate stuff
	int count1();
	int count2() { return count_rec(m_head); }
	T maxElement() { return maxElement_rec(m_head); }

	/// mergeSort
	void mergeSort();

protected:

private:
	int count_rec(Node<T>* ptr);
	T maxElement_rec(Node<T>* ptr);
	void split(LinkedList<T> &l1, LinkedList<T> &l2);
	void merge(LinkedList<T> &l1, LinkedList<T> &l2);

	int m_size;
	Node<T>* m_head;
	Node<T>* m_tail;
};

template <class T>
LinkedList<T>::LinkedList()
{
	//ctor
	m_size = 0;
	m_head = m_tail = NULL;
}

template <class T>
bool LinkedList<T>::empty()
{
	return m_size == 0;
}

template <class T>
void LinkedList<T>::push_front(T data)
{
	if (empty())
	{
		m_head = m_tail = new Node<T>(data, NULL);
	}
	else
	{
		m_head = new Node<T>(data, m_head);
	}
	m_size++;
}

template <class T>
void LinkedList<T>::push_back(T data)
{
	if (empty())
	{
		m_head = m_tail = new Node<T>(data, NULL);
	}
	else
	{
		m_tail->setNext(new Node<T>(data, NULL));
		m_tail = m_tail->getNext();
	}
	m_size++;
}

template <class T>
void LinkedList<T>::pop_front()
{
	if (empty())
	{
		/// "business decision" about what to do
		/// with this error
		std::cerr << "Attempting to remove from an empty container" << endl;
		exit(1);
	}
	Node<T>* deleteMe = m_head;
	/// do we have only 1 node?
	if (m_size == 1)
	{
		m_head = m_tail = NULL;
	}
	else
	{
		m_head = m_head->getNext();
	}

	delete deleteMe;
	m_size--;
}

template <class T>
void LinkedList<T>::print()
{
	Node<T>* ptr = m_head;
	std::cout << "HEAD --> ";
	while (ptr) /// ptr isn't zero
	{
		std::cout << ptr->getData() << " --> ";
		ptr = ptr->getNext();
	}
	std::cout << "TAIL  ";
	std::cout << m_size << " items " << endl;
}

template <class T>
int LinkedList<T>::count1()
{
	int c = 0;   /// init the count to zero.
	Node<T>* ptr = m_head;
	while (ptr)
	{
		c++;
		ptr = ptr->getNext();
	}
	return c;
}

template <class T>
int LinkedList<T>::count_rec(Node<T>* ptr)
{
	/// ptr is the head of a list
	if (!ptr)
		return 0;
	/// ptr isn't null
	return 1 + count_rec(ptr->getNext());
}

template <class T>
T LinkedList<T>::maxElement_rec(Node<T>* ptr)
{
	if (!ptr->getNext()) /// no next pointer
		return ptr->getData();

	T current = ptr->getData();
	T restOfList = maxElement_rec(ptr->getNext());

	if (current > restOfList)
		return current;
	else
		return restOfList;
}

template <class T>
void LinkedList<T>::mergeSort()
{
	if (getSize() <= 1) /// done.
		return;
	LinkedList<T> l1, l2;
	split(l1, l2); /// cut the current list into 2 lists (half size)
	l1.mergeSort();
	l2.mergeSort();
	merge(l1, l2);
}

template <class T>
void LinkedList<T>::split(LinkedList<T> &l1, LinkedList<T> &l2)
{
	//cout << "Splitting a list of size " << getSize() << endl;
	while (!empty())
	{
		l1.push_back(front());
		pop_front();
		if (!empty())
		{
			l2.push_back(front());
			pop_front();
		}
	}
}

template <class T>
void LinkedList<T>::merge(LinkedList<T> &l1, LinkedList<T> &l2)
{
	T top_l1, top_l2;
	while (!l1.empty() && !l2.empty())
	{
		top_l1 = l1.front();
		top_l2 = l2.front();
		if (top_l1 < top_l2)
		{
			push_back(top_l1);
			l1.pop_front();
		}
		else
		{
			push_back(top_l2);
			l2.pop_front();
		}
	}
	while (!l1.empty())
	{
		top_l1 = l1.front();
		push_back(top_l1);
		l1.pop_front();
	}
	while (!l2.empty())
	{
		top_l2 = l2.front();
		push_back(top_l2);
		l2.pop_front();
	}
	//cout << "Merging a list of size " << getSize() << endl;
}



#endif // LINKEDLIST_H
