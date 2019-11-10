#include "DoubleStack.h"

/*
	Implementation of the double stack.
*/

// Constructor that allocates a chunk of memory and initializes all the required variables.
DoubleStack::DoubleStack(U32 stackSize_bytes)
{
	base_pointer = new unsigned char[stackSize_bytes];
	stack_size = stackSize_bytes;
	top_marker = base_pointer + stackSize_bytes;
	bottom_marker = base_pointer;
	size_free = stackSize_bytes;
}

// Destructor for cleaning up with SmartPointer.
DoubleStack::~DoubleStack()
{
	delete[] base_pointer;
	base_pointer = nullptr;
}

// Allocates memory by returning the correct pointer.
unsigned char* DoubleStack::alloc(U32 size_bytes, POSITION stack)
{
	// If the stack being allocated to is top stack then the marker needs to be moved down.
	if (stack == TOP_STACK)
	{
		if (top_marker == NULL)
			top_marker = base_pointer + stack_size;
		else
			top_marker -= size_bytes;

		size_free -= size_bytes;
		return top_marker;
	}// Otherwise, if allocating to bottom stack, the marker needs to be moved up.
	else
	{
		if (bottom_marker == NULL)
			bottom_marker = base_pointer;
		else
			bottom_marker += size_bytes;

		size_free -= size_bytes;
		return bottom_marker - size_bytes;
	} 

}

// Simple return marker method.
DoubleStack::Marker DoubleStack::getMarker(POSITION stack)
{
	return (stack == TOP_STACK) ? top_marker : bottom_marker;
}

// Free to marker by moving the appropriate marker. No memory is 'cleared', it is instead, overwritten.
void DoubleStack::freeToMarker(DoubleStack::Marker marker, POSITION stack)
{
	if (stack == TOP_STACK)
		top_marker = marker;
	else
		bottom_marker = marker;

	size_free = (top_marker - (stack_size + base_pointer)) + (bottom_marker - base_pointer);
}


// Clear the stack by moving the markers. Again, no memory is 'cleared' it is all overwritten.
void DoubleStack::clear()
{
	top_marker = base_pointer + stack_size;
	bottom_marker = base_pointer;
}

// Get the amount of bytes free.
DoubleStack::U32 DoubleStack::getFreeSize()
{
	return size_free;
}
