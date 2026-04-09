#include "queue.h"



// Constructor
template <class Type>
Queue<Type> ::Queue(int size) :
	size(size),
	contents(new Type[size + 1]),
	front(0),
	back(0)
	//count(0)
{
}
// Destructor
template <class Type>
Queue<Type> :: ~Queue()
{
	delete[] contents;
}
// Tests
template <class Type>
bool Queue<Type> ::empty() const
{
	return (front == back) ? true : false;
}
template <class Type>
bool Queue<Type> ::full() const
{
	return ((1 + back) % (size + 1)
		== front) ? true : false;
}
template <class Type>
bool Queue<Type> ::remove(Type& front_element)
{
	if (empty())
		return false;
	else
	{
		front_element = contents[front];
		front = (front + 1) % (size + 1);
		//count--;
		return true;
	}
}
template <class Type>
bool Queue<Type> ::add(const Type& new_element)
{
	if (full())
		return false;
	else
	{
		contents[back] = new_element;
		back = (back + 1) % (size + 1);
		//count++;
		return true;
	}
}

template class Queue<int>;

