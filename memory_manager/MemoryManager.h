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

	void resetStack(U32 stack_size);
	void resetDoubleStack(U32 stack_size);
	void resetPool(U32 type_size, U32 stack_size);

	template <class T>
	void putIntoDoubleStack(T obj, DoubleStack::POSITION stack_position)
	{
		if (dstack->getFreeSize() < sizeof(obj))
		{
			std::cout << "Stack ran out of space.";
			return;
		}

		if (stack_position == DoubleStack::BOTTOM_STACK)
			dstackBottomMarkers.insert(dstackBottomMarkers.end(), dstack->getMarker(stack_position));

		T* result = (T*)dstack->alloc(sizeof(obj), stack_position);

		if (stack_position == DoubleStack::TOP_STACK)
			dstackTopMarkers.insert(dstackTopMarkers.end(), dstack->getMarker(stack_position));

		*result = obj;
	}

	template <class T>
	void putIntoPool(T)
	{

	}

	template <class T>
	void putIntoStack(T obj)
	{
		std::cout << "Stack size: " << stack->getFreeSize() << std::endl;
		if (stack->getFreeSize() < sizeof(obj))
		{
			std::cout << "Stack ran out of space." << std::endl;
			return;
		}
		SingleStack::Marker marker = stack->getMarker();
		stackMarkers.insert(stackMarkers.end(), marker);
		T* result = (T*) stack->alloc(sizeof(obj));
		*result = obj;
	}

	template <class T>
	T getFromStack()
	{
		// Get all the data from the top to the marker.
		T* marker = (T*)stackMarkers.at(0);
		return *marker;
	}

	template <class T>
	T getFromDoubleStack(DoubleStack::POSITION stack_position)
	{
		//
		DoubleStack::Marker marker = dstack->getMarker(stack_position);
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
		SingleStack::Marker marker = stackMarkers.at(0);
		stackMarkers.erase(stackMarkers.begin());
		stack->freeToMarker(marker);
		return *((T*)marker);
	}

	template <class T>
	T takeFromDoubleStack(DoubleStack::POSITION stack_position)
	{
		DoubleStack::Marker marker;

		if (stack_position == DoubleStack::TOP_STACK) 
		{
			marker = dstackTopMarkers.at(0);
			dstack->freeToMarker(marker + sizeof(T), stack_position);
		}
		else
		{
			marker = dstackBottomMarkers.at(0);
			dstack->freeToMarker(marker, stack_position);
		}

		return *((T*)marker);
	}

	template <class T>
	T takeFromPool()
	{

	}


private:
	SmartPointer<SingleStack> stack;
	SmartPointer<Pool> pool;
	SmartPointer<DoubleStack> dstack;
	std::vector<SingleStack::Marker> stackMarkers;
	std::vector<DoubleStack::Marker> dstackTopMarkers;
	std::vector<DoubleStack::Marker> dstackBottomMarkers;
};