#include "SmartPointer.h"

template <class T>
SmartPointer<T>::SmartPointer(T* p)
{
	ptr = p;
	reference_count = new Counter();
	reference_count->incr();

}

template<class T>
SmartPointer<T>::~SmartPointer<T>()
{
	if (reference_count)
	{
		reference_count->decr();
		if (reference_count->getCount() <= 0)
		{
			delete reference_count;
			delete p;

			p = nullptr;
			reference_count = nullptr;
		}
	}
	delete ptr;
}

template<class T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& other)
{
	reference_count = other.reference_count;
	ptr = other.ptr;

	reference_count->incr();
}

template<class T>
SmartPointer<T>& SmartPointer<T>::operator = (const SmartPointer<T>& other)
{
	if (this != other)
	{
		if (reference_count)
		{
			reference_count->decr();
			int count = reference_count->getCount();
			if (count == 0)
			{
				delete reference_count;
				delete ptr;
			}
			ptr = other.ptr;
			reference_count = other.reference_count;
			reference_count->incr();
		}
	}
	return *this;
}

template<class T>
T & SmartPointer<T>::operator*()
{
	return *ptr;
}


template <class T>
T* SmartPointer<T>::operator -> () 
{ 
	return *ptr; 
}

template <class T>
T* SmartPointer<T>::operator + (int x) 
{ 
	return new SmartPointer<T>(ptr + x); 
}