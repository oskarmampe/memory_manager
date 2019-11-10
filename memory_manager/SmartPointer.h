#pragma once
#include "Counter.h"

/*
	SmartPointer class that cleans the memory automatically, and also counts the number of references.
	When the number of references reaches 0, it frees the memory, and the pointer.
*/
template <typename T>
class SmartPointer
{
public:

	SmartPointer()
	{
		// Required empty constructor.
	}

	// Constructor - Create the pointer and increment the number of references.
	SmartPointer(T* p)
	{
		ptr = p;
		reference_count = new Counter();
		reference_count->incr();
	}


	// Destructor - clean up the memory.
	virtual ~SmartPointer()
	{
		if (reference_count) // If there isn't a reference count, the object is already freed. Otherwise:
		{
			reference_count->decr(); // decrease the counter
			if (reference_count->getCount() <= 0) // if there is no more references
			{// clean up
				delete reference_count;
				delete ptr;


				reference_count = nullptr;
				ptr = nullptr;
			}
		}
	}

	// Copy constructor
	SmartPointer(const SmartPointer<T>& other)
	{
		reference_count = other.reference_count;
		ptr = other.ptr;

		reference_count->incr();
	}

	// Get the reference count.
	int getCount()
	{
		return reference_count->getCount();
	}

	// Override the assignment constructor to count the references.
	SmartPointer<T>& operator = (const SmartPointer<T>& other)
	{
		if (this != &other)//avoid self assignment
		{
			if (reference_count) // Check for any other references
			{
				reference_count->decr();
				if (reference_count->getCount() == 0)  // If its the only reference clear the memory
				{
					delete reference_count;
					delete ptr;
				}
			}
			// Assign the new reference
			ptr = other.ptr;
			reference_count = other.reference_count;
			reference_count->incr();
		}
		return *this; // return the reference
	}

	// Override the pointer operator so that it works the same as the default pointer
	T& operator * ()
	{
		return *ptr;
	}

	// Override the pointer operator so that it works the same as the default pointer
	T* operator -> ()
	{
		return ptr;
	}
private:
	Counter* reference_count = nullptr;
	T* ptr = nullptr;
};