#pragma once

//TODO: 5 - Implement a Queue class from scratch
//Remember that your queue should follow the FIFO standard (First In First Out)

template<typename T>
class Queue 
{
public:
	Queue()
		:front(0),
		mCurrentSize(0),
		mCapacity(5),
		rear(-1)
	{
		mData = new T[mCapacity];
	}
	~Queue()
	{
		delete[] mData;
		mData = nullptr;
	}
	//Inserts the data in the queue.
	void Enqueue(T data)
	{
		if (isFull())
		{
			Expansion();
		}

		rear = (rear + 1) % mCapacity;
		mData[rear] = data;
		++mCurrentSize;
	}
	
	//ERROR -5: There is a problem with your dequeue. You are not changing the size of your queue.
	//The output is the element that you will return to the user. It's an OUTPUT. So you should follow the FIFO insertion and removal.
	//So, if the queue is empty, return false and don't fill the output, but you you have something you remove one element giving this 
	//element to the output and return true.

	//Removes an element from the queue and returns this element in the output parameter
	//Also it returns true if the object was removed and false if the Queue is empty
	bool Daqueue(T& output)
	{
		if (isEmpty())
		{
			return false;
		}

		for (auto i = 0; i < mCurrentSize; ++i)
		{
			if (mData[i] == output)
			{
				for (auto j = i; j < mCurrentSize; ++j)
				{
					mData[j] = mData[j + 1];
				}

				return true;
			}
		}

		return false;
	}
	
	//Returns true if queue is empty, false otherwise
	bool isEmpty()
	{
		return (mCurrentSize == 0);
	}

	bool isFull()
	{
		return (mCurrentSize == mCapacity);
	}

	//Display all the elements in the queue:
	//Example, lets suppose you inserted 1, 2, 3, 4, 5
	//Display should print: "front->1, 2, 3, 4, 5<-rear"
	void DisplayQueue()
	{
		std::cout << "front->";

		for (auto i = 0; i < mCurrentSize - 1; ++i)
		{
			std::cout << mData[i] << ", ";
		}

		std::cout << mData[rear] << "<-rear" << std::endl;
	}

private:
	int front;
	int rear;
	int mCurrentSize;
	int mCapacity;
	T* mData;

	void Expansion()
	{
		int additionalCapacity = mCapacity;

		//Expansion
		T* temp = mData;
		mData = new T[mCapacity + additionalCapacity];
		mCapacity += additionalCapacity;

		for (int i = 0; i < mCurrentSize; ++i)
		{
			mData[i] = temp[i];
		}

		delete[] temp;
		temp = nullptr;

		std::cout << "Queue has been expanded\n";
	}
};