#pragma once

#include "SingleStack.h"

/*
	An implementaion of stack allocator.
*/

// Constructor by allocating a chunk of memory, that the allocater gives out.
SingleStack::SingleStack(U32 stackSize_bytes)
{
	//
	base_pointer = new unsigned char[stackSize_bytes];
	top_marker = base_pointer;
	size_free = stackSize_bytes;
	stack_size = stackSize_bytes;
}

// Destruct and clear any memory.
SingleStack::~SingleStack()
{
	delete[] base_pointer;
	base_pointer = nullptr;
}

// Allocate a piece of memory.
SingleStack::Marker SingleStack::alloc(U32 size_bytes)
{
	// Safety check, as top_marker should not be null.
	if (top_marker == NULL)
	{
		top_marker = base_pointer;
	} 
	else
	{
		top_marker += size_bytes;
	}
	size_free -= size_bytes;
	return top_marker - size_bytes;
		
}

// Get the top pointer of the stack
SingleStack::Marker SingleStack::getMarker()
{
	return top_marker;
}


// Free to a specific marker
void SingleStack::freeToMarker(SingleStack::Marker marker)
{
	top_marker = marker;
	size_free = top_marker - base_pointer;
}


// Clear the entire stack, by moving the marker. The memory is not cleared, but it is overwritten.
void SingleStack::clear()
{
	top_marker = base_pointer;
	size_free = stack_size;
}

// Get the free size in bytes.
SingleStack::U32 SingleStack::getFreeSize()
{
	return size_free;
}
