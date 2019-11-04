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
	SingleStack* stack = new SingleStack(stack_size);
	stacks.insert(stacks.end(), stack);
}

void MemoryManager::createDoubleStack(U32 stack_size)
{
	DoubleStack* dstack = new DoubleStack(stack_size);
	dstacks.insert(dstacks.end(), dstack);
}

void MemoryManager::createPool(U32 type_size, U32 stack_size)
{
	Pool* pool = new Pool(type_size, stack_size);
	pools.insert(pools.end(), pool);
}


void MemoryManager::putIntoStack() 
{
	SingleStack* stack = stacks.at(0);
	stack->alloc(200);
	unsigned char* pointer = stack->getMarker();
	*pointer = '1';
}

void MemoryManager::putIntoDoubleStack() 
{
	//
}

void MemoryManager::putIntoPool() 
{
	//
}

void MemoryManager::getFromStack() 
{
	// Get all the data from the top to the marker.
}

void MemoryManager::getFromDoubleStack()
{
	//
}

void MemoryManager::getFromPool() 
{
	//
}
