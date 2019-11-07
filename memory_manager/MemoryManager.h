#pragma once
#include "SingleStack.h"
#include "DoubleStack.h"
#include "Pool.h"
#include "SmartPointer.h"
#include <vector>
#include <tuple>
//
// MEMORY MANAGER
//
// This class needs to do all the book-keeping. The stack/pool structures are very bare, and simply implement a way to allocate memory.
// The structures do not do ANY checks whether the memory is being implemented correctly.
// This should be the functionality of this class. Making sure that when a block is allocated, it's not writing more than allocated etc.
//

class MemoryManager
{
	typedef uint32_t U32;
public:
	MemoryManager()
	{
		// Do nothing
	}
	~MemoryManager()
	{
		// Do nothing
	}
	void startUp();
	void shutDown();

	void createStack(U32 stack_size);
	void createDoubleStack(U32 stack_size);
	void createPool(U32 type_size, U32 stack_size);

	template <class T>
	void putIntoDoubleStack(T, DoubleStack::POSITION);

	template <class T>
	void putIntoPool(T);

	template <class T>
	void putIntoStack(T);

	template <class T>
	T getFromStack();

	template <class T>
	T getFromDoubleStack();
	
	template <class T>
	T getFromPool();

private:
	std::vector<SmartPointer<SingleStack>> stacks;
	std::vector<SmartPointer<SingleStack::Marker>> stacksMarkers;
	std::vector<SmartPointer<DoubleStack>> dstacks;
	std::vector<SmartPointer<std::tuple<DoubleStack::Marker, DoubleStack::Marker>>> dstacksMarkers;
	std::vector<SmartPointer<Pool>> pools;
};