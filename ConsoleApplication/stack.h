#ifndef STACK_H
#define STACK_H
#include <iostream>


const int MAXSTACKSIZE = 100;

template <class Type>
class Stack {

private:
	Type* Contents;
	int stack_size;
	int index_of_top;

public:
	Stack(int stack_size = 100);
	~Stack();
	bool empty() const;
	bool full() const;
	bool pop(Type& top_element);
	bool push(const Type& new_element);
	bool top(Type& top_element);

	int getStackSize() {
		return stack_size;
	}


};

#endif 

