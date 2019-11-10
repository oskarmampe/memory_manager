#pragma once
#include <cstdint>
#include <stdlib.h>
#include <iostream>
#include "SmartPointer.h"

/*
	DoubleStack class representing a double stack allocator.
	This allocator is only used to reserve memory.
	It does little to no book-keeping.
*/

class DoubleStack
{
public:
	// Enum used to denote whether the bottom of stack or the top is modified.
	enum POSITION
	{
		BOTTOM_STACK,
		TOP_STACK
	};

	//Typedefs for clarity.
	typedef uint32_t U32;
	typedef unsigned char* Marker;

	// Constructor/Destructor.
	explicit DoubleStack(U32);
	virtual ~DoubleStack();

	// Allocates memory and returns a marker i.e. pointer of the allocated memory.
	Marker alloc(U32, POSITION);

	// Gets the topmost marker.
	Marker getMarker(POSITION);

	// Frees but only to the marker specified.
	void freeToMarker(Marker, POSITION);

	// Clears the entire stack.
	void clear();

	// Gets the size that can be allocated to.
	U32 getFreeSize();

private:
	Marker base_pointer; // Bottom of the stack i.e. bottom of the allocated memory
	U32 stack_size; // Size of the stack in bytes.
	Marker top_marker; // Top of the top stack
	Marker bottom_marker; // Top of the bottom stack
	U32 size_free; // The amount of free memory in bytes.
};