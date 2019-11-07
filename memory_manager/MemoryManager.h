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
	void putIntoDoubleStack(T, DoubleStack::POSITION)
	{

	}

	template <class T>
	void putIntoPool(T)
	{

	}

	template <class T>
	void putIntoStack(T obj)
	{
		SmartPointer<SingleStack> stack = stacks.at(0);
		if (stack->getFreeSize() < sizeof(obj))
		{
			std::cout << "Stack ran out of space.";
			return;
		}
		SingleStack::Marker marker = stack->getMarker();
		stacksMarkers.insert(stacksMarkers.end(), marker);
		T* result = (T*) stack->alloc(sizeof(obj));
		*result = obj;
	}

	template <class T>
	T getFromStack()
	{
		// Get all the data from the top to the marker.
		T* marker = (T*)stacksMarkers.at(0);
		return *marker;
	}

	template <class T>
	T getFromDoubleStack(DoubleStack::POSITION stack)
	{
		//
		SmartPointer<DoubleStack> dstack = dstacks.at(0);
		DoubleStack::Marker marker = dstack->getMarker(stack);
		return *marker;
	}
	
	template <class T>
	T getFromPool()
	{

	}


	template <class T>
	T takeFromStack()
	{
		// Get all the data from the top to the marker.
		SingleStack::Marker marker = stacksMarkers.at(0);
		SmartPointer<SingleStack> stack = stacks.at(0);
		stacksMarkers.erase(stacksMarkers.begin());
		stack->freeToMarker(marker);
		return *((T*)marker);
	}

	template <class T>
	T takeFromDoubleStack(DoubleStack::POSITION stack)
	{

	}

	template <class T>
	T takeFromPool()
	{

	}


private:
	std::vector<SmartPointer<SingleStack>> stacks;
	std::vector<SingleStack::Marker> stacksMarkers;
	std::vector<SmartPointer<DoubleStack>> dstacks;
	std::vector<SmartPointer<std::tuple<DoubleStack::Marker, DoubleStack::Marker>>> dstacksMarkers;
	std::vector<SmartPointer<Pool>> pools;
};