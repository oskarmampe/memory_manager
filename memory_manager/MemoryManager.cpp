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
	SingleStack stack(stack_size);
	stacks.insert(stacks.end(), stack);
}

void MemoryManager::createDoubleStack(U32 stack_size)
{
	DoubleStack dstack(stack_size);
	dstacks.insert(dstacks.end(), dstack);
}

void MemoryManager::createPool(U32 type_size, U32 stack_size)
{
	Pool pool(type_size, stack_size);
	pools.insert(pools.end(), pool);
}


void MemoryManager::putIntoStack() 
{
	//
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
	//
}

void MemoryManager::getFromDoubleStack()
{
	//
}

void MemoryManager::getFromPool() 
{
	//
}
