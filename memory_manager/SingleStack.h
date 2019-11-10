#pragma once
#include <cstdint>
#include <stdlib.h>
#include <iostream>
#include "SmartPointer.h"

/*
	SingleStack class representing a stack allocator.
	This allocator is only used to reserve memory.
	It does little to no book-keeping.
*/

class SingleStack
{
public:
	// Typedefs for clarity.
	typedef uint32_t U32;
	typedef unsigned char* Marker;

	// Constructor/Destructor
	explicit SingleStack(U32);
	virtual ~SingleStack();

	// Allocate a memory block by returning a pointer to the free memory.
	Marker alloc(U32);

	// Get the top of the stack
	Marker getMarker();

	// Free to a specific marker.
	void freeToMarker(Marker);

	// Clear the stack
	void clear();

	// Get the free size in bytes.
	U32 getFreeSize();

private:
	Marker base_pointer; // Pointer to the bottom of the stack
	Marker top_marker; // Pointer to the top of the stack.
	U32 size_free; // Size free in bytes.
	U32 stack_size; // Size of the overall stack.
};