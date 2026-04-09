#include <iostream>
#include "stack.h"


//constructor
template <class Type>
Stack<Type> ::Stack(int stack_size) : stack_size(stack_size), Contents(new Type[stack_size]), index_of_top(-1) {}


//Destructor
template <class Type>
Stack<Type> :: ~Stack()
{
	delete[] Contents;
}


//check if empty
template <class Type>
bool Stack<Type> ::empty() const

{
	return (index_of_top == -1)
		? true : false;
}


//check if full.
template <class Type>
bool Stack<Type> ::full() const

{
	return (index_of_top == stack_size - 1)
		? true : false;
}

// remove top item
template <class Type>
bool Stack<Type> ::pop(Type& top_element)  
{
	if (empty())
		return false;
	else
	{
		top_element = Contents[index_of_top];
		index_of_top--;
		return true;
	}
}


//push item in.
template <class Type>
bool Stack<Type> ::push(const Type& new_element)   
{
	if (full())
		return false;
	else
	{
		index_of_top++;                         
		Contents[index_of_top] = new_element;    
		return true;
	}
}



// display top objects in the stack
template <class Type>
bool Stack<Type> ::top(Type& top_element)
{
	if (empty())
		return false;
	else
	{
		top_element = Contents[index_of_top];
		std::cout << "hello" << std::endl;
		//top_element.displayStockSet();  // this is a here to test we had right one

		return true;
	}
}

template class Stack<int>;



