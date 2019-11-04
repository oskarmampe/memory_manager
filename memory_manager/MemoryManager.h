#pragma once
#include "SingleStack.h"
#include "DoubleStack.h"
#include "Pool.h"
#include <vector>
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

	void putIntoDoubleStack();
	void putIntoPool();
	void putIntoStack();

	void getFromStack();
	void getFromDoubleStack();
	void getFromPool();

private:
	std::vector<SingleStack*> stacks;
	std::vector<DoubleStack*> dstacks;
	std::vector<Pool*> pools;
};