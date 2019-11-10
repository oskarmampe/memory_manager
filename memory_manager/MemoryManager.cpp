#include "MemoryManager.h"
/*
	Implementation of MemoryManager for methods without a template.
*/

// Create stack by allocating to SmartPointer
void MemoryManager::createStack(U32 stack_size)
{
	stack = { new SingleStack(stack_size) };
}

// Create double stack by allocating to SmartPointer
void MemoryManager::createDoubleStack(U32 stack_size)
{
	dstack = { new DoubleStack(stack_size) };
}

// Create pool by allocating to SmartPointer
void MemoryManager::createPool(U32 type_size, U32 stack_size)
{
	pool = { new Pool(type_size, stack_size) };
}

// Reset the stack by clearing the appropriate vectors and creating a new stack.
void MemoryManager::resetStack(U32 stack_size)
{
	stack->clear();
	stackMarkers.clear();
	createStack(stack_size);
}

// Reset the double stack by clearing the appropriate vectors and creating a new double stack.
void MemoryManager::resetDoubleStack(U32 stack_size)
{
	dstack->clear();
	dstackTopMarkers.clear();
	dstackBottomMarkers.clear();
	createDoubleStack(stack_size);
}

// Reset the pool by clearing the appropriate vectors and creating a new pool.
void MemoryManager::resetPool(U32 type_size, U32 stack_size)
{
	pool->clear();
	poolNodes.clear();
	createPool(type_size, stack_size);
}