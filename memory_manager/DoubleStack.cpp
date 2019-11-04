#include "DoubleStack.h"

///
///
/// <- TOP
///
///
/// <- MARKER
///
///
/// <- BOTTOM
///
///
/// WHILE TOP != MARKER
/// FREE MEMORY


DoubleStack::DoubleStack(U32 stackSize_bytes)
{
	base_pointer = new unsigned char[stackSize_bytes];
	stack_size = stackSize_bytes;
	top_marker = base_pointer + stackSize_bytes;
	bottom_marker = base_pointer;
}

unsigned char* DoubleStack::alloc(U32 size_bytes, POSITION stack = TOP_STACK)
{
	if (stack == TOP_STACK)
	{
		top_marker -= size_bytes;
		return top_marker;
	}
	else if (BOTTOM_STACK)
	{
		bottom_marker += size_bytes;
		return bottom_marker;
	} 
	else
	{
		std::cout << "ERROR: DOUBLE STACK LOCATION NOT SPECIFIED.";
		return nullptr;
	}
}

DoubleStack::Marker DoubleStack::getMarker(POSITION stack)
{
	return (stack == TOP_STACK) ? top_marker : bottom_marker;
}

void DoubleStack::freeToMarker(DoubleStack::Marker marker, POSITION stack)
{
	if (stack == TOP_STACK)
		top_marker = marker;
	else
		bottom_marker = marker;
}

void DoubleStack::clear()
{
	top_marker = base_pointer + stack_size;
	bottom_marker = base_pointer;
	delete[] base_pointer; // cleanup
}

