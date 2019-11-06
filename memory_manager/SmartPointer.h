#pragma once
#include "Counter.h"

template <typename T>
class SmartPointer
{
public:

	SmartPointer()
	{

	}

	SmartPointer(T* p)
	{
		ptr = p;
		reference_count = new Counter();
		reference_count->incr();
	}

	virtual ~SmartPointer()
	{
		if (reference_count)
		{
			reference_count->decr();
			if (reference_count->getCount() <= 0)
			{
				delete reference_count;
				delete ptr;


				reference_count = nullptr;
				ptr = nullptr;
			}
		}
	}

	SmartPointer(const SmartPointer<T>& other)
	{
		reference_count = other.reference_count;
		ptr = other.ptr;

		reference_count->incr();
	}

	int getCount()
	{
		return reference_count->getCount();
	}

	SmartPointer<T>& operator = (const SmartPointer<T>& other)
	{
		if (this != &other)//avoid self assignment
		{
			if (reference_count)
			{
				reference_count->decr();
				if (reference_count->getCount() == 0)
				{
					delete reference_count;
					delete ptr;
				}
			}
			ptr = other.ptr;
			reference_count = other.reference_count;
			reference_count->incr();
		}
		return *this;
	}


	T& operator * ()
	{
		return *ptr;
	}

	T* operator -> ()
	{
		return ptr;
	}

	T* operator + (int x)
	{
		return new SmartPointer<T>(ptr + x);
	}
private:
	Counter* reference_count = nullptr;
	T* ptr = nullptr;
};