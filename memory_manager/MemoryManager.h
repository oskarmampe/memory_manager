#pragma once
#include "SingleStack.h"
#include "DoubleStack.h"
#include "Pool.h"
#include "SmartPointer.h"
#include <vector>
#include <tuple>
/*
	MEMORY MANAGER

	This class needs to do all the book-keeping. The stack/pool structures are very bare, and simply implement a way to allocate memory.
	The structures do not do ANY checks whether the memory is being implemented correctly.
	This should be the functionality of this class. Making sure that when a block is allocated, it's not writing more than allocated etc.
*/

class MemoryManager
{
public:

	// Typedef for clarity.
	typedef uint32_t U32;

	MemoryManager()
	{
		// Do nothing
	}
	~MemoryManager()
	{
		// Do nothing
	}

	// Create the allocators with the required size
	void createStack(U32 stack_size);
	void createDoubleStack(U32 stack_size);
	void createPool(U32 type_size, U32 stack_size);

	// Reset/delete the required memory allocator and create a new one.
	void resetStack(U32 stack_size);
	void resetDoubleStack(U32 stack_size);
	void resetPool(U32 type_size, U32 stack_size);

	// Put into the stack.
	template <class T>
	void putIntoStack(T obj)
	{
		if (stack->getFreeSize() < sizeof(obj))
		{
			std::cout << "Object not placed, not enough space on stack." << std::endl;
			return;
		}
		// Get the marker, as thats where the object will be put
		SingleStack::Marker marker = stack->getMarker();
		
		// Append to the list so that it can be found.
		stackMarkers.insert(stackMarkers.begin(), marker); 
		
		// Assign the object.
		T* result = (T*) stack->alloc(sizeof(obj));
		*result = obj;
	}

	// Take from the stack
	template <class T>
	T takeFromStack()
	{
		if (stackMarkers.size() == 0)
		{
			std::cout << "Nothing has been put into the stack." << std::endl;
			return NULL;
		}
		// Get all the data from the top to the marker.
		SingleStack::Marker marker = stackMarkers.at(0);
		stackMarkers.erase(stackMarkers.begin());
		stack->freeToMarker(marker);
		return *((T*)marker);
	}

	// Get from the stack
	template <class T>
	T getFromStack()
	{
		if (stackMarkers.size() == 0)
		{
			std::cout << "Nothing has been put into the stack." << std::endl;
			return NULL;
		}
		// Get all the data from the top to the marker.
		T* marker = (T*)stackMarkers.at(0);
		return *((T*)marker);
	}

	// Put data into the double stack
	template <class T>
	void putIntoDoubleStack(T obj, DoubleStack::POSITION stack_position)
	{
		if (dstack->getFreeSize() < sizeof(obj))
		{
			std::cout << "Stack ran out of space.";
			return;
		}

		// If the marker is for the bottom stack, then we want the marker before allocation, as that is where the data will be put into.
		if (stack_position == DoubleStack::BOTTOM_STACK)
			dstackBottomMarkers.insert(dstackBottomMarkers.begin(), dstack->getMarker(stack_position));

		T * result = (T*)dstack->alloc(sizeof(obj), stack_position);

		// If the marker is for the top stack, then we want the marker after allocation, as that is where the data will be put into.
		if (stack_position == DoubleStack::TOP_STACK)
			dstackTopMarkers.insert(dstackTopMarkers.begin(), dstack->getMarker(stack_position));

		*result = obj;
	}

	// Take the top item from the double stack
	template <class T>
	T takeFromDoubleStack(DoubleStack::POSITION stack_position)
	{
		// Validation checks
		if (dstackBottomMarkers.size() == 0 && stack_position == DoubleStack::BOTTOM_STACK)
		{
			std::cout << "Nothing has been put into the bottom stack." << std::endl;
			return NULL;
		}
		else if (dstackTopMarkers.size() == 0 && stack_position == DoubleStack::TOP_STACK)
		{
			std::cout << "Nothing has been put into the top stack." << std::endl;
			return NULL;
		}

		// Marker that the data is taken from.
		DoubleStack::Marker marker;

		// Based on whether taking from top or bottom stack, take from different vectors.
		if (stack_position == DoubleStack::TOP_STACK)
		{
			marker = dstackTopMarkers.at(0);
			dstack->freeToMarker(marker + sizeof(T), stack_position);
			dstackTopMarkers.erase(dstackTopMarkers.begin());
		}
		else
		{
			marker = dstackBottomMarkers.at(0);
			dstack->freeToMarker(marker, stack_position);
			dstackBottomMarkers.erase(dstackBottomMarkers.begin());
		}

		return *((T*)marker);
	}

	// Get from the double stack without 'freeing' memory.
	template <class T>
	T getFromDoubleStack(DoubleStack::POSITION stack_position)
	{
		// Validation
		if (dstackBottomMarkers.size() == 0 && stack_position == DoubleStack::BOTTOM_STACK)
		{
			std::cout << "Nothing has been put into the bottom stack." << std::endl;
			return NULL;
		}
		else if (dstackTopMarkers.size() == 0 && stack_position == DoubleStack::TOP_STACK)
		{
			std::cout << "Nothing has been put into the top stack." << std::endl;
			return NULL;
		}
		
		// Marker where the data is taken from.
		DoubleStack::Marker marker;

		if (stack_position == DoubleStack::TOP_STACK)
		{
			marker = dstackTopMarkers.at(0);
		}
		else
		{
			marker = dstackBottomMarkers.at(0);
		}

		return *((T*)marker);
	}

	// Put into the pool.
	template <class T>
	void putIntoPool(T obj)
	{
		Pool::Node* result = pool->alloc();

		if (result == nullptr)
		{
			std::cout << std::endl << "Error during pool allocation: no more free space." << std::endl;
			return;
		}

		*(result->data) = obj;

		poolNodes.insert(poolNodes.end(), result);
	}


	// Take from the pool and 'free' the memory.
	template <class T>
	T takeFromPool(int index)
	{
		//Validate to make sure the data type and vector size is correct.

		if (poolNodes.size() == 0)
		{
			std::cout << "Nothing has been put into the pool." << std::endl;
			return NULL;
		}
		else if (poolNodes.size() - 1 < index || index < 0)
		{
			std::cout << "Retrieve element from pool is out of range.";
		}

		Pool::Node* result = poolNodes.at(index);

		// Get the data otherwise.

		T result_data = *(result->data);
		pool->free(result);
		poolNodes.erase(poolNodes.begin() + index);

		return result_data;
	}

	// Get from the pool
	template <class T>
	T getFromPool(int index)
	{
		// Validation
		if (poolNodes.size() == 0)
		{
			std::cout << "Nothing has been put into the pool." << std::endl;
			return NULL;
		}
		else if (poolNodes.size() - 1 < index || index < 0)
		{
			std::cout << "Retrieve element from pool is out of range.";
		}

		Pool::Node* result = poolNodes.at(index);

		//T* derived = dynamic_cast<T*>(result.data);

		//if (!derived)
		//{
		//	std::cout << "Wrong type";
		//}

		return *(result->data);
	}

private:
	// Pointers to memory allocators
	SmartPointer<SingleStack> stack;
	SmartPointer<Pool> pool;
	SmartPointer<DoubleStack> dstack;

	// Vectors that hold markers to the correct pointers
	std::vector<SingleStack::Marker> stackMarkers;
	std::vector<DoubleStack::Marker> dstackTopMarkers;
	std::vector<DoubleStack::Marker> dstackBottomMarkers;

	// A vector to hold the currently occupied nodes.
	std::vector<Pool::Node*> poolNodes;
};