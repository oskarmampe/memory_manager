#include "MemoryManager.h"

void MemoryManager::startUp()
{
	//
}

void MemoryManager::shutDown() 
{
	//
}

void MemoryManager::createStack(U32 stack_size)
{
	SmartPointer<SingleStack> pointer(new SingleStack(stack_size));
	stacks.insert(stacks.end(), pointer);
}

void MemoryManager::createDoubleStack(U32 stack_size)
{
	SmartPointer<DoubleStack> pointer(new DoubleStack(stack_size));
	dstacks.insert(dstacks.end(), pointer);
}

void MemoryManager::createPool(U32 type_size, U32 stack_size)
{
	SmartPointer<Pool> pointer(new Pool(type_size, stack_size));
	pools.insert(pools.end(), pointer);
}

template <class T>
void MemoryManager::putIntoStack(T obj) 
{
	SmartPointer<SingleStack> stack = stacks.at(0);
	SingleStack::Marker marker = stack->getMarker();
	T* result = stack->alloc(sizeof(obj));
	*result = obj;
}

template <class T>
void MemoryManager::putIntoDoubleStack(T obj, DoubleStack::POSITION stack) 
{
	//
}

template <class T>
void MemoryManager::putIntoPool(T obj) 
{
	//
}

template <class T>
T MemoryManager::getFromStack() 
{
	// Get all the data from the top to the marker.
	SmartPointer<SingleStack> stack = stacks.at(0);
	SingleStack::Marker marker = stack->getMarker();
	return *marker;
}

template <class T>
void MemoryManager::getFromDoubleStack()
{
	//
}

template <class T>
void MemoryManager::getFromPool() 
{
	//
}
