#pragma once

//TODO: 5 - Implement a Queue class from scratch
//Remember that your queue should follow the FIFO standard (First In First Out)

template<typename T>
class Queue 
{
public:
	Queue();
	~Queue();
	//Inserts the data in the queue.
	void Enqueue(T data);
	
	//Removes an element from the queue and returns this element in the output parameter
	//Also it returns true if the object was removed and false if the Queue is empty
	bool Daqueue(T& output);
	
	//Returns true if queue is empty, false otherwise
	bool isEmpty();

	//Display all the elements in the queue:
	//Example, lets suppose you inserted 1, 2, 3, 4, 5
	//Display should print: "front->1, 2, 3, 4, 5<-rear"
	void DisplayQueue();
private:
	int front;
	int rear;
	int mCurrentSize;
	int mCapacity;
	T* mData;
};