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