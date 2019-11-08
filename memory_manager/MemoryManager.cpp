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
	stack = { new SingleStack(stack_size) };
	}

void MemoryManager::createDoubleStack(U32 stack_size)
{
	dstack = { new DoubleStack(stack_size) };
}

void MemoryManager::createPool(U32 type_size, U32 stack_size)
{
	pool = { new Pool(type_size, stack_size) };
}

void MemoryManager::resetStack(U32 stack_size)
{

}
void MemoryManager::resetDoubleStack(U32 stack_size){}
void MemoryManager::resetPool(U32 type_size, U32 stack_size){}