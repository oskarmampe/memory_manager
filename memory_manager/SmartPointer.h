#pragma once
template <class T>
class SmartPointer
{
	T* ptr;

public:
	explicit SmartPointer(T* p = NULL)
	{
		ptr = p;
	}

	~SmartPointer() { delete ptr; };

	T& operator * () { return *ptr; }

	T* operator -> () { return ptr; }

	T* operator + (int x) { return ptr + x; }
};