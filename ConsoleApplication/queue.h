#ifndef QUEUE_H
#define	QUEUE_H


const int MAXQUEUESIZE = 100;

template <class Type>
class Queue {

private:
	Type* contents;
	int size;
	int front;
	int back;
	//int count;

public:
	Queue(int size);
	~Queue();
	bool empty() const;
	bool full() const;
	bool remove(Type& first_element);
	bool add(const Type& new_element);
	int getQueueSize() {
		return size;
	};


};



#endif 