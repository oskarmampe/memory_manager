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
	size_free = stackSize_bytes;
}

DoubleStack::~DoubleStack()
{
	delete[] base_pointer;
	base_pointer = nullptr;
}

unsigned char* DoubleStack::alloc(U32 size_bytes, POSITION stack)
{
	if (stack == TOP_STACK)
	{
		if (top_marker == NULL)
			top_marker = base_pointer + stack_size;
		else
			top_marker -= size_bytes;

		size_free -= size_bytes;
		return top_marker;
	}
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

	size_free = (top_marker - (stack_size + base_pointer)) + (bottom_marker - base_pointer);
}

void DoubleStack::clear()
{
	top_marker = base_pointer + stack_size;
	bottom_marker = base_pointer;
}

DoubleStack::U32 DoubleStack::getFreeSize()
{
	return size_free;
}
