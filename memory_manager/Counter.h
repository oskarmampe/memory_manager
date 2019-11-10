#pragma once
/*
	Counter Class
	It's only used in SmartPointer to keep track of the references.
*/
class Counter
{
	//Int that keeps count of references.
private:
	int ref_count = 0;
public:
	// Increment the counter
	void incr()
	{
		++ref_count;
	}

	// Decrease the counter
	void decr()
	{
		--ref_count;
	}

	// Get the count of references.
	int getCount()
	{
		return ref_count;
	}
};