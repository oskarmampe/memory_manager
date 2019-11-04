#pragma once
#include "Counter.h"

template <class T>
class SmartPointer
{
public:
	SmartPointer(T* p);

	virtual ~SmartPointer();

	SmartPointer(const SmartPointer<T>& other);

	SmartPointer<T>& SmartPointer<T>::operator = (const SmartPointer<T>&);

	T& operator * ();

	T* operator -> ();

	T* operator + (int x);
private:
	Counter* reference_count = nullptr;
	T* ptr;
};