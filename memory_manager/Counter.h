#pragma once
class Counter
{
private:
	int ref_count = 0;
public:
	void incr()
	{
		++ref_count;
	}

	void decr()
	{
		--ref_count;
	}

	int getCount()
	{
		return ref_count;
	}
};